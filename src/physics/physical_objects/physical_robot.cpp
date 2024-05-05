/** ICP Project 2023/2024
 * @file physical_robot.cpp
 * @author Jakub Janšta (xjanst02)
 * @brief Implementation of PhysicalRobot class
 */

#include "physical_robot.h"


PhysicalRobot::PhysicalRobot(Robot* robot) {
	this->robot = robot;
	this->update_shape(); // Create a new shape as it does not exist yet
	this->update_shapecast(); // Create new shapecast shapes as they do not exist yet
}


PhysicalRobot::~PhysicalRobot() {
	// Delete shape
	if (this->shape != nullptr) {
		delete this->shape;
	}
	// Delete shapecast shapes
	if (this->shapecast_capsule_rectangle != nullptr) {
		delete this->shapecast_capsule_rectangle;
	}
	if (this->shapecast_capsule_circle != nullptr) {
		delete this->shapecast_capsule_circle;
	}
}


void PhysicalRobot::update_shape() {
	if (this->shape == nullptr) { // Ensure shape
		this->shape = new CircleCollisionShape(Vector2(), 0); // Don't care about the constructor variables - will be set anyway
	}
	this->shape->set_position(Vector2(this->robot->get_pos()) + Vector2(this->robot->get_diameter() / 2));
	this->shape->set_radius(this->robot->get_diameter() / 2);
	this->shape->set_rotation(this->robot->get_rotation_radians());
}


void PhysicalRobot::update_shapecast() {
	// Ensure shapecast shapes
	if (this->shapecast_capsule_rectangle == nullptr) {
		this->shapecast_capsule_rectangle = new RectangeCollisionShape(Vector2()); // Don't care about the constructor variables - will be set anyway
	}
	if (this->shapecast_capsule_circle == nullptr) {
		this->shapecast_capsule_circle = new CircleCollisionShape(Vector2(), 0); // Don't care about the constructor variables - will be set anyway
	}

	qreal current_rotation = this->robot->get_rotation_radians() - M_PI_2; // Corrected angle in radians so that 0 is pointing up
	Vector2 threshold_endpoint_offset = this->robot->get_detect_threshold() * Vector2(
		qCos(current_rotation),
		qSin(current_rotation)
	); // Rotated shapecast endpoint offset from the robot position

	// Circle
	this->shapecast_capsule_circle->set_position(Vector2(this->robot->get_pos()) + (Vector2(this->robot->get_diameter()) / 2) + threshold_endpoint_offset);
	this->shapecast_capsule_circle->set_radius(this->robot->get_diameter() / 2);
	// Rectangle
	this->shapecast_capsule_rectangle->set_position(Vector2(this->robot->get_pos()) + (Vector2(this->robot->get_diameter()) / 2) + threshold_endpoint_offset / 2);
	this->shapecast_capsule_rectangle->resize(Vector2(this->robot->get_diameter(), this->robot->get_detect_threshold()));
	this->shapecast_capsule_rectangle->set_rotation(this->robot->get_rotation_radians());
}


void PhysicalRobot::move() {
	qreal current_rotation = this->robot->get_rotation_radians() - M_PI_2; // Corrected angle in radians so that 0 is pointing up
	Vector2 movement_delta = 5 * Vector2(
		qCos(current_rotation), // Change on x axis (dx)
		qSin(current_rotation)  // Change on y axis (dy)
	);

    this->robot->set_obj_pos(this->robot->get_pos() + movement_delta);

	this->update_shape(); // Move the shape
	this->update_shapecast(); // Move and rotate the shapecast
}


void PhysicalRobot::turn() {
	int rotation_step_direction_multiplier = this->robot->get_rotation_direction() == Direction::CLOCKWISE ? 1 : -1;
	this->robot->do_rotation(this->robot->get_rotation_step() * rotation_step_direction_multiplier); // Robot visuals
	this->shape->set_rotation(this->robot->get_rotation_radians() + this->robot->get_rotation_step_radians() * rotation_step_direction_multiplier);
	this->update_shapecast(); // Rotate the shapecast
}


void PhysicalRobot::turn_left() {
	this->robot->do_rotation(-this->robot->get_rotation_step());
	this->shape->set_rotation(this->robot->get_rotation_radians() - this->robot->get_rotation_step_radians());
	this->update_shapecast(); // Rotate the shapecast
}


