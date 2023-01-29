#pragma once
#include <vector>
#include "Buttons/Button.h"

// Class for the Game Menu

//-------------------------------------------------------------------
enum class ButtonIdx
{
  NEW_GAME, HELP, EXIT, MUTE
};

//-------------------------------------------------------------------
class Menu {
public:
  Menu(float, float);
  void draw(sf::RenderWindow&) const;
  bool run(sf::RenderWindow&, LevelManager&, bool);
  bool handleClick(const sf::Vector2f&, sf::RenderWindow&, LevelManager&) const;
  bool handleKey(sf::Keyboard::Key, sf::RenderWindow&, LevelManager&) const;
  bool clickBack(const sf::Vector2f& loc) const;

private:
  void buildMenue(float, float);

  bool m_back_button = false;
  sf::Text m_menu;
  std::vector<std::unique_ptr<Button>> m_buttons;
  std::unique_ptr<Button> m_back;
};
