#pragma once
#include "StaticObj.h"

class Wall : public StaticObj
{
public:
  Wall(const sf::Texture&, const sf::Vector2f&, float, float);
//    ~Wall();
  //virtual void collide(const Pacman& other_obj);
  void collide(Pacman& pacman) override { }

  void collide(Object& obj) override {
    obj.collide(*this); }
private:

};