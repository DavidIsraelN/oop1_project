#pragma once
#include "MovingObj.h"

class Demon : public MovingObj
{
public:
  Demon(const sf::Vector2f&, float, float);
  void move(const sf::Time&, const Level&, float, float) override;

  void collide(Object&)     override { }
  void collide(Cookie&)     override { }
  void collide(SuperPGift&) override { }
  void collide(FreezeGift&) override { }
  void collide(TimeGift&)   override { }
  void collide(LifeGift&)   override { }
  void collide(Key&)        override { }
  void collide(Wall&)       override { }
  void collide(Door&)       override { }

private:
};
