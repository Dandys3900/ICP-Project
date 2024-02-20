#include "scene/obstacle.h"

Obstacle::Obstacle (const qreal width, const qreal height, const qreal coord_x, const qreal coord_y, PlayGround* playground)
    : mp_size       (width, height),
      mp_coords     (coord_x, coord_y),
      mp_rotation   (0),
      mp_type       ("Obstacle"),
      mp_obj_action (NO_ACTION),
      mp_playground (playground),
      mp_is_active  (false)
{
    this->setRect(mp_coords.x(), mp_coords.y(), mp_size.x(), mp_size.y());

    // Make Obstacle moveable (able to receive mouse events)
    this->setFlag(QGraphicsItem::ItemIsMovable);

    // Set rotation origin
    this->setTransformOriginPoint(QPointF(mp_coords.x() + (mp_size.x() / 2), mp_coords.y() + (mp_size.y() / 2)));
}

Obstacle::Obstacle (const Vector2& size, const Vector2& coords, PlayGround* playground)
    : Obstacle(size.x(), size.y(), coords.x(), coords.y(), playground)
{
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
    if (scene()->sceneRect().contains(QRectF(pos.x(), pos.y(), mp_size.x(), mp_size.y()))) {
        // If new position is inside current scene, update robot coords
        mp_coords.setX(pos.x());
        mp_coords.setY(pos.y());

        this->setRect(mp_coords.x(), mp_coords.y(), mp_size.x(), mp_size.y());

        // Update rotation origin
        this->setTransformOriginPoint(QPointF(mp_coords.x() + (mp_size.x() / 2), mp_coords.y() + (mp_size.y() / 2)));
    }
}

void Obstacle::set_active (bool active, Action action) {
    Qt::GlobalColor color = Qt::black;
    mp_obj_action         = action;
    mp_is_active          = active;

    if (active) {
        if (action == RESIZE_ACTION)
            // Focused and resizing -> blue
            color = Qt::blue;
        else
            // Focused and moving -> red
            color = Qt::red;
    }

    QPen pen(color);
    // Apply new color
    this->setPen(pen);
}

void Obstacle::mousePressEvent (QGraphicsSceneMouseEvent* event) {
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
        if (!mp_is_active) {
            // Notify PlayGround and get focus
            mp_playground->set_active_obj(this, RESIZE_ACTION);
        }
        else {
            // Lose focus and return to previous pos
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
            // Resize current obstacle
            // Calculate change
            QPointF posChange;
            posChange.setX(qFabs(event->pos().x() - this->get_pos().x()));
            posChange.setY(qFabs(event->pos().y() - this->get_pos().y()));

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

void Obstacle::do_rotation (const qreal angle) {
    mp_rotation += angle;
    // Rotate obstacle
    this->setRotation(mp_rotation);
}
