#include "Objects/Pacman.h"
#include "Level.h"

Pacman::Pacman(const sf::Texture& texture, const sf::Vector2f& position, float width, float height)
	: MovingObj(texture, position, width, height) { }

void Pacman::setDirection(sf::Keyboard::Key key)
{
	switch (key) {
	case sf::Keyboard::Key::Right:   m_new_direction = sf::Vector2f ( 1, 0);   return;
	case sf::Keyboard::Key::Left:    m_new_direction = sf::Vector2f (-1, 0);   return;
	case sf::Keyboard::Key::Up:      m_new_direction = sf::Vector2f ( 0,-1);   return;
	case sf::Keyboard::Key::Down:    m_new_direction = sf::Vector2f ( 0, 1);   return;
	}
}

void Pacman::move(sf::Time deltaTime, float win_height, float win_width, const Level& level)
{
  if (directionLegal(m_new_direction * speedPerSecond * deltaTime.asSeconds(), win_height, win_width, level))
    m_cur_direction = m_new_direction;

  else 
    directionLegal(m_cur_direction * speedPerSecond * deltaTime.asSeconds(), win_height, win_width, level);
  
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

bool Pacman::directionLegal(const sf::Vector2f& direction, float win_height, float win_width, const Level& level)
{
  moveObj(direction, win_height, win_width);
  if (level.collideWithWall(*this))
  {
    moveObj(-direction, win_height, win_width);
    return false;
  }
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
