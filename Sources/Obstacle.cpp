#include "Headers/Obstacle.h"

Obstacle::Obstacle (const qreal width, const qreal height, const qreal axis_x, const qreal axis_y, PlayGround* playground)
    : mp_width      (width),
      mp_height     (height),
      mp_coord_x    (axis_x),
      mp_coord_y    (axis_y),
      mp_rotation   (0),
      mp_type       ("Obstacle"),
      mp_pen_colour (Qt::black),
      mp_playground (playground),
      mp_id         (ConfigManager::generate_id())
{
    this->setRect(mp_coord_x, mp_coord_y, mp_width, mp_height);

    // Make Obstacle moveable (able to receive mouse events)
    this->setFlag(QGraphicsItem::ItemIsMovable);

    // Set rotation origin
    this->setTransformOriginPoint(QPointF(mp_coord_x + (mp_width / 2), mp_coord_y + (mp_height / 2)));
}

Obstacle::~Obstacle ()
{
    delete mp_playground;
}

QString Obstacle::get_type () {
    return mp_type;
}

void* Obstacle::get_object () {
    return this;
}

QPointF Obstacle::get_pos () {
    return QPointF(mp_coord_x, mp_coord_y);
}

void Obstacle::set_obj_pos (const QPointF pos) {
    if (scene()->sceneRect().contains(QRectF(pos.x(), pos.y(), mp_width, mp_height))) {
        // If new position is inside current scene, update robot coords
        mp_coord_x = pos.x();
        mp_coord_y = pos.y();

        this->setRect(mp_coord_x, mp_coord_y, mp_width, mp_height);

        // Update rotation origin
        this->setTransformOriginPoint(QPointF(mp_coord_x + (mp_width / 2), mp_coord_y + (mp_height / 2)));
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
    mp_width  = width;
    mp_height = height;
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
        Obstacle* newObstacle = new Obstacle(mp_width, mp_height, mp_coord_x, mp_coord_y, mp_playground);
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

QString Obstacle::exportObjData () {
    QString objData = "<class>\n";
    objData += "<type>"     + mp_type                        + "</type>\n";
    objData += "<id>"       + QString::number(mp_id)         + "</id>\n";
    objData += "<height>"   + QString::number(mp_height)     + "</height>\n";
    objData += "<width>"    + QString::number(mp_width)      + "</width>\n";
    objData += "<coordx>"   + QString::number(mp_coord_x)    + "</coordx>\n";
    objData += "<coordy>"   + QString::number(mp_coord_y)    + "</coordy>\n";
    objData += "<rotation>" + QString::number(mp_rotation)   + "</rotation>\n";
    objData += "<color>"    + QString::number(mp_pen_colour) + "</color>\n";
    objData += "</class>\n";

    return objData;
}
