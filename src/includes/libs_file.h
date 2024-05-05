/** ICP Project 2023/2024
 * @file libs_file.h
 * @author Tomáš Daniel (xdanie14)
 * @author Jakub Janšta (xjanst02)
 * @brief Header file containing all necessary includes and constants needed among the project.
 */

#ifndef INCLUDEFILE_H
#define INCLUDEFILE_H

/***** CONSTS *****/
#define ARROW_LENGTH 75
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define BORDER_WIDTH 10

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
#include <QPushButton>
#include <QGraphicsProxyWidget>
#include <QSlider>
#include <QComboBox>
#include <QGroupBox>
#include <QIcon>
#include <QLineEdit>
#include <QVector>
#include <QRectF>

#include <iterator>

#include "math/vector2.h"
#include "errors/error_popup.h"

/***** OTHERS *****/
// Enum representing action of active object
enum Action : int {
    NO_ACTION = 0,
    MOVE_ACTION,
    RESIZE_ACTION
};

// Enum representing current Robot mode
enum Mode : int {
    MANUAL = 0,
    AUTOMATIC
};

// Enum representing rotation direction
enum Direction : int {
    CLOCKWISE = 0,
    ANTICLOCKWISE
};

/**
 * @brief Function for remapping values from one range to another.
 * @param value The value to be remapped.
 * @param from1 The lower bound of the original range.
 * @param to1 The upper bound of the original range.
 * @param from2 The lower bound of the target range.
 * @param to2 The upper bound of the target range.
 * @return The remapped value.
 */
template<typename T>
T remap_value_between_ranges(T value, T from1, T to1, T from2, T to2) {
    return (value - from1) / (to1 - from1) * (to2 - from2) + from2;
}

#endif // INCLUDEFILE_H
