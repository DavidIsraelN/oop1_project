#pragma once
#include "Erasable.h"

class Cookie : public Erasable
{
public:
  Cookie(const sf::Vector2f& position, float width, float height)
    : Erasable(ResourceManager::Resource().getObjTexture(ObjIndex::COOKIE),
      position, width, height, 2) { }

  void collide(Pacman& pacman) override
  {
    delObj();
    pacman.collide(*this);
    Sound::Sounds().Play(SoundIndex::COOKIE);
  }

};
