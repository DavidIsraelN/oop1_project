#pragma once
#include "Object.h"

//abstract class

class MovingObj : public Object
{
public:
  MovingObj(const sf::Texture& texture, const sf::Vector2f& position, float width, float height, float scale = 1)
    : Object(texture, position, width, height, scale) { }

  //MovingObj(const sf::Texture&, const sf::Vector2f&, float, float, float = 1);
  virtual void move(sf::Time) = 0;
  virtual void setDirection(sf::Keyboard::Key) { }
  //virtual void collusion() = 0;
};
