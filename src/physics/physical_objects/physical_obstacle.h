/** ICP Project 2023/2024
 * @file physical_obstacle.h
 * @author Jakub Janšta (xjanst02)
 * @brief Header file for PhysicalObstacle class.
 */

#ifndef PHYSICAL_OBSTACLE_H
#define PHYSICAL_OBSTACLE_H


#include <QtGlobal>

#include "math/vector2.h"

#include "scene/obstacle.h"

#include "physics/collision_shapes/rectangle_collision_shape.h"


class Obstacle;


/*!
 * Obstacle representaion for the PhysicsServer
 */
class PhysicalObstacle {
	protected: // fields
		Obstacle* obstacle = nullptr;
		RectangeCollisionShape* shape = nullptr;

	public: // methods
		PhysicalObstacle(Obstacle* obstacle);
		~PhysicalObstacle();

		void update_shape();
};


#endif // PHYSICAL_OBSTACLE_H
