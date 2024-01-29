#include <stdexcept>

#include "../math/functions.h"
#include "triangle.h"

Triangle::Triangle() noexcept
: Triangle({0, 0, 0, 1}, {0, 0, 0, 1}, {0, 0, 0, 1})
{
}

Triangle::Triangle(const Vec4d& p1, const Vec4d& p2, const Vec4d& p3) noexcept
: color(0, 0, 0)
{
    p[0] = p1;
    p[1] = p2;
    p[2] = p3;
}

Triangle::Triangle(const Vec4d p[3]) noexcept : color(0, 0, 0)
{
    for (int i = 0; i < 3; i++)
        this->p[i] = p[i];
}

/* [[nodiscard]] */ Vec4d& Triangle::operator[](int n)
{
    if (n < 0 || n > 2) {
        throw std::out_of_range("index must be in [0, 2]");
    }

    return p[n];
}

/* [[nodiscard]] */ const Vec4d& Triangle::operator[](int n) const
{
    if (n < 0 || n > 2) {
        throw std::out_of_range("index must be in [0, 2]");
    }

    return p[n];
}

void Triangle::setColor(const uint8_t r, const uint8_t g, const uint8_t b) noexcept
{
    color.r = r;
    color.g = g;
    color.b = b;
}

void Triangle::setColor(const Color& col) noexcept
{
    color = col;
}

Vec4d Triangle::norm() const noexcept
{
    Vec4d l1 = p[1] - p[0];
    Vec4d l2 = p[2] - p[0];

    return crossProduct(l1, l2).normalize();
}
