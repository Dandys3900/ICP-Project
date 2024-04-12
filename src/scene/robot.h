#ifndef ROBOT_H
#define ROBOT_H

#include "includes/libs_file.h"
#include "scene/scene_object.h"
#include "scene/playground.h"
#include "scene/robot_info.h"

class Robot : public SceneObject, public QGraphicsEllipseItem {
    private:
        qreal mp_diameter;
        QString mp_type;

        // Robot details
        enum Mode mp_mode;
        enum Direction mp_rotation_direction;
        qreal mp_rotation_angle;
        qreal mp_detect_threshold;

        class PlayGround*     mp_playground;
        QGraphicsPolygonItem* mp_arrow;

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
               PlayGround* playGround);

        ~Robot ();

        // Implementations of virtual base class methods
        QString get_type () override;
        QPointF get_pos () override;
        QRectF get_rect () override;
        void set_obj_pos (const QPointF pos) override;
        void set_active (bool active, Action action) override;
        QJsonObject get_obj_data () override;

        QGraphicsPolygonItem* get_robot_arrow ();

        QVector<QString> get_robot_info ();
        // Setters for possible updates of robot info
        void set_mode (int new_mode);
        void set_rotation_angle (qreal new_angle);
        void set_rotation_direction (int new_direction);
        void set_detect_threshold (qreal new_threshold);

    protected:
        // Events - handling
        void mousePressEvent (QGraphicsSceneMouseEvent* event) override;
        void mouseMoveEvent (QGraphicsSceneMouseEvent* event) override;
        void keyPressEvent (QKeyEvent* event) override;
        void mouseDoubleClickEvent (QGraphicsSceneMouseEvent *event) override;
        void hoverEnterEvent (QGraphicsSceneHoverEvent* event) override;
        void hoverLeaveEvent (QGraphicsSceneHoverEvent* event) override;
};

#endif // ROBOT_H
