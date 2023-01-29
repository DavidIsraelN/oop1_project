#pragma once
#include "Erasable.h"

// Inheritance class for the game object of Erasable type - Door

class Door : public Erasable
{
public:
  Door(const sf::Vector2f& position, float width, float height)
    : Erasable(ResourceManager::Resource().getObjTexture(ObjIndex::DOOR),
      position, width, height) { }

  //-------------------------------------------------------------------
  void collide(Pacman& pacman) override
  {
    delObj();
  }
};
