#pragma once
#include "Objects/Erasable.h"
//#include "Objects/MovingObj.h"
#include "Objects/Wall.h"
#include "Objects/Pacman.h"
#include "Timer.h"
//#include <fstream>
//#include <memory>
//#include <vector>

#include "LevelReader.h"

enum class ObjType
{
  COOKIE = '*', DEMON = '&', DOOR = 'D',
  GIFT   = '$', KEY   = '%', PACMAN = 'a',
  WALL   = '#', SPACE = ' '
};

class Gift;

class Level
{
public:
  Level(const float, const float, Timer&);
  void setCurrentLevel(size_t);
  void resetLevel();
  void draw(sf::RenderWindow&) const;
  bool isOver() const;
  void setDirection(sf::Keyboard::Key) const;
  void moveObjects(const sf::Time&) const;
  bool collideWithWall(MovingObj&) const;
  bool collideWithDoor(MovingObj&) const;
  void handleCollision() const;
  void erase();
  size_t getLevelNum() const;
  size_t getPacmanLife() const;
  size_t getPacmanScore() const;
  void setPacmanScore(size_t);
  void addFinalScore();
  void setPacmanLife(size_t);
  void resetMovingObj() const;
  sf::Vector2f getPacmanPosition() const;

private:
  void chooseLevel();
  void clearLevel();
  void buildLevel();
  void addObject(ObjType, size_t, size_t);
  void delRandomDoor();
  std::unique_ptr<Gift> chooseRandomGift(const sf::Vector2f&) const;

  //std::unique_ptr<std::ifstream> m_current_board;
  std::ifstream* m_current_board = nullptr;
  std::vector<std::unique_ptr<MovingObj>> m_demons;
  std::unique_ptr<Pacman> m_pacman;
  std::vector<std::vector<std::unique_ptr<Erasable>>> m_erasable_obj;
  std::vector<std::unique_ptr<Wall>> m_walls;

  float m_win_width, m_win_height;
  float m_obj_width = 0, m_obj_height = 0;
  size_t m_level_cols = 0, m_level_rows = 0;
  size_t m_level_num = 0;
  Timer& m_timer;
  //LevelReader le;
};
