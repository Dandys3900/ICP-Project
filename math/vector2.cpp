#include "vector2.h"

#include "fancy_math.h"


Vector2::Vector2() {
	this->x = 0.0f;
	this->y = 0.0f;
}


Vector2::Vector2(float x, float y) {
	this->x = x;
	this->y = y;
}


Vector2::Vector2(const Vector2& v) {
	this->x = v.x;
	this->y = v.y;
}


void Vector2::normalize() {
	float length = this->x * this->x + this->y * this->y;
	if (length != 0) {
		length = sqrt(length);
		this->x /= length;
		this->y /= length;
	}
}


Vector2 Vector2::normalized() const {
	Vector2 v = Vector2(*this);
	v.normalize();
	return v;
}


float Vector2::cross(const Vector2& v) const {
	return this->x * v.y - this->y * v.x;
}


float Vector2::dot(const Vector2& v) const {
	return this->x * v.x + this->y * v.y;
}


float Vector2::length() const {
	return sqrt(this->x * this->x + this->y * this->y);
}


float Vector2::length_squared() const {
	return this->x * this->x + this->y * this->y;
}


float Vector2::angle() const {
	return atan2(this->y, this->x);
}


float Vector2::distance_to(const Vector2& v) const {
	return sqrt((this->x - v.x) * (this->x - v.x) + (this->y - v.y) * (this->y - v.y));
}


float Vector2::distance_squared_to(const Vector2& v) const {
	return (this->x - v.x) * (this->x - v.x) + (this->y - v.y) * (this->y - v.y);
}


float Vector2::angle_to(const Vector2& v) const {
	return atan2(cross(v), dot(v));
}
