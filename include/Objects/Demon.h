#pragma once
#include "MovingObj.h"
//class MovingObj;

class Demon : public MovingObj
{
public:
  Demon(const sf::Texture&, const sf::Vector2f&, float, float);
  void move(sf::Time) override;

//	void collusion() override;


private:

};
