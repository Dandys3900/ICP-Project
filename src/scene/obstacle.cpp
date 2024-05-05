/** ICP Project 2023/2024
 * @file obstacle.cpp
 * @author Tomáš Daniel (xdanie14)
 * @brief Representation of an obstacle in the scene.
 */

#include "obstacle.h"

Obstacle::Obstacle (const qreal width, const qreal height, const qreal coord_x, const qreal coord_y, PlayGround* playground)
    : SceneObject       (Vector2(coord_x, coord_y)),
      QGraphicsRectItem (nullptr),
      obj_type          ("Obstacle"),
      size              (width, height),
      playground        (playground)
{
    constructor_actions();
}

Obstacle::Obstacle (const Vector2& size, const Vector2& coords, PlayGround* playground)
    : Obstacle(size.x(), size.y(), coords.x(), coords.y(), playground)
{
}

Obstacle::Obstacle (const Vector2& size, const Vector2& coords, qreal rotation, PlayGround* playground)
    : SceneObject       (coords, rotation),
      QGraphicsRectItem (nullptr),
      obj_type          ("Obstacle"),
      size              (size),
      playground        (playground)
{
    constructor_actions();
}

void Obstacle::constructor_actions () {
    // Set proper stack order
    this->setZValue(0);

    this->setRect(coords.x(), coords.y(), size.x(), size.y());

    // Set rotation origin
    this->setTransformOriginPoint(QPointF(this->rect().center().x(), this->rect().center().y()));

    // Allow hover events
    this->setAcceptHoverEvents(true);

    // Set rotation
    this->setRotation(rotation_angle);

    this->physical_obstacle = new PhysicalObstacle(this);
    playground->get_physics_server()->register_obstacle(this->physical_obstacle);
}

Obstacle::~Obstacle () {
    playground->get_physics_server()->unregister_obstacle(this->physical_obstacle);
    delete physical_obstacle;
}

QString Obstacle::get_type () {
    return obj_type;
}

QPointF Obstacle::get_pos () {
    return QPointF(this->rect().x(), this->rect().y());
}

QRectF Obstacle::get_rect () {
    return this->rect();
}

void Obstacle::set_obj_pos (const QPointF pos) {
    coords.setX(pos.x());
    coords.setY(pos.y());

    this->setRect(coords.x(), coords.y(), size.x(), size.y());

    // Update rotation origin
    this->setTransformOriginPoint(this->rect().center());

    this->physical_obstacle->update_shape();
}


Vector2 Obstacle::get_size() {
    return size;
}

void Obstacle::set_active (bool active, Action action) {
    color      = Qt::black;
    obj_action = action;
    is_active  = active;

    if (active) {
        if (action == RESIZE_ACTION) { // Focused and resizing -> blue
            color = Qt::blue;
        }
        else { // Focused and moving -> red
            color = Qt::red;
        }
    }

    QPen pen(color);
    // Apply new color
    this->setPen(pen);
}

void Obstacle::mousePressEvent (QGraphicsSceneMouseEvent* event) {
    if (event->button() == Qt::MouseButton::LeftButton) {
        if (!is_active) { // Notify PlayGround and get focus
            this->move_action_mouse_offset = this->rect().topLeft() - event->scenePos();
            playground->set_active_obj(this, MOVE_ACTION);
        }
        else { // Lose focus
            playground->disable_focus();
        }
    }

    if (event->button() == Qt::MouseButton::RightButton) {
        if (!is_active) { // Notify PlayGround and get focus
            playground->set_active_obj(this, RESIZE_ACTION);
        }
        else { // Lose focus and return to previous pos
            // this->set_obj_pos(playground->get_active_obj_orig_pos());
            playground->disable_focus();
        }
    }
}

void Obstacle::keyPressEvent (QKeyEvent* event) {
    switch (event->key()) {
        case Qt::Key_Left:
            // Rotate counter-clockwise
            do_rotation(qreal(-5));
            break;
        case Qt::Key_Right:
            // Rotate clockwise
            do_rotation(qreal(5));
            break;
        default:
            break;
    }
    this->physical_obstacle->update_shape();
    this->physical_obstacle->update_shape();
}

void Obstacle::mouseMoveEvent (QGraphicsSceneMouseEvent* event) {
    // React to mouse move only if focused
    if (is_active) {
        if (obj_action == RESIZE_ACTION) {
            // Calculate new rectangle based on initial position and current mouse position
            QRectF newRect = QRectF(coords, event->scenePos()).normalized();

            // Update size
            size.setX(newRect.size().width());
            size.setY(newRect.size().height());

            // If the new rectangle is within the scene, update rectangle and rotation origin
            if (playground->boundingRect().contains(newRect)) {
                this->setRect(newRect);
                this->setTransformOriginPoint(newRect.center());
                this->physical_obstacle->update_shape();
                this->physical_obstacle->update_shape();
            }
        }
        else { // MOVE_ACTION
            this->set_obj_pos(event->scenePos() + this->move_action_mouse_offset);
        }
    }
}

void Obstacle::mouseDoubleClickEvent (QGraphicsSceneMouseEvent* event) {
    // Insert new Obstacle
    if (event->button() == Qt::MouseButton::LeftButton) {
        // Clone this obstacle and insert it to Playground
        Obstacle* newObstacle = new Obstacle(size.x(), size.y(), this->rect().x(), this->rect().y(), playground);

        // Add obstacle to the PlayGround
        playground->add_scene_obj(newObstacle);
    }

    // Remove Obstacle
    if (event->button() == Qt::MouseButton::RightButton) {
        playground->remove_scene_obj(this);
    }
}

void Obstacle::hoverEnterEvent (QGraphicsSceneHoverEvent* event /*not used*/) {
    QPen pen(Qt::gray);
    // Apply new color
    this->setPen(pen);
}

void Obstacle::hoverLeaveEvent (QGraphicsSceneHoverEvent* event /*not used*/) {
    QPen pen(color);
    // Apply new color
    this->setPen(pen);
}

void Obstacle::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    // Texture source
    QPixmap img(":/textures/box.jpeg");
    // Paint the background image
    painter->drawPixmap(
        boundingRect().toRect(),
        img.scaled(boundingRect().size().toSize(), Qt::KeepAspectRatio, Qt::SmoothTransformation)
    );

    // Call the base class implementation to ensure proper drawing
    QGraphicsRectItem::paint(painter, option, widget);
}

void Obstacle::do_rotation (const qreal angle) {
    rotation_angle += angle;
    // Rotate obstacle
    this->setRotation(rotation_angle);
}

QJsonObject Obstacle::get_obj_data () {
    QJsonObject conf_data = SceneObject::get_obj_data();
    conf_data["obj_type"] = obj_type;
    conf_data["size_x"]   = size.x();
    conf_data["size_y"]   = size.y();
    return conf_data;
}
