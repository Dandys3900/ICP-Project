/** ICP Project 2023/2024
 * @file rectangle_collision_shape.cpp
 * @author Jakub Janšta (xjanst02)
 * @brief Handling collisions of rectangular objects.
 */

#include "physics/collision_shapes/rectangle_collision_shape.h"


void RectangeCollisionShape::resize(const Vector2& size) {
	QPointF half_size = size / 2;

	this->verticies[0] = Vector2(this->origin.x() - half_size.x(), this->origin.y() - half_size.y());
	this->verticies[1] = Vector2(this->origin.x() + half_size.x(), this->origin.y() - half_size.y());
	this->verticies[2] = Vector2(this->origin.x() + half_size.x(), this->origin.y() + half_size.y());
	this->verticies[3] = Vector2(this->origin.x() - half_size.x(), this->origin.y() + half_size.y());
}


QVector<Vector2> RectangeCollisionShape::get_sat_collision_normals(const CollisionShape& other_shape) const {
	return QVector<Vector2> {
		Vector2(this->verticies[1] - this->verticies[0]).normalized(),
		Vector2(this->verticies[2] - this->verticies[1]).normalized()
	};
}
