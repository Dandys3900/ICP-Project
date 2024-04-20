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
           physics/collision_shape.cpp \
           physics/circle_collision_shape.cpp \
           physics/polygon_collision_shape.cpp \
           physics/rectangle_collision_shape.cpp

HEADERS += window/custom_view.h \
           window/user_menu.h \
           includes/libs_file.h \
           scene/playground.h \
           scene/scene_object.h \
           scene/obstacle.h \
           scene/robot.h \
           scene/robot_info.h \
           math/vector2.h \
           errors/error_popup.h \
           physics/collision_shape.h \
           physics/circle_collision_shape.h \
           physics/polygon_collision_shape.h \
           physics/rectangle_collision_shape.h

RESOURCES += resources.qrc

CONFIG += c++17
