/** ICP Project 2023/2024
 * @file physics_server.cpp
 * @author Jakub Janšta (xjanst02)
 * @brief Implementation of PhysicsServer class
 */

#include "physics_server.h"


PhysicsServer::PhysicsServer() {

}


PhysicsServer::~PhysicsServer() {

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

	// playground boundary obstacle shapes
	QVector<const CollisionShape*> playground_boundary_obstacle_shapes = {};
	for (PhysicalObstacle* playground_boundary_obstacle : this->playground_boundary_obstacles) {
		playground_boundary_obstacle_shapes.append(playground_boundary_obstacle->get_shape());
	}
	// obstacle shapes
	QVector<const CollisionShape*> obstacle_shapes = {};
	for (PhysicalObstacle* obstacle : this->obstacles) {
		obstacle_shapes.append(obstacle->get_shape());
	}
	// robot shapes
	QVector<const CollisionShape*> robot_shapes = {};
	for (PhysicalRobot* robot : this->robots) {
		robot_shapes.append(robot->get_shape());
	}
	
	for (PhysicalRobot* robot : this->robots) {
		robot->step(playground_boundary_obstacle_shapes, obstacle_shapes, robot_shapes);
	}
}


void PhysicsServer::register_robot(PhysicalRobot* robot) {
	if (this->robots.contains(robot)) {
		return;
	}
	this->robots.append(robot);
}


void PhysicsServer::unregister_robot(PhysicalRobot* robot) {
	int index = this->robots.indexOf(robot);
	if (index == -1) {
		return;
	}
	this->robots.remove(index);
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
