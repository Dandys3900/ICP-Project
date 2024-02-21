#include "physics/circle_collision_shape.h"


void CircleCollisionShape::translate(const Vector2& translation_vector) {
	this->center = Vector2(this->center + translation_vector);
}


void CircleCollisionShape::rotate(qreal angle) {
	// Good luck rotatin a circle around it's center and trying to spot a difference
}


void CircleCollisionShape::rotate_around(qreal angle, const Vector2& pivot) {
	
}


void CircleCollisionShape::project_to_axis(const Vector2& axis, qreal* min, qreal* max) const {
	qreal center_projection = Vector2::dotProduct(this->center, axis);
	*min = center_projection - this->radius;
	*max = center_projection + this->radius;
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
