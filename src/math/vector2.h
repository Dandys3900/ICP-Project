#ifndef VECTOR2_H
#define VECTOR2_H


#include "includes/libs_file.h"


class Vector2 : public QPointF {
    public: // methods
        Vector2();
        Vector2(qreal x, qreal y);
        Vector2(const Vector2& v);
        Vector2(const QPointF& qp);

        Vector2 normal() const;
        Vector2 normal_right() const;
        Vector2 normal_left() const;

        void normalize();
        Vector2 normalized() const;

        void rotate(qreal angle);
        Vector2 rotated(qreal angle) const;

        void rotate_around(const QPointF& point, qreal angle);
        Vector2 rotated_around(const QPointF& point, qreal angle) const;

        qreal length() const;
        qreal length_squared() const;
        qreal angle() const;

        qreal length_to(const QPointF& qp) const;
        qreal length_squared_to(const QPointF& qp) const;
        qreal angle_to(const QPointF& qp) const;

        static qreal crossProduct(const QPointF& qp1, const QPointF& qp2);

        // Assignment operator
        Vector2& operator=(const Vector2& other) {
            if (this != &other) {
                // Copy data
                this->setX(other.x());
                this->setY(other.y());
            }
            return *this;
        }
};


#endif // VECTOR2_H
