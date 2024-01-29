#pragma once

#include "../graphics/triangle.h"
#include "vec4d.h"

class Plane
{
public:
    explicit Plane(const Triangle& t) noexcept;
    Plane(const Vec4d& normal, const Vec4d& point) noexcept;
    ~Plane() noexcept;

    Vec4d intersection(const Vec4d& begin, const Vec4d& end) const noexcept;
    float distance(const Vec4d& point) const noexcept;

    const Vec4d& n() const noexcept;
    const Vec4d& p() const noexcept;

private:
    const Vec4d m_normal;
    const Vec4d m_point;
};
