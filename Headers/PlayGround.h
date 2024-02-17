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

        QGraphicsScene* mp_scene;
        MoveableObject* m_moved_obj;

        void constructor_actions ();

    public:
        PlayGround (const qreal width,
                    const qreal height,
                    QGraphicsScene* scene);
        ~PlayGround ();

        // Adding objects to the playground
        void addObject (MoveableObject* object);

        void set_moved_obj (MoveableObject* object);

        // Events - handling
        void keyPressEvent (QKeyEvent* event) override;
        void mouseMoveEvent (QGraphicsSceneMouseEvent *event) override;
        void mousePressEvent (QGraphicsSceneMouseEvent* event) override;
};

#endif // PLAYGROUND_H
