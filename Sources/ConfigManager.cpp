#include "Headers/ConfigManager.h"

size_t ConfigManager::generate_id () {
    size_t randNum = get_rand_num();

    while (std::find(m_ids_array.begin(), m_ids_array.end(), randNum) != m_ids_array.end()) {
        // Generate number not present in vector to ensure its uniqueness
        randNum = get_rand_num();
    }
    return randNum;
}

void ConfigManager::save_config (PlayGround* playground) {
    // Create/open config file
    std::ofstream confFile(CONF_FILE);

    std::vector<MoveableObject*> objsVec = playground->get_objs_vec();
    std::vector<MoveableObject*>::iterator iter;

    for (iter = objsVec.begin(); iter != objsVec.end(); ++iter) {
        // Print objects data directly to file
        confFile << (*iter)->exportObjData().toStdString();
    }

    // Close file
    confFile.close();
}

void ConfigManager::load_config () {

}

void ConfigManager::insert_item (TItem item) {

}

void ConfigManager::read_item () {

}

size_t ConfigManager::get_rand_num () {
    // Seed value
	srand((unsigned) time(NULL));

    // Get random number
    return (rand() % RAND_MAX);
}