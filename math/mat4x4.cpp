#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>

#include "functions.h"
#include "mat4x4.h"

Matrix4x4::Matrix4x4(std::array<std::array<float, 4>, 4> data /* = {} */)
{
}

Matrix4x4::~Matrix4x4()
{
}

/* [[nodiscard]] */ Vec4d Matrix4x4::operator*(const Vec4d& v) const
{
    Vec4d res;

    res.x = data[0][0] * v.x + data[0][1] * v.y + data[0][2] * v.z + data[0][3];
    res.y = data[1][0] * v.x + data[1][1] * v.y + data[1][2] * v.z + data[1][3];
    res.z = data[2][0] * v.x + data[2][1] * v.y + data[2][2] * v.z + data[2][3];
    res.w = data[3][0] * v.x + data[3][1] * v.y + data[3][2] * v.z + data[3][3];

    if (res.w != 0.0f && res.w != 1.0f) {
        res = res / res.w;
    }

    return res;
}

/* [[nodiscard]] */ Matrix4x4 Matrix4x4::operator*(const Matrix4x4& m) const
{
    Matrix4x4 res;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                res[i][j] += data[i][k] * m.data[k][j];
            }
        }
    }

    return res;
}

/* [[nodiscard]] */ std::array<float, 4>& Matrix4x4::operator[](int n)
{
    if (n < 0 || n > 3) {
        throw std::out_of_range("matrix index must be in range [0, 3]");
    }

    return data[n];
}

/* [[nodiscard]] */ const std::array<float, 4>& Matrix4x4::operator[](int n) const
{
    if (n < 0 || n > 3) {
        throw std::out_of_range("matrix index must be in range [0, 3]");
    }

    return data[n];
}

/* [[nodiscard]] static */ Matrix4x4 Matrix4x4::Identity() noexcept
{
    Matrix4x4 res;

    res[0][0] = 1.0f;
    res[1][1] = 1.0f;
    res[2][2] = 1.0f;
    res[3][3] = 1.0f;

    return res;
}

/* [[nodiscard]] static */ Matrix4x4 Matrix4x4::Zero() noexcept
{
    return Matrix4x4();
}

/* [[nodiscard]] static */ Matrix4x4
    Matrix4x4::Projection(float fov /* = 90.0f */,
                          float aspect /* = 1.0f */,
                          float zNear /* = 1.0f */,
                          float zFar /* = 10.0f */) noexcept
{
    // inverts the Y axis
    Matrix4x4 res;

    float fovRad = fov * 3.14159 / 180;

    res[0][0] = aspect /* h / w */ / (tanf(fovRad * 0.5));
    res[1][1] = 1.f / tanf(fovRad * 0.5);
    res[2][2] = zFar / (zFar - zNear);
    res[2][3] = -zFar * zNear / (zFar - zNear);
    res[3][2] = /* - */ 1.f; // minus inverts x and y coordinates

    return res;
}

/* [[nodiscard]] static */ Matrix4x4 Matrix4x4::Translation(const Vec4d& v) noexcept
{
    Matrix4x4 res = Matrix4x4::Identity();

    res[0][3] = v.x;
    res[1][3] = v.y;
    res[2][3] = v.z;

    return res;
}


/* [[nodiscard]] static */ Matrix4x4 Matrix4x4::RotationX(float angle) noexcept
{
    Matrix4x4 res;

    res[0][0] = 1.0f;
    res[1][1] = cosf(angle);
    res[1][2] = sinf(angle);
    res[2][1] = -sinf(angle);
    res[2][2] = cosf(angle);
    res[3][3] = 1.0f;

    return res;
}

/* [[nodiscard]] static */ Matrix4x4 Matrix4x4::RotationY(float angle) noexcept
{
    Matrix4x4 res;

    res[0][0] = cosf(angle);
    res[0][2] = -sinf(angle);
    res[1][1] = 1.0f;
    res[2][0] = sinf(angle);
    res[2][2] = cosf(angle);
    res[3][3] = 1.0f;

    return res;
}

/* [[nodiscard]] static */ Matrix4x4 Matrix4x4::RotationZ(float angle) noexcept
{
    Matrix4x4 res;

    res[0][0] = cosf(angle);
    res[0][1] = -sinf(angle);
    res[1][0] = sinf(angle);
    res[1][1] = cosf(angle);
    res[2][2] = 1.0f;
    res[3][3] = 1.0f;

    return res;
}

/* [[nodiscard]] static */ Matrix4x4 Matrix4x4::Scale(const Vec4d& scale) noexcept
{
    Matrix4x4 res = Identity();

    res[0][0] = scale.x;
    res[1][1] = scale.y;
    res[2][2] = scale.z;

    return res;
}

/* [[nodiscard]] static */ Matrix4x4 Matrix4x4::Scale(const float scale) noexcept
{
    Matrix4x4 res = Identity();

    res[0][0] = scale;
    res[1][1] = scale;
    res[2][2] = scale;

    return res;
}

/* [[nodiscard]] static */ Matrix4x4
    Matrix4x4::Viewport(const unsigned width, const unsigned height) noexcept
{
    Matrix4x4 res;

    res[0][0] = width / 2.f;
    res[0][3] = width / 2.f;
    res[1][1] = height / 2.f;
    res[1][3] = height / 2.f;
    res[2][2] = 1.f / 2;
    res[2][3] = 1.f / 2;
    res[3][3] = 1.f;

    return res;
}


/* [[nodiscard]] static */ Matrix4x4
    Matrix4x4::View(const Vec4d& cameraPos,
                    const Vec4d& forward,
                    const Vec4d& up,
                    const Vec4d& right) noexcept
{
    Matrix4x4 res = Zero();

    res[0][0] = -right.x;
    res[0][1] = -right.y;
    res[0][2] = -right.z;
    res[0][3] = dotProduct(cameraPos, right);

    res[1][0] = -up.x;
    res[1][1] = -up.y;
    res[1][2] = -up.z;
    res[1][3] = dotProduct(cameraPos, up);

    res[2][0] = forward.x;
    res[2][1] = forward.y;
    res[2][2] = forward.z;
    res[2][3] = -dotProduct(cameraPos, forward);

    res[3][3] = 1.0f;

    return res;
}

std::ostream& operator<<(std::ostream& os, const Matrix4x4& m)
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            os << std::setw(10) << std::left << m[i][j];
        }
        os << '\n';
    }

    return os;
}
