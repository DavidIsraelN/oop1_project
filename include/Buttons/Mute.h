#pragma once
#include "Button.h"
#include "../Colors.h"
#include"Sound.h"

class Mute : public Button
{
public:
  Mute(const sf::Vector2f& position, size_t size)
      : Button("Mute", position, size, sf::Color::White) { }

  bool action(sf::RenderWindow& window, Controller& c) override
  {
    Sound::Sounds()->Mute();
    return false;
  }
};