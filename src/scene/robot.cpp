/** ICP Project 2023/2024
 * @file robot.cpp
 * @author Tomáš Daniel (xdanie14)
 * @brief Representation of a robot in the scene.
 */

#include "robot.h"

Robot::Robot (const qreal size, const qreal coord_x, const qreal coord_y, PlayGround* playground)
    : SceneObject          (Vector2(coord_x, coord_y)),
      QGraphicsEllipseItem (nullptr),
      diameter             (size),
      obj_type             ("Robot"),
      mode                 (MANUAL),
      rotation_direction   (CLOCKWISE),
      rotation_step        (15.0),
      detect_threshold     (0.0),
      playground           (playground),
      arrow                (nullptr)
{
    constructor_actions();
}

Robot::Robot (const qreal size, const Vector2& coords, PlayGround* playground)
    : Robot(size, coords.x(), coords.y(), playground)
{
}

Robot::Robot (const qreal size, const Vector2& coords, qreal rotation_angle, const Mode mode, const Direction rot_direction, const qreal rotation_step, const qreal collision_thr, PlayGround* playground)
    : SceneObject          (coords, rotation_angle),
      QGraphicsEllipseItem (nullptr),
      diameter             (size),
      obj_type             ("Robot"),
      mode                 (mode),
      rotation_direction   (rot_direction),
      rotation_step        (rotation_step),
      detect_threshold     (collision_thr),
      playground           (playground),
      arrow                (nullptr)
{
    constructor_actions();
}

void Robot::constructor_actions() {
    // Set proper stack order
    this->setZValue(0);

    // Set ellipsis properties
    this->setRect(coords.x(), coords.y(), diameter, diameter);

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

    // Create arrow showing current rotation_angle
    arrow = new QGraphicsPolygonItem(QPolygonF(points_arr), this);
    arrow->setPos(this->rect().center().x(), this->rect().center().y() - ARROW_LENGTH);
    arrow->setRotation(rotation_angle);

    // Set arrow color to red to ensure better visibility inside scene
    arrow->setPen(QPen(Qt::red));

    // Set correct rotation_angle origin
    arrow->setTransformOriginPoint(QPointF(0, ARROW_LENGTH));

    // Allow hover events
    this->setAcceptHoverEvents(true);

    this->physical_robot = new PhysicalRobot(this);
    playground->get_physics_server()->register_robot(this->physical_robot);
}

Robot::~Robot () {
    delete arrow;
    playground->get_physics_server()->unregister_robot(this->physical_robot);
    delete physical_robot;
}

QString Robot::get_type () {
    return obj_type;
}

QPointF Robot::get_pos () {
    return QPointF(coords.x(), coords.y());
}

qreal Robot::get_diameter () {
    return diameter;
}

QRectF Robot::get_rect () {
    return this->rect();
}

QGraphicsPolygonItem* Robot::get_robot_arrow () {
    return arrow;
}

QVector<QString> Robot::get_robot_info () {
    // Construct new vector containing robot's details
    return QVector<QString> {
        QString::number(mode),
        QString::number(detect_threshold),
        QString::number(rotation_step),
        QString::number(rotation_direction)
    };
}

void Robot::set_mode (Mode new_mode) {
    mode = new_mode;
    physical_robot->queued_action = PhysicalRobot::QueuedAction::NONE; // Reset queued action just to be sure
}

void Robot::set_detect_threshold (qreal new_threshold) {
    detect_threshold = new_threshold;
}

void Robot::set_rotation_step (qreal new_step) {
    rotation_step = new_step;
}

void Robot::set_rotation_step_radians (qreal new_step) {
    rotation_step = qRadiansToDegrees(new_step);
}

void Robot::set_rotation_direction (Direction new_direction) {
    rotation_direction = new_direction;
}

Mode Robot::get_mode() {
    return mode;
}

qreal Robot::get_rotation_step () {
    return rotation_step;
}

qreal Robot::get_rotation_step_radians () {
    return qDegreesToRadians(rotation_step);
}

Direction Robot::get_rotation_direction () {
    return rotation_direction;
}

qreal Robot::get_detect_threshold () {
    return detect_threshold;
}

