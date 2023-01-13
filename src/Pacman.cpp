#include "Objects/Pacman.h"

Pacman::Pacman(const sf::Texture& texture, const sf::Vector2f& position, float width, float height)
	: MovingObj(texture, position, width, height) { }

void Pacman::setDirection(sf::Keyboard::Key key)
{
	switch (key) {
	case sf::Keyboard::Key::Right:   m_direction = sf::Vector2f ( 1, 0);  break;
	case sf::Keyboard::Key::Left:    m_direction = sf::Vector2f (-1, 0);  break;
	case sf::Keyboard::Key::Up:      m_direction = sf::Vector2f ( 0,-1);  break;
	case sf::Keyboard::Key::Down:    m_direction = sf::Vector2f ( 0, 1);  break;
	}
}

void Pacman::move(sf::Time deltaTime, float win_height, float win_width)
{
  auto direction = (m_direction * speedPerSecond * deltaTime.asSeconds());

  if (getPosition().x + direction.x >= win_width)   direction.x = - win_width;
  else if (getPosition().x + direction.x <= 0.f)    direction.x = win_width;
  if (getPosition().y + direction.y >= win_height)  direction.y = -win_height;
  else if (getPosition().y + direction.y <= 0.f)    direction.y = win_height;

  moveObj(direction);
  rotateObj(m_direction.y == 1 ? 90: m_direction.y == -1 ? 270 : m_direction.x == -1 ? 180 : 0);
}




void Pacman::move(sf::Time deltaTime)
{
  moveObj(m_direction * speedPerSecond * deltaTime.asSeconds());
}

  //case KB_Up:
  //  new_loc.row = (new_loc.row + row - 1) % row;
  //  break;

  //case KB_Down:
  //  ++new_loc.row %= row;
  //  break;

  //case KB_Left:
  //  new_loc.col = (new_loc.col + col - 1) % col;
  //  break;

  //case KB_Right:
  //  ++new_loc.col %= col;
  //  break;
//bool Pacman::directionLegal(Controller & c, Location & new_loc) const
//{
//	setDirection(c.getLevelRow(), c.getLevelCol(), new_loc);
//	return isLegal(c, new_loc);
//}
//
///*---------------------------------------------------------
// * returns whether the new_loc is legal place for pacman on current level or not
// */
//bool Pacman::isLegal(Controller& c, const Location& new_loc) const
//{
//	auto type = c.getTypeInLoc(new_loc);
//	if (type == '#' || type == 'D')
//		return false;
//
//	return true;
//}