#ifndef ROBOT_H
#define ROBOT_H

#include <QGraphicsEllipseItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QtMath>
#include <QTimer>
#include <QObject>

#include "Headers/Consts.h"

class Robot : public QObject, public QGraphicsEllipseItem {
    Q_OBJECT

    private:
        qreal mp_diameter;
        qreal mp_coord_x;
        qreal mp_coord_y;

        size_t mp_rotation;

        void do_rotation (const size_t angle);
        void move_forward ();

        void set_new_pos (qreal new_x, qreal new_y);

    public:
        Robot (const qreal size,
               const qreal axis_x,
               const qreal axis_y);
        ~Robot ();

        // Handling key press
        void keyPressEvent (const QKeyEvent* event);

        QGraphicsPolygonItem* m_arrow;

    public slots:
        void detect_objects ();
};

#endif // ROBOT_H
