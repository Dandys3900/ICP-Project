/** ICP Project 2023/2024
 * @file playground.cpp
 * @author Tomáš Daniel (xdanie14)
 * @brief Representation of a scene where both robots and obstacles are placed.
 */

#include "playground.h"

PlayGround::PlayGround (QGraphicsScene* scene)
    : QGraphicsRectItem      (nullptr),
      mp_scene_objs_vec      (),
      mp_active_obj_orig_pos (),
      mp_scene               (scene),
      mp_active_obj          (nullptr),
      mp_toplace_obj         (nullptr),
      mp_cur_action          (NO_ACTION)
{
    // Make PlayGround focusable
    this->setFlag(QGraphicsItem::ItemIsFocusable);
    this->setFocus();

    // Add PlayGround to the scene
    mp_scene->addItem(this);
}

PlayGround::~PlayGround () {
    // Remove all scene objects
    for (SceneObject* obj : this->mp_scene_objs_vec) {
        delete obj;
    }
}

QPointF PlayGround::get_active_obj_orig_pos () {
    return mp_active_obj_orig_pos;
}

void PlayGround::disable_focus () {
    // Reset original position of active object
    mp_active_obj_orig_pos = QPointF(0, 0);

    // Active item change, lose focus on current active
    if (mp_active_obj) {
        mp_active_obj->set_active(false, NO_ACTION);
        mp_active_obj = nullptr;
    }
}

void PlayGround::set_active_obj (SceneObject* object, Action action) {
    mp_cur_action = action;

    // Un-focus current active object, if any
    disable_focus();

    // Set new active object
    mp_active_obj = object;

    if (mp_active_obj) {
        mp_active_obj_orig_pos = mp_active_obj->get_pos();
        mp_active_obj->set_active(true, mp_cur_action);
    }
}

void PlayGround::set_toplace_obj (SceneObject* object) {
    mp_toplace_obj = object;
    // Change mouse icon to notify user about object to be placed
    QApplication::setOverrideCursor(Qt::PointingHandCursor);
}

void PlayGround::add_scene_obj (SceneObject* object) {
    // Add to scene object vector
    mp_scene_objs_vec.push_back(object);

    if (object->get_type() == QString("Robot")) {
        // Cast it to the Robot class
        Robot* robot = dynamic_cast<Robot*>(object);
        if (robot) {
            // Set Playground as object parent
            robot->setParentItem(this);
            // Add robot + its arrow
            mp_scene->addItem(robot->get_robot_arrow());
            mp_scene->addItem(robot);
        }
    }
    else {
        // Cast it to the Obstacle class
        Obstacle* obstacle = dynamic_cast<Obstacle*>(object);
        if (obstacle) { // Add obstacle
            // Set Playground as object parent
            obstacle->setParentItem(this);
            mp_scene->addItem(obstacle);
        }
    }
}

void PlayGround::remove_scene_obj (SceneObject* object) {
    QVector<SceneObject*>::iterator iter;

    // Try to find object to be deleted in objects vector
    iter = std::find_if(mp_scene_objs_vec.begin(), mp_scene_objs_vec.end(),
                        [object](SceneObject* curObj) {
                            return object == curObj;
                        });

    // Found - delete it
    if (iter != mp_scene_objs_vec.end()) {
        // Delete found object
        delete object;
        // Remove from vector as well
        mp_scene_objs_vec.erase(iter);

        // In case deleted object is active
        if (object == mp_active_obj) {
            mp_active_obj = nullptr;
        }
    }
}

void PlayGround::keyPressEvent (QKeyEvent* event) {
    QVector<SceneObject*>::iterator iter;

    // If we have active object, deliver this exclusively to it
    if (mp_active_obj) {
        mp_active_obj->keyPressEvent(event);
    }
    else { // Robots should receive key presses to move
        for (iter = mp_scene_objs_vec.begin(); iter < mp_scene_objs_vec.end(); ++iter) {
            if ((*iter)->get_type() == QString("Robot")) {
                (*iter)->keyPressEvent(event);
            }
        }
    }
}

void PlayGround::mouseMoveEvent (QGraphicsSceneMouseEvent* event) {
    if (mp_active_obj) { // Distribute mouse move event to focused (active) object
        mp_active_obj->mouseMoveEvent(event);
    }
}

