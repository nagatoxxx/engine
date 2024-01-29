#include <iostream>

#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>

#include "window.h"

/* explicit */ Window::Window(unsigned           width,
                              unsigned           height,
                              const std::string& title) noexcept
: m_window(sf::VideoMode(width, height), title, sf::Style::Close)
{
    std::cout << "Window: created" << '\n';
}

/* virtual */ Window::~Window() noexcept
{
    std::cout << "Window: destroyed" << '\n';
}

void Window::setFramerateLimit(unsigned frames) noexcept
{
    m_window.setFramerateLimit(frames);
}

void Window::draw(const Triangle& t, bool bounds /* = false  */) noexcept
{
    sf::VertexArray triangle(sf::Triangles, 3);

    triangle[0].position = sf::Vector2f(t[0].x, t[0].y);
    triangle[1].position = sf::Vector2f(t[1].x, t[1].y);
    triangle[2].position = sf::Vector2f(t[2].x, t[2].y);

    triangle[0].color.r = t.color.r;
    triangle[0].color.g = t.color.g;
    triangle[0].color.b = t.color.b;

    triangle[1].color.r = t.color.r;
    triangle[1].color.g = t.color.g;
    triangle[1].color.b = t.color.b;

    triangle[2].color.r = t.color.r;
    triangle[2].color.g = t.color.g;
    triangle[2].color.b = t.color.b;

    sf::Vertex lines[4] =
        {sf::Vertex(sf::Vector2f(t[0].x, t[0].y), sf::Color(0, 0, 0, 255)),
         sf::Vertex(sf::Vector2f(t[1].x, t[1].y), sf::Color(0, 0, 0, 255)),
         sf::Vertex(sf::Vector2f(t[2].x, t[2].y), sf::Color(0, 0, 0, 255)),
         sf::Vertex(sf::Vector2f(t[0].x, t[0].y), sf::Color(0, 0, 0, 255))};

    m_window.draw(triangle);

    if (bounds)
        m_window.draw(lines, 4, sf::LineStrip);
}

void Window::processEvents() noexcept
{
    sf::Event e;
    while (m_window.pollEvent(e)) {
        if (e.type == sf::Event::Closed) {
            m_window.close();
        }
    }
}

void Window::clear() noexcept
{
    m_window.clear(sf::Color::White);
}

void Window::display() noexcept
{
    m_window.display();
}

unsigned Window::width() const noexcept
{
    return m_window.getSize().x;
}

unsigned Window::height() const noexcept
{
    return m_window.getSize().y;
}
