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
           window/custom_view.cpp \
           scene/playground.cpp \
           scene/obstacle.cpp \
           scene/robot.cpp \
           math/vector2.cpp

HEADERS += window/custom_view.h \
           includes/libs_file.h \
           scene/playground.h \
           scene/scene_object.h \
           scene/obstacle.h \
           scene/robot.h \
           math/vector2.h

FORMS   += forms/main_window.ui