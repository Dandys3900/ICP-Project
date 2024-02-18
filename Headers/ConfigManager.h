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
        void insert_item (TItem item);
        void read_item ();
        static size_t get_rand_num ();
};

#endif // CONFIG_MANAGER_H
