#ifndef ROBOT_H
#define ROBOT_H

#include "src/includes/libs_file.h"
#include "scene_object.h"
#include "playground.h"

class Robot : public SceneObject, public QGraphicsEllipseItem {
    private:
        qreal mp_diameter;
        QString mp_type;
        const size_t mp_id;

        class PlayGround*           mp_playground;
        class QGraphicsPolygonItem* mp_arrow;

        void constructor_actions ();
        void do_rotation (const qreal angle);
        void move_forward ();

    public:
        Robot (const qreal size,
               const qreal coord_x,
               const qreal coord_y,
               PlayGround* playground);

        Robot (const qreal size,
               const Vector2& coords,
               PlayGround* playground);

        Robot (const qreal size,
               const Vector2& coords,
               qreal rotation,
               Action action,
               bool active,
               Qt::GlobalColor color,
               PlayGround* playGround);

        ~Robot ();

        // Implementations of virtual base class methods
        QString get_type () override;
        QPointF get_pos () override;
        void set_obj_pos (const QPointF pos) override;
        void set_active (bool active, Action action) override;
        QJsonObject get_obj_data () override;

        QGraphicsPolygonItem* get_robot_arrow ();

    protected:
        // Events - handling
        void mousePressEvent (QGraphicsSceneMouseEvent* event) override;
        void mouseMoveEvent (QGraphicsSceneMouseEvent *event) override;
        void keyPressEvent (QKeyEvent* event) override;
};

#endif // ROBOT_H
