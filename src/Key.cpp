#include "Objects/Key.h"

Key::Key(const sf::Texture& texture, const sf::Vector2f& position)
{
    m_sprite.setTexture(texture);
    m_sprite.setPosition(position);
    const auto rect = m_sprite.getLocalBounds();
    m_sprite.setScale(PIXELS / rect.width / 1.5, PIXELS / rect.height / 1.5);
    m_sprite.setOrigin(rect.width / 2, rect.height / 2);
}
