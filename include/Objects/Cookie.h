#pragma once
#include "Erasable.h"

class Cookie : public Erasable
{
public:
  Cookie(const sf::Vector2f&, float, float);
//~Cookie();
  void collide(Pacman& pacman) override
  {
    delObj();
    pacman.collide(*this);
    Sound::Sounds()->Play(SoundIndex::COOKIE);
  }

  void collide(Object& obj) override { }

private:
};
