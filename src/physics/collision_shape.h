/** ICP Project 2023/2024
 * @file collision_shape.h
 * @author Jakub Janšta (xjanst02)
 * @brief Header file for CollisionShape base class.
 */

#ifndef COLLISION_SHAPE_H
#define COLLISION_SHAPE_H


#include "math/vector2.h"
#include <QVector>


/*!
 * Base for all CollisionShapes. This class specifies the uniform interface for collision shapes and cannot be used directly.
 */
class CollisionShape {
	protected: // fields
		/*!
		 * The shape's current rotation angle in radians.
		 */
		qreal angle = 0.0;

	public: // methods
		/*!
		 * Sets the shape's "origin" to the @param origin.
		 * This will not move the shape, but rather just move the origin that the whole shape moves around.
		 */
		virtual void set_origin(Vector2 origin) = 0;

		/*!
		 * Returns the shape's "origin".
		 */
		virtual Vector2 get_origin() const = 0;

		/*!
		 * Translates the shape's "origin" to the @param position and updates it's verticies relative to it. Also @see get_position()
		 * This DOES NOT take rotation into account and will translate the verticies as they are in global coordinates.
		 */
		virtual void set_position(Vector2 position) = 0;

		/*!
		 * Returns the shape's position. Also @see set_position()
		 */
		virtual Vector2 get_position() const = 0;

		/*!
		 * Rotates the shape around the shape's "origin" by @param angle.  Also @see get_rotation()
		 */
		virtual void set_rotation(qreal angle) = 0;

		/*!
		 * Returns the shape's rotation. Also @see set_rotation()
		 */
		virtual qreal get_rotation() const = 0;

		/*!
		 * Scales the shape around the shape's "origin" by and @param scaling_factor.
		 * The current scale will always be seen as 1, so if you want to scale the object to 1.5x it's scale, you would use scale(1.5)
		 * scale(0.5) - scale to 50% original size - 50% off the current size
		 * scale(0.5) - scale to 25% original size - 50% off the current size
		 */
		virtual void scale(qreal scaling_factor) = 0;

		/*!
		 * Projects a CollisionShape to given @param axis and returns it's "shadow" by @param min and @param max on the @param axis.
		 * @note if used on an invalid shape, min will be set to infinity and max to -infinity.
		 */
		virtual void project_to_axis(const Vector2& axis, qreal* min, qreal* max) const = 0;

		/*!
		 * Returns QVector of Vector2s containing outward pointing normalized normals for all the polygon's edges used for SAT collision.
		 * @note The normals might not be the true representation of the shape. For instance circle has infinite normals, but will return just relevat one.
		 */
		virtual QVector<Vector2> get_sat_collision_normals(const CollisionShape& other_shape) const = 0;

		/*!
		 * Returns QVector of verticies, that take part in the SAT collision detection.
		 * @note The verticies might not be the true representation of the shape. For instance circle has infinite verticies, but is represented by it's center.
		 */
		virtual const QVector<Vector2>& get_sat_collision_verticies() const = 0;

		/*!
		 * Checks if this shape is colliding with @param other_shape. This method accepts any other CollisionShape regardless of it's implementation.
		 */
		bool is_colliding_with(const CollisionShape& other_shape);
};


#endif
