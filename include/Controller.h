#pragma once
#include "Board.h"
#include "LevelManager.h"
#include "Menu.h"
#include "Colors.h"

const float WIN_HEIGHT = 800;
const float WIN_WIDTH = 800;
const float INFO_HEIGHT = 60;
const sf::Color MAIN_COLOR = DeepRed;

class Controller
{
public:
  Controller();
  void run();
  void runGame();

private:
  sf::RenderWindow m_window;
  LevelManager m_levels;
  Menu m_menu;
};
