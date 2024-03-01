#include "scene/robot.h"
#include "scene/obstacle.h"
#include "scene/playground.h"
#include "custom_view.h"

/**
 * @brief Main file for starting the simulator by creating
 * the Robot class instance and Obstacle class instance which
 * are then added to the PlayGround class instance.
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
    Robot* robot = new Robot(robot_size, (WINDOW_WIDTH / 2) - (robot_size / 2), (WINDOW_HEIGHT / 2) - (robot_size / 2), playground);

    // Create obstacle
    Obstacle* obstacle = new Obstacle(50, 20, 10, 15, playground);

    // Add robot to the playground
    playground->add_scene_obj(robot);
    // Add obstacle to the playground
    playground->add_scene_obj(obstacle);

    // Place view to window
    main_window->setCentralWidget(view);
    // Add constructed menu bar to window
    main_window->setMenuBar(view->get_menu_bar());
    // Show window
    main_window->show();

    return app.exec();
}
