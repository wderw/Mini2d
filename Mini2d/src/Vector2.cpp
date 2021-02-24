#include "Vector2.h"

namespace mini2d
{
Vector2::Vector2() : x(0), y(0) {}
Vector2::Vector2(const double nx, const double ny) : x(nx), y(ny) {}
Vector2::Vector2(const Vector2& v) : x(v.x), y(v.y) {}

Vector2& Vector2::operator=(const Vector2& v)
{
    x = v.x;
    y = v.y;
    return *this;
}

Vector2& Vector2::operator+=(const Vector2& other)
{
    x += other.x;
    y += other.y;
    return *this;
}

Vector2& Vector2::operator-=(const Vector2& other)
{
    x -= other.x;
    y -= other.x;
    return *this;
}

Vector2& Vector2::operator*=(int scalar)
{
    x *= scalar;
    y *= scalar;
    return *this;
}

Vector2 Vector2::operator+(const Vector2& other) const
{
    return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator-(const Vector2& other) const
{
    return Vector2(x - other.x, y - other.y);
}

Vector2 Vector2::operator*(const int scalar) const
{
    return Vector2(x * scalar, y * scalar);
}

double Vector2::dotProduct(const Vector2& other) const
{
    return (x * other.x) + (y * other.y);
}

double Vector2::dotProduct(const Vector2& v1, const Vector2& v2)
{
    return (v1.x * v2.x) + (v1.y * v2.y);
}

double Vector2::magnitude() const
{
    return sqrt(x * x + y * y);
}

double Vector2::squareMagnitude() const
{
    return x * x + y * y;
}

double Vector2::distanceTo(const Vector2& other) const
{
    return Vector2(other - *this).magnitude();
}

double Vector2::squareDistanceTo(const Vector2& other) const
{
    return Vector2(other - *this).squareMagnitude();
}

void Vector2::normalize()
{
    double length = magnitude();
    x /= length;
    y /= length;
}

Vector2 Vector2::normalized() const
{
    double length = magnitude();
    return Vector2(x / length, y / length);
}

double Vector2::angleBetween(const Vector2& v1, const Vector2& v2)
{
    return acos(Vector2::dotProduct(v1.normalized(), v2.normalized()));
}

double Vector2::angleTo(const Vector2& other) const
{
    return acos(dotProduct(normalized(), other.normalized()));
}
}
