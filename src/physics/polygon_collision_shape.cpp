#include "physics/polygon_collision_shape.h"


void PolygonCollisionShape::translate(const Vector2& translate_vector) {
	// Just translate all the verticies
	for (quint8 i = 0; i < this->verticies.size(); i ++) {
		this->verticies[i] = Vector2(this->verticies[i] + translate_vector);
	}
}


void PolygonCollisionShape::rotate(qreal angle) {
	// TODO
}


void PolygonCollisionShape::rotate_around(qreal angle, const Vector2& pivot) {
	// TODO
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
