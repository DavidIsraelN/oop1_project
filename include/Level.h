#pragma once
#include "Objects/Erasable.h"
#include "Objects/MovingObj.h"
#include "Objects/Wall.h"
#include "Objects/Pacman.h"
#include "LevelReader.h"
#include "Timer.h"
#include <fstream>
#include <memory>
#include <vector>


/* 
 * This class is responsible for the current level, displaying the level,
 * checking for collisions and responding, deleting eaten objects, etc..
 */

class Gift;

class Level
{
public:
  Level(float, float);
  void setCurrentLevel(size_t);
  void resetLevel();
  void draw(sf::RenderWindow&) const;
  bool isOver() const;
  void setDirection(sf::Keyboard::Key) const;
  void moveObjects(const sf::Time&) const;
  bool collideWithWall(MovingObj&) const;
  bool collideWithDoor(MovingObj&) const;
  void handleCollision(Timer&) const;
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
  void checkGiftCollision(Timer&) const;
  void freeseDemons() const;
  std::unique_ptr<Gift> chooseRandomGift(const sf::Vector2f&) const;

  std::unique_ptr<LevelReader> m_current_board;
  std::vector<std::unique_ptr<MovingObj>> m_demons;
  std::unique_ptr<Pacman> m_pacman;
  std::vector<std::vector<std::unique_ptr<Erasable>>> m_erasable_obj;
  std::vector<std::unique_ptr<Wall>> m_walls;
  float m_win_width, m_win_height;
  float m_obj_width = 0, m_obj_height = 0;
  size_t m_level_num = 0;
};
