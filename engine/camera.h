#pragma once

#include <vector>

#include "../math/mat4x4.h"
#include "../math/plane.h"
#include "../math/vec4d.h"

class Camera
{
public:
    Camera(const Vec4d& pos     = {0, 0, 0, 1},
           const Vec4d& forward = {0, 0, 1, 0},
           const Vec4d& up      = {0, 1, 0, 0},
           const Vec4d& right   = {1, 0, 0, 0}) noexcept;
    ~Camera() noexcept;

    void rotate(const Vec4d& v) noexcept;
    void transtale(const Vec4d& v) noexcept;

    void setFov(float fov) noexcept;
    void setZ(float zn, float zf) noexcept;
    void setAspect(float aspect) noexcept;

    [[nodiscard]] const Vec4d& pos() const noexcept;
    [[nodiscard]] const Vec4d& forward() const noexcept;
    [[nodiscard]] const Vec4d& up() const noexcept;
    [[nodiscard]] const Vec4d& right() const noexcept;

    const std::vector<Plane>& getPlanes() noexcept;
    const Matrix4x4&          getProjectionMatrix() noexcept;

private:
    Vec4d m_position;
    Vec4d m_forward;
    Vec4d m_up;
    Vec4d m_right;

    float m_fov;
    float m_zNear;
    float m_zFar;
    float m_aspect;

    bool      m_projectionMatrixCalculated;
    Matrix4x4 m_projectionMatrix;

    bool               m_clipPlanesCalculated;
    std::vector<Plane> m_clipPlanes;
};
