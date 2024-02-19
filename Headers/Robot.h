#ifndef ROBOT_H
#define ROBOT_H

#include "LibsFile.h"
#include "MoveableObject.h"
#include "PlayGround.h"

class Robot : public MoveableObject, public QGraphicsEllipseItem {
    private:
        Vector2 mp_coords;

        qreal mp_diameter;
        qreal mp_rotation;

        QString mp_type;

        Qt::GlobalColor mp_pen_colour;

        class PlayGround* mp_playground;

        QGraphicsPolygonItem* mp_arrow;

        void do_rotation (const qreal angle);
        void move_forward ();

    public:
        Robot (const qreal size,
               const qreal coords_x,
               const qreal coords_y,
               PlayGround* playground);

        Robot (const qreal size,
               const Vector2& coords,
               PlayGround* playground);

        ~Robot ();

        // Implementations of virtual base class methods
        QString get_type () override;
        QPointF get_pos () override;
        void set_obj_pos (const QPointF pos) override;
        void set_marked (bool marked, Action action) override;
        QGraphicsPolygonItem* get_robot_arrow ();

    protected:
        // Events - handling
        void mousePressEvent (QGraphicsSceneMouseEvent* event) override;
        void mouseMoveEvent (QGraphicsSceneMouseEvent *event) override;
        void keyPressEvent (QKeyEvent* event) override;
};

#endif // ROBOT_H
