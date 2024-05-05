/** ICP Project 2023/2024
 * @file rectangle_collision_shape.cpp
 * @author Jakub Janšta (xjanst02)
 * @brief Handling collisions of rectangular objects.
 */

#include "physics/collision_shapes/rectangle_collision_shape.h"


void RectangeCollisionShape::resize(const Vector2& size) {
	Vector2 old_origin = this->origin;
	qreal old_angle = this->angle;

	this->origin = Vector2(); // Reset origin to (0,0)
	this->angle = 0; // Reset angle to 0

	// Create the new rect
	QPointF half_size = size / 2;
	this->verticies[0] = Vector2(this->origin.x() - half_size.x(), this->origin.y() - half_size.y());
	this->verticies[1] = Vector2(this->origin.x() + half_size.x(), this->origin.y() - half_size.y());
	this->verticies[2] = Vector2(this->origin.x() + half_size.x(), this->origin.y() + half_size.y());
	this->verticies[3] = Vector2(this->origin.x() - half_size.x(), this->origin.y() + half_size.y());

	this->set_rotation(old_angle); // Rotate the new rect
	this->set_position(old_origin); // Move the new rect
}


QVector<Vector2> RectangeCollisionShape::get_sat_collision_normals(const CollisionShape& other_shape) const {
	return QVector<Vector2> {
		Vector2(this->verticies[1] - this->verticies[0]).normalized(),
		Vector2(this->verticies[2] - this->verticies[1]).normalized()
	};
}
