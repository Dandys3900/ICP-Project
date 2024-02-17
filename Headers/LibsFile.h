#ifndef INCLUDEFILE_H
#define INCLUDEFILE_H

/***** CONSTS *****/
#define ZERO_VAL 0
#define ARROW_SHIFT 75
#define ROBOT_SIZE 100
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define BORDER_WIDTH 10
#define TIMER_MILISECS 50

/***** LIBS *****/
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QString>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QPointF>
#include <QGraphicsEllipseItem>
#include <QGraphicsPolygonItem>
#include <QtMath>
#include <QTimer>
#include <vector>
#include <iterator>
#include <QGraphicsRectItem>
#include <QMouseEvent>

/***** OTHERS *****/
enum Action {
    NO_ACTION = 0,
    MOVE_ACTION,
    RESIZE_ACTION
};

#endif // INCLUDEFILE_H
