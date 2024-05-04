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
    // Set proper stack order
    this->setZValue(0);

    // Make PlayGround focusable
    this->setFlag(QGraphicsItem::ItemIsFocusable);
    this->setFocus();

    // Set texture for rectangle (playground)
    QBrush background(QPixmap(":/textures/ground.jpeg"));
    this->setBrush(background);

    // Add PlayGround to the scene
    add_to_scene(this);

    this->physics_server = new PhysicsServer();
    
    this->resize_playground(scene->sceneRect());
    
    this->automatic_mode_timer = new QTimer();
    connect(this->automatic_mode_timer, &QTimer::timeout, this, &PlayGround::on_automatic_mode_timer_timeout);
}

PlayGround::~PlayGround () {
    // Remove all scene objects
    for (SceneObject* obj : this->mp_scene_objs_vec) {
        delete obj;
    }
    delete this->physics_server;
    delete this->automatic_mode_timer;
}

void PlayGround::resize_playground(QRectF new_rect) {
    this->setRect(new_rect);
    this->physics_server->register_boundaries(Vector2(new_rect.width(), new_rect.height()));
}

void PlayGround::add_to_scene (QGraphicsItem* new_item) {
    // Avoid duplicit insertion to the scene
    if (!mp_scene->items().contains(new_item)) {
        mp_scene->addItem(new_item);
    }
}

void PlayGround::on_automatic_mode_timer_timeout() {
    this->physics_server->force_step();
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

void PlayGround::set_mode(Mode mode) {
    this->simulation_mode = mode;
    if (mode == MANUAL) {
        this->automatic_mode_running = false;
        this->automatic_mode_timer->stop();
    }
}

void PlayGround::set_automatic_mode_running(bool running) {
    this->automatic_mode_running = running;
    if (running) {
        this->automatic_mode_timer->start(this->automatic_mode_step_interval);
    } else {
        this->automatic_mode_timer->stop();
    }
}

void PlayGround::set_automatic_mode_speed(int speed) {
    this->automatic_mode_step_interval = (int)remap_value_between_ranges((double)speed, 1.0, 100.0, 250.0, 1.0);
    if (this->automatic_mode_running) {
        this->automatic_mode_timer->start(this->automatic_mode_step_interval);
    }
}

PhysicsServer* PlayGround::get_physics_server() {
    return this->physics_server;
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
            add_to_scene(robot->get_robot_arrow());
            add_to_scene(robot);
        }
    }
    else {
        // Cast it to the Obstacle class
        Obstacle* obstacle = dynamic_cast<Obstacle*>(object);
        if (obstacle) { // Add obstacle
            // Set Playground as object parent
            obstacle->setParentItem(this);
            add_to_scene(obstacle);
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

    if (mp_active_obj) { // If we have active object, deliver this exclusively to it
        mp_active_obj->keyPressEvent(event);
    }
    else { // All robots should receive key presses to move
        for (iter = mp_scene_objs_vec.begin(); iter < mp_scene_objs_vec.end(); ++iter) {
            if ((*iter)->get_type() == QString("Robot")) {
                (*iter)->keyPressEvent(event);
            }
        }
        if (this->simulation_mode == MANUAL) {
            this->physics_server->step();
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

void PlayGround::mouseReleaseEvent (QGraphicsSceneMouseEvent* event) {
    if (mp_active_obj) { // Distribute mouse press event to focused (active) object
        mp_active_obj->mouseReleaseEvent(event);
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
            qreal diameter =
                (scene_obj.contains("diameter")) ? scene_obj["diameter"].toDouble() : 20;
            Mode mode = static_cast<enum Mode>(
                (scene_obj.contains("mode")) ? scene_obj["mode"].toInt() : MANUAL);
            qreal rot_step =
                (scene_obj.contains("rotation_step")) ? scene_obj["rotation_step"].toDouble() : 5.0;
            Direction rot_direction = static_cast<enum Direction>(
                (scene_obj.contains("rotation_dir")) ? scene_obj["rotation_direction"].toInt() : CLOCKWISE);
            qreal collision_thr =
                (scene_obj.contains("collis_threshold")) ? scene_obj["collis_threshold"].toDouble() : 0;

            new_obj = new Robot(diameter,
                                coords,
                                rotation,
                                mode,
                                rot_direction,
                                rot_step,
                                collision_thr,
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
