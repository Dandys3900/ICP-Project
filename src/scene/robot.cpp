/** ICP Project 2023/2024
 * @file robot.cpp
 * @author Tomáš Daniel (xdanie14)
 * @brief Representation of a robot in the scene.
 */

#include "robot.h"

Robot::Robot (const qreal size, const qreal coord_x, const qreal coord_y, PlayGround* playground)
    : SceneObject           (Vector2(coord_x, coord_y)),
      QGraphicsEllipseItem  (nullptr),
      mp_diameter           (size),
      mp_obj_type           ("Robot"),
      mp_mode               (MANUAL),
      mp_rotation_direction (CLOCKWISE),
      mp_rotation_step      (5.0),
      mp_detect_threshold   (0.0),
      mp_playground         (playground),
      mp_arrow              (nullptr)
{
    constructor_actions();
}

Robot::Robot (const qreal size, const Vector2& coords, PlayGround* playground)
    : Robot(size, coords.x(), coords.y(), playground)
{
}

Robot::Robot (const qreal size, const Vector2& coords, qreal rotation, const Mode mode, const Direction rot_direction, const qreal rotation_step, const qreal collision_thr, PlayGround* playground)
    : SceneObject           (coords, rotation),
      QGraphicsEllipseItem  (nullptr),
      mp_diameter           (size),
      mp_obj_type           ("Robot"),
      mp_mode               (mode),
      mp_rotation_direction (rot_direction),
      mp_rotation_step      (rotation_step),
      mp_detect_threshold   (collision_thr),
      mp_playground         (playground),
      mp_arrow              (nullptr)
{
    constructor_actions();
}

void Robot::constructor_actions() {
    // Set proper stack order
    this->setZValue(0);

    // Set ellipsis properties
    this->setRect(mp_coords.x(), mp_coords.y(), mp_diameter, mp_diameter);

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
    mp_arrow = new QGraphicsPolygonItem(QPolygonF(points_arr), this);
    mp_arrow->setPos(this->rect().center().x(), this->rect().center().y() - ARROW_LENGTH);
    mp_arrow->setRotation(mp_rotation);

    // Set correct rotation origin
    mp_arrow->setTransformOriginPoint(QPointF(0, ARROW_LENGTH));

    // Allow hover events
    this->setAcceptHoverEvents(true);

    this->physical_robot = new PhysicalRobot(this);
}

Robot::~Robot () {
    delete mp_arrow;
    delete physical_robot;
}

QString Robot::get_type () {
    return mp_obj_type;
}

QPointF Robot::get_pos () {
    return QPointF(mp_coords.x(), mp_coords.y());
}

qreal Robot::get_diameter () {
    return mp_diameter;
}

QRectF Robot::get_rect () {
    return this->rect();
}

QGraphicsPolygonItem* Robot::get_robot_arrow () {
    return mp_arrow;
}

QVector<QString> Robot::get_robot_info () {
    // Construct new vector containing robot's details
    return QVector<QString> {
        QString::number(mp_mode),
        QString::number(mp_detect_threshold),
        QString::number(mp_rotation_step),
        QString::number(mp_rotation_direction)
    };
}

void Robot::set_mode (Mode new_mode) {
    mp_mode = new_mode;
}

void Robot::set_detect_threshold (qreal new_threshold) {
    mp_detect_threshold = new_threshold;
}

void Robot::set_rotation_step (qreal new_step) {
    mp_rotation_step = new_step;
}

void Robot::set_rotation_step_radians (qreal new_step) {
    mp_rotation_step = qRadiansToDegrees(new_step);
}

void Robot::set_rotation_direction (Direction new_direction) {
    mp_rotation_direction = new_direction;
}

qreal Robot::get_rotation_step () {
    return mp_rotation_step;
}

qreal Robot::get_rotation_step_radians () {
    return qDegreesToRadians(mp_rotation_step);
}

Direction Robot::get_rotation_direction () {
    return mp_rotation_direction;
}

qreal Robot::get_detect_threshold () {
    return mp_detect_threshold;
}

