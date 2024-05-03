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


/*!
 * Robot representaion for the PhysicsServer
 */
class PhysicalRobot {
	public: // fields
		enum QueuedAction {
			NOTHING,
			MOVE,
			TURN_LEFT,
			TURN_RIGHT,
		};

		QueuedAction queued_action = QueuedAction::NOTHING;

	protected: // fields
		Robot* robot = nullptr;
		// Robot collision shape
		CircleCollisionShape* shape = nullptr;
		// Shapecast collision shapes
		RectangeCollisionShape* shapecast_capsule_rectangle = nullptr;
		CircleCollisionShape* shapecast_capsule_circle = nullptr;
	
	public: // methods
		PhysicalRobot(Robot* robot);
		~PhysicalRobot();

		void update_shape();
		void update_shapecast();
	
		bool is_colliding_with(const CollisionShape& other_shape) const ;
		bool is_shapecast_colliding_with(const CollisionShape& other_shape) const;

		bool is_colliding_with_any(QVector<const CollisionShape*>& other_shapes) const;
		bool is_shapecast_colliding_with_any(QVector<const CollisionShape*>& other_shapes) const;

		const CircleCollisionShape* get_shape();

		void step(QVector<const CollisionShape*>& playground_boundary_obstacles, QVector<const CollisionShape*>& obstacles, QVector<const CollisionShape*>& robots);

	protected: // methods
		void move();
		void turn();
		void turn_left();
		void turn_right();
};


#endif // PHYSICAL_ROBOT_H
