/** ICP Project 2023/2024
 * @file collision_shape.cpp
 * @author Jakub Janšta (xjanst02)
 * @brief Handling collisions of objects in general.
 */

#include "collision_shape.h"


bool CollisionShape::is_colliding_with(const CollisionShape& other_shape) {
	qreal min_this, min_other;
	qreal max_this, max_other;
	// Get all the interesting normals of the shapes, that can be separation axis
	QVector<Vector2> axis = this->get_sat_collision_normals(other_shape) + other_shape.get_sat_collision_normals(*this);

	// Check each possible axis, if it is a separating axis
	for (int i = 0; i < axis.size(); i++) {
		// Project the shapes on the axis
		this->project_to_axis(axis[i], &min_this, &max_this);
		other_shape.project_to_axis(axis[i], &min_other, &max_other);
		// Check if the projections intersect
		if (min_this >= max_other || max_this <= min_other) {
			return false; // Separation axis found
		}
	}

	// No separating axis found => shapes are colliding
	return true;
}
