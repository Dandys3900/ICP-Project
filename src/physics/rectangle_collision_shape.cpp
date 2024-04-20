/** ICP Project 2023/2024
 * @file rectangle_collision_shape.cpp
 * @author Jakub Janšta (xjanst02)
 * @brief Handling collisions of rectangular objects.
 */

#include "physics/rectangle_collision_shape.h"


QVector<Vector2> RectangeCollisionShape::get_sat_collision_normals(const CollisionShape& other_shape) const {
	return QVector<Vector2> {
		Vector2(this->verticies[1] - this->verticies[0]).normalized(),
		Vector2(this->verticies[2] - this->verticies[1]).normalized()
	};
}
