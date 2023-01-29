#pragma once
#include "InfoBar.h"
#include "GameOver.h"
#include "Level.h"
#include "Timer.h"

/* 
 * This class is responsible for selecting and running the levels, running the status bar, 
 * moving the Objects, checking for collisions, changing level when the previous one is over,
 * and running the game over
 */

const size_t LEVELS = 3;

class LevelManager
{
public:
  LevelManager(const float, const float, const float);
  bool run(sf::RenderWindow&);
  void chooseNewLevel(size_t, size_t = 3, size_t = 0);

private:
  void nextLevel(sf::RenderWindow&);
  void levelAction(const sf::Time&);
  void gameOver(sf::RenderWindow&);
  void resetLevel();
  void setLevel(sf::RenderWindow&);

  Level m_current_level;
  Timer m_timer;
  InfoBar m_info;
  GameOver m_game_over;
  float m_win_width, m_win_height;
};
