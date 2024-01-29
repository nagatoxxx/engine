#pragma once

#include "../math/vec4d.h"
#include "color.h"

#include <cstdint>

struct Triangle
{
    Triangle() noexcept;
    Triangle(const Vec4d& p1, const Vec4d& p2, const Vec4d& p3) noexcept;
    Triangle(const Vec4d p[3]) noexcept;


    [[nodiscard]] Vec4d&       operator[](int n);
    [[nodiscard]] const Vec4d& operator[](int n) const;

    void setColor(const uint8_t r, const uint8_t g, const uint8_t b) noexcept;
    void setColor(const Color& col) noexcept;

    Color color;

    Vec4d norm() const noexcept;

private:
    Vec4d p[3];
};
