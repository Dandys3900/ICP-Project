/** ICP Project 2023/2024
 * @file physical_robot.h
 * @author Jakub Janšta (xjanst02)
 * @brief Header file for PhysicalRobot class.
 */

#ifndef PHYSICAL_ROBOT_H
#define PHYSICAL_ROBOT_H


#include <QtGlobal>
#include <QVector>

#include "math/vector2.h"

#include "scene/robot.h"

#include "physics/collision_shapes/collision_shape.h"
#include "physics/collision_shapes/circle_collision_shape.h"
#include "physics/collision_shapes/rectangle_collision_shape.h"

#include "physics/physical_objects/physical_obstacle.h"


class Robot;
class PhysicalRobot;
class PhysicalObstacle;


/**
 * Robot representaion for the PhysicsServer
 */
class PhysicalRobot {
	public: // Fields
		enum QueuedAction {
			NONE,
			MOVE,
			TURN_LEFT,
			TURN_RIGHT,
		};

		QueuedAction queued_action = QueuedAction::NONE;

	protected: // Fields
		Robot* robot = nullptr;
		// Robot collision shape
		CircleCollisionShape* shape = nullptr;
		// Shapecast collision shapes
		RectangeCollisionShape* shapecast_capsule_rectangle = nullptr;
		CircleCollisionShape* shapecast_capsule_circle = nullptr;

	public: // Methods
		/**
         * @brief Constructor.
         * @param robot Related robot object.
         */
		PhysicalRobot(Robot* robot);
		/**
         * @brief Destructor.
         */
		~PhysicalRobot();

		/**
         * @brief Updates robot's shape to match the Robot's position, rotation and scale.
         */
		void update_shape();
		/**
         * @brief Updates robot's shapecast.
         */
		void update_shapecast();

		/**
         * @brief Determines whether robot is in collision with given object's (collision) shape.
         * @param other_shape Shape to check collision with.
		 * @return True if collides, false otherwise.
         */
		bool is_colliding_with(const CollisionShape& other_shape) const ;
		/**
         * @brief Determines whether robot's shapecast is in collision with given object's (collision) shape.
         * @param other_shape Shape to check collision with.
		 * @return True if collides, false otherwise.
         */
		bool is_shapecast_colliding_with(const CollisionShape& other_shape) const;
		/**
         * @brief Determines whether robot is in collision with given vector of object's (collision) shapes.
         * @param other_shape Vector containing shapes to check collision with.
		 * @return True if collides, false otherwise.
         */
		bool is_colliding_with_any(QVector<const CollisionShape*>& other_shapes) const;
		/**
         * @brief Determines whether robot's shapecast is in collision with given vector of object's (collision) shapes.
         * @param other_shape Vector containing shapes to check collision with.
		 * @return True if collides, false otherwise.
         */
		bool is_shapecast_colliding_with_any(QVector<const CollisionShape*>& other_shapes) const;

		/**
         * @brief Getter for the robot shape.
		 * @return Robot (circle) collision shape.
         */
		const CircleCollisionShape* get_shape();

		/**
		 * @brief Executes a step for the robot according its current mode (automatic/manual).
		 * @param playground_boundary_obstacles Vector containing collision shapes for current scene boundaries.
		 * @param obstacles Vector containing collision shapes of obstacles.
		 * @param robots Vector containing collision shapes of other robots.
		 */
		void step(QVector<const CollisionShape*>& playground_boundary_obstacles, QVector<const CollisionShape*>& obstacles, QVector<const CollisionShape*>& robots);
		/**
		 * @brief Executes a step for the robot in automatic mode.
		 * @param playground_boundary_obstacles Vector containing collision shapes for current scene boundaries.
		 * @param obstacles Vector containing collision shapes of obstacles.
		 * @param robots Vector containing collision shapes of other robots.
		 */
		void step_automatic(QVector<const CollisionShape*>& playground_boundary_obstacles, QVector<const CollisionShape*>& obstacles, QVector<const CollisionShape*>& robots);
		/**
		 * @brief Executes a step for the robot in manual mode.
		 * @param playground_boundary_obstacles Vector containing collision shapes for current scene boundaries.
		 * @param obstacles Vector containing collision shapes of obstacles.
		 * @param robots Vector containing collision shapes of other robots.
		 */
		void step_manual(QVector<const CollisionShape*>& playground_boundary_obstacles, QVector<const CollisionShape*>& obstacles, QVector<const CollisionShape*>& robots);

	protected: // Methods
		/**
         * @brief Method for robot's scene move.
         */
		void move();
		/**
         * @brief Method for robot's turning.
         */
		void turn();
		/**
         * @brief Method for robot's left-turning.
         */
		void turn_left();
		/**
         * @brief Method for robot's right-turning.
         */
		void turn_right();
};


#endif // PHYSICAL_ROBOT_H
