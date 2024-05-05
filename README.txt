ICP-Project 2024

Authors:
Tomáš Daniel (xdanie14)
Jakub Janšta (xjanst02)


General description:
	This application provides a simulated playground of robots and obstacles.
	Robots can move, rotate and detect collisions with other robots and obstacles with the ability to move autonomously or manually. 
	Obstacles are simple static objects that the robots can avoid and collide with.

Objects:
	Robots:
		Manual:
			Can move forward with the up arrow key.
			Can turn left with the left arrow key. The rotation angle is determined by the Rotation Angle accesible in Robot attributes.
			Can turn right with the right arrow key. The rotation angle is determined by the Rotation Angle accesible in Robot attributes.
		Automatic:
			Will move autonomously throught the playground.
			It will move forward until a collision is detected. Then it will turn by the Rotation Angle in the Rotation direction accesible in Robot attributes.
			Collision threshold, accesible in Robot attributes, represents the robot forward "vision" length. If it spots an obstacle or a robot in it's path it will behave as if it collided with them.
			The robot "vision" is as wide as the robot itself, so it will not try to fit in narrow spaces.
	Obstacles:
		Simple static objects that the robots collide with.
		In the automatic simulation they can be used to dynamically change environment for the robots to navigate.

Control:
	Adding / deleting objects:
		The user can create robots and obstacles by clicking the top-left menu button and selecting Add Robot or Add Obstacle respectively and the clicking anywhere in the playground where the robot or obstacle should be placed.
		Removing robots and obstacles can be done by double right-click.

	Object interaction:
		Robots and obstacles can be moved by left-click and dragging.
		Obstacles can be resized by right-click and dragging.
		Obstacles can be rotated by selecting the obstacle with left or right-click and then pressing left or right arrow key.
		Robot attributes can be managed by right-clicking the robot and then modifying them in the top-right context menu.
	
	Loading / saving playgrounds:
		Playground can be loaded by opening the top-left menu and clicking the Load button. Your operating systems filedialog will prompt you with name and location of the savefile that is to be loaded.
		The current playground state can be saved by opening the top-left menu and clicking the Save button. Your operating systems filedialog will prompt you with name and location of the savefile that is to be saved.
		Playground save files are .json files, that can be easily modified if your heart desires.
	
		Example playgrounds:
			Some example playgrounds can be found in the examples/ folder. You can load and modify them as any other playground save file.
	
	Simulation control:
		The default simulation mode is Manual. It can be changed in the top-left menu and switching the mode to Automatic.

		Manual simulation:
			In this mode every simulation step is triggered by moving a manual robot via the arrow keys or by pressing space.
			All the manual robots will do the same requested action while all the automatic robots will do one independent step.
		
		Automatic simulation:
			In this mode the simulation runs consistently. All the automatic robots will move independently while manual robots will wait for a user command.
			The simulation speed can be changed in the top-left menu and then changing the simulation speed slider.


Interesting features:
	All the object interactions can be done while the simulation is running even in automatic mode. For example, the user can drag an obstacle in front of a moving robot and it will collide with it correctly.
	The playground space can be resized by resizing the window.

	Physics:
		All the physical interactions are done from scratch with SAT (Separation Axis Theorem) collisions. The idea is that if there is at least one axis, on which two objects are not overlaping, then there is definitelly no collision.
		The effect of this is that the robot's circular shape is not approximated by a regular n-polygon, but is a presice circle with faster collisions.


Notes:
	The math/Vector2 class is loosely based on open source Godot Engine's Vector2 implementation. It was used as it has a familiar interface and is feature complete for physics.
	https://github.com/godotengine/godot/blob/master/core/math/vector2.h
