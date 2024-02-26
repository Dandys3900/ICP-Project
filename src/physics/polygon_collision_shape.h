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
		
		/*!
		 * Polyon's imaginary origin around which is everything scaled and rotated.
		 * If not set, the first vertex is used as origin.
		 */
		Vector2 origin;

	public: // methods
		virtual void set_origin(Vector2 origin) override;
		
		virtual Vector2 get_origin() const override;

		virtual void set_position(Vector2 position) override;

		virtual Vector2 get_position() const override;

		virtual void set_rotation(qreal angle) override;

		virtual qreal get_rotation() const override;

		virtual void scale(qreal scaling_factor) override;

		void project_to_axis(const Vector2& axis, qreal* min, qreal* max) const override;

		QVector<Vector2> get_sat_collision_normals(const CollisionShape& other_shape) const override;

		const QVector<Vector2>& get_sat_collision_verticies() const override;
};


#endif // POLYGON_COLLISION_SHAPE_H
