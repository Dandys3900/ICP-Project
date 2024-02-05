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
    math/vector2.cpp

HEADERS  += mainwindow.h \
    math/fancy_math.h \
    math/vector2.h

FORMS    += mainwindow.ui
