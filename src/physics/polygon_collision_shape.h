#ifndef POLYGON_COLLISION_SHAPE_H
#define POLYGON_COLLISION_SHAPE_H


#include "physics/collision_shape.h"


class PolygonCollisionShape : public CollisionShape {
	protected: // fields
		/*!
		 * QVector of plygon's verticies in CLOCKWISE direction in GLOBAL coordinates.
		 * The first and last verticies will be connected to form a closing edge of the polygon.
		 * A valid polygon is guaranteed to have between 3 and 256 (inclusive) verticies.
		 * An invalid polygon is represended with not verticies.
		 */
		QVector<Vector2> verticies; // Should not be handled ONLY by provided methods

	public: // methods
		void translate(const Vector2& translation_vector) override;

		void rotate_around(const QPointF& pivot, qreal angle) override;

		void project_to_axis(const Vector2& axis, qreal* min, qreal* max) const override;

		QVector<Vector2> get_sat_collision_normals(const CollisionShape& other_shape) const override;

		const QVector<Vector2>& get_sat_collision_verticies() const override;
};


#endif // POLYGON_COLLISION_SHAPE_H
