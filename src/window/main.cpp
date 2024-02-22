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

    // Create scene
    QGraphicsScene* scene = new QGraphicsScene();
    // Set its initial size
    scene->setSceneRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    // Create playground
    PlayGround* playground = new PlayGround(WINDOW_WIDTH, WINDOW_HEIGHT, scene);

    // Create robot
    qreal robot_size = 100;
    Robot* robot = new Robot(robot_size, (WINDOW_WIDTH / 2) - (robot_size / 2), (WINDOW_HEIGHT / 2) - (robot_size / 2), playground);

    // Create obstacle
    Obstacle* obstacle = new Obstacle(50, 20, 10, 15, playground);

    // Add robot to the playground
    playground->add_scene_obj(robot);

    // Add obstacle to the playground
    playground->add_scene_obj(obstacle);

    // Create view
    QGraphicsView* view = new QGraphicsView();
    // Set title
    view->setWindowTitle("ICP 2023/2024 Project");
    // Add scene to the view
    view->setScene(scene);
    // Set view visible
    view->show();

    return app.exec();
}
