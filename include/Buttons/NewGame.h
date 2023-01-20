#pragma once
#include "Button.h"
#include <vector>

class NewGame : public Button
{
public:
  NewGame(float, float);
  bool action(sf::RenderWindow&, LevelManager&) override;

private:
  void drawLevels(sf::RenderWindow&) const;
  void bulidLevelsTxt();

  float m_window_width;
  float m_window_height;
  sf::Text m_levels_txt;
  sf::RectangleShape m_levels_rect;
  std::vector<std::unique_ptr<Button>> m_levels;
};