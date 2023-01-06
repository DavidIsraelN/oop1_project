#include "Buttons/Button.h"

Button::Button(const std::string& text, const sf::Font& font, const sf::Vector2f& position, size_t size, sf::Color color)
{
	m_text.setString(text);
	m_text.setFont(font);
	m_text.setPosition(position);
	m_text.setCharacterSize(size);
	m_text.setFillColor(color);
	const auto rect = m_text.getLocalBounds();
	//m_text.setScale(width / rect.width / scale, height / rect.height / scale);
	m_text.setOrigin(rect.width / 2, rect.height / 2);
}

bool Button::clickMe(const sf::Vector2f& loc) const
{
	return m_text.getGlobalBounds().contains(loc);
}

void Button::draw(sf::RenderWindow& window) const
{
	//window.draw(m_rectangle);
	window.draw(m_text);
}