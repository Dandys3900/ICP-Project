#ifndef VECTOR2_H
#define VECTOR2_H


#include <stdio.h>
#include <string>


class Vector2 {

public: // fields
    float x;
    float y;

public: // methods
    Vector2(float x, float y);
    Vector2(const Vector2& v);

    void normalize();
    Vector2 normalized() const;

    float cross(const Vector2& v) const;
    float dot(const Vector2& v) const;

    float length() const;
    float length_squared() const;
    float angle() const;

    float distance_to(const Vector2& v) const;
    float distance_squared_to(const Vector2& v) const;
    float angle_to(const Vector2& v) const;

public: // operators
    Vector2 operator + (Vector2 const& v) { // Vector2 = Vector2 + Vector2
        return Vector2(this->x + v.x, this->y + v.y);
    }
    Vector2 operator += (Vector2 const& v) { // Vector2 += Vector2
        this->x += v.x;
        this->y += v.y;
        return *this;
    }
    Vector2 operator - (Vector2 const& v) { // Vector2 = Vector2 - Vector2
        return Vector2(this->x - v.x, this->y - v.y);
    }
    Vector2 operator -= (Vector2 const& v) { // Vector2 -= Vector2
        this->x -= v.x;
        this->y -= v.y;
        return *this;
    }
    Vector2 operator * (float f) { // Vector2 = Vector2 * float
        return Vector2(this->x * f, this->y * f);
    }
    Vector2 operator *= (float f) { // // Vector2 *= float
        this->x *= f;
        this->y *= f;
        return *this;
    }
    Vector2 operator / (float f) { // Vector2 = Vector2 / float
        return Vector2(this->x / f, this->y / f);
    }
    Vector2 operator /= (float f) { // Vector2 /= float
        this->x /= f,
        this->y /= f;
        return *this;
    }
    Vector2 operator - () { // -Vector2
        return Vector2(-this->x, -this->y);
    }
    std::string to_string() { // to_string
        return "Vector2(" + std::to_string(this->x) + ", " + std::to_string(this->y) + ")";
    }

};


#endif
