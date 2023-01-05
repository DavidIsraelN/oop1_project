#include "Objects/Pacman.h"

Pacman::Pacman(const sf::Texture& texture, const sf::Vector2f& position)
{
    m_sprite.setTexture(texture);
    m_sprite.setPosition(position);
    const auto rect = m_sprite.getLocalBounds();
    m_sprite.setScale(PIXELS / rect.width, PIXELS / rect.height);
    m_sprite.setOrigin(rect.width / 2, rect.height / 2);
}
