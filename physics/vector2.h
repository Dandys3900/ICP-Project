#ifndef VECTOR2_H
#define VECTOR2_H


#include <QPointF>


class Vector2 : public QPointF {
public: // methods
    Vector2();
    Vector2(qreal x, qreal y);
    Vector2(const Vector2& v);
    Vector2(const QPointF& qp);

    Vector2 normal() const; // clockwise normal vector

    void normalize();
    Vector2 normalized() const;

    void rotate(qreal angle);
    Vector2 rotated(qreal angle) const;

    qreal length() const;
    qreal length_squared() const;
    qreal angle() const;

    qreal length_to(const QPointF& qp) const;
    qreal length_squared_to(const QPointF& qp) const;
    qreal angle_to(const QPointF& qp) const;

    static qreal crossProduct(const QPointF& qp1, const QPointF& qp2);
};


#endif
