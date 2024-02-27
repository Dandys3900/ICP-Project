#include "obstacle.h"

Obstacle::Obstacle (const qreal width, const qreal height, const qreal coord_x, const qreal coord_y, PlayGround* playground)
    : SceneObject(Vector2(coord_x, coord_y)),
      mp_type       ("Obstacle"),
      mp_size       (width, height),
      mp_playground (playground)
{
    constructor_actions();
}

Obstacle::Obstacle (const Vector2& size, const Vector2& coords, PlayGround* playground)
    : Obstacle(size.x(), size.y(), coords.x(), coords.y(), playground)
{
}

Obstacle::Obstacle (const Vector2& size, const Vector2& coords, qreal rotation, PlayGround* playground)
    : SceneObject(coords, rotation),
      mp_type       ("Obstacle"),
      mp_size       (size),
      mp_playground (playground)
{
    constructor_actions();
}

void Obstacle::constructor_actions () {
    this->setRect(mp_coords.x(), mp_coords.y(), mp_size.x(), mp_size.y());

    // Set rotation origin
    this->setTransformOriginPoint(QPointF(mp_coords.x() + (mp_size.x() / 2), mp_coords.y() + (mp_size.y() / 2)));

    // Allow hover events
    this->setAcceptHoverEvents(true);

    // Set rotation
    this->setRotation(mp_rotation);
}

Obstacle::~Obstacle () {
}

QString Obstacle::get_type () {
    return mp_type;
}

QPointF Obstacle::get_pos () {
    return QPointF(mp_coords.x(), mp_coords.y());
}

void Obstacle::set_obj_pos (const QPointF pos) {
    if (mp_playground->boundingRect().contains(QRectF(pos.x(), pos.y(), mp_size.x(), mp_size.y()))) {
        // If new position is inside current scene, update robot coords
        mp_coords.setX(pos.x());
        mp_coords.setY(pos.y());

        this->setRect(mp_coords.x(), mp_coords.y(), mp_size.x(), mp_size.y());

        // Update rotation origin
        this->setTransformOriginPoint(QPointF(mp_coords.x() + (mp_size.x() / 2), mp_coords.y() + (mp_size.y() / 2)));
    }
}

void Obstacle::set_active (bool active, Action action) {
    mp_color      = Qt::black;
    mp_obj_action = action;
    mp_is_active  = active;

    if (active) {
        if (action == RESIZE_ACTION) { // Focused and resizing -> blue
            mp_color = Qt::blue;
        }
        else { // Focused and moving -> red
            mp_color = Qt::red;
        }
    }

    QPen pen(mp_color);
    // Apply new color
    this->setPen(pen);
}

void Obstacle::mousePressEvent (QGraphicsSceneMouseEvent* event) {
    if (event->button() == Qt::MouseButton::LeftButton) {
        if (!mp_is_active) { // Notify PlayGround and get focus
            mp_playground->set_active_obj(this, MOVE_ACTION);
        }
        else { // Lose focus
            mp_playground->disable_focus();
        }
    }

    if (event->button() == Qt::MouseButton::RightButton) {
        if (!mp_is_active) { // Notify PlayGround and get focus
            mp_playground->set_active_obj(this, RESIZE_ACTION);
        }
        else { // Lose focus and return to previous pos
            this->set_obj_pos(mp_playground->get_active_obj_orig_pos());
            mp_playground->disable_focus();
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
}

void Obstacle::mouseMoveEvent (QGraphicsSceneMouseEvent *event) {
    // React to mouse move only if focused
    if (mp_is_active) {
        if (mp_obj_action == RESIZE_ACTION) {
            // Calculate resize change
            QPointF posChange;
            posChange.setX(qFabs(event->pos().x() - mp_coords.x()));
            posChange.setY(qFabs(event->pos().y() - mp_coords.y()));

            // Update obstacle size
            this->mp_size.setX(posChange.x());
            this->mp_size.setY(posChange.y());

            // Update rectangle and rotation origin
            this->set_obj_pos(mp_coords);
        }
        else { // MOVE_ACTION
            this->set_obj_pos(event->pos());
        }
    }
}

void Obstacle::mouseDoubleClickEvent (QGraphicsSceneMouseEvent *event) {
    // Insert new Obstacle
    if (event->button() == Qt::MouseButton::LeftButton) {
        // Clone this obstacle and insert it to Playground
        Obstacle* newObstacle = new Obstacle(mp_size.x(), mp_size.y(), mp_coords.x(), mp_coords.y(), mp_playground);

        // Add obstacle to the PlayGround
        mp_playground->add_scene_obj(newObstacle);
    }

    // Remove Obstacle
    if (event->button() == Qt::MouseButton::RightButton) {
        mp_playground->remove_scene_obj(this);
    }
}

void Obstacle::hoverEnterEvent (QGraphicsSceneHoverEvent *event /*not used*/) {
    // Light grey color
    setBrush(QBrush(QColor(245, 245, 245)));
}

void Obstacle::hoverLeaveEvent (QGraphicsSceneHoverEvent *event /*not used*/) {
    setBrush(QBrush(Qt::white));
}

void Obstacle::do_rotation (const qreal angle) {
    mp_rotation += angle;
    // Rotate obstacle
    this->setRotation(mp_rotation);
}

QJsonObject Obstacle::get_obj_data () {
    QJsonObject conf_data = SceneObject::get_obj_data();
    conf_data["obj_type"] = mp_type;
    conf_data["size_x"]   = mp_size.x();
    conf_data["size_y"]   = mp_size.y();
    return conf_data;
}
