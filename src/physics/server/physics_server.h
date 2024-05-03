/** ICP Project 2023/2024
 * @file physics_server.h
 * @author Jakub Janšta (xjanst02)
 * @brief Header file for PhysicsServer class.
 */

#ifndef PHYSICS_SERVER_H
#define PHYSICS_SERVER_H


#include <QVector>

#include "math/vector2.h"

#include "physics/collision_shapes/collision_shape.h"
#include "physics/collision_shapes/rectangle_collision_shape.h"
#include "physics/collision_shapes/circle_collision_shape.h"
#include "physics/collision_shapes/polygon_collision_shape.h"

#include "physics/physical_objects/physical_robot.h"
#include "physics/physical_objects/physical_obstacle.h"


class PhysicalObstacle;
class PhysicalRobot;


/*!
 * PhysicsServer class. This this class is responsible managing CollisionShape instances and their physics simulation.
 */
class PhysicsServer {
	protected: // fields
		bool is_step_queued = false;
		/*!
		 * Used for playground boundaries, that cannot be passed trough. Must be changed everytime the playground is resized.
		 */
		QVector<PhysicalObstacle*> playground_boundary_obstacles = {};
		/*!
		 * Used for Obstacles. During simulation Obstacles cannot be moved.
		 */
		QVector<PhysicalObstacle*> obstacles = {};
		/*!
		 * Used for Robots. During simulation they interact with every other shape.
		 */
		QVector<PhysicalRobot*> robots = {};
	

	public: // methods
		PhysicsServer();
		~PhysicsServer();

		void step();
		void queue_step();
		void force_step(bool clean_step_queue = true);

		void register_robot(PhysicalRobot* robot);
		void unregister_robot(PhysicalRobot* robot);
		void register_obstacle(PhysicalObstacle* obstacle);
		void unregister_obstacle(PhysicalObstacle* obstacle);

};


#endif // PHYSICS_SERVER_H
