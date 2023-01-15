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
void Object::moveObj(const sf::Vector2f& direction, float win_height, float win_width)
{
  auto movment = direction;
  if (m_sprite.getPosition().x + movment.x >= win_width)   movment.x = -win_width;
  else if (m_sprite.getPosition().x + movment.x <= 0.f)    movment.x = win_width;
  if (m_sprite.getPosition().y + movment.y >= win_height)  movment.y = -win_height;
  else if (m_sprite.getPosition().y + movment.y <= 0.f)    movment.y = win_height;
  m_sprite.move(movment);
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
