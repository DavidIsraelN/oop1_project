#pragma once
#include "MovingObj.h"

const auto speedPerSecond = 130.f;

class Pacman : public MovingObj
{
public:
  Pacman(const sf::Vector2f&, float, float);

  void setDirection(sf::Keyboard::Key) override;
  void move(const sf::Time&, const Level&, float, float) override;

  size_t getLife() const;
  size_t getScore() const;
  //void lifeReduction();
  void setScore(const size_t);
  void setLife(const size_t);
  void setAnimate(const sf::Time&);
  void stopSPacman();
  void SPacmanClock(const sf::Time&);
  bool isSuperPacman() const;

  void collide(Object&)     override;
  void collide(Cookie&)     override;
  void collide(SuperPGift&) override;
  void collide(FreezeGift&) override;
  void collide(TimeGift&)   override;
  void collide(LifeGift&)   override;
  void collide(Key&)        override;
  void collide(Demon&)      override;

private:

  size_t m_life = 3;
  size_t m_score = 0;
  bool is_super_pacman = false;
  float m_counter_seconds = 0;
  float m_spacman_clock = 0;
  float m_colors_clock = 0;

  //std::unique_ptr<Movement> m_move;

//  float m_obj_h_w;
//  bool m_scale = false;
};