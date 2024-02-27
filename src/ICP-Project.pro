#-------------------------------------------------
#
# Project created by QtCreator 2024-02-05T15:47:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ICP-Project
TEMPLATE = app


SOURCES += window/main.cpp \
           window/main_window.cpp \
           scene/playground.cpp \
           scene/obstacle.cpp \
           scene/robot.cpp \
           math/vector2.cpp \
           physics/collision_shape.cpp \
           physics/circle_collision_shape.cpp \
           physics/polygon_collision_shape.cpp \
           physics/rectangle_collision_shape.cpp \

HEADERS += window/main_window.h \
           includes/libs_file.h \
           scene/playground.h \
           scene/scene_object.h \
           scene/obstacle.h \
           scene/robot.h \
           math/vector2.h \
           physics/collision_shape.h \
           physics/circle_collision_shape.h \
           physics/polygon_collision_shape.h \
           physics/rectangle_collision_shape.h \

FORMS   += forms/main_window.ui
