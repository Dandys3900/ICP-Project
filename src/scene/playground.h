#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#include "scene/robot.h"
#include "scene/obstacle.h"

// Enum representing desired config file operation
enum Operation : int {
    LOAD = 0,
    STORE
};

class PlayGround : public QGraphicsRectItem {
    private:
        // Vector for storing instancies of Robots and Obstacles placed to scene
        QVector<SceneObject*> mp_scene_objs_vec;

        // Vector for storing generated objects ids
        QVector<size_t> m_ids_array;

        QPointF mp_active_obj_orig_pos;

        QGraphicsScene*    mp_scene;
        class SceneObject* mp_active_obj;

        Action mp_cur_action;

    public:
        PlayGround (QGraphicsScene* scene);
        ~PlayGround ();

        // Adding objects to the playground
        void add_scene_obj (SceneObject* object);
        // Removing objects from the playground
        void remove_scene_obj (SceneObject* object);
        // Set scene object as currently active
        void set_active_obj (SceneObject* object, Action action);
        // Active object will lose focus
        void disable_focus ();

        QPointF get_active_obj_orig_pos ();

        // Methods for load/store scene configuration
        QString get_selected_file (Operation operation);
        void load_config ();
        void store_config ();

        // Events - handling
        void keyPressEvent (QKeyEvent* event) override;
        void mouseMoveEvent (QGraphicsSceneMouseEvent *event) override;
        void mousePressEvent (QGraphicsSceneMouseEvent* event) override;
};

#endif // PLAYGROUND_H
