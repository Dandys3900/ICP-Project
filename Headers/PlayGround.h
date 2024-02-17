#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#include "Robot.h"
#include "Obstacle.h"

class PlayGround : public QGraphicsRectItem {
    private:
        qreal mp_width;
        qreal mp_height;

        // Vector for storing instancies of Robots and Obstacles
        std::vector<MoveableObject*> mp_objs_vec;

        QPointF mp_moved_obj_orig_pos;

        QGraphicsScene*       mp_scene;
        class MoveableObject* mp_moved_obj;
        class MoveableObject* mp_resized_obj;

        enum Action mp_cur_action;

        void constructor_actions ();
        MoveableObject*& get_action_obj (Action action);
        void set_orig_pos_var (const QPointF pos, Action action);

    public:
        PlayGround (const qreal width,
                    const qreal height,
                    QGraphicsScene* scene);
        ~PlayGround ();

        // Adding objects to the playground
        void addObject (MoveableObject* object);

        void set_active_obj (MoveableObject* object, Action action);

        // Events - handling
        void keyPressEvent (QKeyEvent* event) override;
        void mouseMoveEvent (QGraphicsSceneMouseEvent *event) override;
        void mousePressEvent (QGraphicsSceneMouseEvent* event) override;
};

#endif // PLAYGROUND_H
