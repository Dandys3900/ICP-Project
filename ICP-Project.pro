#-------------------------------------------------
#
# Project created by QtCreator 2024-02-05T15:47:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ICP-Project
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    physics/vector2.cpp \
    physics/collision_shape.cpp \

HEADERS  += mainwindow.h \
    physics/vector2.h \
    physics/collision_shape.h \
FORMS    += mainwindow.ui \
    physics/world_state.h
