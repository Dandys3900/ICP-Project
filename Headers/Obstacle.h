#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <QGraphicsRectItem>

class Obstacle : public QGraphicsRectItem {
    private:
        qreal mp_width;
        qreal mp_height;
        qreal mp_coord_x;
        qreal mp_coord_y;

    public:
        Obstacle (const qreal width,
                  const qreal height,
                  const qreal axis_x,
                  const qreal axis_y);
        ~Obstacle ();
};

#endif // OBSTACLE_H
