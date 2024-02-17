#ifndef MOVEABLEOBJECT_H
#define MOVEABLEOBJECT_H

#include "LibsFile.h"

class MoveableObject {
    public:
        virtual QString get_type () = 0;
        virtual void* get_object () = 0;

        virtual QPointF get_pos () = 0;
        virtual void set_obj_pos (QPointF pos) = 0;

        virtual void set_marked (bool marked, Action action) = 0;

        virtual void mousePressEvent (QGraphicsSceneMouseEvent* event) = 0;
        virtual void keyPressEvent (QKeyEvent* event) = 0;
        virtual void mouseMoveEvent (QGraphicsSceneMouseEvent *event) = 0;
};

#endif // MOVEABLEOBJECT_H
