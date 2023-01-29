#pragma once
#include "MovingObj.h"

// Inheritance class for the game object of Moving type - Pacman

const float speedPerSecond = 130;

class Pacman : public MovingObj
{
public:
  Pacman(const sf::Vector2f&, float, float);
  void setDirection(sf::Keyboard::Key) override;
  void move(const sf::Time&, const Level&, float, float) override;
  void setScore(const size_t);
  void setLife(const size_t);
  bool isSuperPacman() const;
  void collide(Object&)     override;
  void collide(Cookie&)     override;
  void collide(SuperPGift&) override;
  void collide(FreezeGift&) override;
  void collide(TimeGift&)   override;
  void collide(LifeGift&)   override;
  void collide(Key&)        override;
  void collide(Demon&)      override;
  size_t getLife() const;
  size_t getScore() const;

private:
  void SPacmanClock(const sf::Time&);
  void setAnimate(const sf::Time&);
  void stopSPacman();

  size_t m_life = 3;
  size_t m_score = 0;
  bool is_super_pacman = false;
  float m_counter_seconds = 0;
  float m_spacman_clock = 0;
  float m_colors_clock = 0;
};