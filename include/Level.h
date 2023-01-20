#pragma once
#include "Objects/Erasable.h"
#include "Objects/MovingObj.h"
#include "Objects/Wall.h"
#include "Timer.h"
#include <fstream>
#include <memory>
#include <vector>

enum class ObjType
{
  COOKIE = '*', DEMON = '&', DOOR = 'D',
  GIFT   = '$', KEY   = '%', PACMAN = 'a',
  WALL   = '#', SPACE = ' '
};

class Level
{
public:
  Level(const float, const float);
  void setCurrentLevel(size_t);
  void draw(sf::RenderWindow&) const;
  bool isOver() const;
  void setDirection(sf::Keyboard::Key) const;
  void moveObjects(sf::Time deltaTime) const;
  bool collideWithWallOrDoor(MovingObj& moving_obj) const;
  void handleCollision() const;
  void erase();
  size_t getLevelNum() const;
  size_t getPacmanLife() const;
  size_t getPacmanScore() const;

private:
  void chooseLevel();
  void clearLevel();
  void buildLevel();
  void addObject(ObjType, size_t, size_t);
  void delDoor();

  std::ifstream* m_current_board = nullptr;
  std::vector<std::unique_ptr<MovingObj>> m_moving_obj;
  std::unique_ptr<Pacman> m_pacman;
  std::vector<std::vector<std::unique_ptr<Erasable>>> m_erasable_obj;
  std::vector<std::unique_ptr<Wall>> m_walls;

  float m_win_width, m_win_height;
  float m_obj_width = 0, m_obj_height = 0;
  size_t m_level_cols = 0, m_level_rows = 0;
  size_t m_level_num = 0;
};
