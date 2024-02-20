#include "Headers/PlayGround.h"

PlayGround::PlayGround (const qreal width, const qreal height, QGraphicsScene* scene)
    : mp_size                (width, height),
      mp_scene_objs_vec      (),
      mp_active_obj_orig_pos (),
      mp_scene               (scene),
      mp_active_obj          (nullptr),
      mp_cur_action          (NO_ACTION)
{
    this->setRect(0, 0, mp_size.x(), mp_size.y());

    // Create black pen
    QPen pen(Qt::black);
    // Set border width
    pen.setWidth(BORDER_WIDTH);
    // Add pen to border to make it bolder
    this->setPen(pen);

    // Make PlayGround focusable
    this->setFlag(QGraphicsItem::ItemIsFocusable);
    this->setFocus();

    // Add PlayGround to the scene
    mp_scene->addItem(this);
}

PlayGround::PlayGround (const Vector2& size, QGraphicsScene* scene)
    : PlayGround(size.x(), size.y(), scene)
{
}

PlayGround::~PlayGround () {
}

QPointF PlayGround::get_active_obj_orig_pos () {
    return mp_active_obj_orig_pos;
}

void PlayGround::disable_focus () {
    // Reset original position of active object
    mp_active_obj_orig_pos = QPointF(0, 0);

    // Active item change, lose focus on current active
    if (mp_active_obj) {
        mp_active_obj->set_active(false, NO_ACTION);
        mp_active_obj = nullptr;
    }
}

void PlayGround::set_active_obj (SceneObject* object, Action action) {
    mp_cur_action = action;

    // Un-focus current active object, if any
    disable_focus();

    // Set new active object
    mp_active_obj = object;

    if (mp_active_obj) {
        mp_active_obj_orig_pos = mp_active_obj->get_pos();
        mp_active_obj->set_active(true, mp_cur_action);
    }
}

void PlayGround::add_scene_obj (SceneObject* object) {
    mp_scene_objs_vec.push_back(object);

    if (object->get_type() == QString("Robot")) {
        // Cast it to the Robot class
        Robot* robot = dynamic_cast<Robot*>(object);
        if (robot) {
            // Add robot + its arrow
            mp_scene->addItem(robot->get_robot_arrow());
            mp_scene->addItem(robot);
        }
    }
    else {
        // Cast it to the Obstacle class
        Obstacle* obstacle = dynamic_cast<Obstacle*>(object);
        if (obstacle) {
            // Add obstacle
            mp_scene->addItem(obstacle);
        }
    }
}

void PlayGround::remove_scene_obj (SceneObject* object) {
    QVector<SceneObject*>::iterator iter;

    // Try to find object to be deleted in objects vector
    iter = std::find_if(mp_scene_objs_vec.begin(), mp_scene_objs_vec.end(),
                        [object](SceneObject* curObj) {
                            return object == curObj;
                        });

    // Found - delete it
    if (iter != mp_scene_objs_vec.end()) {
        // Remove from scene
        Obstacle* obstacle = dynamic_cast<Obstacle*>(object);
        if (obstacle) {
            mp_scene->removeItem(obstacle);
        }
        // Remove from vector as well
        mp_scene_objs_vec.erase(iter);

        // In case deleted object is active
        if (object == mp_active_obj) {
            mp_active_obj = nullptr;
        }
    }
}

void PlayGround::keyPressEvent (QKeyEvent* event) {
    QVector<SceneObject*>::iterator iter;

    // If we have active object, deliver this exclusively to it
    if (mp_active_obj) {
        mp_active_obj->keyPressEvent(event);
    }
    else {
        // Robots should receive key presses to move
        for (iter = mp_scene_objs_vec.begin(); iter < mp_scene_objs_vec.end(); ++iter) {
            if ((*iter)->get_type() == QString("Robot")) {
                (*iter)->keyPressEvent(event);
            }
        }
    }
}

void PlayGround::mouseMoveEvent (QGraphicsSceneMouseEvent *event) {
    if (mp_active_obj) {
        // Distribute mouse move event to focused (active) object
        mp_active_obj->mouseMoveEvent(event);
    }
}

void PlayGround::mousePressEvent (QGraphicsSceneMouseEvent* event) {
    if (mp_active_obj) {
        // Distribute mouse move event to focused (active) object
        mp_active_obj->mousePressEvent(event);
    }
}
