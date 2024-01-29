#pragma once

#define KEY(x) (sf::Keyboard::x)

#include <SFML/Window/Keyboard.hpp>
#include <map>

class Keyboard
{
public:
    Keyboard() noexcept;
    ~Keyboard() noexcept;

    static bool isKeyPressed(sf::Keyboard::Key k) noexcept;

private:
    // std::map<sf::Keyboard::Key, float> m_pressedKeys;
};
