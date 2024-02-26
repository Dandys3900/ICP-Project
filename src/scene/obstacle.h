#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "includes/libs_file.h"
#include "scene/scene_object.h"
#include "scene/playground.h"

class Obstacle : public SceneObject, public QGraphicsRectItem {
    private:
        QString mp_type;

        /* mp_size.x() ... width
           mp_size.y() ... height */
        Vector2 mp_size;
        const size_t mp_id;

        Action mp_obj_action;

        class PlayGround* mp_playground;

        void constructor_actions ();
        void do_rotation (const qreal angle);

    public:
        Obstacle (const qreal width,
                  const qreal height,
                  const qreal coord_x,
                  const qreal coord_y,
                  PlayGround* playground);

        Obstacle (const Vector2& size,
                  const Vector2& coords,
                  PlayGround* playground);

        Obstacle (const Vector2& size,
                  const Vector2& coords,
                  qreal rotation,
                  PlayGround* playGround);

        ~Obstacle ();

        // Implementations of virtual base class methods
        QString get_type () override;
        QPointF get_pos () override;
        void set_obj_pos (const QPointF pos) override;
        void set_active (bool active, Action action) override;
        QJsonObject get_obj_data () override;

    protected:
        // Events - handling
        void mousePressEvent (QGraphicsSceneMouseEvent* event) override;
        void mouseMoveEvent (QGraphicsSceneMouseEvent *event) override;
        void keyPressEvent (QKeyEvent* event) override;
        void mouseDoubleClickEvent (QGraphicsSceneMouseEvent *event);
        void hoverEnterEvent (QGraphicsSceneHoverEvent *event) override;
        void hoverLeaveEvent (QGraphicsSceneHoverEvent *event) override;
};

#endif // OBSTACLE_H
