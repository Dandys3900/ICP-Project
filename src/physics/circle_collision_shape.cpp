#include "physics/circle_collision_shape.h"


void CircleCollisionShape::set_origin(Vector2 origin) {
	// Do nothing - the origin is always center
}


Vector2 CircleCollisionShape::get_origin() const {
	return this->center;
}


void CircleCollisionShape::set_position(Vector2 position) {
	this->center = position;
}


Vector2 CircleCollisionShape::get_position() const {
	return this->center;
}


void CircleCollisionShape::set_rotation(qreal angle) {
	this->angle = angle;
	// Good luck trying to rotate circle around it's center and trying to spot a difference.
}


void CircleCollisionShape::get_rotation() const {
	return this->angle;
}


void CircleCollisionShape::scale(qreal scaling_factor) {
	this->radius = this->radius * scaling_factor;
}


void CircleCollisionShape::project_to_axis(const Vector2& axis, qreal* min, qreal* max) const {
	qreal point1_projection = Vector2::dotProduct(this->center + (axis * this->radius), axis);
	qreal point2_projection = Vector2::dotProduct(this->center - (axis * this->radius), axis);
	if (point1_projection < point2_projection) {
		*min = point1_projection;
		*max = point2_projection;
	} else {
		*min = point2_projection;
		*max = point1_projection;
	}
}


QVector<Vector2> CircleCollisionShape::get_sat_collision_normals(const CollisionShape& other_shape) const {
	// NOTE: Verify that this optimisation is actually numerically correct
	return QVector<Vector2> {
		Vector2(
			get_closest_vertex(other_shape.get_sat_collision_verticies()) - this->center
		).normalized()
	};
}


const QVector<Vector2>& CircleCollisionShape::get_sat_collision_verticies() const {
	return QVector<Vector2> {this->center};
}


const Vector2 CircleCollisionShape::get_closest_vertex(const QVector<Vector2>& verticies) const {
	quint8 closest_vertex_index = 0;
	// we just need the closest distance and not the exact one
	qreal closest_vertex_distance_squared = this->center.length_squared_to(verticies[closest_vertex_index]);

	for (quint8 i = 1; i < verticies.size(); i++) {
		qreal vertex_distance_squared = this->center.length_squared_to(verticies[i]);
		if (vertex_distance_squared > closest_vertex_distance_squared) {
			closest_vertex_distance_squared = vertex_distance_squared;
			closest_vertex_index = i;
		}
	}

	return verticies[closest_vertex_index];
}
