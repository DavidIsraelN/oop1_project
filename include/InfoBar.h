#pragma once
#include <SFML/Graphics.hpp>
#include "Timer.h"

class Level;

class InfoBar {
public:
  InfoBar(const float, const float, const float);
  void draw(sf::RenderWindow&) const;
  void setInfo(Level&, Timer&);

private:
  void drawLife(sf::RenderWindow&) const;
  void setTimerColor(std::string);

  sf::RectangleShape m_rect;
  sf::Text m_timer, m_level, m_score;
  std::vector<sf::Sprite> m_pacman_icon;
  size_t m_life = 3;
};