void PhysicalRobot::turn_right() {
	this->robot->do_rotation(this->robot->get_rotation_step());
	this->shape->set_rotation(this->robot->get_rotation_radians() + this->robot->get_rotation_step_radians());
	this->update_shapecast(); // Rotate the shapecast
}


bool PhysicalRobot::is_colliding_with(const CollisionShape& other_shape) const {
	if (&other_shape == this->shape) { // Prevent self-collision
		return false;
	}
	return this->shape->is_colliding_with(other_shape);
}


bool PhysicalRobot::is_shapecast_colliding_with(const CollisionShape& other_shape) const {
	if (&other_shape == this->shape) { // Prevent self-collision
		return false;
	}
	return this->shapecast_capsule_rectangle->is_colliding_with(other_shape) || this->shapecast_capsule_circle->is_colliding_with(other_shape);
}


bool PhysicalRobot::is_colliding_with_any(QVector<const CollisionShape*>& other_shapes) const {
	for (const CollisionShape* other_shape : other_shapes) {
		if (this->is_colliding_with(*other_shape)) {
			return true;
		}
	}
	return false;
}


bool PhysicalRobot::is_shapecast_colliding_with_any(QVector<const CollisionShape*>& other_shapes) const {
	for (const CollisionShape* other_shape : other_shapes) {
		if (this->is_shapecast_colliding_with(*other_shape)) {
			return true;
		}
	}
	return false;
}


const CircleCollisionShape* PhysicalRobot::get_shape() {
	return this->shape;
}


void PhysicalRobot::step(QVector<const CollisionShape*>& playground_boundary_obstacles, QVector<const CollisionShape*>& obstacles, QVector<const CollisionShape*>& robots) {
	if (this->robot->get_mode() == AUTOMATIC) {
		this->step_automatic(playground_boundary_obstacles, obstacles, robots);
	} else {
		this->step_manual(playground_boundary_obstacles, obstacles, robots);
	}
}


void PhysicalRobot::step_automatic(QVector<const CollisionShape*>& playground_boundary_obstacles, QVector<const CollisionShape*>& obstacles, QVector<const CollisionShape*>& robots) {
	// If shapecast is colliding, rotate
	if (this->is_shapecast_colliding_with_any(playground_boundary_obstacles) || this->is_shapecast_colliding_with_any(obstacles) || this->is_shapecast_colliding_with_any(robots)) {
		this->turn();
		return;
	}
	this->move();
	if (this->robot->get_detect_threshold() > 0) {
		return;
	}
	// This is used if collision threshold is 0 (robot collides only with its own body)
	if (this->is_colliding_with_any(playground_boundary_obstacles) || this->is_colliding_with_any(obstacles) || this->is_colliding_with_any(robots)) { // If colliding, undo the test move
		this->robot->set_rotation_radians(this->robot->get_rotation_radians() + M_PI); // Flip the robot
		this->move(); // Move back
		this->robot->set_rotation_radians(this->robot->get_rotation_radians() - M_PI); // Flip the robot back

		this->turn(); // After undoing the test move, turn the robot
	}
}


void PhysicalRobot::step_manual(QVector<const CollisionShape*>& playground_boundary_obstacles, QVector<const CollisionShape*>& obstacles, QVector<const CollisionShape*>& robots) {
	switch (this->queued_action) {
		case QueuedAction::MOVE:
			this->move(); // Do test move
			if (this->is_colliding_with_any(playground_boundary_obstacles) || this->is_colliding_with_any(obstacles) || this->is_colliding_with_any(robots)) { // If colliding, undo the test move
				this->robot->set_rotation_radians(this->robot->get_rotation_radians() + M_PI); // Flip the robot
				this->move(); // Move back
				this->robot->set_rotation_radians(this->robot->get_rotation_radians() - M_PI); // Flip the robot back
				break;
			}
			// Commit to the test move
			break;
		case QueuedAction::TURN_LEFT:
			this->turn_left();
			break;
		case QueuedAction::TURN_RIGHT:
			this->turn_right();
			break;
		default: // QueuedAction::NONE
			break;
	}
	this->queued_action = QueuedAction::NONE; // Prevent action looping
}