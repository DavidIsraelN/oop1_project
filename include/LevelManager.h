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
  void chooseNewLevel(size_t, size_t = 3, size_t = 0);

private:
  void buildGameOverScreen();
  void nextLevel(sf::RenderWindow&);
  void levelAction(const sf::Time&);
  void gameOver(sf::RenderWindow&);
  void resetLevel();
  void setLevel(sf::RenderWindow&);

  Level m_current_level;
  Timer m_timer;
  InfoBar m_info;
  sf::Text m_game_over, m_game_over_score;
  float m_win_width, m_win_height;
};
