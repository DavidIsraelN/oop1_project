#pragma once
#include <SFML/Graphics.hpp>

class MovingObj;
class Level;

class Movement
{
public:
  virtual ~Movement() = default;
  virtual bool isLegal(const sf::Vector2f&, const Level&, MovingObj&, float, float) = 0;
};

//-------------------------------------------------------------------
class RegularMovement : public Movement
{
public:
  //void action(const sf::Vector2f&, MovingObj&) override;
  bool isLegal(const sf::Vector2f&, const Level&, MovingObj&, float, float) override;
};

//-------------------------------------------------------------------
class SPacmanMovement : public Movement
{
public:
  //void action(const sf::Time&, const Level&, MovingObj&) override;
  bool isLegal(const sf::Vector2f&, const Level&, MovingObj&, float, float) override;
};
