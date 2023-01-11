#pragma once
#include "Board.h"
#include "Level.h"
#include "Menu.h"
//#include "CurrentLevel.h"
//#include "DrawGame.h"
#include "Colors.h"
#include "FontLoader.h"


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
  void play() const;

private:

//  CurrentLevel m_current_level;
//  DrawGame m_draw_game;
  sf::Font m_font;
  sf::RenderWindow m_window;
  Board m_my_board;
  Level m_level;
  Menu m_menu;
  int chooseLevel;
};
