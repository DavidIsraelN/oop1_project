#pragma once
#include <SFML/Graphics.hpp>


class InfoBar {
public:
  InfoBar(const float, const float, const float);
  void draw(sf::RenderWindow&) const;
  void drawLife(sf::RenderWindow&) const;
  void setValues( size_t, std::string, size_t, size_t);

private:
  sf::RectangleShape m_rect;
  sf::Text m_timer, m_level, m_score;
  std::vector<sf::Sprite> m_pacman_icon;
  size_t m_life;
};