#include "Board.h"

Board::Board() : m_board(std::ifstream("Level_3.txt")), m_level_cols(0), m_level_rows(0) { }

void Board::setCurrentLevel()
{
    std::string line;
    std::getline(m_board, line);
    auto size = std::istringstream(line);
    size >> m_level_rows >> m_level_cols;

    m_current_level.clear();
    for (int i = 0; i < m_level_rows ; ++i)
        if(std::getline(m_board, line))
            m_current_level.push_back(line);

    //std::getline(m_board, line); // for the space between levels
}
size_t Board::getCols() const
{
  return m_level_cols;
}

size_t Board::getRows() const
{
  return m_level_rows;
}


std::vector<std::string> Board::getVector()
{
    return m_current_level;
}
