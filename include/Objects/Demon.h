#pragma once
#include "MovingObj.h"

class Demon : public MovingObj
{
public:
  Demon(const sf::Vector2f&, float, float, float, float);
  void move(sf::Time) override;

//	void collusion() override;
  void collide(Object& object) override { }
  void collide(Cookie& cookie) override { }
  void collide(Gift& gift) override { }
  void collide(Key& key) override { }
  void collide(Door& door) override { }
  void collide(Wall& wall) override { }


private:

};
