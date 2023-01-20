#pragma once
#include "Button.h"

class ExitGame : public Button
{
public:
  //-------------------------------------------------------------------
  ExitGame(float width, float height)
    : Button("Exit Game", { width / 2 , height / 1.6f }, height / 30, SoftYellow) { }

  //-------------------------------------------------------------------
  bool action(sf::RenderWindow& window, LevelManager& level_m) override { window.close(); return false;}
};