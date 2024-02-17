#include "Headers/Robot.h"

Robot::Robot (const qreal size, const qreal axis_x, const qreal axis_y, PlayGround* playground)
    : mp_diameter   (size),
      mp_coord_x    (axis_x),
      mp_coord_y    (axis_y),
      mp_rotation   (0),
      mp_type       ("Robot"),
      mp_pen_colour (Qt::black),
      mp_playground (playground),
      mp_arrow      (nullptr)
{
    // Set ellipsis properties
    this->setRect(mp_coord_x, mp_coord_y, mp_diameter, mp_diameter);

    // Make Robot moveable (able to receive mouse events)
    this->setFlag(QGraphicsItem::ItemIsSelectable);

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
    mp_arrow = new QGraphicsPolygonItem(QPolygonF(points_arr));
    mp_arrow->setPos(mp_coord_x + (mp_diameter / 2), mp_coord_y + (mp_diameter / 2) - ARROW_SHIFT);
    mp_arrow->setRotation(mp_rotation); // mp_rotation == 0

    // Set correct rotation origin
    mp_arrow->setTransformOriginPoint(QPointF(0, ARROW_SHIFT));
}

Robot::~Robot ()
{
    delete mp_arrow;
    delete mp_playground;
}

QString Robot::get_type () {
    return mp_type;
}

void* Robot::get_object () {
    return this;
}

QPointF Robot::get_pos () {
    return QPointF(mp_coord_x, mp_coord_y);
}

QGraphicsPolygonItem* Robot::get_robot_arrow () {
    return mp_arrow;
}

void Robot::set_marked (bool marked, Action action /*not used*/) {
    mp_pen_colour = Qt::black;

    // Change robot + arrow color when selected or not
    if (marked) {
        mp_pen_colour = Qt::red;
    }

    QPen pen(mp_pen_colour);
    // Apply new color
    this->setPen(pen);
    this->mp_arrow->setPen(pen);
}

void Robot::set_obj_pos (const QPointF pos) {
    if (scene()->sceneRect().contains(QRectF(pos.x(), pos.y(), mp_diameter, mp_diameter))) {
        // If new position is inside current scene, update robot coords
        mp_coord_x = pos.x();
        mp_coord_y = pos.y();

        // Set new position of robot
        this->setRect(mp_coord_x, mp_coord_y, mp_diameter, mp_diameter);

        // Re-center arrow after robot moved
        mp_arrow->setPos(mp_coord_x + (mp_diameter / 2), mp_coord_y + (mp_diameter / 2) - ARROW_SHIFT);
    }
}

void Robot::keyPressEvent (QKeyEvent* event) {
    switch (event->key()) {
        case Qt::Key_Left:
            // Rotate counter-clockwise
            do_rotation(qreal(-6));
            break;
        case Qt::Key_Right:
            // Rotate clockwise
            do_rotation(qreal(6));
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

void Robot::mousePressEvent (QGraphicsSceneMouseEvent* event) {
    // Mark this object for moving
    if (event->button() == Qt::MouseButton::LeftButton) {
        // Robot unused, begin moving of it
        if (mp_pen_colour == Qt::black) {
            // Mouse click on the Robot, notify PlayGround we have an object to move with
            mp_playground->set_active_obj(this, MOVE_ACTION);
        }
        else {
            // Robot already used, so stop moving and unmark
            mp_playground->mousePressEvent(event);
        }
    }
    // Unmark this object from moving
    if (event->button() == Qt::MouseButton::RightButton) {
        mp_playground->mousePressEvent(event);
    }
}

void Robot::mouseMoveEvent (QGraphicsSceneMouseEvent *event) {
    mp_playground->mouseMoveEvent(event);
}

void Robot::do_rotation (const qreal angle) {
    mp_rotation += angle;
    // Rotation of the arrow
    mp_arrow->setRotation(mp_rotation);
}

void Robot::move_forward () {
    // Covert current rotation (in degrees) to radians [required by qCos and qSin methods]
    qreal rads = qDegreesToRadians((double)(-mp_rotation + 90));

    // Calculate changes for both axis and multiply by 10 to make the movement visible
    qreal dx = 10 * qCos(rads);
    qreal dy = 10 * qSin(rads);

    set_obj_pos(QPointF((get_pos().x() + dx), (get_pos().y() - dy)));
}
