#pragma once
#include "StaticObj.h"

class Wall : public StaticObj
{
public:
  Wall(const sf::Vector2f& position, float width, float height)
    : StaticObj(ResourceManager::Resource().getObjTexture(ObjIndex::WALL),
      position, width, height) { }

  void collide(Pacman& pacman) override { /*pacman.collide(*this);*/ }
};
