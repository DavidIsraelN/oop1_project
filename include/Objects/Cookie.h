#pragma once
#include "Erasable.h"
#include <chrono>
#include <thread>

class Cookie : public Erasable
{
public:
  Cookie(const sf::Vector2f&, float, float);
//~Cookie();
  void collide(Pacman& pacman) override
  {
    delObj();
    pacman.collide(*this);
    static sf::Sound m_sound(*ResourceManage::Resource()->getEatCookie());
    m_sound.play();
  }

  void collide(Object& obj) override { }

private:
//  static sf::Sound m_sound(*ResourceManage::Resource()->getEatCookie());
};

//sf::Sound Cookie::sound = sf::Sound(*ResourceManage::Resource()->getEatCookie());
