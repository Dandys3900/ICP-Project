#ifndef ROBOTINFO_H
#define ROBOTINFO_H

#include "includes/libs_file.h"
#include "scene/robot.h"

class Robot_Info : public QWidget {
    Q_OBJECT

    public:
        Robot_Info (QGraphicsScene* scene, QWidget* window);
        ~Robot_Info ();

        static void show_widget (class Robot* cur_robot);
        static void clean_up ();

    private:
        QGraphicsScene*       mp_scene;
        QWidget*              mp_main_window;
        class Robot*          mp_robot;
        QWidget*              mp_info_container;
        QComboBox*            mp_typeComboBox;
        QLineEdit*            mp_collisionLineEdit;
        QLineEdit*            mp_rotationLineEdit;
        QComboBox*            mp_directionComboBox;
        QGraphicsProxyWidget* mp_proxy;
        QGroupBox*            mp_auto_mode_items;
        bool                  mp_visible;

        static Robot_Info* instance;

        void process_robot_info ();
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
