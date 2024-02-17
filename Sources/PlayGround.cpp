#include "Headers/PlayGround.h"

PlayGround::PlayGround (const qreal width, const qreal height, QGraphicsScene* scene)
    : mp_width                 (width),
      mp_height                (height),
      mp_objs_vec              (),
      mp_moved_obj_orig_pos    (),
      mp_scene                 (scene),
      mp_moved_obj             (nullptr),
      mp_resized_obj           (nullptr),
      mp_cur_action            (NO_ACTION)
{
    this->setRect(0, 0, scene->sceneRect().width(), scene->sceneRect().height());

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

PlayGround::~PlayGround ()
{
}

void PlayGround::set_active_obj (MoveableObject* object, Action action) {
    mp_cur_action = action;

    MoveableObject*& obj = ((mp_cur_action == RESIZE_ACTION) ? mp_moved_obj : mp_resized_obj);
    if (obj) {
        // Unmark object of current action when the action changes
        obj->set_marked(false, mp_cur_action);
        obj = nullptr;
    }

    // Get obj for moving or resizing
    MoveableObject*& action_obj = ((mp_cur_action == RESIZE_ACTION) ? mp_resized_obj : mp_moved_obj);

    if (action_obj) {
        if (action_obj != object) {
            // Unmark current object as it differs from newly selected one
            action_obj->set_marked(false, mp_cur_action);
        }
    }

    action_obj = object;
    mp_moved_obj_orig_pos = QPointF(0, 0);

    if (action_obj) {
        if (action == MOVE_ACTION) {
            mp_moved_obj_orig_pos = action_obj->get_pos();
        }

        action_obj->set_marked(true, mp_cur_action);
    }
}

void PlayGround::addObject (MoveableObject* object) {
    mp_objs_vec.push_back(object);

    if (object->get_type() == QString("Robot")) {
        // Cast it to the Robot class
        Robot* robot = (Robot*)object->get_object();
        if (robot) {
            // Add robot + its arrow
            mp_scene->addItem(robot->get_robot_arrow());
            mp_scene->addItem(robot);
        }
    }
    else {
        // Cast it to the Obstacle class
        Obstacle* obstacle = (Obstacle*)object->get_object();
        if (obstacle) {
            // Add obstacle
            mp_scene->addItem(obstacle);
        }
    }
}

void PlayGround::removeObject (MoveableObject* object) {
    // Try to find object to be deleted in objects vector
    std::vector<MoveableObject*>::iterator iter =
        std::find_if(mp_objs_vec.begin(), mp_objs_vec.end(), [object](MoveableObject* curObj) { return object == curObj; });

    // Found - delete it
    if (iter != mp_objs_vec.end()) {
        // Remove from scene
        mp_scene->removeItem(((Obstacle*)object->get_object()));
        // Remove from vector
        mp_objs_vec.erase(iter);
    }
}

void PlayGround::keyPressEvent (QKeyEvent* event) {
    std::vector<MoveableObject*>::iterator iter;

    for (iter = mp_objs_vec.begin(); iter < mp_objs_vec.end(); ++iter) {
        // Only moving Obstacle should receive keyPresses to rotate
        if (mp_moved_obj && mp_moved_obj->get_type() == QString("Obstacle")) {
            mp_moved_obj->keyPressEvent(event);
        }

        // If none object selected for action, Robot should receive keyPresses
        if ((*iter)->get_type() == QString("Robot") && !mp_resized_obj && !mp_moved_obj) {
            // Distribute the key press event to all robots in the playground
            (*iter)->keyPressEvent(event);
        }
    }
}

void PlayGround::mouseMoveEvent (QGraphicsSceneMouseEvent *event) {
    if (mp_moved_obj) {
        // Set its position to be same as mouse's
        mp_moved_obj->set_obj_pos(event->pos());
    }

    if (mp_resized_obj) {
        Obstacle* curObst = (Obstacle*)mp_resized_obj->get_object();
        QPointF curPos = curObst->get_pos();

        // Calculate change
        QPointF posChange;
        posChange.setX(qFabs(event->pos().x() - curPos.x()));
        posChange.setY(qFabs(event->pos().y() - curPos.y()));

        // Update obstacle size
        curObst->set_rect(curPos, posChange.x(), posChange.y());
    }
}

void PlayGround::mousePressEvent (QGraphicsSceneMouseEvent* event) {
    if (event->button() == Qt::MouseButton::RightButton) {
        if (mp_moved_obj) {
            // Pressing right mouse key means to reset moving object pos
            mp_moved_obj->set_obj_pos(mp_moved_obj_orig_pos);
            set_active_obj(nullptr, MOVE_ACTION);
        }

        if (mp_resized_obj) {
            // Stop resizing and unmark
            set_active_obj(nullptr, RESIZE_ACTION);
        }
    }

    if (event->button() == Qt::MouseButton::LeftButton) {
        // Left key pressed outside moving object -> stop moving and unmark
        if (mp_moved_obj) {
            set_active_obj(nullptr, MOVE_ACTION);
        }
    }
}
