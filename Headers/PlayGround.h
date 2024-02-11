#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#include <QGraphicsRectItem>
#include <QGraphicsItem>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QGraphicsScene>
#include <QGraphicsView>

#include <vector>
#include <iterator>

#include "Obstacle.h"
#include "Robot.h"

class PlayGround : public QGraphicsRectItem {
    private:
        qreal mp_width;
        qreal mp_height;

        // Vector for storing instancies of Robots and Obstacles
        std::vector<MoveableObject*> mp_objs_vec;

        QPointF mp_moved_obj_orig_pos;

        QGraphicsScene* mp_scene;

        void constructor_actions ();

    public:
        PlayGround (const qreal width,
                    const qreal height,
                    QGraphicsScene* scene);
        ~PlayGround ();

        // Adding objects to the playground
        void addObject (MoveableObject* object);

        // Events:
        // -> Handling key press
        void keyPressEvent (QKeyEvent* event);
// -> Handling mouse move event
        void mouseMoveEvent (QGraphicsSceneMouseEvent *event);
        // -> Handling mouse press event
        void mousePressEvent (QGraphicsSceneMouseEvent* event);

        void set_moved_obj (MoveableObject* object);

        MoveableObject* m_moved_obj;
};

#endif // PLAYGROUND_H
