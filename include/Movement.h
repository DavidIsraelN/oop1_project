#pragma onec
#include <SFML/Graphics.hpp>

class MovingObj;
class Level;

class Movement
{
public:
  virtual void action(const sf::Time&, const Level&, MovingObj&) = 0;
};

class PacmanMovement : public Movement
{
public:
  void action(const sf::Time&, const Level&, MovingObj&) override;
  void directionLegal(const sf::Time&, const Level&, MovingObj&);
};

class sPacmanMovement : public Movement
{
public:
  void action(const sf::Time&, const Level&, MovingObj&) override;
};

class randomMovement : public Movement
{
public:
  void action(const sf::Time&, const Level&, MovingObj&) override;
};

class smartMovement : public Movement
{
public:
  void action(const sf::Time&, const Level&, MovingObj&) override;
};