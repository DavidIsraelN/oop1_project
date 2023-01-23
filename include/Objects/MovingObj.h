#pragma once
#include "Object.h"
#include "Movement.h"
//abstract class

class MovingObj : public Object
{
public:
  MovingObj(const sf::Texture& texture, const sf::Vector2f& position, float width,
            float height, float win_width, float win_height, float scale = 1.0001)
  : Object(texture, position, width <= height ? width : height, width <= height ? width : height, scale),
  m_win_width(win_width), m_win_height(win_height) { }
  void collide(Pacman& pacman) override { }

  //MovingObj(const sf::Texture&, const sf::Vector2f&, float, float, float = 1);
  virtual void move(const sf::Time&, const Level&) = 0;
  virtual void setDirection(sf::Keyboard::Key) { }
  //virtual void collusion() = 0;
protected:
  float m_win_width, m_win_height;
  std::unique_ptr<Movement> m_move;
};
