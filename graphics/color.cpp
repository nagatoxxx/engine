#include "color.h"

Color::Color(const uint8_t r, const uint8_t g, const uint8_t b) noexcept
: r(r),
  g(g),
  b(b)
{
}

sf::Color Color::toSFMLColor() const
{
    return sf::Color(r, g, b);
}
