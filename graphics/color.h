#pragma once

#include <SFML/Graphics/Color.hpp>

#include <cstdint>

struct Color
{
    Color(const uint8_t r, const uint8_t g, const uint8_t b) noexcept;

    sf::Color toSFMLColor() const;

    uint8_t r;
    uint8_t g;
    uint8_t b;
};
