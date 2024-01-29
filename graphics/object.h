#pragma once

#include <string>

#include "../math/mat4x4.h"
#include "../math/vec4d.h"
#include "mesh.h"

class Object
{
public:
    Object() noexcept;
    virtual ~Object() noexcept;

    void loadFromFile(const std::string& filename);

    void rotate(const Vec4d& angle) noexcept;
    void translate(const Vec4d& v) noexcept;
    void scale(float scale) noexcept;
    void scale(const Vec4d& scale) noexcept;
    void transform(const Matrix4x4& tm) noexcept;

    [[nodiscard]] const Mesh&      getMesh() const noexcept;
    [[nodiscard]] const Matrix4x4& getTransformationMatrix() const noexcept;

private:
    Mesh      m_mesh;
    Matrix4x4 m_transformationMatrix;
};
