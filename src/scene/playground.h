/** ICP Project 2023/2024
 * @file playground.h
 * @author Tomáš Daniel (xdanie14)
 * @brief Header file for PlayGround class.
 */

#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#include "includes/libs_file.h"

#include "scene/robot.h"
#include "scene/obstacle.h"

#include "physics/server/physics_server.h"

// Enum representing desired config file operation
enum Operation : int {
    LOAD = 0,
    STORE
};


class PhysicsServer;


class PlayGround : public QGraphicsRectItem, public QObject {
    private:
        // Vector for storing instancies of Robots and Obstacles placed to scene
        QVector<SceneObject*> mp_scene_objs_vec;

        // Vector for storing generated objects ids
        QVector<size_t> m_ids_array;

        QPointF mp_active_obj_orig_pos;

        QGraphicsScene*    mp_scene;
        class SceneObject* mp_active_obj;
        class SceneObject* mp_toplace_obj;

        Action mp_cur_action;

        // PhysicsServer of the Playground
        PhysicsServer* physics_server;
        Mode simulation_mode = MANUAL;

        QTimer* automatic_mode_timer;
        bool automatic_mode_running = false;
        int automatic_mode_step_interval = 0;

        /**
         * @brief Private method for adding new item(s) to the scene.
         * @param new_item Item to be added.
         */
        void add_to_scene (QGraphicsItem* new_item);

        void on_automatic_mode_timer_timeout();

    public:
        /**
         * @brief Constructor.
         * @param scene Constructed scene to be handled.
         */
        PlayGround (QGraphicsScene* scene);
        /**
         * @brief Destructor.
         */
        ~PlayGround ();

        /**
         * @brief Adding objects to the playground (scene).
         * @param object Target object.
         */
        void add_scene_obj (SceneObject* object);
        /**
         * @brief Removing objects from the playground (scene).
         * @param object Target object.
         */
        void remove_scene_obj (SceneObject* object);
        /**
         * @brief Set target scene object as currently active.
         * @param object Target object.
         * @param action Selects action to be done with target (active) object.
         */
        void set_active_obj (SceneObject* object, Action action);
        /**
         * @brief Active scene object will lose focus.
         */
        void disable_focus ();
        /**
         * @brief New scene object which will be placed by mouse click to the playground (scene).
         * @param object Target object.
         */
        void set_toplace_obj (SceneObject* object);
        /**
         * @brief Sets the simulation mode
         * @param mode new simulation mode
         */
        void set_mode(Mode mode);
        /**
         * @brief Enables or pauses automatic mode
         * @param running determines if automatic simulation is enabled or stopped
         */
        void set_automatic_mode_running(bool running);
        /**
         * @brief sets the speed of automatic mode
         * @param speed speed of the automatic mode simulation from 1 to 100. Higher is faster.
         */
        void set_automatic_mode_speed(int speed);
        /**
         * @brief Returns pointer to the Playground's PhysicsServer
         * @return PhysicsServer* of this Playground.
         */
        PhysicsServer* get_physics_server();
        /**
         * @brief Returns scene coordinates where current active object is located.
         * @return QPointF Active object coordinates.
         */
        QPointF get_active_obj_orig_pos ();

        /**
         * @brief Constructs file dialog widget for user to select a file.
         * @param operation Defines restrictions for file selection related to selected operation.
         * @return QString Selected filename.
         */
        QString get_selected_file (Operation operation);
        /**
         * @brief Handles selected file content representing stored scene.
         */
        void load_config ();
        /**
         * @brief Stores current scene to the file.
         */
        void store_config ();

        // Events - handling
        void keyPressEvent (QKeyEvent* event) override;
        void mouseMoveEvent (QGraphicsSceneMouseEvent* event) override;
        void mousePressEvent (QGraphicsSceneMouseEvent* event) override;
};

#endif // PLAYGROUND_H
