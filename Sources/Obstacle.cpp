#include "Headers/Obstacle.h"

Obstacle::Obstacle (const qreal width, const qreal height, const qreal axis_x, const qreal axis_y)
    : mp_width  (width),
      mp_height (height),
      mp_coord_x(axis_x),
      mp_coord_y(axis_y)
{
    this->setRect(mp_coord_x, mp_coord_y, mp_width, mp_height);
}

Obstacle::~Obstacle ()
{
}