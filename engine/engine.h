#pragma once

#include <memory>

#include "../graphics/object.h"
#include "../graphics/triangle.h"
#include "../io/keyboard.h"
#include "../io/window.h"
#include "../utility/logger.h"
#include "../utility/timer.h"
#include "camera.h"

class Engine
{
public:
    explicit Engine(unsigned width, unsigned height) noexcept;
    virtual ~Engine() noexcept;

    void run();

private:
    void         init() noexcept;
    virtual void update() noexcept;
    void         render(Object& t) noexcept;

private:
    std::unique_ptr<Window>   m_window;
    std::unique_ptr<Keyboard> m_keyboard;

    Object obj1;

    Timer m_timer;

    Camera m_camera;
};
