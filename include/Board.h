#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Objects/Pacman.h"
#include "Objects/Demon.h"
#include "Objects/Cookie.h"
#include "Objects/Gift.h"
#include "Objects/Wall.h"
#include "Objects/Door.h"
#include "Objects/Key.h"


class Board{
public:
    Board();
    void setCurrentLevel(size_t);
    size_t getCols() const;
    size_t getRows() const;
    std::vector<std::string> getVector();

private:
  void chooseBoard(size_t);

    std::ifstream m_board_1;
    std::ifstream m_board_2;
    std::ifstream m_board_3;
    std::ifstream* m_current_board;
    std::vector<std::string> m_current_level;
    size_t m_level_cols = 0;
    size_t m_level_rows = 0;
};