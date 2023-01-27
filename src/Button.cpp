#include "Buttons/Button.h"
#include "ResourceManager.h"

//-------------------------------------------------------------------
Button::Button(const std::string& text, const sf::Vector2f& position, size_t size, sf::Color color)
{
  m_text.setString(text);
  m_text.setFont(ResourceManager::Resource().getFont(FontIndex::PACMAN));
  m_text.setPosition(position);
  m_text.setCharacterSize(size);
  m_text.setFillColor(color);
  const auto rect = m_text.getLocalBounds();
  m_text.setOrigin(rect.width / 2, rect.height / 2);
//  m_text.setStyle(sf::Text::Underlined);

}

//-------------------------------------------------------------------
bool Button::clickMe(const sf::Vector2f& loc) const
{
  return m_text.getGlobalBounds().contains(loc);
}

//-------------------------------------------------------------------
void Button::draw(sf::RenderWindow& window) const
{
  //window.draw(m_rectangle);
  window.draw(m_text);
}
