#include "plane.h"
#include "functions.h"

/* explicit */ Plane::Plane(const Triangle& t) noexcept
: m_normal(t.norm()),
  m_point(t[0])
{
}

Plane::Plane(const Vec4d& normal, const Vec4d& point) noexcept
: m_normal(normal.normalize()),
  m_point(point)
{
}

Plane::~Plane() noexcept
{
}

Vec4d Plane::intersection(const Vec4d& begin, const Vec4d& end) const noexcept
{
    float dot = dotProduct(begin, end);
    float k   = (dot - dotProduct(m_point, m_normal)) /
              (dot - dotProduct(end, m_normal));

    Vec4d res = begin + (end - begin) * k;
    return res;
}

float Plane::distance(const Vec4d& point) const noexcept
{
    return dotProduct(point, m_normal) - dotProduct(m_point, m_normal);
}

const Vec4d& Plane::n() const noexcept
{
    return m_normal;
}

const Vec4d& Plane::p() const noexcept
{
    return m_point;
}
