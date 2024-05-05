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
       /**
         * @brief Constructor.
         * @param scene Constructed scene.
         * @param playground Scene objects and event management.
         * @param window Program window widget.
         */
        UserMenu (QGraphicsScene* scene, PlayGround* playground, QWidget* window);
        /**
         * @brief Destructor.
         */
        ~UserMenu ();

    private:
        PlayGround*           mp_playground;
        QGraphicsScene*       mp_scene;
        QWidget*              mp_menu_container; // Widgets containing all menu items
        QGroupBox*            mp_sim_mode_items;
        QGraphicsProxyWidget* mp_proxy_button;
        QGraphicsProxyWidget* mp_container_proxy;

        QPushButton* mp_stop_sim_button;
        QPushButton* mp_start_sim_button;

        bool mp_expanded;

    private slots:
        // Methods for handling menu items events
        /**
         * @brief Handles the button click event.
         */
        void btn_click ();
        /**
         * @brief Triggers playground method for selecting config file to load a scene from.
         */
        void load_config();
        /**
         * @brief Triggers playground method for storing current scene into config file.
         */
        void store_config();
        /**
         * @brief Creates new robot which user will place to the scene.
         */
        void add_robot ();
        /**
         * @brief Creates new obstacle which user will place to the scene.
         */
        void add_obstacle ();
        /**
         * @brief Handles the selection of simulation mode (automatic/manual).
         * @param index Index of the selected mode.
         */
        void mode_select (int index);
        /**
         * @brief Sets the simulation speed.
         * @param slider_value The value of the simulation speed (0-100).
         */
        void sim_speed_set (int slider_value);
        /**
         * @brief Starts the simulation.
         */
        void start_sim ();
        /**
         * @brief Stops the simulation.
         */
        void stop_sim ();
};

#endif // USER_MENU_H
