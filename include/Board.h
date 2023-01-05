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
    void setCurrentLevel();
    std::vector<std::string> getVector();

private:
    std::ifstream m_board;
    std::vector<std::string> m_current_level;
    unsigned int m_level_col;
    unsigned int m_level_row;
};