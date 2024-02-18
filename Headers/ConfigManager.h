#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H

#include "Headers/LibsFile.h"
#include "Headers/PlayGround.h"

typedef struct {
    const char* name;
    qreal value;
} TItem;

class ConfigManager {
    public:
        static std::vector<size_t> m_ids_array;

        static size_t generate_id ();
        static void save_config (PlayGround* playground);
        static void load_config ();

    private:
        static void read_obj (const std::string obj);
        static std::string do_regex_search (const std::regex rule, const std::string fileLine);
        static size_t get_rand_num ();
};

#endif // CONFIG_MANAGER_H
