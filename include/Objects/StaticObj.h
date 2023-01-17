#pragma once
#include "Object.h"

//abstract class

class StaticObj : public Object
{
public:
  StaticObj(const sf::Texture&, const sf::Vector2f&, float, float, float = 1);

  virtual void collide(Object&) = 0;
  virtual void collide(Pacman&) = 0;
//  virtual void collide(Cookie&) = 0;
  void collide(Cookie&) override { }
  void collide(Gift&) override { }
  void collide(Key&) override { }

  //virtual ~StaticObj() = 0;
};
