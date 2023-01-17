#pragma once
#include "Erasable.h"

//class Erasable;

class Key : public Erasable
{
public:
  Key(const sf::Vector2f&, float, float);
//	~Key();
  void collide(Object& obj) override { }
  void collide(Pacman& pacman) override
  {
    delObj();
    pacman.collide(*this);
    static sf::Sound sound(*ResourceManage::Resource()->getEatGift());
    sound.play();
    delRandomDoor();
  }
  void delRandomDoor()
  {
    //*****************
  }
private:

};