#ifndef USER_MENU_H
#define USER_MENU_H

#include "includes/libs_file.h"
#include "scene/playground.h"

class UserMenu : public QWidget {
    Q_OBJECT

    public:
        UserMenu (QGraphicsScene* scene, PlayGround* playground, QWidget* window = nullptr);
        ~UserMenu ();

    private:
        PlayGround*           mp_playground;
        QGraphicsScene*       mp_scene;
        QPushButton*          mp_menu_button;
        QGraphicsProxyWidget* mp_proxy_button;
        QWidget*              mp_menu_container;
        QVBoxLayout*          mp_menu_layout;
        QPushButton*          mp_load_conf_btn;
        QPushButton*          mp_store_conf_btn;
        QHBoxLayout*          mp_conf_items_layout;
        QPushButton*          mp_add_robot_btn;
        QPushButton*          mp_add_obstacle_btn;
        QComboBox*            mp_sim_select_box;
        QGroupBox*            mp_sim_mode_items;
        QPushButton*          mp_stop_sim_btn;
        QPushButton*          mp_start_sim_btn;
        QHBoxLayout*          mp_sim_buttons_layout;
        QSlider*              mp_speed_slider;
        QVBoxLayout*          mp_sim_items_layout;
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
