/** ICP Project 2023/2024
 * @file obstacle.h
 * @author Tomáš Daniel (xdanie14)
 * @brief Header file for Obstacle class.
 */

#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "includes/libs_file.h"
#include "scene/scene_object.h"
#include "scene/playground.h"

class Obstacle : public SceneObject, public QGraphicsRectItem {
    private:
        QString mp_obj_type;

        /* mp_size.x() ... width
           mp_size.y() ... height */
        Vector2 mp_size;

        Action mp_obj_action;

        class PlayGround* mp_playground;

        void constructor_actions ();
        void do_rotation (const qreal angle);

    public:
        /**
         * @brief Constructor.
         * @param width Width of rectangle (obstacle).
         * @param height Height of rectangle (obstacle).
         * @param coord_x X-axis position of obstacle in the scene.
         * @param coord_y Y-axis position of obstacle in the scene.
         * @param playground Scene objects and event management.
         */
        Obstacle (const qreal width,
                  const qreal height,
                  const qreal coord_x,
                  const qreal coord_y,
                  PlayGround* playground);
        /**
         * @brief Constructor.
         * @param size Vector containing size of rectangle (obstacle).
         * @param coords Vector containing position of obstacle in the scene.
         * @param playground Scene objects and event management.
         */
        Obstacle (const Vector2& size,
                  const Vector2& coords,
                  PlayGround* playground);
        /**
         * @brief Constructor.
         * @param size Vector containing size of rectangle (obstacle).
         * @param coords Vector containing position of obstacle in the scene.
         * @param rotation Initial rotation of rectangle (obstacle).
         * @param playground Scene objects and event management.
         */
        Obstacle (const Vector2& size,
                  const Vector2& coords,
                  qreal rotation,
                  PlayGround* playGround);
        /**
         * @brief Destructor.
         */
        ~Obstacle ();

        // Implementations of virtual base class methods
        QString get_type () override;
        QPointF get_pos () override;
        QRectF get_rect () override;
        void set_obj_pos (const QPointF pos) override;
        void set_active (bool active, Action action) override;
        QJsonObject get_obj_data () override;

    protected:
        // Events - handling
        void mousePressEvent (QGraphicsSceneMouseEvent* event) override;
        void mouseMoveEvent (QGraphicsSceneMouseEvent* event) override;
        void keyPressEvent (QKeyEvent* event) override;
        void mouseDoubleClickEvent (QGraphicsSceneMouseEvent* event) override;
        void hoverEnterEvent (QGraphicsSceneHoverEvent* event) override;
        void hoverLeaveEvent (QGraphicsSceneHoverEvent* event) override;
};

#endif // OBSTACLE_H
