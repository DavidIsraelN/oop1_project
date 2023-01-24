#pragma once
#include "Erasable.h"

class Gift : public Erasable
{
public:
  Gift(const sf::Vector2f& position, float width, float height)
    : Erasable(ResourceManager::Resource().getObjTexture(ObjIndex::GIFT),
      position, width, height, 1.5) { }

  //Gift(const sf::Texture& texture, const sf::Vector2f& position, float width, float height)
  //  : Erasable(texture, position, width, height, 1.5) { }

  void chooseGift() const;

  void collide(Pacman& pacman) override
  {
    delObj();
    pacman.collide(*this);
    Sound::Sounds().Play(SoundIndex::GIFTS);

//    RandomGift();
  }

};
