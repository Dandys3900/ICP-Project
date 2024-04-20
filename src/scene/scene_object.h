/** ICP Project 2023/2024
 * @file scene_object.h
 * @author Tomáš Daniel (xdanie14)
 * @brief Header file for SceneObject class.
 */

#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "includes/libs_file.h"

class SceneObject {
    public:
        /**
         * @brief Constructor.
         * @param coords Vector containing position of object (robot/obstacle) in the scene.
         */
        SceneObject (const Vector2& coords) :
            mp_coords     (coords),
            mp_rotation   (0),
            mp_obj_action (NO_ACTION),
            mp_is_active  (false),
            mp_color      (Qt::black)
        {
        }
        /**
         * @brief Constructor.
         * @param coords Vector containing position of object (robot/obstacle) in the scene.
         * @param rotation Initial object rotation.
         */
        SceneObject (const Vector2& coords, qreal rotation) :
            SceneObject (coords)
        {
            mp_rotation = rotation;
        }
        /**
         * @brief Virtual destructor.
         */
        virtual ~SceneObject () {}

        /**
         * @brief Pure virtual getter for object's type (robot/obstacle).
         * @return QString Object type.
         */
        virtual QString get_type ()                          = 0;
        /**
         * @brief Pure virtual getter for object's surrounding rectangle.
         * @return QRectF Object rectangle.
         */
        virtual QRectF get_rect ()                           = 0;
        /**
         * @brief Pure virtual getter for object's current scene position.
         * @return QPointF Object position.
         */
        virtual QPointF get_pos ()                           = 0;
        /**
         * @brief Pure virtual setter for object's scene position.
         * @param pos New object's position.
         */
        virtual void set_obj_pos (QPointF pos)               = 0;
        /**
         * @brief Pure virtual setter for toggling object's active (focus) status (active/inactive).
         * @param active Boolean value marking object active or not.
         * @param action Selects action to be done with object when active.
         */
        virtual void set_active (bool active, Action action) = 0;

        /**
         * @brief Pure virtual getter for object's current attributes values to be stored into the file.
         * @return QJsonObject Contains object's attributes.
         */
        virtual QJsonObject get_obj_data () {
            QJsonObject conf_data;
            conf_data["coord_x"]  = mp_coords.x();
            conf_data["coord_y"]  = mp_coords.y();
            conf_data["rotation"] = mp_rotation;
            // Return constructed object
            return conf_data;
        }

        /**
         * @brief Pure virtual method for handling mouse press event in the scene.
         * @param event Generated mouse press event.
         * Each derived class must implement this function to define custom behavior for this event.
         */
        virtual void mousePressEvent (QGraphicsSceneMouseEvent* event)       = 0;
        /**
         * @brief Pure virtual method for handling mouse double click event in the scene.
         * @param event Generated mouse press event.
         * Each derived class must implement this function to define custom behavior for this event.
         */
        virtual void mouseDoubleClickEvent (QGraphicsSceneMouseEvent* event) = 0;
        /**
         * @brief Pure virtual method for handling key press event in the scene.
         * @param event Generated key press event.
         * Each derived class must implement this function to define custom behavior for this event.
         */
        virtual void keyPressEvent (QKeyEvent* event)                        = 0;
        /**
         * @brief Pure virtual method for handling mouse move event in the scene.
         * @param event Generated mouse move event.
         * Each derived class must implement this function to define custom behavior for this event.
         */
        virtual void mouseMoveEvent (QGraphicsSceneMouseEvent* event)        = 0;
        /**
         * @brief Pure virtual method for handling mouse hover event over object.
         * @param event Generated hover event.
         * Each derived class must implement this function to define custom behavior for this event.
         */
        virtual void hoverEnterEvent (QGraphicsSceneHoverEvent* event)       = 0;
        /**
         * @brief Pure virtual method for handling mouse hover leave event over object.
         * @param event Generated hover leave event.
         * Each derived class must implement this function to define custom behavior for this event.
         */
        virtual void hoverLeaveEvent (QGraphicsSceneHoverEvent* event)       = 0;

    protected:
        // Attributes similar for both robot and obstacle classes
        Vector2 mp_coords;
        qreal mp_rotation;
        Action mp_obj_action;
        bool mp_is_active;
        Qt::GlobalColor mp_color;
        Vector2 mp_move_action_mouse_offset;
};

#endif // SCENEOBJECT_H
