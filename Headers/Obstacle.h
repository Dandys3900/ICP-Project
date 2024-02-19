#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "LibsFile.h"
#include "SceneObject.h"
#include "PlayGround.h"

class Obstacle : public SceneObject, public QGraphicsRectItem {
    private:
        /* mp_size.x() ... width
           mp_size.y() ... height */
        Vector2 mp_size;
        Vector2 mp_coords;

        qreal mp_rotation;

        QString mp_type;

        Action mp_obj_action;

        class PlayGround* mp_playground;

        bool mp_has_focus;

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

        ~Obstacle ();

        // Implementations of virtual base class methods
        QString get_type () override;
        QPointF get_pos () override;
        void set_obj_pos (const QPointF pos) override;
        void set_focus (bool focus, Action action) override;

    protected:
        // Events - handling
        void mousePressEvent (QGraphicsSceneMouseEvent* event) override;
        void mouseMoveEvent (QGraphicsSceneMouseEvent *event) override;
        void keyPressEvent (QKeyEvent* event) override;
        void mouseDoubleClickEvent (QGraphicsSceneMouseEvent *event);
};

#endif // OBSTACLE_H
