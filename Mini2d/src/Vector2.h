#pragma once

#include <cmath>
#include "Logger.h"

namespace mini2d
{
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
}

template <>
struct fmt::formatter<mini2d::Vector2>
{
    char presentation = 'f';

    constexpr auto parse(format_parse_context& ctx)
    {
        auto it = ctx.begin(), end = ctx.end();
        if (it != end && (*it == 'f' || *it == 'e')) presentation = *it++;

        if (it != end && *it != '}')
            throw format_error("invalid format");

        return it;
    }

    template <typename FormatContext>
    auto format(const mini2d::Vector2& p, FormatContext& ctx)
    {
        return format_to(
            ctx.out(),
            presentation == 'f' ? "({:.1f}, {:.1f})" : "({:.1e}, {:.1e})",
            p.x, p.y);
    }
};
