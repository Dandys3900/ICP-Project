/** ICP Project 2023/2024
 * @file physics_server.cpp
 * @author Jakub Janšta (xjanst02)
 * @brief Implementation of PhysicsServer class
 */

#include "physics_server.h"


PhysicsServer::PhysicsServer() {}


PhysicsServer::~PhysicsServer() {
	this->unregister_boundaries();
}


void PhysicsServer::step() {
	if (this->is_step_queued) {
		this->force_step(true);
	}
}


void PhysicsServer::queue_step() {
	this->is_step_queued = true;
}


void PhysicsServer::force_step(bool clean_step_queue) {
	if (clean_step_queue) {
		this->is_step_queued = false;
	}

	// Obstacle shapes
	QVector<const CollisionShape*> obstacle_shapes = {};
	for (PhysicalObstacle* obstacle : this->obstacles) {
		obstacle_shapes.append(obstacle->get_shape());
	}
	// Robot shapes
	QVector<const CollisionShape*> robot_shapes = {};
	for (PhysicalRobot* robot : this->robots) {
		robot_shapes.append(robot->get_shape());
	}

	for (PhysicalRobot* robot : this->robots) {
		robot->step(playground_boundary_obstacle_shapes, obstacle_shapes, robot_shapes);
	}
}


void PhysicsServer::register_robot(PhysicalRobot* robot) {
	if (!this->robots.contains(robot)) {
		this->robots.append(robot);
	}
}


void PhysicsServer::unregister_robot(PhysicalRobot* robot) {
	int index = this->robots.indexOf(robot);
	if (index >= 0) {
		this->robots.remove(index);
	}
}


void PhysicsServer::register_obstacle(PhysicalObstacle* obstacle) {
	if (this->obstacles.contains(obstacle)) {
		return;
	}
	this->obstacles.append(obstacle);
}


void PhysicsServer::unregister_obstacle(PhysicalObstacle* obstacle) {
	int index = this->obstacles.indexOf(obstacle);
	if (index == -1) {
		return;
	}
	this->obstacles.remove(index);
}


void PhysicsServer::register_boundaries(Vector2 playground_size) {
	this->unregister_boundaries();

	QPointF half_size = playground_size / 2;

	this->playground_boundary_obstacle_shapes = {
		new RectangeCollisionShape(playground_size, Vector2(half_size.x(), -half_size.y())), // Upper boundary
		new RectangeCollisionShape(playground_size, Vector2(half_size.x(), playground_size.y() + half_size.y())), // Lower boundary
		new RectangeCollisionShape(playground_size, Vector2(-half_size.x(), half_size.y())),
		new RectangeCollisionShape(playground_size, Vector2(playground_size.x() + half_size.x(), half_size.y()))
	};
}


void PhysicsServer::unregister_boundaries() {
	for (const CollisionShape* playground_boundary_obstacle_shape : this->playground_boundary_obstacle_shapes) {
		delete playground_boundary_obstacle_shape;
	}
}
