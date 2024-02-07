#include "Headers/Robot.h"

Robot::Robot (const qreal size, const qreal axis_x, const qreal axis_y)
    : mp_diameter(size),
      mp_coord_x (axis_x),
      mp_coord_y (axis_y),
      mp_rotation(ZERO_VAL),
      m_arrow    (nullptr)
{
    // Set ellipsis properties
    this->setRect(mp_coord_x, mp_coord_y, size, size);

    // Prepare vector of points from which polygon will be created
    QVector<QPointF> points_arr;

    // Arrow top
    points_arr.append(QPointF(0, -10));
    // Arrow left side
    points_arr.append(QPointF(-5, 5));
    // Arrow leg
    points_arr.append(QPointF(0, 5));
    points_arr.append(QPointF(0, ARROW_SHIFT));
    points_arr.append(QPointF(0, 5));
    // Arrow right side
    points_arr.append(QPointF(5, 5));

    // Create arrow showing current rotation
    m_arrow = new QGraphicsPolygonItem(QPolygonF(points_arr));
    m_arrow->setPos(mp_coord_x + (mp_diameter / 2), mp_coord_y + (mp_diameter / 2) - ARROW_SHIFT);
    m_arrow->setRotation(mp_rotation); // mp_rotation == 0

    // Set correct rotation origin
    m_arrow->setTransformOriginPoint(QPointF(0, ARROW_SHIFT));

    // Create timer
    QTimer* timer = new QTimer();
    // Connect timer to robot slot to run detect_objects() method periodically
    connect(timer, SIGNAL(timeout()), this, SLOT(detect_objects()));

    // Set timer period
    timer->start(TIMER_MILISECS);
}

Robot::~Robot ()
{
    delete m_arrow;
}

void Robot::keyPressEvent (const QKeyEvent* event) {
    switch (event->key()) {
        case Qt::Key_Left:
            // Rotate counter-clockwise
            do_rotation(-10);
            break;
        case Qt::Key_Right:
            // Rotate clockwise
            do_rotation(10);
            break;
        case Qt::Key_Up:
            // Move forward
            move_forward();
            break;
        case Qt::Key_Down:
            // Ignore as robot should move only forward
        default:
            break;
    }
}

void Robot::do_rotation (const size_t angle) {
    mp_rotation += angle;
    // Rotation of the arrow
    m_arrow->setRotation((mp_rotation % 360));
}

void Robot::set_new_pos (qreal new_x, qreal new_y) {
    if (scene()->sceneRect().contains(new_x, new_y)) {
        // If new position is inside current scene, update robot coords
        mp_coord_x = new_x;
        mp_coord_y = new_y;

        // Set new position of robot
        this->setPos(mp_coord_x, mp_coord_y);

        // Re-center arrow after robot moved
        m_arrow->setPos(mp_coord_x + (mp_diameter / 2), mp_coord_y + (mp_diameter / 2) - ARROW_SHIFT);
    }
}

void Robot::move_forward () {
    // In case no rotation is set yet (zero value) avoid any position calculation and simply move forward
    if (!mp_rotation) {
        set_new_pos(x(), y() - 10);
        return;
    }

    // Covert current rotation (in degrees) to radians [required by qCos and qSin methods]
    qreal rads = qDegreesToRadians((double)mp_rotation + 90);

    // Calculate changes for both axis and multiply by 10 to make the movement visible
    qreal dx = 10 * qCos(rads);
    qreal dy = 10 * qSin(rads);

    mp_coord_x = x() + dx;
    mp_coord_y = y() + dy;

    set_new_pos(x() + dx, y() - dy);
}

void Robot::detect_objects () {
    // TODO - casting shaperays to detect objects around the robot and detecting the potencial collisions
}
