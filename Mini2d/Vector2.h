#pragma once

#include <cmath>

class Vector2
{
public:
    explicit Vector2();

    Vector2(const double, const double);
    Vector2(const Vector2&);

    Vector2& operator=(const Vector2& v);
    Vector2& operator+=(const Vector2& other);
    Vector2& operator-=(const Vector2& other);
    Vector2& operator*=(const int scalar);

    Vector2 operator+(const Vector2& other) const;
    Vector2 operator-(const Vector2& other) const;
    Vector2 operator*(const int scalar) const;

    double dotProduct(const Vector2& other) const;
    static double dotProduct(const Vector2& v1, const Vector2& v2);

    double magnitude() const;
    double squareMagnitude() const;
    double distanceTo(const Vector2& other) const;
    double squareDistanceTo(const Vector2& other) const;

    void normalize();
    Vector2 normalized() const;

    static double angleBetween(const Vector2& v1, const Vector2& v2);
    double angleTo(const Vector2& other) const;

    double x, y;
};
