#include "config_manager.h"

size_t ConfigManager::get_rand_num () {
    // Seed value
	srand((unsigned) time(NULL));

    return (rand() % RAND_MAX_VAL);
}

size_t ConfigManager::generate_id () {
    size_t randNum = get_rand_num();

    while (std::find(m_ids_array.begin(), m_ids_array.end(), randNum) != m_ids_array.end()) {
        // Generate number not present in vector to ensure its uniqueness
        randNum = get_rand_num();
    }
    m_ids_array.push_back(randNum);

    return randNum;
}

void ConfigManager::load_config (PlayGround* playground) {
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
    for (const QJsonValueRef &array_item : obj_array) {
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
                                playground);
        }
        else { // obj_type == Obstacle
            new_obj = new Obstacle(Vector2(scene_obj["size_x"].toInt(), scene_obj["size_y"].toInt()),
                                   Vector2(scene_obj["coord_x"].toInt(), scene_obj["coord_y"].toInt()),
                                   scene_obj["rotation"].toDouble(),
                                   (Action)scene_obj["action"].toInt(),
                                   scene_obj["active"].toBool(),
                                   (Qt::GlobalColor)scene_obj["color"].toInt(),
                                   playground);
        }
        // Add to scene
        playground->add_scene_obj(new_obj);
    }
}
