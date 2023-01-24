#pragma once
#include "Object.h"
#include "Pacman.h"
#include "Demon.h"

//abstract class

class StaticObj : public Object
{
public:
  StaticObj(const sf::Texture& texture, const sf::Vector2f& position,
    float width, float height, float scale = 1)
    : Object(texture, position, width, height, scale) { }

  virtual void collide(Object&) { }
  virtual void collide(Pacman&) = 0;
  void collide(Cookie&)     override { }
  void collide(SuperPGift&) override { }
  void collide(FreezeGift&) override { }
  void collide(TimeGift&)   override { }
  void collide(LifeGift&)   override { }
  void collide(Key&)        override { }
  void collide(Wall&)       override { }
  void collide(Door&)       override { }
};
