#ifndef COLLISION_SHAPE_H
#define COLLISION_SHAPE_H


#include "vector2.h"


class CollisionCircleShape;
class CollisionRectangleShape;


class CollisionShape {
public: // methods
	virtual bool is_colliding_with_circle(const CollisionCircleShape& circ) const {
		return false;
	}
	virtual bool is_colliding_with_rectangle(const CollisionRectangleShape& rect) const {
		return false;
	}
};


class CollisionCircleShape : CollisionShape {
public: // fields
	Vector2 origin; // top-left corner of the circles bounding box (Why, Qt why?)
	qreal radius;

public: // methods
	CollisionCircleShape();
	CollisionCircleShape(const Vector2& origin, qreal radius);

	// virtual ~CollisionCircleShape();

	bool is_colliding_with_circle(const CollisionCircleShape& circ) const override;
	bool is_colliding_with_rectangle(const CollisionRectangleShape& rect) const override;
};


class CollisionRectangleShape : CollisionShape {
public: // fields
	Vector2 origin; // top-left corner
	Vector2 size;
	qreal angle;

public:
	CollisionRectangleShape();
	CollisionRectangleShape(const Vector2& origin, const Vector2& size, qreal angle);

	// virtual ~CollisionRectangleShape();

	bool is_colliding_with_circle(const CollisionCircleShape& circ) const override;
	bool is_colliding_with_rectangle(const CollisionRectangleShape& rect) const override;
};


#endif
