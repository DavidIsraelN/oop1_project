#pragma once
#include "Button.h"
#include <vector>

class ChooseLevel : public Button
{
public:
  ChooseLevel(const sf::Vector2f&, size_t, char);
  bool action(sf::RenderWindow&, Controller&) override;

private:
  size_t m_level_num;
};
