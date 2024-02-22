#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H

#include "includes/libs_file.h"
#include "scene/playground.h"

class ConfigManager {
    public:
        static size_t generate_id ();
        static void load_config (PlayGround* playground);

    private:
        static std::vector<size_t> m_ids_array;
        static size_t get_rand_num ();
};

#endif // CONFIG_MANAGER_H
