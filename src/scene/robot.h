#ifndef ROBOT_H
#define ROBOT_H

#include "includes/libs_file.h"
#include "scene/scene_object.h"
#include "scene/playground.h"

class Robot : public SceneObject, public QGraphicsEllipseItem {
    private:
        Vector2 mp_coords;

        qreal mp_diameter;
        qreal mp_rotation;

        QString mp_type;

        Action mp_obj_action;

        class PlayGround*           mp_playground;
        class QGraphicsPolygonItem* mp_arrow;

        bool mp_is_active;

        void do_rotation (const qreal angle);
        void move_forward ();

    public:
        Robot (const qreal size,
               const qreal coords_x,
               const qreal coords_y,
               PlayGround* playground);

        Robot (const qreal size,
               const Vector2& coords,
               PlayGround* playground);

        ~Robot ();

        // Implementations of virtual base class methods
        QString get_type () override;
        QPointF get_pos () override;
        void set_obj_pos (const QPointF pos) override;
        void set_active (bool active, Action action) override;
        QGraphicsPolygonItem* get_robot_arrow ();

    protected:
        // Events - handling
        void mousePressEvent (QGraphicsSceneMouseEvent* event) override;
        void mouseMoveEvent (QGraphicsSceneMouseEvent *event) override;
        void keyPressEvent (QKeyEvent* event) override;
};

#endif // ROBOT_H
