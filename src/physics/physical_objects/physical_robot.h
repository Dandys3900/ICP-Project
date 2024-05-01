/** ICP Project 2023/2024
 * @file physical_robot.h
 * @author Jakub Janšta (xjanst02)
 * @brief Header file for PhysicalRobot class.
 */

#ifndef PHYSICAL_ROBOT_H
#define PHYSICAL_ROBOT_H


#include <QtGlobal>

#include "math/vector2.h"

#include "scene/robot.h"

#include "physics/collision_shapes/circle_collision_shape.h"
#include "physics/collision_shapes/rectangle_collision_shape.h"


class Robot;


/*!
 * Robot representaion for the PhysicsServer
 */
class PhysicalRobot {
	protected: // fields
		Robot* robot = nullptr;
		CircleCollisionShape* shape = nullptr;

		// Shapecast collision shapes
		RectangeCollisionShape* shapecast_capsule_rectangle = nullptr;
		CircleCollisionShape* shapecast_capsule_circle = nullptr;
	
	public: // methods
		PhysicalRobot(Robot* robot);
		~PhysicalRobot();

		void update_shape();
		void update_shapecast();

		void move();
		void turn();
		void turn_left();
		void turn_right();
};


#endif // PHYSICAL_ROBOT_H