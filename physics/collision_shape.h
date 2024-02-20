#ifndef COLLISION_SHAPE_H
#define COLLISION_SHAPE_H


#include <vector>
#include <QLineF>
#include "vector2.h"


// forward declarations
// class CollisionCircleShape;
// class CollisionRectangleShape;


class CollisionShape {
	public: // methods





		// virtual bool is_colliding_with_circle(const CollisionCircleShape& circ) const {
		// 	return false;
		// }
		// virtual bool is_colliding_with_rectangle(const CollisionRectangleShape& rect) const {
		// 	return false;
		// }
		// bool is_colliding(const CollisionShape& other_shape) const;




	// protected:
		// std::vector<Vector2> verticies; // clockwise vecticies in global coordinates (max 256 verticies)
	
	protected:
		static std::vector<Vector2> get_normals(const std::vector<Vector2>& verticies);
		static Vector2 get_circle_normal(const Vector2& circle_center, const std::vector<Vector2>& other_shape_verticies);

		static void project_verticies_to_axis(const std::vector<Vector2>& verticies, const Vector2& axis, qreal* min, qreal* max);
};


// class CollisionCircleShape : CollisionShape {
// 	public: // fields
// 		Vector2 origin; // top-left corner of the circle's bounding box (Why, Qt why?)
// 		qreal radius;

// 	public: // methods
// 		CollisionCircleShape();
// 		CollisionCircleShape(const Vector2& origin, qreal radius);

// 		bool is_colliding_with_circle(const CollisionCircleShape& circ) const override;
// 		bool is_colliding_with_rectangle(const CollisionRectangleShape& rect) const override;
// };


// class CollisionRectangleShape : CollisionShape {
// 	public: // fields
// 		Vector2 origin; // top-left corner
// 		Vector2 size;
// 		qreal angle;

// 	public: // methods
// 		CollisionRectangleShape();
// 		CollisionRectangleShape(const Vector2& origin, const Vector2& size, qreal angle);

// 		bool is_colliding_with_circle(const CollisionCircleShape& circ) const override;
// 		bool is_colliding_with_rectangle(const CollisionRectangleShape& rect) const override;

// 	private: // methods
// 		Vector2 get_center();
// 		std::vector<QLineF> get_axes();
// 		std::vector<Vector2> get_corners();
// };


#endif
