#include "playground.h"

PlayGround::PlayGround (QGraphicsScene* scene)
    : mp_scene_objs_vec      (),
      mp_active_obj_orig_pos (),
      mp_scene               (scene),
      mp_active_obj          (nullptr),
      mp_cur_action          (NO_ACTION)
{
    // Make PlayGround focusable
    this->setFlag(QGraphicsItem::ItemIsFocusable);
    this->setFocus();

    // Add PlayGround to the scene
    mp_scene->addItem(this);
}

PlayGround::~PlayGround () {
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

void PlayGround::add_scene_obj (SceneObject* object) {
    mp_scene_objs_vec.push_back(object);

    if (object->get_type() == QString("Robot")) {
        // Cast it to the Robot class
        Robot* robot = dynamic_cast<Robot*>(object);
        if (robot) {
            // Add robot + its arrow
            mp_scene->addItem(robot->get_robot_arrow());
            mp_scene->addItem(robot);
        }
    }
    else {
        // Cast it to the Obstacle class
        Obstacle* obstacle = dynamic_cast<Obstacle*>(object);
        if (obstacle) { // Add obstacle
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
        // Remove from scene
        Obstacle* obstacle = dynamic_cast<Obstacle*>(object);
        if (obstacle) {
            mp_scene->removeItem(obstacle);
        }
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

void PlayGround::mouseMoveEvent (QGraphicsSceneMouseEvent *event) {
    if (mp_active_obj) { // Distribute mouse move event to focused (active) object
        mp_active_obj->mouseMoveEvent(event);
    }
}

void PlayGround::mousePressEvent (QGraphicsSceneMouseEvent* event) {
    if (mp_active_obj) { // Distribute mouse move event to focused (active) object
        mp_active_obj->mousePressEvent(event);
    }
}

/************ SCENE OBJS IDs ************/
size_t PlayGround::get_rand_num () {
    // Seed value
	srand((unsigned) time(NULL));
    return (rand() % RAND_MAX_VAL);
}

size_t PlayGround::generate_id () {
    size_t randNum = get_rand_num();

    while (std::find(m_ids_array.begin(), m_ids_array.end(), randNum) != m_ids_array.end()) {
        // Generate number not already present in vector to ensure its uniqueness
        randNum = get_rand_num();
    }

    // Store new id before return
    m_ids_array.push_back(randNum);
    return randNum;
}

/************ CONFIG STORE/LOAD METHODS ************/
void PlayGround::store_config () {
    // Open config file
    QFile conf_file(CONFIG_FILE);
    if (!conf_file.open(QIODevice::WriteOnly)) {
        qWarning() << "Failed to open configuration file for writing:" << conf_file.errorString();
        return;
    }

    // Array of JSON objects from each scene obj
    QJsonArray objs_data_arr;
    for (size_t pos = 0; pos < mp_scene_objs_vec.size(); ++pos) {
        objs_data_arr.append(mp_scene_objs_vec.at(pos)->get_obj_data());
    }

    // Store to file
    QJsonDocument doc(objs_data_arr);
    conf_file.write(doc.toJson());
    conf_file.close();
}

void PlayGround::load_config () {
    // List of all JSON objects in file (=> one JSON object for each scene object)
    QList<QJsonObject> obj_config;

    // Open files with configuration
    QFile conf_file(CONFIG_FILE);
    if (!conf_file.open(QIODevice::ReadOnly)) {
        qWarning() << "Failed to open configuration file for writing:" << conf_file.errorString();
        return;
    }

    // Parse the file to JSON format
    QJsonParseError parse_error;
    QJsonDocument json_doc = QJsonDocument::fromJson(conf_file.readAll(), &parse_error);
    conf_file.close();

    if (parse_error.error != QJsonParseError::NoError) {
        qWarning() << "Failed to parse JSON:" << parse_error.errorString();
        return;
    }

    QJsonArray obj_array = json_doc.array();
    for (const QJsonValueRef& array_item : obj_array) {
        QJsonObject scene_obj = array_item.toObject();
        // Create new scene object and place it to scene
        SceneObject* new_obj;

        if (scene_obj["obj_type"].toString() == QString("Robot")) {
            new_obj = new Robot(scene_obj["diameter"].toInt(),
                                Vector2(scene_obj["coord_x"].toInt(), scene_obj["coord_y"].toInt()),
                                scene_obj["rotation"].toDouble(),
                                (Action)scene_obj["action"].toInt(),
                                scene_obj["active"].toBool(),
                                (Qt::GlobalColor)scene_obj["color"].toInt(),
                                this);
        }
        else { // obj_type == Obstacle
            new_obj = new Obstacle(Vector2(scene_obj["size_x"].toInt(), scene_obj["size_y"].toInt()),
                                   Vector2(scene_obj["coord_x"].toInt(), scene_obj["coord_y"].toInt()),
                                   scene_obj["rotation"].toDouble(),
                                   (Action)scene_obj["action"].toInt(),
                                   scene_obj["active"].toBool(),
                                   (Qt::GlobalColor)scene_obj["color"].toInt(),
                                   this);
        }
        // Add to scene
        add_scene_obj(new_obj);
    }
}
