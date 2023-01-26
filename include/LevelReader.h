//#pragma once
//#include <sstream>
//
//class LevelReader
//{
//public:
//  LevelReader(std::ifstream& board = ResourceManager::Resource().getTxtFile(TxtIndex::LEVEL1)) : m_level_board(board)
//  {
//    backToStart();
//      std::string line;
//      std::getline(m_level_board, line);
//      auto size = std::istringstream(line);
//      size >> m_level_rows >> m_level_cols;
//  }
//
//  LevelReader(const LevelReader& other) : LevelReader(other.m_level_board) { }
//  
//  LevelReader& operator=(const LevelReader& other)
//  {
//    auto temp = other;         //copy with copy c-tor
//    return temp;
//  }
//  size_t getRows() const {return m_level_rows;}
//  size_t getCols() const {return m_level_cols;}
//  char getChar() const {return m_level_board.get();}
//  void backToStart() {m_level_board.seekg(0, m_level_board.beg);}
//
//private:
//  std::ifstream& m_level_board;
//  size_t m_level_rows, m_level_cols;
//};