#pragma once

#include <array>
#include <ostream>

#include "vec4d.h"

class Matrix4x4
{
public:
    Matrix4x4(std::array<std::array<float, 4>, 4> data = {});
    ~Matrix4x4();

    [[nodiscard]] Vec4d                 operator*(const Vec4d& v) const;
    [[nodiscard]] Matrix4x4             operator*(const Matrix4x4& m) const;
    [[nodiscard]] std::array<float, 4>& operator[](int n);
    [[nodiscard]] const std::array<float, 4>& operator[](int n) const;

    [[nodiscard]] static Matrix4x4 Identity() noexcept;
    [[nodiscard]] static Matrix4x4 Zero() noexcept;
    [[nodiscard]] static Matrix4x4
        Projection(const float fov    = 90.0f,
                   const float aspect = 1.0f,
                   const float zNear  = 1.0f,
                   const float zFar   = 10.0f) noexcept;

    [[nodiscard]] static Matrix4x4 Translation(const Vec4d& v) noexcept;
    [[nodiscard]] static Matrix4x4 RotationX(const float angle) noexcept;
    [[nodiscard]] static Matrix4x4 RotationY(const float angle) noexcept;
    [[nodiscard]] static Matrix4x4 RotationZ(const float angle) noexcept;
    [[nodiscard]] static Matrix4x4 Scale(const Vec4d& scale) noexcept;
    [[nodiscard]] static Matrix4x4 Scale(const float scale) noexcept;
    [[nodiscard]] static Matrix4x4
        Viewport(const unsigned width, const unsigned height) noexcept;
    [[nodiscard]] static Matrix4x4
        View(const Vec4d& cameraPos,
             const Vec4d& forward,
             const Vec4d& up,
             const Vec4d& right) noexcept;

private:
    std::array<std::array<float, 4>, 4> data = {};
};

std::ostream& operator<<(std::ostream& os, const Matrix4x4& m);
