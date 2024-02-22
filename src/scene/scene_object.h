#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "src/includes/libs_file.h"

class SceneObject {
    public:
        SceneObject (const class Vector2& coords) :
            mp_coords     (coords),
            mp_rotation   (0),
            mp_obj_action (NO_ACTION),
            mp_is_active  (false),
            mp_color      (Qt::black)
        {
        }

        SceneObject (const Vector2& coords, qreal rotation, Action action, bool active, Qt::GlobalColor color) :
            mp_coords     (coords),
            mp_rotation   (rotation),
            mp_obj_action (action),
            mp_is_active  (active),
            mp_color      (color)
        {
        }

        virtual ~SceneObject () {}

        virtual QString get_type () = 0;
        virtual QPointF get_pos ()  = 0;

        virtual void set_obj_pos (QPointF pos)               = 0;
        virtual void set_active (bool active, Action action) = 0;

        // Fill this generic values
        virtual QJsonObject get_obj_data () {
            QJsonObject conf_data;
            conf_data["coord_x"] = this->mp_coords.x();
            conf_data["coord_y"] = this->mp_coords.y();
            conf_data["rotation"] = this->mp_rotation;
            conf_data["action"] = this->mp_obj_action;
            conf_data["active"] = ((this->mp_is_active) ? "true" : "false");
            conf_data["color"] = this->mp_color;

            return conf_data;
        }

        virtual void mousePressEvent (QGraphicsSceneMouseEvent* event) = 0;
        virtual void keyPressEvent (QKeyEvent* event)                  = 0;
        virtual void mouseMoveEvent (QGraphicsSceneMouseEvent *event)  = 0;

    protected:
        Vector2 mp_coords;
        qreal mp_rotation;
        Action mp_obj_action;
        bool mp_is_active;
        Qt::GlobalColor mp_color;
};

#endif // SCENEOBJECT_H
