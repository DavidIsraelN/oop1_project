#pragma once
#include "InfoBar.h"
#include "Objects/Erasable.h"
#include "Objects/MovingObj.h"
#include "Objects/Pacman.h"
#include "Objects/Wall.h"
#include "ResourceManage.h"
#include "Timer.h"
#include <fstream>
#include <memory>
#include <string>
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
  Level(const float, const float, const float);
  //~Level();
  //void resetLevel(size_t, size_t);
  //Object* createObject(ObjType, ResourceManage&, size_t, size_t) const;//get char and return pointe to the right object.

  void buildLevel();
  void clearLevel();
  void draw(sf::RenderWindow&) const;
  void setCurrentLevel(size_t);
  size_t getRows() const;
  size_t getCols() const;
  //ObjType getType(const sf::Vector2f&) const;
  bool runLevel(sf::RenderWindow&);

  bool collideWithWallOrDoor(MovingObj &moving_obj) const;
private:
  void chooselevel();
  void addObject(ObjType, size_t, size_t);
  //std::unique_ptr<Erasable> createObject(ObjType, const sf::Vector2f&) const;
  void handleCollision();
  void delDoor();

  std::ifstream* m_current_board = nullptr;

  //std::unique_ptr<MovingObj> m_player;
  std::unique_ptr<Pacman> m_player;
//  std::vector<std::unique_ptr<Erasable>> m_level;
  std::vector<std::vector<std::unique_ptr<Erasable>>> m_erasable_obj;
  std::vector<std::unique_ptr<MovingObj>> m_demons;
  std::vector<std::unique_ptr<Wall>> m_walls;

  Timer m_timer;
  InfoBar m_info;

  float m_obj_width = 0;
  float m_obj_height = 0;
  size_t m_level_cols = 0;
  size_t m_level_rows = 0;
  size_t m_level_num = 0;
  float m_win_width, m_win_height, m_info_height;
};