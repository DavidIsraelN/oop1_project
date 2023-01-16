#pragma once
#include "Erasable.h"
#include <chrono>
#include <thread>

class Cookie : public Erasable
{
public:
  Cookie(const sf::Texture&, const sf::Vector2f&, float, float);
//~Cookie();
  void collide(Pacman& pacman) override
  {
    delObj();
    pacman.collide(*this);

    static sf::Sound sound(*ResourceManage::Instance()->getEatCookie());
    sound.play();
  }

  void collide(Object& obj) override { }

private:
};