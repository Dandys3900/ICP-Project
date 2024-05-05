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


/**
 * PhysicsServer class. This this class is responsible managing CollisionShape instances and their physics simulation.
 */
class PhysicsServer {
	protected: // Fields
		bool is_step_queued = false;
		/**
		 * Used for playground boundaries, that cannot be passed trough. Must be changed everytime the playground is resized.
		 */
		QVector<const CollisionShape*> playground_boundary_obstacle_shapes = {};
		/**
		 * Used for Obstacles. During simulation Obstacles cannot be moved.
		 */
		QVector<PhysicalObstacle*> obstacles = {};
		/**
		 * Used for Robots. During simulation they interact with every other shape.
		 */
		QVector<PhysicalRobot*> robots = {};


	public: // Methods
		/**
         * @brief Constructor.
         */
		PhysicsServer();
		/**
         * @brief Destructor.
         */
		~PhysicsServer();

		/**
		 * @brief Executes a physics step if queued. See queue_step().
		 */
		void step();
		/**
		 * @brief Queues a step.
		 */
		void queue_step();
		/**
		 * @brief Forces a step to be executed.
		 * @param clean_step_queue If true, clears the step queue after execution.
		 */
		void force_step(bool clean_step_queue = true);

		/**
		 * @brief Registers a (physical) robot.
		 * @param robot Robot to be registered.
		 */
		void register_robot(PhysicalRobot* robot);
		/**
		 * @brief Unregisters a (physical) robot (if already registered).
		 * @param robot Robot to be unregistered.
		 */
		void unregister_robot(PhysicalRobot* robot);
		/**
		 * @brief Registers a (physical) obstacle.
		 * @param robot Obstacle to be registered.
		 */
		void register_obstacle(PhysicalObstacle* obstacle);
		/**
		 * @brief Unregisters a (physical) obstacle (if already registered).
		 * @param robot Obstacle to be unregistered.
		 */
		void unregister_obstacle(PhysicalObstacle* obstacle);
		/**
		 * @brief Registers scene (playground) boundaries.
		 * @param playground_size Vector representing current size of the scene (playground).
		 */
		void register_boundaries(Vector2 playground_size);
		/**
		 * @brief Unregisters scene (playground) boundaries.
		 */
		void unregister_boundaries();
};


#endif // PHYSICS_SERVER_H
