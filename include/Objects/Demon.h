#pragma once
#include "MovingObj.h"
#include "Objects/Pacman.h"

class Pacman;

class Demon : public MovingObj
{
public:
  Demon(const sf::Vector2f&, float, float);

  void move(const sf::Time&, const Level&, float, float) override;
  sf::Vector2f setDirection(const sf::Vector2f&, const sf::Time&, const Level&, float, float);
  void setNonRandomDirection(sf::Vector2f[]);
  void setRandomDirection(sf::Vector2f[]);
  void setFirstAndSecondDirection(sf::Vector2f[]);
  void setThirdDirection(sf::Vector2f[]);


  void collide(Object&)     override { }
  void collide(Pacman&)     override;
  void collide(Cookie&)     override { }
  void collide(SuperPGift&) override { }
  void collide(FreezeGift&) override { }
  void collide(TimeGift&)   override { }
  void collide(LifeGift&)   override { }
  void collide(Key&)        override { }
  void collide(Wall&)       override { }
  void collide(Door&)       override { }

private:
  float m_distance_x, m_distance_y;
  float m_random_clock = 0;
};
