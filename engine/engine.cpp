#include <iostream>

#include "../math/functions.h"
#include "engine.h"

/* explicit */ Engine::Engine(unsigned width, unsigned height) noexcept
: m_window(new Window(width, height, "engine")),
  m_keyboard(new Keyboard()),
  obj1(),
  m_timer(),
  m_camera()
{
    std::cout << "Engine: created" << '\n';

    obj1.loadFromFile("objects/monkey.obj");
    obj1.translate({0, 0, 5, 1});

    m_camera.setFov(90.f);
    m_camera.setZ(0.1f, 100.f);
    m_camera.setAspect(static_cast<float>(height) / width);
}

/* virtual */ Engine::~Engine() noexcept
{
    std::cout << "Engine: destroyed" << '\n';
}

void Engine::run()
{
    while (m_window->isOpen()) {
        m_window->processEvents();

        update();
    }
}

void Engine::init() noexcept
{
    m_window->setFramerateLimit(60);
    m_timer.start();

    std::cout << "Engine: set variables" << '\n';
}

void Engine::update() noexcept
{
    m_window->clear();

    float dtime = m_timer.reset();

    obj1.rotate(Vec4d(0, 20, 0, 1) * dtime);

    if (m_keyboard->isKeyPressed(KEY(Right))) {
        m_camera.rotate(Vec4d(0, 4, 0, 0) * dtime);
    }
    else if (m_keyboard->isKeyPressed(KEY(Left))) {
        m_camera.rotate(Vec4d(0, -4, 0, 0) * dtime);
    }

    if (m_keyboard->isKeyPressed(KEY(W))) {
        // m_camera.m_position = m_camera.m_position + m_camera.m_forward * -10 * dtime;
        m_camera.transtale(m_camera.forward() * 10 * dtime);
    }
    else if (m_keyboard->isKeyPressed(KEY(S))) {
        // m_camera.m_position = m_camera.m_position + m_camera.m_forward * 10 * dtime;
        m_camera.transtale(m_camera.forward() * -10 * dtime);
    }

    if (m_keyboard->isKeyPressed(KEY(D))) {
        // m_camera.m_position = m_camera.m_position + m_camera.m_right * 10 * dtime;
        m_camera.transtale(m_camera.right() * -10 * dtime);
    }
    else if (m_keyboard->isKeyPressed(KEY(A))) {
        // m_camera.m_position = m_camera.m_position + m_camera.m_right * -10 * dtime;
        m_camera.transtale(m_camera.right() * 10 * dtime);
    }

    render(obj1);

    m_window->display();
}

void Engine::render(Object& obj) noexcept
{
    const Mesh&      mesh           = obj.getMesh();
    const Matrix4x4& transformation = obj.getTransformationMatrix();

    unsigned width  = m_window->width();
    unsigned height = m_window->height();

    std::vector<Triangle> toDraw;
    toDraw.reserve(mesh.triangles.size());

    for (const Triangle& t : mesh.triangles) {
        Triangle projected;

        // transformation apply
        projected[0] = transformation * t[0];
        projected[1] = transformation * t[1];
        projected[2] = transformation * t[2];

        // camera apply
        Matrix4x4 viewMatrix = Matrix4x4::View(m_camera.pos(),
                                               m_camera.forward(),
                                               m_camera.up(),
                                               m_camera.right());

        projected[0] = viewMatrix * projected[0];
        projected[1] = viewMatrix * projected[1];
        projected[2] = viewMatrix * projected[2];

        // back face culling
        Vec4d normal = projected.norm();

        Vec4d v = projected[0] -
                  m_camera.pos().normalize(); // vector from camera to triangle

        if (dotProduct(normal, v) > -0.4f) {
            // lightning
            Vec4d ld(0, 0, 1, 0);

            Color col(244, 64, 96);
            float b = std::max(0.f, dotProduct(ld, normal));

            col.r *= b;
            col.g *= b;
            col.b *= b;

            projected.setColor(col);

            // projection apply
            Matrix4x4 projectionMatrix = m_camera.getProjectionMatrix();

            projected[0] = projectionMatrix * projected[0];
            projected[1] = projectionMatrix * projected[1];
            projected[2] = projectionMatrix * projected[2];

            // clipping
            for (const Plane& p : m_camera.getPlanes()) {
            }


            // viewport matrix apply
            Matrix4x4 viewport = Matrix4x4::Viewport(width, height);

            projected[0] = viewport * projected[0];
            projected[1] = viewport * projected[1];
            projected[2] = viewport * projected[2];

            toDraw.push_back(std::move(projected));
        }
    }

    std::sort(toDraw.begin(),
              toDraw.end(),
              [](const Triangle& t1, const Triangle& t2)
              {
                  float z1 = (t1[0].z + t1[1].z + t1[2].z) / 3.f;
                  float z2 = (t2[0].z + t2[1].z + t2[2].z) / 3.f;
                  return z1 > z2;
              });

    for (const Triangle& t : toDraw) {
        m_window->draw(t, true);
    }
}
