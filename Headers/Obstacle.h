#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "LibsFile.h"
#include "MoveableObject.h"
#include "PlayGround.h"

class Obstacle : public MoveableObject, public QGraphicsRectItem {
    private:
        qreal mp_width;
        qreal mp_height;
        qreal mp_coord_x;
        qreal mp_coord_y;

        qreal mp_rotation;

        QString mp_type;

        class PlayGround* mp_playground;

        void do_rotation (const qreal angle);

    public:
        Obstacle (const qreal width,
                  const qreal height,
                  const qreal axis_x,
                  const qreal axis_y,
                  PlayGround* playground);
        ~Obstacle ();

        // Implementations of virtual base class methods
        QString get_type () override;
        void* get_object () override;
        QPointF get_pos () override;
        void set_obj_pos (const QPointF pos) override;
        void set_marked (bool marked) override;

    protected:
        // Events - handling
        void mousePressEvent (QGraphicsSceneMouseEvent* event) override;
        void mouseMoveEvent (QGraphicsSceneMouseEvent *event) override;
        void keyPressEvent (QKeyEvent* event) override;
};

#endif // OBSTACLE_H
