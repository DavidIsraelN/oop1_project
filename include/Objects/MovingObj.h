#pragma once
#include "Object.h"
#include "Movement.h"
#include <memory>

class Level;
const auto speedPerSecond = 130.f;

//abstract class
class MovingObj : public Object
{
public:
  MovingObj(const sf::Texture& texture, const sf::Vector2f& position, float width,
            float height, float scale = 1.05)
  : Object(texture, position, width <= height ? width : height, width <= height ? width : height, scale)
  {
    m_original_position = m_sprite.getPosition();
  }

  void resetPosition() {m_sprite.setPosition(m_original_position);}
  void collide(Pacman& pacman) override { }
  void collide(Demon& demon) override { }

  //MovingObj(const sf::Texture&, const sf::Vector2f&, float, float, float = 1);
  virtual void setDirection(sf::Keyboard::Key) { }

  virtual void move(const sf::Time&, const Level&, float, float) = 0;

  sf::Vector2f getPosition() const { return m_sprite.getPosition(); }
  void freeze() { std::cout << "hi";}

protected:
  //float m_win_width, m_win_height;
  std::unique_ptr<Movement> m_move;
  sf::Vector2f m_original_position;
  sf::Vector2f m_cur_direction = { 0, 0 };
  sf::Vector2f m_new_direction = { 0, 0 };
};
