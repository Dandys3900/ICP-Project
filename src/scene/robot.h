/** ICP Project 2023/2024
 * @file robot.h
 * @author Tomáš Daniel (xdanie14)
 * @brief Header file for Robot class.
 */

#ifndef ROBOT_H
#define ROBOT_H

#include "includes/libs_file.h"
#include "scene/scene_object.h"
#include "scene/playground.h"
#include "scene/robot_info.h"

class Robot : public SceneObject, public QGraphicsEllipseItem {
    private:
        qreal mp_diameter;
        QString mp_type;

        // Robot details
        enum Mode mp_mode;
        enum Direction mp_rotation_direction;
        qreal mp_rotation_angle;
        qreal mp_detect_threshold;

        class PlayGround*     mp_playground;
        QGraphicsPolygonItem* mp_arrow;

        void constructor_actions ();
        void do_rotation (const qreal angle);
        void move_forward ();

    public:
        /**
         * @brief Constructor.
         * @param size Diameter of circle (robot).
         * @param coord_x X-axis position of robot in the scene.
         * @param coord_y Y-axis position of robot in the scene.
         * @param playground Scene objects and event management.
         */
        Robot (const qreal size,
               const qreal coord_x,
               const qreal coord_y,
               PlayGround* playground);
        /**
         * @brief Constructor.
         * @param size Diameter of circle (robot).
         * @param coords Vector containing position of robot in the scene.
         * @param playground Scene objects and event management.
         */
        Robot (const qreal size,
               const Vector2& coords,
               PlayGround* playground);
        /**
         * @brief Constructor.
         * @param size Diameter of circle (robot).
         * @param coords Vector containing position of robot in the scene.
         * @param rotation Initial rotation of robot's arrow.
         * @param mode Initial mode of robot (manual/automatic).
         * @param rot_direction Initial direction of robot's rotation (clockwise/anticlockwise).
         * @param rotation_step Sets rotation value used with each robot's arrow movement.
         * @param collision_thr Initial values for collision threshold of robot.
         * @param playground Scene objects and event management.
         */
        Robot (const qreal size,
               const Vector2& coords,
               qreal rotation,
               const int mode,
               const int rot_direction,
               const qreal rotation_step,
               const qreal collision_thr,
               PlayGround* playGround);
        /**
         * @brief Destructor.
         */
        ~Robot ();

        // Implementations of virtual base class methods
        QString get_type () override;
        QPointF get_pos () override;
        QRectF get_rect () override;
        void set_obj_pos (const QPointF pos) override;
        void set_active (bool active, Action action) override;
        QJsonObject get_obj_data () override;

        /**
         * @brief Getter for robot's arrow polygon (pointing current direction of movement).
         * @return QGraphicsPolygonItem Representing robot's arrow.
         */
        QGraphicsPolygonItem* get_robot_arrow ();

        /**
         * @brief Getter for robot's current attribute values used for constructing robot_info widget.
         * @return QVector<QString> Vector of robot's attributes.
         */
        QVector<QString> get_robot_info ();
        // Setters for possible updates of robot attributes
        void set_mode (int new_mode);
        void set_rotation_angle (qreal new_angle);
        void set_rotation_direction (int new_direction);
        void set_detect_threshold (qreal new_threshold);

    protected:
        // Events - handling
        void mousePressEvent (QGraphicsSceneMouseEvent* event) override;
        void mouseMoveEvent (QGraphicsSceneMouseEvent* event) override;
        void keyPressEvent (QKeyEvent* event) override;
        void mouseDoubleClickEvent (QGraphicsSceneMouseEvent* event) override;
        void hoverEnterEvent (QGraphicsSceneHoverEvent* event) override;
        void hoverLeaveEvent (QGraphicsSceneHoverEvent* event) override;
};

#endif // ROBOT_H
