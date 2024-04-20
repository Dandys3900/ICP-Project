/** ICP Project 2023/2024
 * @file polygon_collision_shape.h
 * @author Jakub Janšta (xjanst02)
 * @brief Header file for PolygonCollisionShape class.
 */

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
		PolygonCollisionShape(QVector<Vector2> verticies) {
			int size = verticies.size();
			if (size < 3) {
				throw std::invalid_argument("'verticies' must include at least 3 elements.");
			}
			if (size > 256) {
				throw std::invalid_argument("'verticies' must include at most 256 elements.");
			}

			this->verticies = verticies;
			this->origin = verticies[0];
		}

		PolygonCollisionShape(QVector<Vector2> verticies, Vector2 origin) : PolygonCollisionShape(verticies) {
			this->origin = origin;
		}

		PolygonCollisionShape(QVector<Vector2> verticies, Vector2 origin, Vector2 position) : PolygonCollisionShape(verticies, origin) {
			this->set_position(position);
		}

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

	protected:
		// Do nothing constructor for use in derived classes
		PolygonCollisionShape(){}
};


#endif // POLYGON_COLLISION_SHAPE_H
