#pragma once
#include "Button.h"
#include "../Colors.h"

class Back : public Button
{
public:
  Back(const sf::Vector2f& position, size_t size)
      : Button("< Back", position, size, sf::Color::White) { }

  bool action(sf::RenderWindow& window, Controller& c) override { return false; }
};
