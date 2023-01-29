#pragma once
#include "Button.h"
#include "Buttons/Back.h"
#include <vector>

class Help : public Button
{
public:
  Help(float, float);
  bool action(sf::RenderWindow&, LevelManager&) override;

private:
  void readHelpTxt();
  void buildHelpScreen();
  void drawHelp(sf::RenderWindow&) const;

  Back m_back;
  sf::RectangleShape m_help_rect;
  float m_window_width;
  float m_window_height;
  std::vector<std::string> m_help_str;
  std::vector<sf::Text> m_help_txt;
};