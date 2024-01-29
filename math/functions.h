#pragma once

#include <algorithm>
#include <bit>
#include <cstdint>

#include "vec4d.h"

constexpr float inverseSqrt(float n) noexcept
{
    const float y = std::bit_cast<float>(
        0x5f3759df - (std::bit_cast<std::uint32_t>(n) >> 1));
    return y * (1.5f - (n * 0.5f * y * y));
}

inline constexpr float
    map(float val, float old_min, float old_max, float new_min, float new_max) noexcept
{
    return new_min + (val - old_min) * (new_max - new_min) / (old_max - old_min);
}

inline float dotProduct(const Vec4d& a, const Vec4d& b) noexcept
{
    return (a.x * b.x + a.y * b.y + a.z * b.z);
}

inline Vec4d crossProduct(const Vec4d& a, const Vec4d& b) noexcept
{
    Vec4d res;

    // coordinate form for left basis
    res.x = b.y * a.z - b.z * a.y;
    res.y = b.z * a.x - b.x * a.z;
    res.z = b.x * a.y - b.y * a.x;

    return res;
}
