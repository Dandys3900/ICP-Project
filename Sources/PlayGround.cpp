#include "Headers/PlayGround.h"

PlayGround::PlayGround (const qreal width, const qreal height, const qreal axis_x, const qreal axis_y)
    : mp_width  (width),
      mp_height (height),
      mp_coord_x(axis_x),
      mp_coord_y(axis_y)
{
    this->setRect(mp_coord_x, mp_coord_y, mp_width, mp_height);

    // Create black pen
    QPen pen(Qt::black);
    // Set border width
    pen.setWidth(BORDER_WIDTH);
    // Add pen to border to make it bolder
    this->setPen(pen);

    constructor_actions();
}

PlayGround::~PlayGround ()
{
}

void PlayGround::constructor_actions () {
    // Make PlayGround focusable
    this->setFlag(QGraphicsItem::ItemIsFocusable);
    this->setFocus();

    // Clean vectors - not neccessary
    mp_obstacle_vec.clear();
    mp_robot_vec.clear();

    // Add PlayGround to the scene
    scene()->addItem(this);
}

void PlayGround::addRobot (Robot* robot) {
    mp_robot_vec.push_back(robot);
    // Add robot + its arrow
    scene()->addItem(robot->m_arrow);
    scene()->addItem(robot);
}

void PlayGround::addObstacle (Obstacle* obstacle) {
    mp_obstacle_vec.push_back(obstacle);
}

void PlayGround::keyPressEvent (QKeyEvent* event) {
    // Distribute the key press event to all robots in the playground
    std::vector<Robot*>::iterator iter;

    for (iter = mp_robot_vec.begin(); iter < mp_robot_vec.end(); ++iter) {
        (*iter)->keyPressEvent(event);
    }
}
