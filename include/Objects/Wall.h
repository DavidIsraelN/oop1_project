#pragma once
#include "StaticObj.h"

// Inheritance class for the game object of Non-movind type - Wall

class Wall : public StaticObj
{
public:
  Wall(const sf::Vector2f& position, float width, float height)
    : StaticObj(ResourceManager::Resource().getObjTexture(ObjIndex::WALL),
      position, width, height) { }

  void collide(Pacman& pacman) override { }
};
