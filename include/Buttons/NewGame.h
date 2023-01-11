#pragma once
#include "Button.h"
#include <vector>

class NewGame : public Button
{
public:
  NewGame(sf::Font&, float, float);
  bool action(sf::RenderWindow&, Controller&) override;

private:
  void drawLevels(sf::RenderWindow&) const;
  bool handleClick(const sf::Vector2f &loc, sf::RenderWindow &window, Controller &c) const;
  void bulidLevelsScreen();

  float m_window_width;
  float m_window_height;
  sf::Font m_font;
  sf::Text m_levels_txt;
  sf::Text m_back;
  sf::RectangleShape m_levels_rect;
  std::vector<Button*> m_levels;
};