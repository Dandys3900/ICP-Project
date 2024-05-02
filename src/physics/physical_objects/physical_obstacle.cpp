/** ICP Project 2023/2024
 * @file physical_obstacle.cpp
 * @author Jakub Janšta (xjanst02)
 * @brief Implementation of PhysicalObstacle class
 */

#include "physical_obstacle.h"


PhysicalObstacle::PhysicalObstacle(Obstacle* obstacle) {
	this->obstacle = obstacle;
	this->update_shape(); // create a new shape as it does not exist yet
}


PhysicalObstacle::~PhysicalObstacle() {
	if (this->shape != nullptr) {
		delete this->shape;
	}
}


void PhysicalObstacle::update_shape() {
	if (this->shape == nullptr) { // ensure shape
		this->shape = new RectangeCollisionShape(Vector2()); // don't care about the constructor variables - will be set anyway
	}
	this->shape->set_position(Vector2(this->obstacle->get_rect().center()));
	this->shape->resize(Vector2(this->obstacle->get_size()));
	this->shape->set_rotation(this->obstacle->get_rotation_radians());
}
