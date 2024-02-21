#ifndef RECTANGLE_COLLISION_SHAPE_H
#define RECTANGLE_COLLISION_SHAPE_H


#include "physics/polygon_collision_shape.h"


class RectangeCollisionShape : protected PolygonCollisionShape {
	public:
		/*!
		 * A rectangle has two pairs of parallel edges, so just getting one of them is sufficient.
		 * Parallel lines in SAT collisions come to identical results.
		 * This is just a small optimisation and every RectangeCollisionShape should behave identically to PolygonCollisionShape;
		 */
		QVector<Vector2> get_sat_collision_normals(const CollisionShape& other_shape) const override;
};


#endif // RECTANGLE_COLLISION_SHAPE_H
