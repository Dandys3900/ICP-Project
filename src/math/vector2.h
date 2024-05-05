/** ICP Project 2023/2024
 * @file vector2.h
 * @author Jakub Janšta (xjanst02)
 * @brief Header file for Vector2 class.
 */

#ifndef VECTOR2_H
#define VECTOR2_H


#include "includes/libs_file.h"


class Vector2 : public QPointF {
    public: // Methods
        /**
         * @brief Constructor. x-value and y-value are set to 0.
         */
        Vector2();
        /**
         * @brief Constructor.
         * @param xy Initial position of vector. Both x-value and y-value will be set to xy.
         */
        Vector2(qreal xy);
        /**
         * @brief Constructor.
         * @param x Initial x-value position of vector.
         * @param y Initial y-value position of vector.
         */
        Vector2(qreal x, qreal y);
        /**
         * @brief Constructor.
         * @param v Vector representing initial position of vector.
         */
        Vector2(const Vector2& v);
        /**
         * @brief Constructor.
         * @param qp QPointF representing initial position of vector.
         */
        Vector2(const QPointF& qp);

        /**
         * @brief Calculates normal vector to the current vector.
         * @return Normal vector.
         */
        Vector2 normal() const;
        /**
         * @brief Calculates normal vector to the current vector on the right side.
         * @return Normal vector on the right side.
         */
        Vector2 normal_right() const;
        /**
         * @brief Calculates normal vector to the current vector on the left side.
         * @return Normal vector on the left side.
         */
        Vector2 normal_left() const;

        /**
         * @brief Calculates normalized vector to the current vector.
         */
        void normalize();
        /**
         * @brief Returns normalized vector to the current vector @see normalize() method.
         * @return Normalized vector.
         */
        Vector2 normalized() const;

        /**
         * @brief Calculates rotation of the current vector.
         * @param angle Angle vector will be rotate around.
         */
        void rotate(qreal angle);
        /**
         * @brief Returns rotated vector of the current vector.
         * @param angle Angle vector will be rotate around.
         * @return Rotated vector.
         */
        Vector2 rotated(qreal angle) const;

        /**
         * @brief Calculates rotation of the current vector around given point.
         * @param point Rotation origin point.
         * @param angle Angle vector will be rotate around.
         */
        void rotate_around(const QPointF& point, qreal angle);
        /**
         * @brief Returns rotated vector around given point.
         * @param point Rotation origin point.
         * @param angle Angle vector will be rotate around.
         * @return Rotated vector.
         */
        Vector2 rotated_around(const QPointF& point, qreal angle) const;

        /**
         * @brief Calculates length of the vector.
         * @return Length of the vector.
         */
        qreal length() const;
        /**
         * @brief Calculates squared length of the vector.
         * @return Squared length of the vector.
         */
        qreal length_squared() const;
        /**
         * @brief Calculates angle of the vector.
         * @return Angle of the vector.
         */
        qreal angle() const;

        /**
         * @brief Calculates distance from the vector to given point.
         * @param qp Point to which the distance is measured.
         * @return Distance from the vector to the given point.
         */
        qreal length_to(const QPointF& qp) const;
        /**
         * @brief Calculates squared distance from the vector to given point.
         * @param qp Point to which the (squared) distance is measured.
         * @return Squared distance from the vector to the given point.
         */
        qreal length_squared_to(const QPointF& qp) const;
        /**
         * @brief Calculates angle between the vector and given point.
         * @param qp Point to which the angle is measured.
         * @return Angle between the vector and the given point.
         */
        qreal angle_to(const QPointF& qp) const;
        /**
         * @brief Calculates cross product between two given vectors.
         * @param qp1 First vector.
         * @param qp2 Second vector.
         * @return Cross product of these two vectors.
         */
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
