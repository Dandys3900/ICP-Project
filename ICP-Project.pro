#-------------------------------------------------
#
# Project created by QtCreator 2024-02-05T15:47:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ICP-Project
TEMPLATE = app


SOURCES += Sources/main.cpp \
           Sources/mainwindow.cpp \
           Sources/Obstacle.cpp \
           Sources/PlayGround.cpp \
           Sources/Robot.cpp

HEADERS += Headers/mainwindow.h \
           Headers/Obstacle.h \
           Headers/PlayGround.h \
           Headers/Robot.h \
           Headers/Consts.h

FORMS   += Forms\mainwindow.ui
