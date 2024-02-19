#include "collision_shape.h"

/*
SAT collision detection (Separating Axis Theorem)
*/


CollisionCircleShape::CollisionCircleShape() {
	this->origin = Vector2();
	this->radius = 0.0;
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
	this->angle = 0.0;
}


CollisionRectangleShape::CollisionRectangleShape(const Vector2& origin, const Vector2& size, qreal angle) {
	this->origin = Vector2(origin);
	this->size = Vector2(size);
	this->angle = angle;
}


// even better and super ultra patented collision detection algorithm
bool CollisionRectangleShape::is_colliding_with_circle(const CollisionCircleShape& circ) const {
	return circ.is_colliding_with_rectangle(*this);
}


bool CollisionRectangleShape::is_colliding_with_rectangle(const CollisionRectangleShape& rect) const {
	std::vector<QLineF> axes = rect.get_axes();
	std::vector<Vector2> corners = this->get_corners();

	




	return false;
}


Vector2 CollisionRectangleShape::get_center() {
	return this->origin + (this->size / 2);
}


std::vector<QLineF> CollisionRectangleShape::get_axes() {
	Vector2 center = Vector2(this->origin + (this->size / 2)).rotated(this->angle);
	Vector2 x_direction = Vector2(1.0, 0.0).rotated(this->angle);
	Vector2 y_direction = Vector2(0.0, 1.0).rotated(this->angle);
	
	return std::vector<QLineF> {
		QLineF(center, center + x_direction), // x asix
		QLineF(center, center + y_direction) // y axis
	};
}


std::vector<Vector2> CollisionRectangleShape::get_corners() {
	std::vector<QLineF> axes = this->get_axes();
	Vector2 center = this->get_center();
	Vector2 x_from_center = Vector2(axes[0].p2() - axes[0].p1()).normalized() * (this->size.x() / 2);
	Vector2 y_from_center = Vector2(axes[1].p2() - axes[0].p1()).normalized() * (this->size.y() / 2);

	return std::vector<Vector2> {
		center + x_from_center + y_from_center,
		center + x_from_center - y_from_center,
		center - x_from_center + y_from_center,
		center - x_from_center - y_from_center
	};
}