void Robot::set_active (bool active, Action action) {
    mp_color      = Qt::black;
    mp_is_active  = active;
    mp_obj_action = action;

    if (active && action == MOVE_ACTION) { // Focused and moving -> red
        mp_color = Qt::red;
    }

    QPen pen(mp_color);
    // Apply new color
    this->setPen(pen);
    this->mp_arrow->setPen(pen);
}

void Robot::set_obj_pos (const QPointF pos) {
    if (mp_playground->boundingRect().contains(QRectF(pos.x(), pos.y(), mp_diameter, mp_diameter))) {
        // If new position is inside current scene, update robot coords
        mp_coords.setX(pos.x());
        mp_coords.setY(pos.y());

        // Set new position of robot
        this->setRect(mp_coords.x(), mp_coords.y(), mp_diameter, mp_diameter);

        // Re-center arrow after robot moved
        mp_arrow->setPos(this->rect().center().x(), this->rect().center().y() - ARROW_LENGTH);
    }
}

void Robot::keyPressEvent (QKeyEvent* event) {
    if (mp_mode == AUTOMATIC) {
        return;
    }
    switch (event->key()) {
        case Qt::Key_Left: // Rotate counter-clockwise
            physical_robot->turn_left();
            break;
        case Qt::Key_Right: // Rotate clockwise
            physical_robot->turn_right();
            break;
        case Qt::Key_Up: // Move forward
            physical_robot->move();
            break;
        case Qt::Key_Down: // Ignore as robot should move only forward
        default: // Ignore any other keys
            break;
    }
}

void Robot::mouseDoubleClickEvent (QGraphicsSceneMouseEvent* event) {
    // Remove Robot
    if (event->button() == Qt::MouseButton::RightButton) {
        // if robot widget is shown, hide it first
        Robot_Info::hide_related_widget(this);
        mp_playground->remove_scene_obj(this);
    }
}

void Robot::mousePressEvent (QGraphicsSceneMouseEvent* event) {
    if (event->button() == Qt::MouseButton::LeftButton) {
        if (!mp_is_active) { // Notify PlayGround and get focus
            this->mp_move_action_mouse_offset = this->mp_coords - event->scenePos();
            mp_playground->set_active_obj(this, MOVE_ACTION);
        }
        else { // Lose focus
            mp_playground->disable_focus();
        }
    }

    if (event->button() == Qt::MouseButton::RightButton) {
        if (mp_is_active) { // Lose focus and return to previous pos
            this->set_obj_pos(mp_playground->get_active_obj_orig_pos());
            mp_playground->disable_focus();
        }
        else { // Show Robot details
            Robot_Info::show_widget(this);
        }
    }
}

void Robot::mouseMoveEvent (QGraphicsSceneMouseEvent* event) {
    if (mp_is_active) { // Move robot, if focused
        this->set_obj_pos(event->scenePos() + this->mp_move_action_mouse_offset);
        this->physical_robot->update_shape();
    }
}

void Robot::hoverEnterEvent (QGraphicsSceneHoverEvent* event /*not used*/) {
    QPen pen(Qt::gray);
    // Apply new color
    this->setPen(pen);
}

void Robot::hoverLeaveEvent (QGraphicsSceneHoverEvent* event /*not used*/) {
    QPen pen(mp_color);
    // Apply new color
    this->setPen(pen);
}

void Robot::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    // Texture source
    QPixmap img(":/textures/robot.png");
    // Paint the background image
    painter->drawPixmap(
        boundingRect().toRect(),
        img.scaled(boundingRect().size().toSize(), Qt::KeepAspectRatio, Qt::SmoothTransformation)
    );

    QGraphicsEllipseItem::paint(painter, option, widget);
}

void Robot::do_rotation (const qreal angle) {
    mp_rotation += angle;
    // Rotation of the arrow
    mp_arrow->setRotation(mp_rotation);
}

QJsonObject Robot::get_obj_data () {
    QJsonObject conf_data = SceneObject::get_obj_data();
    conf_data["obj_type"]           = mp_obj_type;
    conf_data["diameter"]           = mp_diameter;
    conf_data["mode"]               = mp_mode;
    conf_data["rotation_step"]      = mp_rotation_step;
    conf_data["rotation_direction"] = mp_rotation_direction;
    conf_data["collis_threshold"]   = mp_detect_threshold;
    return conf_data;
}
