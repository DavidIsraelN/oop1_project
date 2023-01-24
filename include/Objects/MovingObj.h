#pragma once
#include "Object.h"
#include "Movement.h"
#include <memory>

//class Movement;

//abstract class
class MovingObj : public Object
{
public:
  MovingObj(const sf::Texture& texture, const sf::Vector2f& position, float width,
            float height, float scale = 1.01)
  : Object(texture, position, width <= height ? width : height, width <= height ? width : height, scale) { }

  void collide(Pacman& pacman) override { }
  //MovingObj(const sf::Texture&, const sf::Vector2f&, float, float, float = 1);
  virtual void setDirection(sf::Keyboard::Key) { }

  virtual void move(const sf::Time&, const Level&, float, float) = 0;

protected:
  //float m_win_width, m_win_height;
  std::unique_ptr<Movement> m_move;
  //std::unique_ptr<Movement> m_move;
};