void Robot::set_active (bool active, Action action) {
    color      = Qt::black;
    is_active  = active;
    obj_action = action;

    if (active && action == MOVE_ACTION) { // Focused and moving -> red
        color = Qt::red;
    }

    QPen pen(color);
    // Apply new color
    this->setPen(pen);
}

void Robot::set_obj_pos (const QPointF pos) {
    // if (playground->boundingRect().contains(QRectF(pos.x(), pos.y(), diameter, diameter))) { // If new position is inside current scene, update robot coords
        coords.setX(pos.x());
        coords.setY(pos.y());

        // Set new position of robot
        this->setRect(coords.x(), coords.y(), diameter, diameter);

        // Re-center arrow after robot moved
        arrow->setPos(this->rect().center().x(), this->rect().center().y() - ARROW_LENGTH);

        this->physical_robot->update_shape();
        this->physical_robot->update_shapecast();
    // }
}

void Robot::keyPressEvent (QKeyEvent* event) {
    if (mode == AUTOMATIC) {
        return;
    }
    switch (event->key()) {
        case Qt::Key_Left: // Rotate counter-clockwise
            this->physical_robot->queued_action = PhysicalRobot::QueuedAction::TURN_LEFT;
            this->playground->get_physics_server()->queue_step();
            break;
        case Qt::Key_Right: // Rotate clockwise
            this->physical_robot->queued_action = PhysicalRobot::QueuedAction::TURN_RIGHT;
            this->playground->get_physics_server()->queue_step();
            break;
        case Qt::Key_Up: // Move forward
            this->physical_robot->queued_action = PhysicalRobot::QueuedAction::MOVE;
            this->playground->get_physics_server()->queue_step();
            break;
        case Qt::Key_Down: // Ignore as robot should move only forward
            break;
        case Qt::Key_Space:
            this->playground->get_physics_server()->queue_step();
        default: // Ignore any other keys
            break;
    }
}

void Robot::mouseDoubleClickEvent (QGraphicsSceneMouseEvent* event) {
    // Remove Robot
    if (event->button() == Qt::MouseButton::RightButton) {
        // If robot widget is shown, hide it first
        Robot_Info::hide_related_widget(this);
        playground->remove_scene_obj(this);
    }
}

void Robot::mousePressEvent (QGraphicsSceneMouseEvent* event) {
    if (event->button() == Qt::MouseButton::LeftButton) {
        if (!is_active) { // Notify PlayGround and get focus
            // Stop the robot if moving around
            this->old_mode = this->mode;
            this->mode = MANUAL;
            this->move_action_mouse_offset = this->coords - event->scenePos();
            playground->set_active_obj(this, MOVE_ACTION);
        }
        else { // Lose focus
            playground->disable_focus();
        }
    }

    if (event->button() == Qt::MouseButton::RightButton) {
        if (is_active) { // Lose focus and return to previous pos
            // this->set_obj_pos(playground->get_active_obj_orig_pos());
            playground->disable_focus();
        }
        else { // Show Robot details
            Robot_Info::show_widget(this);
        }
    }
}

void Robot::mouseReleaseEvent (QGraphicsSceneMouseEvent* event) {
    if (event->button() == Qt::MouseButton::LeftButton) { // move event ended
        // Re-enable robot
        this->mode = this->old_mode;
    }
}

void Robot::mouseMoveEvent (QGraphicsSceneMouseEvent* event) {
    if (is_active) { // Move robot, if focused
        this->set_obj_pos(event->scenePos() + this->move_action_mouse_offset);
    }
}

void Robot::hoverEnterEvent (QGraphicsSceneHoverEvent* event /*not used*/) {
    QPen pen(Qt::gray);
    // Apply new color
    this->setPen(pen);
}

void Robot::hoverLeaveEvent (QGraphicsSceneHoverEvent* event /*not used*/) {
    QPen pen(color);
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
    rotation_angle += angle;
    // Rotation_angle of the arrow
    arrow->setRotation(rotation_angle);
}

QJsonObject Robot::get_obj_data () {
    QJsonObject conf_data = SceneObject::get_obj_data();
    conf_data["obj_type"]           = obj_type;
    conf_data["diameter"]           = diameter;
    conf_data["mode"]               = mode;
    conf_data["rotation_step"]      = rotation_step;
    conf_data["rotation_direction"] = rotation_direction;
    conf_data["collis_threshold"]   = detect_threshold;
    return conf_data;
}
