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
#include "physics/physical_objects/physical_robot.h"

class Robot : public SceneObject, public QGraphicsEllipseItem {
    private:
        qreal mp_diameter;
        QString mp_obj_type;

        // Robot details
        enum Mode mp_mode;
        enum Mode mp_old_mode;
        enum Direction mp_rotation_direction;
        qreal mp_rotation_step;
        qreal mp_detect_threshold;

        class PlayGround*     mp_playground;
        QGraphicsPolygonItem* mp_arrow;

        class PhysicalRobot* physical_robot;

        /**
         * @brief Method handling initial setup of scene object.
         */
        void constructor_actions ();

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
               const Mode mode,
               const Direction rot_direction,
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
        qreal get_diameter();
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
        /**
         * @brief Sets the mode of the robot.
         * @param new_mode New mode to set.
         */
        void set_mode (Mode new_mode);
        /**
         * @brief Sets the rotation step of the robot.
         * @param new_angle New rotation step in degrees.
         */
        void set_rotation_step (qreal new_angle);
        /**
         * @brief Sets the rotation step of the robot in radians.
         * @param new_angle New rotation step in radians.
         */
        void set_rotation_step_radians (qreal new_angle);
        /**
         * @brief Sets the rotation direction of the robot.
         * @param new_direction New rotation direction.
         */
        void set_rotation_direction (Direction new_direction);
        /**
         * @brief Sets the collision detection threshold of the robot.
         * @param new_threshold New collision detection threshold.
         */
        void set_detect_threshold (qreal new_threshold);

        // Getters for robot attributes
        /**
         * @brief Gets the mode of the robot.
         * @return Mode of the robot.
         */
        Mode get_mode();
        /**
         * @brief Gets the rotation step of the robot.
         * @return Rotation step of the robot.
         */
        qreal get_rotation_step ();
        /**
         * @brief Gets the rotation step of the robot in radians.
         * @return Rotation step of the robot in radians.
         */
        qreal get_rotation_step_radians ();
        /**
         * @brief Gets the rotation direction of the robot.
         * @return Rotation direction of the robot.
         */
        Direction get_rotation_direction ();
        /**
         * @brief Gets the collision detection threshold of the robot.
         * @return Collision detection threshold of the robot.
         */
        qreal get_detect_threshold ();
        /**
         * @brief Performs robot rotation by given angle.
         * @param angle Rotation angle.
         */
        void do_rotation (const qreal angle);

    protected:
        // Events - handling
        void mousePressEvent (QGraphicsSceneMouseEvent* event) override;
        void mouseReleaseEvent (QGraphicsSceneMouseEvent* event) override;
        void mouseMoveEvent (QGraphicsSceneMouseEvent* event) override;
        void keyPressEvent (QKeyEvent* event) override;
        void mouseDoubleClickEvent (QGraphicsSceneMouseEvent* event) override;
        void hoverEnterEvent (QGraphicsSceneHoverEvent* event) override;
        void hoverLeaveEvent (QGraphicsSceneHoverEvent* event) override;
        /**
         * @brief Overriden Qt paint method for ensuring proper displaying of robot texture.
         */
        void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
};

#endif // ROBOT_H
