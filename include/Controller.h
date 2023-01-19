#pragma once
#include "Board.h"
#include "Level.h"
#include "Menu.h"
#include "Colors.h"

const float WIN_HEIGHT = 800;
const float WIN_WIDTH = 800;
const float INFO_HEIGHT = 60;

class Controller
{
public:
  Controller();
//	~Controller();
  void run();
  bool runMenu();
  void runGame();
  void chooseNewLevel(size_t);

private:
  sf::RenderWindow m_window;
  Level m_level;
  Menu m_menu;
};
