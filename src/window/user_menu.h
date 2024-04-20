/** ICP Project 2023/2024
 * @file user_menu.h
 * @author Tomáš Daniel (xdanie14)
 * @brief Header file for UserMenu class.
 */

#ifndef USER_MENU_H
#define USER_MENU_H

#include "includes/libs_file.h"
#include "scene/playground.h"

class UserMenu : public QWidget {
    Q_OBJECT

    public:
        UserMenu (QGraphicsScene* scene, PlayGround* playground, QWidget* window);
        ~UserMenu ();

    private:
        PlayGround*           mp_playground;
        QGraphicsScene*       mp_scene;
        QWidget*              mp_menu_container;
        QGroupBox*            mp_sim_mode_items;
        QGraphicsProxyWidget* mp_proxy_button;
        QGraphicsProxyWidget* mp_container_proxy;

        bool mp_expanded;

    private slots:
        // Methods for handling menu items events
        void btn_click ();
        void load_config();
        void store_config();
        void add_robot ();
        void add_obstacle ();
        void mode_select (int index);
        void sim_speed_set (int slider_value);
        void start_sim ();
        void stop_sim ();
};

#endif // USER_MENU_H
