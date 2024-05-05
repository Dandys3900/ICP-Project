/** ICP Project 2023/2024
 * @file circle_collision_shape.h
 * @author Jakub Janšta (xjanst02)
 * @brief Header file for CircleCollisionShape class.
 */

#ifndef CIRCLE_COLLISION_SHAPE_H
#define CIRCLE_COLLISION_SHAPE_H


#include "physics/collision_shapes/collision_shape.h"
#include <QtGlobal>


class CircleCollisionShape : public CollisionShape {
	protected: // Fields
		Vector2 center;
		qreal radius;

	public: // Methods
		/**
         * @brief Constructor.
         * @param position Initial position of circle shape.
         * @param radius Initial radius angle of circle shape.
         */
		CircleCollisionShape(Vector2 position, qreal radius) {
			this->center = position;
			this->radius = radius;
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

		QVector<Vector2> get_sat_collision_verticies() const override;

		/**
         * @brief Returns the closest vertex from @param verticies to center of this circle.
         * @param verticies Vector containing verticies where the closest vertex is to be found.
		 * @return Closest vertex from given vector.
         */
		const Vector2 get_closest_vertex(const QVector<Vector2>& verticies) const;

		/**
         * @brief Setter for shape radius.
		 * @param radius New value to be set.
         */
		virtual void set_radius(qreal radius);
		/**
         * @brief Getter for shape current radius.
         * @return Current radius of the shape.
         */
		virtual qreal get_radius() const;
};


#endif // CIRCLE_COLLISION_SHAPE_H
