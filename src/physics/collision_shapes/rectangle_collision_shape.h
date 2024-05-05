/** ICP Project 2023/2024
 * @file rectangle_collision_shape.h
 * @author Jakub Janšta (xjanst02)
 * @brief Header file for RectangeCollisionShape class.
 */

#ifndef RECTANGLE_COLLISION_SHAPE_H
#define RECTANGLE_COLLISION_SHAPE_H


#include "physics/collision_shapes/polygon_collision_shape.h"


class RectangeCollisionShape : public PolygonCollisionShape {
	public:
		/**
         * @brief Constructor.
         * @param size Initial size of rectangle shape.
         */
		RectangeCollisionShape(const Vector2& size) : PolygonCollisionShape() {
			this->origin = Vector2();
			QPointF half_size = size / 2;

			this->verticies.resize(4);
			this->verticies[0] = Vector2(this->origin.x() - half_size.x(), this->origin.y() - half_size.y());
			this->verticies[1] = Vector2(this->origin.x() + half_size.x(), this->origin.y() - half_size.y());
			this->verticies[2] = Vector2(this->origin.x() + half_size.x(), this->origin.y() + half_size.y());
			this->verticies[3] = Vector2(this->origin.x() - half_size.x(), this->origin.y() + half_size.y());
		}
		/**
         * @brief Constructor.
         * @param size Initial size of rectangle shape.
		 * @param position Initial shape position.
         */
		RectangeCollisionShape(const Vector2& size, Vector2 position) : RectangeCollisionShape(size) {
			this->set_position(position);
		}

		/**
         * @brief Resizes rectangle shape to new value.
         * @param size Value the rectangle will be resized to.
         */
		void resize(const Vector2& size);

		/**
		 * A rectangle has two pairs of parallel edges, so just getting one of them is sufficient.
		 * Parallel lines in SAT collisions come to identical results.
		 * This is just a small optimisation and every RectangeCollisionShape should behave identically to PolygonCollisionShape;
		 */
		QVector<Vector2> get_sat_collision_normals(const CollisionShape& other_shape) const override;
};


#endif // RECTANGLE_COLLISION_SHAPE_H