void PlayGround::mousePressEvent (QGraphicsSceneMouseEvent* event) {
    if (mp_active_obj) { // Distribute mouse press event to focused (active) object
        mp_active_obj->mousePressEvent(event);
    }
    else if (mp_toplace_obj) { // Place new object to mouse click position
        mp_toplace_obj->set_obj_pos(event->scenePos());
        add_scene_obj(mp_toplace_obj);
        // Reset for next use
        mp_toplace_obj = nullptr;
        // Restore mouse icon
        QApplication::restoreOverrideCursor();
    }
}

/************ CONFIG STORE/LOAD METHODS ************/
QString PlayGround::get_selected_file (Operation operation) {
    // Allow use to choose/create the config file
    QFileDialog dialog;

    if (operation == LOAD) { // Allow only existing file being selected
        dialog.setFileMode(QFileDialog::ExistingFile);
        dialog.setWindowTitle("Select File To Load Configuration From");
    }
    else { // operation == STORE -> let user pick/create the file
        dialog.setFileMode(QFileDialog::AnyFile);
        dialog.setWindowTitle("Select Where To Store Configuration");
    }

    // Show the dialog
    if (dialog.exec()) { // Return selected file name
        return dialog.selectedFiles().first();
    } else { // Dialog was canceled - return empty string leading to halting the load/store process
        return QString("");
    }
}

void PlayGround::store_config () {
    // Open config file
    QFile conf_file(get_selected_file(STORE));
    if (!conf_file.open(QIODevice::WriteOnly)) {
        Error_PopUp::show_err(QString("Failed to open configuration file for writing: " + conf_file.errorString()));
        return;
    }

    // Array of JSON objects from each scene obj
    QJsonArray objs_data_arr;
    for (auto pos = 0; pos < mp_scene_objs_vec.size(); ++pos) {
        objs_data_arr.append(mp_scene_objs_vec.at(pos)->get_obj_data());
    }

    // Store to file
    QJsonDocument doc(objs_data_arr);
    conf_file.write(doc.toJson());
    conf_file.close();
}

void PlayGround::load_config () {
    QFile conf_file(get_selected_file(LOAD));
    if (!conf_file.open(QIODevice::ReadOnly)) {
        Error_PopUp::show_err(QString("Failed to open configuration file for reading: " + conf_file.errorString()));
        return;
    }

    // Clear current scene objects as new one will be created
    for (SceneObject* obj : this->mp_scene_objs_vec) {
        delete obj;
    }
    mp_scene_objs_vec.clear();

    // Parse the file to JSON format
    QJsonParseError parse_error;
    QJsonDocument json_doc = QJsonDocument::fromJson(conf_file.readAll(), &parse_error);
    conf_file.close();

    if (parse_error.error != QJsonParseError::NoError) {
        Error_PopUp::show_err(QString("Failed to parse JSON: " + parse_error.errorString()));
        return;
    }

    QJsonArray obj_array = json_doc.array();
    for (const QJsonValueRef& array_item : obj_array) {
        QJsonObject scene_obj = array_item.toObject();
        // Create new scene object and place it to scene
        SceneObject* new_obj;

        // Store object type
        QString obj_type;
        if (scene_obj.contains("obj_type")) {
            obj_type = scene_obj["obj_type"].toString();
        }
        else { // If missing -> output error and exit
            Error_PopUp::show_err(QString("Missing mandatory JSON value: object type, can't finish the loading procedure"));
            return;
        }

        // See if loaded config file contains desired values and if not use default ones
        Vector2 coords(                                       // config value : default value
            (scene_obj.contains("coord_x")) ? scene_obj["coord_x"].toDouble() : 100,
            (scene_obj.contains("coord_y")) ? scene_obj["coord_y"].toDouble() : 100
        );

        qreal rotation =
            (scene_obj.contains("rotation")) ? scene_obj["rotation"].toDouble() : 0;

        if (obj_type == QString("Robot")) {
            size_t diameter =
                (scene_obj.contains("diameter")) ? scene_obj["diameter"].toDouble() : 20;

            new_obj = new Robot(diameter,
                                coords,
                                rotation,
                                this);
        }
        else { // obj_type == Obstacle
            Vector2 size(
                (scene_obj.contains("size_x")) ? scene_obj["size_x"].toDouble() : 20,
                (scene_obj.contains("size_y")) ? scene_obj["size_y"].toDouble() : 20
            );

            new_obj = new Obstacle(size,
                                   coords,
                                   rotation,
                                   this);
        }
        // Add to scene
        add_scene_obj(new_obj);
    }
}
