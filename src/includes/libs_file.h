#ifndef INCLUDEFILE_H
#define INCLUDEFILE_H

/***** CONSTS *****/
#define ARROW_LENGTH 75
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define BORDER_WIDTH 10
#define RAND_MAX_VAL 10000

/***** LIBS *****/
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QString>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneResizeEvent>
#include <QGraphicsSceneHoverEvent>
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
#include <QBrush>
#include <QFileDialog>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QMainWindow>
#include <QLabel>
#include <QVBoxLayout>

#include <iterator>

#include "math/vector2.h"
#include "errors/error_popup.h"

/***** OTHERS *****/
enum Action : int {
    NO_ACTION = 0,
    MOVE_ACTION,
    RESIZE_ACTION
};

#endif // INCLUDEFILE_H
