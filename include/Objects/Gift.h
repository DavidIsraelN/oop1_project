#pragma once
#include "Erasable.h"

//class Erasable;

class Gift : public Erasable
{
public:
  Gift(const sf::Vector2f&, float, float);
//	~Gift();
  void chooseGift() const;

  void collide(Object& obj) override { }
  void collide(Pacman& pacman) override
  {
    delObj();
    pacman.collide(*this);
    static sf::Sound sound(*ResourceManage::Resource()->getEatGift());
    sound.play();
//    RandomGift();
  }
private:

};