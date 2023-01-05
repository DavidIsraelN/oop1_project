#include "Board.h"

Board::Board() : m_board(std::ifstream("Board.txt")), m_level_col(0), m_level_row(0) { }

void Board::setCurrentLevel()
{
    std::string line;
    std::getline(m_board, line);
    auto size = std::istringstream(line);
    size >> m_level_row >> m_level_col;

    m_current_level.clear();
    for (int i = 0; i < m_level_row ; ++i)
        if(std::getline(m_board, line))
            m_current_level.push_back(line);

    std::getline(m_board, line); // for the space between levels
}

std::vector<std::string> Board::getVector()
{
    return m_current_level;
}
