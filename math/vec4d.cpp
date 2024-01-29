#include <stdexcept>

#include "functions.h"
#include "vec4d.h"

Vec4d::Vec4d() noexcept : x(0.f), y(0.f), z(0.f), w(1.f)
{
}

Vec4d::Vec4d(float x, float y, float z, float w) noexcept
: x(x),
  y(y),
  z(z),
  w(w)
{
}

Vec4d::Vec4d(float coords[4]) noexcept
: x(coords[0]),
  y(coords[1]),
  z(coords[2]),
  w(coords[3])
{
}

/* virtual */ Vec4d::~Vec4d() noexcept
{
}

/* [[nodiscard]] */ Vec4d Vec4d::normalize() const noexcept
{
    float invLen = inverseSqrt(x * x + y * y + z * z);

    return Vec4d(x * invLen, y * invLen, z * invLen, w);
}

/* [[nodiscard]] */ Vec4d Vec4d::operator+(const Vec4d& v) const noexcept
{
    return Vec4d(x + v.x, y + v.y, z + v.z, (w == 0 && w == v.w) ? 0 : 1);
}

/* [[nodiscard]] */ Vec4d Vec4d::operator-(const Vec4d& v) const noexcept
{
    return Vec4d(x - v.x, y - v.y, z - v.z, (w == 0 && w == v.w) ? 0 : 1);
}

/* [[nodiscard]] */ Vec4d Vec4d::operator*(const float n) const noexcept
{
    return Vec4d(n * x, n * y, n * z, w);
}

/* [[nodiscard]] */ Vec4d Vec4d::operator/(const float n) const
{
    if (n == 0.0f) {
        throw std::overflow_error("division by zero");
    }
    return Vec4d(x / n, y / n, z / n, w);
}

std::ostream& operator<<(std::ostream& os, const Vec4d& v)
{
    os << '{' << v.x << ", " << v.y << ", " << v.z << ", " << v.w << '}';

    return os;
}
