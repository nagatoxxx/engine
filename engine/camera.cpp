#include <cmath>

#include "camera.h"

Camera::Camera(const Vec4d& pos,
               const Vec4d& forward,
               const Vec4d& up,
               const Vec4d& right) noexcept
: m_position(pos),
  m_forward(forward),
  m_up(up),
  m_right(right),
  m_fov(90.0f),   //
  m_zNear(0.1f),  // default values
  m_zFar(100.0f), //
  m_aspect(1.f),
  m_projectionMatrixCalculated(true),
  m_projectionMatrix(),
  m_clipPlanesCalculated(true),
  m_clipPlanes()
{
    m_projectionMatrix = Matrix4x4::Projection(m_fov, m_aspect, m_zNear, m_zFar);

    m_clipPlanes.reserve(6);

    m_clipPlanes.emplace_back(Vec4d(0, 0, 1, 1), Vec4d(0, 0, m_zNear, 1)); // near plane
    m_clipPlanes.emplace_back(Vec4d(0, 0, -1, 1), Vec4d(0, 0, m_zFar, 1)); // far plane

    float thetta1 = 3.14159 * 0.5 / 180;
    float thetta2 = std::atan(1 / m_aspect * tan(thetta1));

    m_clipPlanes.emplace_back(Vec4d(-cos(thetta2), 0, sin(thetta2), 1),
                              Vec4d(0, 0, 0, 1)); // left plane
    m_clipPlanes.emplace_back(Vec4d(cos(thetta2), 0, sin(thetta2), 1),
                              Vec4d(0, 0, 0, 1)); //  right plane
    m_clipPlanes.emplace_back(Vec4d(0, cos(thetta1), sin(thetta1), 1),
                              Vec4d(0, 0, 0, 1)); // bottom plane
    m_clipPlanes.emplace_back(Vec4d(0, -cos(thetta1), sin(thetta1), 1),
                              Vec4d(0, 0, 0, 1)); // top plane
}

Camera::~Camera() noexcept
{
}

void Camera::rotate(const Vec4d& v) noexcept
{
    Matrix4x4 rot = Matrix4x4::RotationX(v.x) * Matrix4x4::RotationY(v.y) *
                    Matrix4x4::RotationZ(v.z);

    m_forward = rot * m_forward;
    m_up      = rot * m_up;
    m_right   = rot * m_right;
}

void Camera::transtale(const Vec4d& v) noexcept
{
    Matrix4x4 tr = Matrix4x4::Translation(v);

    m_position = tr * m_position;
}

void Camera::setFov(float fov) noexcept
{
    m_projectionMatrixCalculated = false;
    m_fov                        = fov;
}

void Camera::setZ(float zn, float zf) noexcept
{
    m_projectionMatrixCalculated = false;
    m_zNear                      = zn;
    m_zFar                       = zf;
}

void Camera::setAspect(float aspect) noexcept
{
    m_aspect = aspect;
}

const Vec4d& Camera::pos() const noexcept
{
    return m_position;
}

const Vec4d& Camera::forward() const noexcept
{
    return m_forward;
}

const Vec4d& Camera::up() const noexcept
{
    return m_up;
}

const Vec4d& Camera::right() const noexcept
{
    return m_right;
}

const std::vector<Plane>& Camera::getPlanes() noexcept
{
    if (!m_clipPlanesCalculated) {
        m_clipPlanes.clear();

        m_clipPlanes.emplace_back(Vec4d(0, 0, 1, 1), Vec4d(0, 0, m_zNear, 1)); // near plane
        m_clipPlanes.emplace_back(Vec4d(0, 0, -1, 1), Vec4d(0, 0, m_zFar, 1)); // far plane

        float thetta1 = 3.14159 * 0.5 / 180;
        float thetta2 = std::atan(1 / m_aspect * tan(thetta1));

        m_clipPlanes.emplace_back(Vec4d(-cos(thetta2), 0, sin(thetta2), 1),
                                  Vec4d(0, 0, 0, 1)); // left plane
        m_clipPlanes.emplace_back(Vec4d(cos(thetta2), 0, sin(thetta2), 1),
                                  Vec4d(0, 0, 0, 1)); //  right plane
        m_clipPlanes.emplace_back(Vec4d(0, cos(thetta1), sin(thetta1), 1),
                                  Vec4d(0, 0, 0, 1)); // bottom plane
        m_clipPlanes.emplace_back(Vec4d(0, -cos(thetta1), sin(thetta1), 1),
                                  Vec4d(0, 0, 0, 1)); // top plane
    }

    m_clipPlanesCalculated = true;
    return m_clipPlanes;
}

const Matrix4x4& Camera::getProjectionMatrix() noexcept
{
    if (!m_projectionMatrixCalculated) {
        m_projectionMatrix = Matrix4x4::Projection(m_fov, m_aspect, m_zNear, m_zFar);
    }

    m_projectionMatrixCalculated = true;
    return m_projectionMatrix;
}
