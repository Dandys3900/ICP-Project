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
    if (!std::filesystem::exists(CONF_FILE)) {
        // Throw exception for non-existing file
        throw ("Configuration file not found");
    }

    // Open config file
    std::ifstream confFile(CONF_FILE);

    std::string fileLine;
    std::string objData;
    while (std::getline(confFile, fileLine)) {
        if (fileLine == std::string("<class>\n")) {
            // Skip header
            continue;
        }
        if (fileLine == std::string("</class>\n")) {
            read_obj(objData);
        }
        objData += fileLine;
    }

    // Close file
    confFile.close();
}

void ConfigManager::read_obj (const std::string obj) {
    std::regex regex;
    std::map<std::string, std::string> valuesMap;

    if (obj.find("<type>") != std::string::npos) {
        regex = "<type>(.*)</type>";
        valuesMap.insert(std::make_pair("type", do_regex_search(regex, obj)));
    }
    if (obj.find("<id>") != std::string::npos) {
        regex = "<id>(.*)</id>";
        valuesMap.insert(std::make_pair("id", do_regex_search(regex, obj)));
    }
    if (obj.find("<height>") != std::string::npos) {
        regex = "<height>(.*)</height>";
        valuesMap.insert(std::make_pair("height", do_regex_search(regex, obj)));
    }
    if (obj.find("<width>") != std::string::npos) {
        regex = "<width>(.*)</width>";
        valuesMap.insert(std::make_pair("width", do_regex_search(regex, obj)));
    }
    if (obj.find("<coordx>") != std::string::npos) {
        regex = "<coordx>(.*)</coordx>";
        valuesMap.insert(std::make_pair("coordx", do_regex_search(regex, obj)));
    }
    if (obj.find("<coordy>") != std::string::npos) {
        regex = "<coordy>(.*)</coordy>";
        valuesMap.insert(std::make_pair("coordy", do_regex_search(regex, obj)));
    }
    if (obj.find("<rotation>") != std::string::npos) {
        regex = "<rotation>(.*)</rotation>";
        valuesMap.insert(std::make_pair("rotation", do_regex_search(regex, obj)));
    }
    if (obj.find("<color>") != std::string::npos) {
        regex = "<color>(.*)</color>";
        valuesMap.insert(std::make_pair("color", do_regex_search(regex, obj)));
    }
}

std::string ConfigManager::do_regex_search (const std::regex rule, const std::string fileLine) {
    std::smatch match;
    if (std::regex_search(fileLine, match, rule) && match.size() > 1) {
        return match.str(1);
    }
    else {
        throw ("Wrong or missing file element");
    }
}

size_t ConfigManager::get_rand_num () {
    // Seed value
	srand((unsigned) time(NULL));

    // Get random number
    return (rand() % RAND_MAX);
}