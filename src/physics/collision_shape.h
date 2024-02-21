#ifndef COLLISION_SHAPE_H
#define COLLISION_SHAPE_H


#include "math/vector2.h"
#include <QVector>


/*!
 * Base for all CollisionShapes. This class cpecifies the uniform interface for collision shapes and cannot be used directly.
 */
class CollisionShape {
	public: // methods
		/*!
		 * Translates the polygon's verticies by the @param translation_vector.
		 * This DOES NOT take rotation into account and will translate the verticies as they are in global coordinates.
		 * @note each subclass has to implement this method to it's own specific needs.
		 */
		virtual void translate(const Vector2& translation_vector) = 0;

		/*!
		 *
		 */
		virtual void rotate(qreal angle) = 0;

		/*!
		 *
		 */		
		virtual void rotate_around(const Vector2& pivot, qreal angle) = 0;

		/*!
		 * Checks if this shape is colliding with @param other_shape. This method accepts any other CollisionShape regardless of it's implementation.
		 */
		bool is_colliding_with(const CollisionShape& other_shape);

		/*!
		 * Projects a CollisionShape to given @param axis and returns it's "shadow" by @param min and @param max on the @param axis.
		 * @note if used on an invalid (empty) polygon, min will be set to infinity and max to -infinity.
		 * @note each subclass has to implement this method to it's own specific needs.
		 */
		virtual void project_to_axis(const Vector2& axis, qreal* min, qreal* max) const = 0;

		/*!
		 * Returns QVector of Vector2s containing outward pointing normalized normals for all the polygon's edges used for SAT collision.
		 * @note The normals might not be the true representation of the shape. For instance circle has infinite normals, but will return just relevat one.
		 * @note each subclass has to implement this method to it's own specific needs.
		 */
		virtual QVector<Vector2> get_sat_collision_normals(const CollisionShape& other_shape) const = 0;

		/*!
		 * Returns QVector of verticies, that take part in the SAT collision detection.
		 * @note The normals might not be the true representation of the shape. For instance circle has infinite verticies, but is represented by it's center.
		 * @note each subclass has to implement this method to it's own specific needs.
		 */
		virtual const QVector<Vector2>& get_sat_collision_verticies() const = 0;

};


#endif
