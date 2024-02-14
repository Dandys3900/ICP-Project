#include "collision_shape.h"


CollisionCircleShape::CollisionCircleShape() {
	this->origin = Vector2();
	this->radius = 0.0f;
}


CollisionCircleShape::CollisionCircleShape(const Vector2& origin, qreal radius) {
	this->origin = Vector2(origin);
	this->radius = radius;
}


// super advanced patented collision algorithm
bool CollisionCircleShape::is_colliding_with_circle(const CollisionCircleShape& circ) const {
	return Vector2(this->origin + QPointF(this->radius, this->radius)).length_to(circ.origin + QPointF(circ.radius, circ.radius)) <= (this->radius + circ.radius);
}


bool CollisionCircleShape::is_colliding_with_rectangle(const CollisionRectangleShape& rect) const {
	// Rotate circles origin into rectangle local coordinates
	Vector2 local_circle_origin = this->origin.rotated(-rect.angle) - rect.origin.rotated(-rect.angle);
	// Closest point in the rectangle to the center of circle rotated backwards(unrotated)
	Vector2 closest_point = Vector2(local_circle_origin);
	
	// Find the closest local X coordinate on the rect to the circle origin
	if (local_circle_origin.x() < rect.origin.x()) {
		closest_point.setX(rect.origin.x());
	} else if (local_circle_origin.x() > rect.origin.x() + rect.size.x()) {
		closest_point.setX(rect.origin.x() + rect.size.x());
	}
	// Find the closest local Y coordinate on the rect to the circle origin
	if (local_circle_origin.y() < rect.origin.y()) {
		closest_point.setY(rect.origin.y());
	} else if (local_circle_origin.y() > rect.origin.y() + rect.size.y()) {
		closest_point.setY(rect.origin.y() + rect.size.y());
	}

	// Check if the circle center is closer to the closest point than circle radius
	return local_circle_origin.length_to(closest_point) < this->radius;
}


CollisionRectangleShape::CollisionRectangleShape() {
	this->origin = Vector2();
	this->size = Vector2();
	this->angle = 0.0f;
}


CollisionRectangleShape::CollisionRectangleShape(const Vector2& origin, const Vector2& size, qreal angle) {
	this->origin = Vector2(origin);
	this->size = Vector2(size);
	this->angle = angle;
}


bool CollisionRectangleShape::is_colliding_with_circle(const CollisionCircleShape& circ) const {
	return false;
}


bool CollisionRectangleShape::is_colliding_with_rectangle(const CollisionRectangleShape& rect) const {
	return false;
}