#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#include <QGraphicsRectItem>
#include <QGraphicsItem>
#include <QKeyEvent>
#include <QGraphicsScene>

#include <vector>
#include <iterator>

#include "Obstacle.h"
#include "Robot.h"

class PlayGround : public QGraphicsRectItem {
    private:
        qreal mp_width;
        qreal mp_height;
        qreal mp_coord_x;
        qreal mp_coord_y;

        // Vector for storing instancies of Robots and Obstacles
        std::vector<Robot*>    mp_robot_vec;
        std::vector<Obstacle*> mp_obstacle_vec;

        void constructor_actions ();

    public:
        PlayGround (const qreal width,
                    const qreal height,
                    const qreal axis_x,
                    const qreal axis_y);
        ~PlayGround ();

        // Adding objects to the playground
        void addRobot    (Robot* robot);
        void addObstacle (Obstacle* obstacle);

        // Handling key press
        void keyPressEvent (QKeyEvent* event);
};

#endif // PLAYGROUND_H
