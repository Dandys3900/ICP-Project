#ifndef COLLISION_SHAPE_H
#define COLLISION_SHAPE_H


#include "../math/vector2.h"


class CollisionShape {
public: // methods
	virtual float udf(const Vector2& point);
	virtual float sdf(const Vector2& point);
};


class CollisionCircleShape : CollisionShape {
private: // fields
	Vector2 origin;
	float radius;

public: // methods
	CollisionCircleShape();
	CollisionCircleShape(const Vector2& origin, float radius);
	virtual float udf(const Vector2& point);
	virtual float sdf(const Vector2& point);
};


class CollisionRectangleShape : CollisionShape {
private: // fields
	Vector2 origin;
	Vector2 size;
	float angle;

public:
	CollisionRectangleShape();
	CollisionRectangleShape(const Vector2& origin, const Vector2& size, float angle);
	virtual float udf(const Vector2& point);
	virtual float sdf(const Vector2& point);
};


#endif
