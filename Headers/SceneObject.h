#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "LibsFile.h"

class SceneObject {
    public:
        virtual QString get_type () = 0;
        virtual QPointF get_pos ()  = 0;

        virtual void set_obj_pos (QPointF pos)             = 0;
        virtual void set_focus (bool focus, Action action) = 0;

        virtual void mousePressEvent (QGraphicsSceneMouseEvent* event) = 0;
        virtual void keyPressEvent (QKeyEvent* event)                  = 0;
        virtual void mouseMoveEvent (QGraphicsSceneMouseEvent *event)  = 0;
};

#endif // SCENEOBJECT_H
