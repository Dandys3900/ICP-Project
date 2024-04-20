/** ICP Project 2023/2024
 * @file robot_info.h
 * @author Tomáš Daniel (xdanie14)
 * @brief Header file for Robot_Info class.
 */

#ifndef ROBOTINFO_H
#define ROBOTINFO_H

#include "includes/libs_file.h"
#include "scene/robot.h"

class Robot_Info : public QWidget {
    Q_OBJECT

    public:
        /**
         * @brief Constructor.
         * @param scene Constructed scene.
         * @param window Parent.
         */
        Robot_Info (QGraphicsScene* scene, QWidget* window);
        /**
         * @brief Destructor.
         */
        ~Robot_Info ();

        /**
         * @brief Shows widget containing given robot object properties.
         * @param cur_robot Robot which details are shown.
         */
        static void show_widget (class Robot* cur_robot);
        /**
         * @brief Hides shown widget if belongs to given robot.
         * @param cur_robot Caller robot.
         */
        static void hide_related_widget (class Robot* cur_robot);
        /**
         * @brief Deallocates static instance of this class.
         */
        static void clean_up ();

    private:
        QGraphicsScene*       mp_scene;
        QWidget*              mp_main_window;
        class Robot*          mp_robot; // Current robot instance
        QWidget*              mp_info_container;
        QComboBox*            mp_typeComboBox;
        QLineEdit*            mp_collisionLineEdit;
        QLineEdit*            mp_rotationLineEdit;
        QComboBox*            mp_directionComboBox;
        QGraphicsProxyWidget* mp_proxy;
        QGroupBox*            mp_auto_mode_items;
        bool                  mp_visible;

        static Robot_Info* instance;

        /**
         * @brief Fills widget values with properities of current robot.
         */
        void process_robot_info ();
        /**
         * @brief Show proper widget items based on passed mode (manual/automatic).
         * @param mode Current mode.
         */
        void update_visible_items (int mode);

    private slots:
        // Methods for handling widget items events
        void ok_click ();
        void robot_type (int index);
        void collision_value (const QString& text);
        void rotation_value (const QString& text);
        void rotation_direction (int index);
};

#endif // ROBOTINFO_H
