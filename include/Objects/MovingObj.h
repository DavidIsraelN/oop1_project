#pragma once
#include "Object.h"
#include "Movement.h"
#include <memory>
#include "Colors.h"

class Level;

//abstract class
class MovingObj : public Object
{
public:
  MovingObj(const sf::Texture& texture, const sf::Vector2f& position, float width,
            float height, float scale = 1.05f)
      : Object(texture, position, width <= height ? width : height, width <= height ? width : height, scale)
  {
    m_original_position = m_sprite.getPosition();
  }

  void resetPosition() { m_sprite.setPosition(m_original_position); }
  void collide(Pacman&)     override { }
  void collide(Demon&)      override { }
  void collide(Wall&)       override { }
  void collide(Door&)       override { }
  void collide(Cookie&)     override { }
  void collide(SuperPGift&) override { }
  void collide(FreezeGift&) override { }
  void collide(TimeGift&)   override { }
  void collide(LifeGift&)   override { }
  void collide(Key&)        override { }

  virtual void setDirection(sf::Keyboard::Key) { }
  virtual void move(const sf::Time&, const Level&, float, float) = 0;
  virtual void freeze() { }
  virtual void stopFreeze() { }

  sf::Vector2f getPosition() const { return m_sprite.getPosition(); }

protected:
  std::unique_ptr<Movement> m_move;
  sf::Vector2f m_original_position;
  sf::Vector2f m_cur_direction = { 0, 0 };
  sf::Vector2f m_new_direction = { 0, 0 };
};
