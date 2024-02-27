#ifndef RECTANGLE_COLLISION_SHAPE_H
#define RECTANGLE_COLLISION_SHAPE_H


#include "physics/polygon_collision_shape.h"


class RectangeCollisionShape : protected PolygonCollisionShape {
	public:
		RectangeCollisionShape(const Vector2& size) {
			this->origin = Vector2();
			QPointF half_size = size / 2;
			
			this->verticies.resize(4);
			this->verticies[0] = Vector2(this->origin.x() - half_size.x(), this->origin.y() - half_size.y());
			this->verticies[1] = Vector2(this->origin.x() + half_size.x(), this->origin.y() - half_size.y());
			this->verticies[2] = Vector2(this->origin.x() + half_size.x(), this->origin.y() + half_size.y());
			this->verticies[3] = Vector2(this->origin.x() - half_size.x(), this->origin.y() + half_size.y());
		}
		
		RectangeCollisionShape(const Vector2& size, Vector2 position) : RectangeCollisionShape(size) {
			this->set_position(position);
		}

		/*!
		 * A rectangle has two pairs of parallel edges, so just getting one of them is sufficient.
		 * Parallel lines in SAT collisions come to identical results.
		 * This is just a small optimisation and every RectangeCollisionShape should behave identically to PolygonCollisionShape;
		 */
		QVector<Vector2> get_sat_collision_normals(const CollisionShape& other_shape) const override;
};


#endif // RECTANGLE_COLLISION_SHAPE_H
