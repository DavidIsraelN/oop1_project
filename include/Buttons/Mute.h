#pragma once
#include "Button.h"
#include "Sound.h"

class Mute : public Button
{
public:
  //-------------------------------------------------------------------
  Mute(const sf::Vector2f& position, size_t size)
      : Button("Mute", position, size, sf::Color::White) { }

  //-------------------------------------------------------------------
  bool action(sf::RenderWindow& window, LevelManager& level_m) override
  {
    Sound::Sounds().Mute();
    m_text.setString(Sound::Sounds().isMute() ? "Unmute" : "Mute");
    return false;
  }
};