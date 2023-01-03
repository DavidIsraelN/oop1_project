#pragma once
#include "Board.h"
#include "Level.h"
#include "CurrentLevel.h"
#include "DrawGame.h"

class Controller
{
public:
	Controller();
	~Controller();
  void run();

private:
  Board m_my_board;
  Level m_level;
  CurrentLevel m_current_level;
  DrawGame m_draw_game;
};
