#include "Objects/Object.h"

//-------------------------------------------------------------------
//Object::Object() { }
//
////-------------------------------------------------------------------
Object::Object(const sf::Texture& texture, const sf::Vector2f& position, float width, float height, float scale)
{
  m_sprite.setTexture(texture);
  m_sprite.setPosition(position);
  const auto rect = m_sprite.getLocalBounds();
  m_sprite.setScale(width / rect.width / scale, height / rect.height / scale);
  m_sprite.setOrigin(rect.width / 2, rect.height / 2);
}

//-------------------------------------------------------------------
sf::Vector2f Object::getPosition() const
{
  return m_sprite.getPosition();
}

//-------------------------------------------------------------------
sf::FloatRect Object::getGlobalBounds() const
{
  return m_sprite.getGlobalBounds();
}

//-------------------------------------------------------------------
void Object::moveObj(const sf::Vector2f& direction, float win_height, float win_width, float obj_h, float obj_w)
{
  auto movment = direction;
  if (m_sprite.getPosition().x + movment.x >= win_width)   movment.x = -win_width;
  else if (m_sprite.getPosition().x + movment.x <= 0.f)    movment.x = win_width;
  if (m_sprite.getPosition().y + movment.y >= win_height)  movment.y = -win_height;
  else if (m_sprite.getPosition().y + movment.y <= 0.f)    movment.y = win_height;
  m_sprite.move(movment);
  //auto move_x = m_sprite.getPosition().x;
  //while (move_x >= obj_w)
  //  move_x -= obj_w;
  ////if (direction.y > 0 ? 90 : direction.y == -1 ? 270 : m_cur_direction.x == -1 ? 180 : 0)
  //  if (move_x > 1)
  //    move_x = 0;
  //  else if (direction.x < 0)
  //    move_x *= (-1);

  //auto move_y = m_sprite.getPosition().y;
  //while (move_y >= obj_h)
  //  move_y -= obj_h;
  //if (move_y > 1)
  //  move_y = 0;
  //else if (direction.y < 0)
  //  move_y *= (-1);
  //m_sprite.move({ move_x, move_y });
}

//-------------------------------------------------------------------
void Object::rotateObj(float angle)
{
  m_sprite.setRotation(angle);
}

//-------------------------------------------------------------------
void Object::draw(sf::RenderWindow& window) const
{
  window.draw(m_sprite);
}

//-------------------------------------------------------------------
bool Object::collidesWith(const Object& other_obj) const
{
  return m_sprite.getGlobalBounds().intersects(other_obj.m_sprite.getGlobalBounds());
}
