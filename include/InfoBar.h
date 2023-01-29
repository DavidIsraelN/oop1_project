#pragma once
#include <SFML/Graphics.hpp>
#include "Timer.h"

/* 
 * Class for the game information bar. 
 * display the level number, life left, score, timer.
 */

class Level;

class InfoBar {
public:
  InfoBar(float, float, float);
  void draw(sf::RenderWindow&) const;
  void setInfo(const Level&, const Timer&);

private:
  void drawLife(sf::RenderWindow&) const;
  void setLifeVector(float, float, float);
  void setInfoBar(float, float, float);

  sf::RectangleShape m_rect;
  sf::Text m_timer, m_level, m_score;
  std::vector<sf::Sprite> m_pacman_icon;
  size_t m_life = 3;
};