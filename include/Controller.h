#pragma once
#include "LevelManager.h"
#include "Menu.h"
#include "Colors.h"

const size_t WIN_HEIGHT = 800;
const size_t  WIN_WIDTH = 800;
const size_t  INFO_HEIGHT = 60;

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
