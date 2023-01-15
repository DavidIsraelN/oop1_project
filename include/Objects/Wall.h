#pragma once
#include "StaticObj.h"

class Wall : public StaticObj
{
public:
  Wall(const sf::Texture&, const sf::Vector2f&, float, float);
//    ~Wall();
  //virtual void collide(const Pacman& other_obj);
    

private:

};