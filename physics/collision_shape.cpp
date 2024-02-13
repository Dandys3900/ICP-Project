#include "collision_shape.h"

#include "../math/fancy_math.h"


CollisionCircleShape::CollisionCircleShape() {
	this->origin = Vector2(0.0f, 0.0f);
	this->radius = 0.0f;
}


CollisionCircleShape::CollisionCircleShape(const Vector2& origin, qreal radius) {
	this->origin = Vector2(origin);
	this->radius = radius;
}


qreal CollisionCircleShape::udf(const Vector2& point) {
	return maxf(0, point.distance_to(this->origin) - this->radius);
}


qreal CollisionCircleShape::sdf(const Vector2& point) {
	return point.distance_to(this->origin) - this->radius;
}


CollisionRectangleShape::CollisionRectangleShape() {
	this->origin = Vector2(0.0f, 0.0f);
	this->size = Vector2(0.0f, 0.0f);
	this->angle = 0.0f;
}


CollisionRectangleShape::CollisionRectangleShape(const Vector2& origin, const Vector2& size, qreal angle) {
	this->origin = Vector2(origin);
	this->size = Vector2(size);
	this->angle = angle;
}


qreal CollisionRectangleShape::udf(const Vector2& point) {
	// translate the point to the rectangle local space
	Vector2 local_point;// = point.rotated(-angle) - center.rotated(-angle);
	
	qreal dx = maxf(abs(local_point.x) - size.x / 2.0f, 0.0f);
	qreal dy = maxf(abs(local_point.y) - size.y / 2.0f, 0.0f);
	
	return Vector2(dx, dy).length();
}


qreal CollisionRectangleShape::sdf(const Vector2& point) {
	// translate the point to the rectangle local space
	Vector2 local_point;// = point.rotated(-angle) - this->origin.rotated(-angle);
	
	qreal dx = abs(local_point.x) - this->size.x / 2.0f;
	qreal dy = abs(local_point.y) - this->size.y / 2.0f;
	qreal dx_max = maxf(0, dx);
	qreal dy_max = maxf(0, dy);

	return minf(maxf(dx, dy), 0.0) + Vector2(dx_max, dy_max).length();
}
