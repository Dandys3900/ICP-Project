/** ICP Project 2023/2024
 * @file physical_robot.cpp
 * @author Jakub Janšta (xjanst02)
 * @brief Implementation of PhysicalRobot class
 */

#include "physical_robot.h"


PhysicalRobot::PhysicalRobot(Robot* robot) {
	QTextStream(stdout) << "ROBOOOOOT" << endl;
	this->robot = robot;
	this->update_shape(); // create a new shape as it does not exist yet
	this->update_shapecast(); // create new shapecast shapes as they do not exist yet
}


PhysicalRobot::~PhysicalRobot() {
	// delete shape
	if (this->shape != nullptr) {
		delete this->shape;
	}
	// delete shapecast shapes	
	if (this->shapecast_capsule_rectangle != nullptr) {
		delete this->shapecast_capsule_rectangle;
	}
	if (this->shapecast_capsule_circle != nullptr) {
		delete this->shapecast_capsule_circle;
	}
}


void PhysicalRobot::update_shape() {
	if (this->shape == nullptr) { // ensure shape
		this->shape = new CircleCollisionShape(Vector2(), 0); // don't care about the constructor variables - will be set anyway
	}
	this->shape->set_position(Vector2(this->robot->get_pos()) + Vector2(this->robot->get_diameter() / 2));
	this->shape->set_radius(this->robot->get_diameter() / 2);
	this->shape->set_rotation(this->robot->get_rotation_radians());
}


void PhysicalRobot::update_shapecast() {
	// ensure shapecast shapes
	if (this->shapecast_capsule_rectangle == nullptr) {
		this->shapecast_capsule_rectangle = new RectangeCollisionShape(Vector2()); // don't care about the constructor variables - will be set anyway
	}
	if (this->shapecast_capsule_circle == nullptr) {
		this->shapecast_capsule_circle = new CircleCollisionShape(Vector2(), 0); // don't care about the constructor variables - will be set anyway
	}
	qreal current_rotation = this->robot->get_rotation_radians() - M_PI_2; // corrected angle in radians so that 0 is pointing up
	Vector2 threshold_endpoint_offset = this->robot->get_detect_threshold() * Vector2(
		qCos(current_rotation),
		qSin(current_rotation)
	); // rotated shapecast endpoint offset from the robot position
	// Circle
	this->shapecast_capsule_circle->set_position(Vector2(this->robot->get_pos()) + threshold_endpoint_offset);
	this->shapecast_capsule_circle->set_radius(this->robot->get_diameter() / 2);
	// Rectangle
	this->shapecast_capsule_rectangle->set_position(Vector2(this->robot->get_pos()) + threshold_endpoint_offset / 2);
	this->shapecast_capsule_rectangle->set_rotation(this->robot->get_rotation_radians());
	// TODO handle dynamic robot resize

	QTextStream(stdout) << this->shapecast_capsule_circle->get_position().x() << "," << this->shapecast_capsule_circle->get_position().y() << endl;
}


void PhysicalRobot::move() {
	qreal current_rotation = this->robot->get_rotation_radians() - M_PI_2; // corrected angle in radians so that 0 is pointing up
	Vector2 movement_delta = 10 * Vector2(
		qCos(current_rotation), // change on x axis (dx)
		qSin(current_rotation)  // change on y axis (dy)
	);

    this->robot->set_obj_pos(this->robot->get_pos() + movement_delta);

	this->update_shape(); // move the shape
	this->update_shapecast(); // move and rotate the shapecast
}


void PhysicalRobot::turn() {
	int rotation_step_direction_multiplier = this->robot->get_rotation_direction() == Direction::CLOCKWISE ? 1 : -1;
	this->robot->do_rotation(this->robot->get_rotation_step() * rotation_step_direction_multiplier); // robot visuals
	this->shape->set_rotation(this->shape->get_rotation() + this->robot->get_rotation_step_radians() * rotation_step_direction_multiplier);
	this->update_shapecast(); // rotate the shapecast
}


void PhysicalRobot::turn_left() {
	this->shape->set_rotation(this->shape->get_rotation() - this->robot->get_rotation_step_radians());
	this->update_shapecast(); // rotate the shapecast
}


void PhysicalRobot::turn_right() {
	this->shape->set_rotation(this->shape->get_rotation() + this->robot->get_rotation_step_radians());
	this->update_shapecast(); // rotate the shapecast
}
