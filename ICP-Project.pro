#-------------------------------------------------
#
# Project created by QtCreator 2024-02-05T15:47:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ICP-Project
TEMPLATE = app


SOURCES += src/window/main.cpp \
           src/window/main_window.cpp \
           src/scene/playground.cpp \
           src/scene/obstacle.cpp \
           src/scene/robot.cpp \
           src/math/vector2.cpp \
           src/config/config_manager.cpp

HEADERS += src/window/main_window.h \
           src/includes/libs_file.h \
           src/scene/playground.h \
           src/scene/scene_object.h \
           src/scene/obstacle.h \
           src/scene/robot.h \
           src/math/vector2.h \
           src/config/config_manager.h

FORMS   += src/forms/main_window.ui
