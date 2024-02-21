#ifndef CIRCLE_COLLISION_SHAPE_H
#define CIRCLE_COLLISION_SHAPE_H


#include "physics/collision_shape.h"
#include <QtGlobal>


class CircleCollisionShape : public CollisionShape {
	protected: // fields
		Vector2 center;
		qreal radius;

	public: // methods
		void translate(const Vector2& translation_vector) override;

		void rotate(qreal angle) override;	

		void rotate_around(qreal angle, const Vector2& pivot) override;

		void project_to_axis(const Vector2& axis, qreal* min, qreal* max) const override;

		QVector<Vector2> get_sat_collision_normals(const CollisionShape& other_shape) const override;

		const QVector<Vector2>& get_sat_collision_verticies() const override;

		/*!
		 * Returns the closes vertex from @param verticies to center of this circle.
		 */
		const Vector2 get_closest_vertex(const QVector<Vector2>& verticies) const;
};


#endif // CIRCLE_COLLISION_SHAPE_H
