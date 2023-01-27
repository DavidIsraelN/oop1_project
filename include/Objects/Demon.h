#pragma once
#include "MovingObj.h"
#include "Objects/Pacman.h"

class Pacman;

const auto NonRandomSpeed = 110.f;
const auto RandomSpeed = 120.f;

class Demon : public MovingObj
{
public:
  Demon(const sf::Vector2f&, float, float);
  void move(const sf::Time&, const Level&, float, float) override;
  void collide(Object&)  override { }
  void collide(Pacman&)  override;

private:
  void setMode(const sf::Time& deltaTime);
  sf::Vector2f setDirection(const sf::Vector2f&, const sf::Time&, const Level&, float, float);
  void setNonRandomDirection(sf::Vector2f[]);
  void setRandomDirection(sf::Vector2f[]);
  void setFirstAndSecondDirection(sf::Vector2f[]);
  void setThirdDirection(sf::Vector2f[]);

  float m_distance_x, m_distance_y;
  float m_random_clock = 0;
  float m_speed = 0;
};
