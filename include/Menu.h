#pragma once
#include <vector>
#include "Buttons/Button.h"


class Menu {
public:
  Menu(sf::Font&, float, float);
  void draw(sf::RenderWindow&) const;
  void handlClick(const sf::Vector2f&, sf::RenderWindow&) const;


private:
  std::vector<Button*> m_buttons;
};