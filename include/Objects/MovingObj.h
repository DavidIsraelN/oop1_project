#pragma once
#include "Object.h"

//abstract class

class MovingObj : public Object
{
public:
  MovingObj(const sf::Texture& texture, const sf::Vector2f& position, float width, float height, float scale = 1.01)
  //: Object(texture, position, width, height, scale) { }
      : Object(texture, position, width <= height ? width : height, width <= height ? width : height, scale) { }
  void collide(Pacman& pacman) override { }


  //MovingObj(const sf::Texture&, const sf::Vector2f&, float, float, float = 1);
  //virtual void move(sf::Time) = 0;
  virtual void setDirection(sf::Keyboard::Key) { }
  //virtual void collusion() = 0;
};
