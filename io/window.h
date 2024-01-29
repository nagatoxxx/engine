#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/OpenGL.hpp>

#include "../graphics/triangle.h"

class Window
{
public:
    explicit Window(unsigned width, unsigned height, const std::string& title) noexcept;
    virtual ~Window() noexcept;

    void setFramerateLimit(unsigned frames) noexcept;

    inline bool isOpen() const noexcept
    {
        return m_window.isOpen();
    }

    void draw(const Triangle& t, bool bounds = false) noexcept;
    void processEvents() noexcept;
    void clear() noexcept;
    void display() noexcept;

    unsigned width() const noexcept;
    unsigned height() const noexcept;

private:
    sf::RenderWindow m_window;
};
