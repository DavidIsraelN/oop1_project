#include "Board.h"

Board::Board() : m_current_board(nullptr),
	m_board_1(std::ifstream("Level_1.txt")),
	m_board_2(std::ifstream("Level_2.txt")),
	m_board_3(std::ifstream("Level_3.txt")) { }

void Board::setCurrentLevel(size_t board_num)
{
	chooseBoard(board_num);
	std::string line;
	std::getline(*m_current_board, line);
	auto size = std::istringstream(line);
	size >> m_level_rows >> m_level_cols;

	m_current_level.clear();
	for (int i = 0; i < m_level_rows; ++i)
		if (std::getline(*m_current_board, line))
			m_current_level.push_back(line);
   // m_current_board->seekg(0, std::ios::beg);
}

void Board::chooseBoard(size_t board_num)
{
	m_current_board = (board_num == 1) ? &m_board_1 : (board_num == 2) ? &m_board_2 : &m_board_3;
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
