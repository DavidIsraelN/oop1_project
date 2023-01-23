#include "Movement.h"
#include "Objects/MovingObj.h"
#include "Level.h"


void PacmanMovement::action(const sf::Time& delta_time, const Level& level, MovingObj& obj)
{
  if (directionLegal(obj.m_new_direction * (obj_h / 2), win_height, win_width, level, obj_h, obj_w))
  {
    moveObj(m_new_direction * speedPerSecond * deltaTime.asSeconds(), win_height, win_width, obj_h, obj_w);
    m_cur_direction = m_new_direction;
  }

  else if(directionLegal(m_cur_direction * speedPerSecond * deltaTime.asSeconds(), win_height, win_width, level, obj_h, obj_w))
    moveObj(m_cur_direction * speedPerSecond * deltaTime.asSeconds(), win_height, win_width, obj_h, obj_w);


  moveObj(direction, win_height, win_width, obj_h, obj_w);
  if (level.collideWithWallOrDoor(*this))
  {
    moveObj(-direction, win_height, win_width, obj_h, obj_w);
    return false;
  }
  moveObj(-direction, win_height, win_width, obj_h, obj_w);
}

void PacmanMovement::directionLegal(const sf::Time& delta_time, const Level& level, MovingObj& obj)
{

}

void sPacmanMovement::action(const sf::Time& delta_time, const Level& level, MovingObj& obj)
{

}

void randomMovement::action(const sf::Time& delta_time, const Level& level, MovingObj& obj)
{

}

void smartMovement::action(const sf::Time& delta_time, const Level& level, MovingObj& obj)
{

}
