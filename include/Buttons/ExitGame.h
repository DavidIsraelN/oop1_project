#pragma once
#include "Button.h"

class ExitGame : public Button
{
public:
  //-------------------------------------------------------------------
  ExitGame(const sf::Vector2f& position, size_t size)
    : Button("Exit Game", position, size, SoftYellow) { }

  //-------------------------------------------------------------------
  bool action(sf::RenderWindow& window, LevelManager& level_m) override { window.close(); return false;}
};