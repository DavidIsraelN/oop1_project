#pragma once
#include "Button.h"
#include <vector>

// Inherit class for Level Choose button

class ChooseLevel : public Button
{
public:
  //-------------------------------------------------------------------
  ChooseLevel(const sf::Vector2f& position, size_t size, size_t level_num)
    : Button(std::string("Level ") + std::to_string(level_num), position, size, SoftYellow),
    m_level_num(level_num) { }

  //-------------------------------------------------------------------
  bool action(sf::RenderWindow& win, LevelManager& level_m)
  {
    level_m.chooseNewLevel(m_level_num);
    return true;
  }

private:
  size_t m_level_num;
};
