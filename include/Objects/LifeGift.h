#pragma once
#include "Objects/Gift.h"

// Inheritance class for the game object of Gift type - Life Gift

class LifeGift : public Gift
{
public:
  LifeGift(const sf::Vector2f& position, float width, float height)
      : Gift(ResourceManager::Resource().getObjTexture(ObjIndex::LIFE), position, width, height) { }

  //-------------------------------------------------------------------
  void collide(Pacman& pacman) override
  {
    delObj();
    pacman.collide(*this);
    Sound::Sounds().Play(SoundIndex::GIFTS);
  }
};
