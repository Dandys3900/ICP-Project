/** ICP Project 2023/2024
 * @file main.cpp
 * @author Tomáš Daniel (xdanie14)
 * @brief Application execution point.
 */

#include "scene/robot.h"
#include "scene/obstacle.h"
#include "scene/playground.h"
#include "custom_view.h"
#include "user_menu.h"

/**
 * @brief ICP Project 2023/2024 - Implementation of robot's movement and collision avoiding simulator.
 *
 * The aim of this project is to create an iterative simulator that simulates the movements of robots,
 * both manually and automatically controlled, in an environment full of obstacles to avoid collision with.
 *
 * Dependencies:
 * - QT Library (version 5.5 or higher)
 * - C++17 compiler
 *
 * Contributors:
 * - Tomáš Daniel (xdanie14)
 * - Jakub Janšta (xjanst02)
 *
 * License: MIT License
 */
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Create the main window
    QMainWindow* main_window = new QMainWindow();

    // Create scene
    QGraphicsScene* scene = new QGraphicsScene();
    // Set its initial size
    scene->setSceneRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    // Create playground
    PlayGround* playground = new PlayGround(scene);

    // Create view
    CustomView* view = new CustomView(scene, playground, main_window);
    // Set borders
    view->setStyleSheet("border: 5px solid black;");
    // Set title
    view->setWindowTitle("ICP 2023/2024 Project");
    // Add scene to the view
    view->setScene(scene);

    // Create robot
    qreal robot_size = 100;
    Robot* robot = new Robot(robot_size, main_window->rect().center().x(), main_window->rect().center().y(), playground);

    // Create obstacle
    Obstacle* obstacle = new Obstacle(75, 75, 150, 150, playground);

    // Add robot to the playground
    playground->add_scene_obj(robot);
    // Add obstacle to the playground
    playground->add_scene_obj(obstacle);

    // Place view to window
    main_window->setCentralWidget(view);
    // Show window
    main_window->show();

    // Create and add user menu to the scene
    UserMenu* user_menu = new UserMenu(scene, playground, main_window);

    // Init error popup class - must be after main window being shown
    Error_PopUp* err_popup = new Error_PopUp(main_window);

    // Init robot info (help) class
    Robot_Info* info = new Robot_Info(scene, main_window);

    const int app_retval = app.exec();

    /***** Clean memory *****/
    Robot_Info::clean_up();
    Error_PopUp::clean_up();
    delete user_menu;
    delete view;
    delete playground;
    delete scene;
    delete main_window;

    // Return and end
    return app_retval;
}
