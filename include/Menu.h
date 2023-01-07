#pragma once
#include <vector>
#include "Buttons/Button.h"

class Menu {
public:
  Menu(sf::Font&, float, float);
  //~Menu();
  void draw(sf::RenderWindow&) const;
  void handlClick(const sf::Vector2f&, sf::RenderWindow&, Controller&) const;

private:
  sf::Text m_menu;
  std::vector<Button*> m_buttons;
};