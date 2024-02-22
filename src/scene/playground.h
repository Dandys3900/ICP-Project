#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#include "robot.h"
#include "obstacle.h"

class PlayGround : public QGraphicsRectItem {
    private:
        /* mp_size.x() ... width
           mp_size.y() ... height */
        class Vector2 mp_size;

        // Vector for storing instancies of Robots and Obstacles
        QVector<SceneObject*> mp_scene_objs_vec;

        QPointF mp_active_obj_orig_pos;

        class QGraphicsScene* mp_scene;
        class SceneObject*    mp_active_obj;

        Action mp_cur_action;

    public:
        PlayGround (const qreal width,
                    const qreal height,
                    QGraphicsScene* scene);

        PlayGround (const Vector2& size,
                    QGraphicsScene* scene);

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

        void store_scene ();

        // Events - handling
        void keyPressEvent (QKeyEvent* event) override;
        void mouseMoveEvent (QGraphicsSceneMouseEvent *event) override;
        void mousePressEvent (QGraphicsSceneMouseEvent* event) override;
};

#endif // PLAYGROUND_H
