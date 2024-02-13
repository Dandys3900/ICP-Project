#ifndef ROBOT_H
#define ROBOT_H

#include <QGraphicsEllipseItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QtMath>
#include <QTimer>

#include "Headers/Consts.h"
#include "Headers/MoveableObject.h"
#include "Headers/PlayGround.h"

class Robot : public MoveableObject, public QGraphicsEllipseItem {
    private:
        qreal mp_diameter;
        qreal mp_coord_x;
        qreal mp_coord_y;

        qreal mp_rotation;

        QString mp_type;

        class PlayGround* mp_playground;

        void do_rotation (const qreal angle);
        void move_forward ();

    public:
        Robot (const qreal size,
               const qreal axis_x,
               const qreal axis_y,
               PlayGround* playground);
        ~Robot ();

        // Implementations of virtual base class methdos
        QString get_type () override;
        MoveableObject* get_object () override;
        // Handling key press
        void keyPressEvent (QKeyEvent* event) override;
        QPointF get_pos () override;
        void set_obj_pos (QPointF pos) override;
        void set_marked (bool marked) override;
        void mouseMoveEvent (QGraphicsSceneMouseEvent *event) override;

        QGraphicsPolygonItem* m_arrow;

    protected:
        void mousePressEvent (QGraphicsSceneMouseEvent* event) override;
};

#endif // ROBOT_H
