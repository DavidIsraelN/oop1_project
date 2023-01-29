#pragma once
#include "Erasable.h"

// Inheritance class for the game object of Erasable type - Key

class Key : public Erasable
{
public:
  Key(const sf::Vector2f& position, float width, float height)
    : Erasable(ResourceManager::Resource().getObjTexture(ObjIndex::KEY),
      position, width, height, 1.5) { }

  //-------------------------------------------------------------------
  void collide(Pacman& pacman) override
  {
    delObj();
    pacman.collide(*this);
    Sound::Sounds().Play(SoundIndex::GIFTS);
  }
};
