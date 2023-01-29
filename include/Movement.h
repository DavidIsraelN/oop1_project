#pragma once
#include <SFML/Graphics.hpp>

/* 
 * Abstract class with 2 inheriting classes that are responsible for the legality of Movement in game.
 * Regular Movement - does not go through walls and doors.
 * Super Pacman Movement - goes through doors, but not walls.
 */

class MovingObj;
class Level;

class Movement
{
public:
  virtual bool isLegal(const sf::Vector2f&, const Level&, MovingObj&, float, float) = 0;
};

//-------------------------------------------------------------------
class RegularMovement : public Movement
{
public:
  bool isLegal(const sf::Vector2f&, const Level&, MovingObj&, float, float) override;
};

//-------------------------------------------------------------------
class SPacmanMovement : public Movement
{
public:
  bool isLegal(const sf::Vector2f&, const Level&, MovingObj&, float, float) override;
};
