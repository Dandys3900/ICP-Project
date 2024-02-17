#include "Headers/PlayGround.h"

PlayGround::PlayGround (const qreal width, const qreal height, QGraphicsScene* scene)
    : mp_width              (width),
      mp_height             (height),
      mp_objs_vec           (),
      mp_moved_obj_orig_pos (),
      mp_scene              (scene),
      m_moved_obj           (nullptr)
{
    this->setRect(ZERO_VAL, ZERO_VAL, scene->sceneRect().width(), scene->sceneRect().height());

    // Create black pen
    QPen pen(Qt::black);
    // Set border width
    pen.setWidth(BORDER_WIDTH);
    // Add pen to border to make it bolder
    this->setPen(pen);

    constructor_actions();
}

PlayGround::~PlayGround ()
{
}

void PlayGround::constructor_actions () {
    // Make PlayGround focusable
    this->setFlag(QGraphicsItem::ItemIsFocusable);
    this->setFocus();

    // Add PlayGround to the scene
    mp_scene->addItem(this);
}

void PlayGround::set_moved_obj (MoveableObject* object) {
    if (m_moved_obj) {
        if (m_moved_obj != object) {
            // Unmark current object as it differs from newly selected one
            m_moved_obj->set_marked(false);
        }
    }

    m_moved_obj = object;
    mp_moved_obj_orig_pos = QPointF(0, 0);

    if (object) {
        mp_moved_obj_orig_pos = object->get_pos();
        object->set_marked(true);
    }
}

void PlayGround::addObject (MoveableObject* object) {
    mp_objs_vec.push_back(object);

    if (object->get_type() == QString("Robot")) {
        // Cast it to the Robot class
        Robot* robot = (Robot*)object->get_object();
        if (robot) {
            // Add robot + its arrow
            mp_scene->addItem(robot->m_arrow);
            mp_scene->addItem(robot);
        }
    }
    else {
        // Cast it to the Robot class
        Obstacle* obstacle = (Obstacle*)object->get_object();
        if (obstacle) {
            // Add obstacle
            mp_scene->addItem(obstacle);
        }
    }
}

void PlayGround::keyPressEvent (QKeyEvent* event) {
    std::vector<MoveableObject*>::iterator iter;

    for (iter = mp_objs_vec.begin(); iter < mp_objs_vec.end(); ++iter) {
        if (m_moved_obj) {
            m_moved_obj->keyPressEvent(event);
        }
        else if ((*iter)->get_type() == QString("Robot")) {
            // Distribute the key press event to all robots in the playground
            (*iter)->keyPressEvent(event);
        }
    }
}

void PlayGround::mouseMoveEvent (QGraphicsSceneMouseEvent *event) {
    if (m_moved_obj) {
        // There is an object to be moved with
        QPointF orig_pos = m_moved_obj->get_pos();

        // Set its position to be same as mouse's
        m_moved_obj->set_obj_pos(event->pos());

        // Check if still fits to the window
        if (!mp_scene->sceneRect().contains(m_moved_obj->get_pos())) {
            // If not, revert to previous pos
            m_moved_obj->set_obj_pos(orig_pos);
        }
    }
}

void PlayGround::mousePressEvent (QGraphicsSceneMouseEvent* event) {
    if (m_moved_obj) {
        if (event->button() == Qt::MouseButton::RightButton) {
            // Pressing right mouse key means to reset moving object pos
            m_moved_obj->set_obj_pos(mp_moved_obj_orig_pos);
            m_moved_obj->set_marked(false);
        }

        // Left key pressed outside moving object -> stop moving and unmark
        if (event->button() == Qt::MouseButton::LeftButton) {
            m_moved_obj->set_marked(false);
            set_moved_obj(nullptr);
        }
    }
}
