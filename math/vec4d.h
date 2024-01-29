#pragma once

#include <ostream>

struct Vec4d
{
    Vec4d() noexcept;
    Vec4d(float x, float y, float z, float w) noexcept;
    Vec4d(float coords[4]) noexcept;
    virtual ~Vec4d() noexcept;

    [[nodiscard]] Vec4d normalize() const noexcept;

    [[nodiscard]] Vec4d operator+(const Vec4d& v) const noexcept;
    [[nodiscard]] Vec4d operator-(const Vec4d& v) const noexcept;
    [[nodiscard]] Vec4d operator*(const float n) const noexcept;
    [[nodiscard]] Vec4d operator/(const float n) const;

    float x;
    float y;
    float z;
    float w;
};

std::ostream& operator<<(std::ostream& os, const Vec4d& v);
