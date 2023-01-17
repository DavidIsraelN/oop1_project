#include "Objects/Pacman.h"
#include "Level.h"

Pacman::Pacman(const sf::Vector2f& position, float width, float height)
    : MovingObj(*ResourceManage::Resource()->getPacmanT(), position, width, height) { }

void Pacman::setDirection(sf::Keyboard::Key key)
{
  switch (key) {
  case sf::Keyboard::Key::Space:   m_new_direction = sf::Vector2f ( 0, 0);   return;
  case sf::Keyboard::Key::Right:   m_new_direction = sf::Vector2f ( 1, 0);   return;
  case sf::Keyboard::Key::Left:    m_new_direction = sf::Vector2f (-1, 0);   return;
  case sf::Keyboard::Key::Up:      m_new_direction = sf::Vector2f ( 0,-1);   return;
  case sf::Keyboard::Key::Down:    m_new_direction = sf::Vector2f ( 0, 1);   return;
  }
}

//void Pacman::move(sf::Time deltaTime, float win_height, float win_width, const Level& level)
void Pacman::move(sf::Time deltaTime, float obj_h, float obj_w, float cols, float rows, const Level& level)
{
  auto win_height = obj_h * rows, win_width = obj_w * cols;

  if (directionLegal(m_new_direction * speedPerSecond * deltaTime.asSeconds(), win_height, win_width, level, obj_h, obj_w))
    m_cur_direction = m_new_direction;

  else
    directionLegal(m_cur_direction * speedPerSecond * deltaTime.asSeconds(), win_height, win_width, level, obj_h, obj_w);

  rotateObj(m_cur_direction.y == 1 ? 90: m_cur_direction.y == -1 ? 270 : m_cur_direction.x == -1 ? 180 : 0);


  //else if (!directionLegal(m_cur_direction * speedPerSecond * deltaTime.asSeconds(), win_height, win_width, level))
  //  m_cur_direction = { 0, 0 };


  //if (directionLegal(getPosition() + m_new_direction * speedPerSecond * deltaTime.asSeconds(), level))
  //  m_cur_direction = m_new_direction;

  //else if (!directionLegal(getPosition() + m_cur_direction * speedPerSecond * deltaTime.asSeconds(), level))
  //  m_cur_direction = { 0, 0 };

  //auto direction = (m_cur_direction * speedPerSecond * deltaTime.asSeconds());

  //if (getPosition().x + direction.x >= win_width)   direction.x = - win_width;
  //else if (getPosition().x + direction.x <= 0.f)    direction.x = win_width;
  //if (getPosition().y + direction.y >= win_height)  direction.y = -win_height;
  //else if (getPosition().y + direction.y <= 0.f)    direction.y = win_height;

  //moveObj(direction, win_height, win_width);
  //rotateObj(m_cur_direction.y == 1 ? 90: m_cur_direction.y == -1 ? 270 : m_cur_direction.x == -1 ? 180 : 0);
}

bool Pacman::directionLegal(const sf::Vector2f& direction, float win_height, float win_width, const Level& level, float obj_h, float obj_w)
{
  moveObj(direction, win_height, win_width, obj_h, obj_w);
  if (level.collideWithWall(*this))
  {
    moveObj(-direction, win_height, win_width, obj_h, obj_w);
    return false;
  }

  //auto delta_x = getPosition().x;
  //auto delta_y = getPosition().y;
  //auto epsilon = float(10);

  //while (delta_x >= obj_w)
  //  delta_x -= obj_w;

  //if (delta_x >= obj_w / 2 - epsilon && delta_x <= obj_w / 2 + epsilon) delta_x = obj_w / 2 - delta_x;

  //while (delta_y >= obj_h)
  //  delta_y -= obj_h;

  //if (delta_y >= obj_h / 2 - epsilon && delta_y <= obj_h / 2 + epsilon) delta_y = obj_h / 2 - delta_y;

  //moveObj({ delta_x, delta_y }, win_height, win_width, obj_h, obj_w);


  //moveObj(-direction, win_height, win_width, obj_h, obj_w);
  //moveObj(direction, win_height, win_width, obj_h, obj_w);

  return true;
  //if (type == DEMON|| type == DOOR)
  //  return false;
  //return true;
}



//
//void Pacman::move(sf::Time deltaTime)
//{
//  moveObj(m_cur_direction * speedPerSecond * deltaTime.asSeconds());
//}
