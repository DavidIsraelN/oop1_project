#pragma once
#include "MovingObj.h"

const auto speedPerSecond = 130.f;
class Level;
class Cookie;
class Gift;
class Key;

class Pacman : public MovingObj
{
public:
  Pacman(const sf::Vector2f&, float, float);
  void setDirection(sf::Keyboard::Key) override;
  //void move(sf::Time) override;
  void move(sf::Time, float, float, float, float, const Level&);
  //	void collusion() override;
  void collide(Object& object) override {object.collide(*this);}
  void collide(Cookie& cookie) override {m_score += 2;     std::cout << m_score << std::endl;}
  void collide(Gift& gift) override {m_score += 4;     std::cout << m_score << std::endl;}
  void collide(Key& key) override {m_score += 4;     std::cout << m_score << std::endl;}

private:
  bool directionLegal(const sf::Vector2f&, float, float, const Level&, float, float);
  sf::Vector2f m_cur_direction = { 0, 0 };
  sf::Vector2f m_new_direction = { 0, 0 };
  size_t m_hearts = 3;
  size_t m_score = 0;
};