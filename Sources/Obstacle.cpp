#include "Headers/Obstacle.h"

Obstacle::Obstacle (const qreal width, const qreal height, const qreal coord_x, const qreal coord_y, PlayGround* playground)
    : mp_size       (width, height),
      mp_coords     (coord_x, coord_y),
      mp_rotation   (0),
      mp_type       ("Obstacle"),
      mp_pen_colour (Qt::black),
      mp_playground (playground)
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
    delete mp_playground;
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

void Obstacle::set_marked (bool marked, Action action) {
    mp_pen_colour = Qt::black;
    if (marked) {
        if (action == RESIZE_ACTION)
            // Marked and resizing
            mp_pen_colour = Qt::GlobalColor::blue;
        else
            // Marked and just selected
            mp_pen_colour = Qt::GlobalColor::red;
    }

    QPen pen(mp_pen_colour);
    // Apply new color
    this->setPen(pen);
}

void Obstacle::set_rect (const QPointF pos, const qreal width, const qreal height) {
    mp_size.setX(width);
    mp_size.setY(height);
    set_obj_pos(pos);
}

void Obstacle::mousePressEvent (QGraphicsSceneMouseEvent* event) {
    Action action;
    // Left mouse key for placing objects
    if (event->button() == Qt::MouseButton::LeftButton) {
        action = MOVE_ACTION;
    }
    // Right mouse key for resizing obstacle
    else if (event->button() == Qt::MouseButton::RightButton) {
        action = RESIZE_ACTION;
    }

    // Start action
    if (mp_pen_colour == Qt::black) {
        mp_playground->set_active_obj(this, action);
    }
    else {
        // Stop action and unmark
        mp_playground->mousePressEvent(event);
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
    mp_playground->mouseMoveEvent(event);
}

void Obstacle::mouseDoubleClickEvent (QGraphicsSceneMouseEvent *event) {
    // Insert new Obstacle
    if (event->button() == Qt::MouseButton::LeftButton) {
        // Clone this obstacle and insert it to Playground
        Obstacle* newObstacle = new Obstacle(mp_size.x(), mp_size.y(), mp_coords.x(), mp_coords.y(), mp_playground);
        // Add obstacle to the playground thus to the scene
        mp_playground->addObject(newObstacle);
    }

    // Remove Obstacle
    if (event->button() == Qt::MouseButton::RightButton) {
        mp_playground->removeObject(this);
    }
}

void Obstacle::do_rotation (const qreal angle) {
    mp_rotation += angle;
    // Rotate obstacle
    this->setRotation(mp_rotation);
}
