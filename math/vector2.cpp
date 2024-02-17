#include "vector2.h"


Vector2::Vector2() : QPointF() {}

Vector2::Vector2(qreal x, qreal y) : QPointF(x, y) {}

Vector2::Vector2(const Vector2& v) : QPointF(v) {}

Vector2::Vector2(const QPointF& qp) : QPointF(qp) {}


void Vector2::normalize() {
	qreal length = this->x() * this->x() + this->y() * this->y();
	if (length != 0) {
		length = qSqrt(length);
		this->setX(this->x() / length);
		this->setY(this->y() / length);
	}
}

Vector2 Vector2::normalized() const {
	Vector2 v = Vector2(*this);
	v.normalize();
	return v;
}

void Vector2::rotate(qreal angle) {
	qreal angle_sin = qSin(angle);
	qreal angle_cos = qCos(angle);
	setX(this->x() * angle_cos - this->y() * angle_sin);
	setY(this->x() * angle_sin + this->y() * angle_cos);
}

Vector2 Vector2::rotated(qreal angle) const {
	Vector2 v = Vector2(*this);
	v.rotate(angle);
	return v;
}

qreal Vector2::length() const {
	return qSqrt(this->length_squared());
}

qreal Vector2::length_squared() const {
	return this->x() * this->x() + this->y() * this->y();
}

qreal Vector2::angle() const {
	return qAtan2(this->y(), this->x());
}

qreal Vector2::length_to(const QPointF& qp) const {
	return qSqrt(this->length_squared_to(qp));
}

qreal Vector2::length_squared_to(const QPointF& qp) const {
	return (this->x() - qp.x()) * (this->x() - qp.x()) + (this->y() - qp.y()) * (this->y() - qp.y());
}

qreal Vector2::angle_to(const QPointF& qp) const {
	return qAtan2(crossProduct(*this, qp), dotProduct(*this, qp));
}

qreal Vector2::crossProduct(const QPointF& qp1, const QPointF& qp2) {
	return qp1.x() * qp2.y() - qp1.y() * qp2.x();
}
