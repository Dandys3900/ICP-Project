#include "collision_shape.h"

/*
SAT collision detection (Separating Axis Theorem)
*/

// SAT colllision
// bool CollisionShape::is_colliding(const CollisionShape& other_shape) const {}


// QVector<Vector2> CollisionShape::get_normals(const QVector<Vector2>& verticies) {
// 	QVector<Vector2> normals;

// 	// calculate normals for every edge
// 	for (quint8 i = 0; i < verticies.size(); i++) {
// 		normals.push_back(Vector2(verticies[(i + 1) % verticies.size()] - verticies[i]).normal().normalized());
// 	}
	
// 	return normals;
// }


// TODO
// get closest point to the circle origin and use vector between the two as a normal
// https://www.youtube.com/watch?v=59BTXB-kFNs
// Vector2 CollisionShape::get_circle_normal(const Vector2& circle_center, const QVector<Vector2>& other_shape_verticies) {
// 	quint8 closest_vertex_index = 0;
// 	// we just need the closest distance and not the exact one
// 	qreal closest_vertex_distance_squared = circle_center.length_squared_to(other_shape_verticies[closest_vertex_index]);

// 	// got trough all the verticies and find the closest one
// 	for (quint8 i = 1; i < other_shape_verticies.size(); i++) {
// 		qreal vertex_distance_squared = circle_center.length_squared_to(other_shape_verticies[i]);

// 		if (vertex_distance_squared > closest_vertex_distance_squared) {
// 			closest_vertex_distance_squared = vertex_distance_squared;
// 			closest_vertex_index = i;
// 		}
// 	}

// 	// use the vector between the circle center and the closest vertex as the circles sole normal
// 	return Vector2(other_shape_verticies[closest_vertex_index] - circle_center);
// }


// void CollisionShape::project_verticies_to_axis(const QVector<Vector2>& verticies, const Vector2& axis, qreal* min, qreal* max) {
// 	qreal vertex_projection = Vector2::dotProduct(verticies[0], axis);
// 	*min = vertex_projection;
// 	*max = vertex_projection;

// 	for (quint8 i = 1; i < verticies.size(); i++) {
// 		vertex_projection = Vector2::dotProduct(verticies[i], axis);
// 		if (vertex_projection < *min) {
// 			*min = vertex_projection;
// 		}
// 		if (vertex_projection > *max) {
// 			*max = vertex_projection;
// 		}
// 	}
// }






bool is_colliding_with(const CollisionShape& other_shape) {
	
}








// CollisionCircleShape::CollisionCircleShape() {
// 	this->origin = Vector2();
// 	this->radius = 0.0;
// }


// CollisionCircleShape::CollisionCircleShape(const Vector2& origin, qreal radius) {
// 	this->origin = Vector2(origin);
// 	this->radius = radius;
// }


// // super advanced patented collision algorithm
// bool CollisionCircleShape::is_colliding_with_circle(const CollisionCircleShape& circ) const {
// 	return Vector2(this->origin + QPointF(this->radius, this->radius)).length_to(circ.origin + QPointF(circ.radius, circ.radius)) <= (this->radius + circ.radius);
// }


// bool CollisionCircleShape::is_colliding_with_rectangle(const CollisionRectangleShape& rect) const {
// 	// Rotate circles origin into rectangle local coordinates
// 	Vector2 local_circle_origin = this->origin.rotated(-rect.angle) - rect.origin.rotated(-rect.angle);
// 	// Closest point in the rectangle to the center of circle rotated backwards(unrotated)
// 	Vector2 closest_point = Vector2(local_circle_origin);
	
// 	// Find the closest local X coordinate on the rect to the circle origin
// 	if (local_circle_origin.x() < rect.origin.x()) {
// 		closest_point.setX(rect.origin.x());
// 	} else if (local_circle_origin.x() > rect.origin.x() + rect.size.x()) {
// 		closest_point.setX(rect.origin.x() + rect.size.x());
// 	}
// 	// Find the closest local Y coordinate on the rect to the circle origin
// 	if (local_circle_origin.y() < rect.origin.y()) {
// 		closest_point.setY(rect.origin.y());
// 	} else if (local_circle_origin.y() > rect.origin.y() + rect.size.y()) {
// 		closest_point.setY(rect.origin.y() + rect.size.y());
// 	}

// 	// Check if the circle center is closer to the closest point than circle radius
// 	return local_circle_origin.length_to(closest_point) < this->radius;
// }


// CollisionRectangleShape::CollisionRectangleShape() {
// 	this->origin = Vector2();
// 	this->size = Vector2();
// 	this->angle = 0.0;
// }


// CollisionRectangleShape::CollisionRectangleShape(const Vector2& origin, const Vector2& size, qreal angle) {
// 	this->origin = Vector2(origin);
// 	this->size = Vector2(size);
// 	this->angle = angle;
// }


// // even better and super ultra patented collision detection algorithm
// bool CollisionRectangleShape::is_colliding_with_circle(const CollisionCircleShape& circ) const {
// 	return circ.is_colliding_with_rectangle(*this);
// }


// bool CollisionRectangleShape::is_colliding_with_rectangle(const CollisionRectangleShape& rect) const {
// 	QVector<QLineF> axes = rect.get_axes();
// 	QVector<Vector2> corners = this->get_corners();

	




// 	return false;
// }


// Vector2 CollisionRectangleShape::get_center() {
// 	return this->origin + (this->size / 2);
// }


// QVector<QLineF> CollisionRectangleShape::get_axes() {
// 	Vector2 center = Vector2(this->origin + (this->size / 2)).rotated(this->angle);
// 	Vector2 x_direction = Vector2(1.0, 0.0).rotated(this->angle);
// 	Vector2 y_direction = Vector2(0.0, 1.0).rotated(this->angle);
	
// 	return QVector<QLineF> {
// 		QLineF(center, center + x_direction), // x asix
// 		QLineF(center, center + y_direction) // y axis
// 	};
// }


// QVector<Vector2> CollisionRectangleShape::get_corners() {
// 	QVector<QLineF> axes = this->get_axes();
// 	Vector2 center = this->get_center();
// 	Vector2 x_from_center = Vector2(axes[0].p2() - axes[0].p1()).normalized() * (this->size.x() / 2);
// 	Vector2 y_from_center = Vector2(axes[1].p2() - axes[0].p1()).normalized() * (this->size.y() / 2);

// 	return QVector<Vector2> {
// 		center + x_from_center + y_from_center,
// 		center + x_from_center - y_from_center,
// 		center - x_from_center + y_from_center,
// 		center - x_from_center - y_from_center
// 	};
// }