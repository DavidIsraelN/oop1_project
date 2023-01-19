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
    Sound::Sounds()->Play(SoundIndex::GIFTS);
    delRandomDoor();
  }
  void delRandomDoor()
  {
    //*****************
  }
private:

};