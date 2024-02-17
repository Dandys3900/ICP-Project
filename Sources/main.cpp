#include "Headers/LibsFile.h"
#include "Headers/Robot.h"
#include "Headers/Obstacle.h"
#include "Headers/PlayGround.h"

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
    scene->setSceneRect(ZERO_VAL, ZERO_VAL, WINDOW_WIDTH, WINDOW_HEIGHT);

    // Create playground
    PlayGround* playground = new PlayGround(WINDOW_WIDTH, WINDOW_HEIGHT, scene);

    // Create robot
    Robot* robot = new Robot(ROBOT_SIZE, (WINDOW_WIDTH / 2) - (ROBOT_SIZE / 2), (WINDOW_HEIGHT / 2) - (ROBOT_SIZE / 2), playground);

    // Create obstacle
    Obstacle* obstacle = new Obstacle(50, 20, 10, 15, playground);

    // Add robot to the playground thus to the scene
    playground->addObject(robot);

    // Add obstacle to the playground thus to the scene
    playground->addObject(obstacle);

    // Create view
    QGraphicsView* view = new QGraphicsView();
    // Set title
    view->setWindowTitle("ICP 2023/2024 Project");
    // Set fixed size for view
    view->setFixedSize(WINDOW_WIDTH + BORDER_WIDTH * 2, WINDOW_HEIGHT + BORDER_WIDTH * 2);
    // Add scene to the view
    view->setScene(scene);
    // Set view visible
    view->show();

    return app.exec();
}
