#pragma once
#include "Button.h"
#include "../Colors.h"

//Inherit class for Back button

class Back : public Button
{
public:
  //-------------------------------------------------------------------
  Back(const sf::Vector2f& position, size_t size)
      : Button("< Back", position, size, sf::Color::White) { }

  //-------------------------------------------------------------------
  bool action(sf::RenderWindow& window, LevelManager& level_m) override { return false; }
};
