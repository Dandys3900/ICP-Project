#include "Headers/Obstacle.h"

Obstacle::Obstacle (const qreal width, const qreal height, const qreal axis_x, const qreal axis_y, PlayGround* playground)
    : mp_width      (width),
      mp_height     (height),
      mp_coord_x    (axis_x),
      mp_coord_y    (axis_y),
      mp_type       ("Obstacle"),
      mp_playground (playground)
{
    this->setRect(mp_coord_x, mp_coord_y, mp_width, mp_height);

    // Make Obstacle moveable (able to receive mouse events)
    this->setFlag(QGraphicsItem::ItemIsMovable);
}

Obstacle::~Obstacle ()
{
}

QString Obstacle::get_type () {
    return mp_type;
}

MoveableObject* Obstacle::get_object () {
    return this;
}

QPointF Obstacle::get_pos () {
    return QPointF(mp_coord_x, mp_coord_y);
}

void Obstacle::set_obj_pos (QPointF pos) {
    if (scene()->sceneRect().contains(pos.x(), pos.y())) {
        // If new position is inside current scene, update robot coords
        mp_coord_x = pos.x();
        mp_coord_y = pos.y();

        this->setRect(mp_coord_x, mp_coord_y, mp_width, mp_height);
    }
}

void Obstacle::set_marked (bool marked) {
    // Change obstacle color when selected or not
    QPen pen((marked) ? Qt::red : Qt::black);

    // Apply new color
    this->setPen(pen);
}

void Obstacle::mousePressEvent (QGraphicsSceneMouseEvent* event) {
    // Allow using only the left mouse key for placing objects
    if (event->button() == Qt::MouseButton::LeftButton) {
        // Mouse click on the Obstacle, notify PlayGround we have an object to move with
        mp_playground->set_moved_obj(this);
    }
}

void Obstacle::keyPressEvent (QKeyEvent* event) {
    // Ignore key presses
}

void Obstacle::mouseMoveEvent (QGraphicsSceneMouseEvent *event) {
    mp_playground->mouseMoveEvent(event);
}
