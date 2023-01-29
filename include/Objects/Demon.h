#pragma once
#include "MovingObj.h"

// Inheritance class for the game object of Moving type - Demon

class Pacman;
const float NonRandomSpeed = 100;
const float RandomSpeed = 110;

class Demon : public MovingObj
{
public:
  Demon(const sf::Vector2f&, float, float);
  void move(const sf::Time&, const Level&, float, float) override;
  void collide(Object&)  override { }
  void collide(Pacman&)  override;
  void freeze() override;                     // to freeze demon

private:
  void setMode(const sf::Time&);   // set random / nonrandom movement
  sf::Vector2f setDirection(const sf::Vector2f&, const sf::Time&, const Level&, float, float);
  void setNonRandomDirection(sf::Vector2f[]);
  void setRandomDirection(sf::Vector2f[]);
  void setFirstAndSecondDirection(sf::Vector2f[]);
  void setThirdDirection(sf::Vector2f[]);
  void freezeClock(const sf::Time&);
  void stopFreeze() override;

  float m_distance_x = 0, m_distance_y = 0;
  float m_random_clock = 0, m_freeze_clock = 0;
  float m_speed = 0;
  bool m_is_freeze = false;
};
