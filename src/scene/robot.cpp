#include "scene/robot.h"

Robot::Robot (const qreal size, const qreal coords_x, const qreal coords_y, PlayGround* playground)
    : mp_coords     (coords_x, coords_y),
      mp_diameter   (size),
      mp_rotation   (0),
      mp_type       ("Robot"),
      mp_obj_action (NO_ACTION),
      mp_playground (playground),
      mp_arrow      (nullptr),
      mp_is_active  (false)
{
    // Set ellipsis properties
    this->setRect(mp_coords.x(), mp_coords.y(), mp_diameter, mp_diameter);

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
    points_arr.append(QPointF(0, ARROW_LENGTH));
    points_arr.append(QPointF(0, 5));
    // Arrow right side
    points_arr.append(QPointF(5, 5));

    // Create arrow showing current rotation
    mp_arrow = new QGraphicsPolygonItem(QPolygonF(points_arr));
    mp_arrow->setPos(mp_coords.x() + (mp_diameter / 2), mp_coords.y() + (mp_diameter / 2) - ARROW_LENGTH);
    mp_arrow->setRotation(mp_rotation); // mp_rotation == 0

    // Set correct rotation origin
    mp_arrow->setTransformOriginPoint(QPointF(0, ARROW_LENGTH));
}

Robot::Robot (const qreal size, const Vector2& coords, PlayGround* playground)
    : Robot(size, coords.x(), coords.y(), playground)
{
}

Robot::~Robot () {
    delete mp_arrow;
}

QString Robot::get_type () {
    return mp_type;
}

QPointF Robot::get_pos () {
    return QPointF(mp_coords.x(), mp_coords.y());
}

QGraphicsPolygonItem* Robot::get_robot_arrow () {
    return mp_arrow;
}

void Robot::set_active (bool active, Action action) {
    Qt::GlobalColor color = Qt::black;
    mp_is_active          = active;
    mp_obj_action         = action;

    if (active) {
        if (action == MOVE_ACTION)
            // Focused and moving -> red
            color = Qt::red;
    }

    QPen pen(color);
    // Apply new color
    this->setPen(pen);
    this->mp_arrow->setPen(pen);
}

void Robot::set_obj_pos (const QPointF pos) {
    if (scene()->sceneRect().contains(QRectF(pos.x(), pos.y(), mp_diameter, mp_diameter))) {
        // If new position is inside current scene, update robot coords
        mp_coords.setX(pos.x());
        mp_coords.setY(pos.y());

        // Set new position of robot
        this->setRect(mp_coords.x(), mp_coords.y(), mp_diameter, mp_diameter);

        // Re-center arrow after robot moved
        mp_arrow->setPos(mp_coords.x() + (mp_diameter / 2), mp_coords.y() + (mp_diameter / 2) - ARROW_LENGTH);
    }
}

void Robot::keyPressEvent (QKeyEvent* event) {
    switch (event->key()) {
        case Qt::Key_Left:
            // Rotate counter-clockwise
            do_rotation(qreal(-5));
            break;
        case Qt::Key_Right:
            // Rotate clockwise
            do_rotation(qreal(5));
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
    if (event->button() == Qt::MouseButton::LeftButton) {
        if (!mp_is_active) {
            // Notify PlayGround and get focus
            mp_playground->set_active_obj(this, MOVE_ACTION);
        }
        else {
            // Lose focus
            mp_playground->disable_focus();
        }
    }

    if (event->button() == Qt::MouseButton::RightButton) {
        if (mp_is_active) {
            // Lose focus and return to previous pos
            this->set_obj_pos(mp_playground->get_active_obj_orig_pos());
            mp_playground->disable_focus();
        }
    }
}

void Robot::mouseMoveEvent (QGraphicsSceneMouseEvent *event) {
    // Move robot, if focused
    if (mp_is_active) {
        this->set_obj_pos(event->pos());
    }
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
