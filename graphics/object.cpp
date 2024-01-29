#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>

#include "object.h"

Object::Object() noexcept
{
    std::cout << "Object: created\n";

    m_transformationMatrix = Matrix4x4::Identity();
}

/* virtual */ Object::~Object() noexcept
{
    std::cout << "Object: destroyed\n";
}

void Object::loadFromFile(const std::string& filename)
{
    std::ifstream f(filename);

    if (!f.is_open()) {
        throw std::runtime_error("Object: error opening file");
    }

    // to avoid vector reallocations
    long verticies_count = std::count(std::istreambuf_iterator<char>(f),
                                      std::istreambuf_iterator<char>(),
                                      'v');
    f.seekg(0);
    long faces_count = std::count(std::istreambuf_iterator<char>(f),
                                  std::istreambuf_iterator<char>(),
                                  'f');
    f.seekg(0);

    std::vector<Vec4d> verts;
    verts.reserve(verticies_count);
    m_mesh.triangles.reserve(faces_count);

    while (!f.eof()) {
        char line[128];
        f.getline(line, 128);

        std::stringstream ss;
        ss << line;

        char junk;

        if (line[0] == 'v') {
            Vec4d v;
            ss >> junk >> v.x >> v.y >> v.z;
            verts.push_back(v);
        }
        else if (line[0] == 'f') {
            int f[3];
            ss >> junk >> f[0] >> f[1] >> f[2];
            m_mesh.triangles.push_back(
                {verts[f[0] - 1], verts[f[1] - 1], verts[f[2] - 1]});
        }
    }

    std::cout << "Object: loaded from file\n";
}

void Object::rotate(const Vec4d& angle) noexcept
{
    Vec4d rad; // angle in radians

    rad.x = angle.x * 3.14159f / 180.0f;
    rad.y = angle.y * 3.14159f / 180.0f;
    rad.z = angle.z * 3.14159f / 180.0f;

    Matrix4x4 rotateMatrix = Matrix4x4::RotationX(rad.x);

    rotateMatrix = rotateMatrix * Matrix4x4::RotationY(rad.y);
    rotateMatrix = rotateMatrix * Matrix4x4::RotationZ(rad.z);

    transform(rotateMatrix);
}

void Object::translate(const Vec4d& v) noexcept
{
    Matrix4x4 tm = Matrix4x4::Translation(v);
    transform(tm);
}

void Object::scale(float scale) noexcept
{
    Matrix4x4 tm = Matrix4x4::Identity();

    tm[0][0] = scale;
    tm[1][1] = scale;
    tm[2][2] = scale;

    transform(tm);
}

void Object::scale(const Vec4d& scale) noexcept
{
    Matrix4x4 tm = Matrix4x4::Identity();

    tm[0][0] = scale.x;
    tm[1][1] = scale.y;
    tm[2][2] = scale.z;

    transform(tm);
}

void Object::transform(const Matrix4x4& tm) noexcept
{
    m_transformationMatrix = m_transformationMatrix * tm;
}


/* [[nodiscard]] */ const Mesh& Object::getMesh() const noexcept
{
    return m_mesh;
}

/* [[nodiscard]] */ const Matrix4x4& Object::getTransformationMatrix() const noexcept
{
    return m_transformationMatrix;
}
