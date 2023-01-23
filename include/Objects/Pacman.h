#pragma once
#include "MovingObj.h"

const auto speedPerSecond = 130.f * 2;
class Level;
class Cookie;
class Gift;
class Key;
class Wall;

class Pacman : public MovingObj
{
public:
  Pacman(const sf::Vector2f&, float, float, float, float);

  void setDirection(sf::Keyboard::Key) override;
  void move(const sf::Time&, const Level&) override;
//  void move(sf::Time, float, float, float, float, const Level&);

  size_t getLife() const;
  size_t getScore() const;
  void lifeReduction();
  void setScore(const size_t);
  void setLife(const size_t);

  //	void collusion() override;
  void collide(Object&) override;
  void collide(Cookie&) override;
  void collide(Gift&) override;
  void collide(Key&) override;
  void collide(Wall&) override;
  void collide(Door&) override;

private:
  bool directionLegal(const sf::Vector2f&, float, float, const Level&, float, float);
  sf::Vector2f m_cur_direction = { 0, 0 };
  sf::Vector2f m_new_direction = { 0, 0 };
  sf::Vector2f m_lest_movement = { 0, 0 };
  size_t m_life = 3;
  size_t m_score = 0;
//  ֿfloat m_obj_h_w;
//  bool m_scale = false;
};