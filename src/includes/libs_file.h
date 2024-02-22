#ifndef INCLUDEFILE_H
#define INCLUDEFILE_H

/***** CONSTS *****/
#define ARROW_LENGTH 75
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define BORDER_WIDTH 104
#define RAND_MAX_VAL 10000
#define CONFIG_FILE "config_file"

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
#include <QGraphicsRectItem>
#include <QMouseEvent>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QDebug>

#include <iterator>

#include "src/math/vector2.h"
#include "src/config/config_manager.h"

/***** OTHERS *****/
enum Action : int {
    NO_ACTION = 0,
    MOVE_ACTION,
    RESIZE_ACTION
};

#endif // INCLUDEFILE_H
