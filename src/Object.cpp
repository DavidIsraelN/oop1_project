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


//-------------------------------------------------------------------


//-------------------------------------------------------------------
void Object::draw(sf::RenderWindow& window) const
{
  window.draw(m_sprite);
}
