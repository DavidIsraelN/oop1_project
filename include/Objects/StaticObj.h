#pragma once
#include "Object.h"
#include "Pacman.h"
#include "Demon.h"

//abstract class

class StaticObj : public Object
{
public:
  StaticObj(const sf::Texture&, const sf::Vector2f&, float, float, float = 1);

  virtual void collide(Object&) = 0;
  virtual void collide(Pacman&) = 0;
//  virtual void collide( Cookie&) = 0;
  void collide(Cookie& c) override { }
  void collide(Gift& c) override { }
  void collide(Key& c) override { }
  void collide(Wall& c) override { }
  void collide(Door& c) override { }

//  virtual ~StaticObj() = 0;
};
