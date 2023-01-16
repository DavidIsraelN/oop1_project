#pragma once
#include "Erasable.h"

//class Erasable;

class Key : public Erasable
{
public:
  Key(const sf::Texture&, const sf::Vector2f&, float, float);
//	~Key();
  void collide(Pacman& pacman) override { }
  void collide(Object& obj) override {
    delObj();
    obj.collide(*this); }
private:

};