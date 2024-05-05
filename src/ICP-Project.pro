QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ICP-Project
TEMPLATE = app


SOURCES += window/main.cpp \
           window/custom_view.cpp \
           window/user_menu.cpp \
           scene/playground.cpp \
           scene/obstacle.cpp \
           scene/robot.cpp \
           scene/robot_info.cpp \
           math/vector2.cpp \
           errors/error_popup.cpp \
           physics/server/physics_server.cpp \
           physics/collision_shapes/collision_shape.cpp \
           physics/collision_shapes/circle_collision_shape.cpp \
           physics/collision_shapes/polygon_collision_shape.cpp \
           physics/collision_shapes/rectangle_collision_shape.cpp \
           physics/physical_objects/physical_robot.cpp \
           physics/physical_objects/physical_obstacle.cpp

HEADERS += window/custom_view.h \
           window/user_menu.h \
           includes/libs_file.h \
           includes/physics.h \
           scene/playground.h \
           scene/scene_object.h \
           scene/obstacle.h \
           scene/robot.h \
           scene/robot_info.h \
           math/vector2.h \
           errors/error_popup.h \
           physics/server/physics_server.h \
           physics/collision_shapes/collision_shape.h \
           physics/collision_shapes/circle_collision_shape.h \
           physics/collision_shapes/polygon_collision_shape.h \
           physics/collision_shapes/rectangle_collision_shape.h \
           physics/physical_objects/physical_robot.h \
           physics/physical_objects/physical_obstacle.h

RESOURCES += resources.qrc

CONFIG += c++17
