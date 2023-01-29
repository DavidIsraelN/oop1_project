#include "Objects/Object.h"

//-------------------------------------------------------------------
Object::Object(const sf::Texture& texture, const sf::Vector2f& position, float width, float height, float scale)
{
  m_sprite.setTexture(texture);
  m_sprite.setPosition(position);
  const auto rect = m_sprite.getLocalBounds();
  m_sprite.setScale(width / rect.width / scale, height / rect.height / scale);
  m_sprite.setOrigin(rect.width / 2, rect.height / 2);
}

//-------------------------------------------------------------------
void Object::moveObj(const sf::Vector2f& direction, float win_height, float win_width)
{
  auto movement = direction;
  if (m_sprite.getPosition().x + movement.x >= win_width)  movement.x = -win_width;
  else if (m_sprite.getPosition().x + movement.x <= 0.f)   movement.x = win_width;
  if (m_sprite.getPosition().y + movement.y >= win_height) movement.y = -win_height;
  else if (m_sprite.getPosition().y + movement.y <= 0.f)   movement.y = win_height;

  auto delta_x = m_sprite.getPosition().x + movement.x;
  auto delta_y = m_sprite.getPosition().y + movement.y;
  auto epsilon = 0.15f;
  auto obj_w = m_sprite.getGlobalBounds().width, obj_h = m_sprite.getGlobalBounds().height;

  while (delta_x >= obj_w) delta_x -= obj_w;
  if (delta_x >= obj_w / 2 - epsilon && delta_x <= obj_w / 2 + epsilon) delta_x = obj_w / 2 - delta_x;
  else delta_x = 0;

  while (delta_y >= obj_h) delta_y -= obj_h;
  if (delta_y >= obj_h / 2 - epsilon && delta_y <= obj_h / 2 + epsilon) delta_y = obj_h / 2 - delta_y;
  else delta_y = 0;

  m_sprite.move(movement);
  m_sprite.move(sf::Vector2f(delta_x, delta_y));
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
bool Object::collidesWith(Object& other_obj) const
{
  return m_sprite.getGlobalBounds().intersects(other_obj.m_sprite.getGlobalBounds());
}
