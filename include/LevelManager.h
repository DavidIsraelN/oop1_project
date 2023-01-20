#pragma once
#include "InfoBar.h"
#include "Level.h"
#include "Timer.h"

const size_t LEVELS = 3;

class LevelManager
{
public:
  LevelManager(const float, const float, const float);
  bool run(sf::RenderWindow&);
  void chooseNewLevel(size_t);

private:
  void setNextLevel(sf::RenderWindow&);
  void levelAction(sf::Time, sf::Clock);
  void gameOver(sf::RenderWindow&) const;

  Level m_current_level;
  Timer m_timer;
  InfoBar m_info;

  float m_win_width, m_win_height, m_info_height;
};
