#pragma once
#include "Erasable.h"

// Abstract class for game objects of Erasable type - all the Gifts

class Gift : public Erasable
{
public:
  Gift(const sf::Texture& texture, const sf::Vector2f& position, float width, float height)
    : Erasable(texture, position, width, height, 1.5) { }
};
