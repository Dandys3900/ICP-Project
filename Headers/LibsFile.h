#ifndef INCLUDEFILE_H
#define INCLUDEFILE_H

/***** CONSTS *****/
#define ARROW_SHIFT 75
#define ROBOT_SIZE 100
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define BORDER_WIDTH 10
#define RAND_MAX 10000
#define CONF_FILE "config_file.conf"

/***** LIBS *****/
// QT Libs
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

// C++ Libs
#include <vector>
#include <iterator>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <filesystem>
#include <regex>
#include <map>

/***** OTHERS *****/
enum Action {
    NO_ACTION = 0,
    MOVE_ACTION,
    RESIZE_ACTION
};

#endif // INCLUDEFILE_H
