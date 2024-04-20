/** ICP Project 2023/2024
 * @file polygon_collision_shape.cpp
 * @author Jakub Janšta (xjanst02)
 * @brief Handling collisions of polygon objects.
 */

#include "physics/polygon_collision_shape.h"


void PolygonCollisionShape::set_origin(Vector2 origin) {
	this->origin = origin;
}


Vector2 PolygonCollisionShape::get_origin() const {
	return this->origin;
}


void PolygonCollisionShape::set_position(Vector2 position) {
	Vector2 position_delta = Vector2(position - this->origin);
	this->origin = position;
	// Move all the verticies based on position_delta
	for (quint8 i = 0; i < this->verticies.size(); i++) {
		this->verticies[i] = Vector2(this->verticies[i] + position_delta);
	}
}


Vector2 PolygonCollisionShape::get_position() const {
	return this->origin;
}


void PolygonCollisionShape::set_rotation(qreal angle) {
	for (quint8 i = 0; i < this->verticies.size(); i++) {
		this->verticies[i] = this->verticies[i].rotated_around(this->origin, -this->angle).rotated_around(this->origin, angle);
	}
	this->angle = angle;
}


qreal PolygonCollisionShape::get_rotation() const {
	return this->angle;
}


void PolygonCollisionShape::scale(qreal scaling_factor) {
	for (quint8 i = 0; i < this->verticies.size(); i++) {
		// get vector from origin to vertex
		Vector2 origin_to_vertex = Vector2(this->verticies[i] - this->origin);
		// scale the vector by scaling_factor
		origin_to_vertex = origin_to_vertex.normalized() * (origin_to_vertex.length() * scaling_factor);
		// override the vertex with the scaled one
		this->verticies[i] = this->origin + origin_to_vertex;
	}
}


void PolygonCollisionShape::project_to_axis(const Vector2& axis, qreal* min, qreal* max) const {
	*min = qInf();
	*max = -qInf();

	for (quint8 i = 0; i < verticies.size(); i++) {
		qreal vertex_projection = Vector2::dotProduct(verticies[i], axis);
		if (vertex_projection < *min) {
			*min = vertex_projection;
		}
		if (vertex_projection > *max) {
			*max = vertex_projection;
		}
	}
}


QVector<Vector2> PolygonCollisionShape::get_sat_collision_normals(const CollisionShape& other_shape) const {
	QVector<Vector2> normals;
	// calculate normals for every edge
	for (quint8 i = 0; i < this->verticies.size(); i++) {
		normals.push_back(Vector2(this->verticies[(i + 1) % this->verticies.size()] - this->verticies[i]).normal().normalized());
	}
	return normals;
}


const QVector<Vector2>& PolygonCollisionShape::get_sat_collision_verticies() const {
	return this->verticies;
}
