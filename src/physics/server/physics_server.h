/** ICP Project 2023/2024
 * @file physics_server.h
 * @author Jakub Janšta (xjanst02)
 * @brief Header file for PhysicsServer class.
 */

#ifndef PHYSICS_SERVER_H
#define PHYSICS_SERVER_H


#include "physics/collision_shapes/collision_shape.h"
#include "physics/collision_shapes/rectangle_collision_shape.h"
#include "physics/collision_shapes/circle_collision_shape.h"
#include "physics/collision_shapes/polygon_collision_shape.h"

#include "math/vector2.h"

#include <QVector>


/*!
 * PhysicsServer class. This this class is responsible managing CollisionShape instances and their physics simulation.
 */
class PhysicsServer {
	protected: // fields
		/*!
		 * Used for playground boundaries, that cannot be passed trough. Must be changed everytime the playground is resized
		 */
		QVector<CollisionShape> playground_boundary_shapes = [];
		/*!
		 * Used for static objects like obstacles. During simulation static shapes cannot be moved.
		 */
		QVector<CollisionShape> static_shapes = [];
		/*!
		 * used for dynamic objects like robots. During simulation they interact with every other shape.
		 */
		QVector<CollisionShape> dynamic_shapes = [];
}


#endif // PHYSICS_SERVER_H