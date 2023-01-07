#pragma once
#include <SFML/Graphics.hpp>

class Button
{
public:
	Button(const std::string&, const sf::Font&, const sf::Vector2f&, size_t, sf::Color);
	//~Button();
	void draw(sf::RenderWindow&) const;
	bool clickMe(const sf::Vector2f&) const;
	virtual void action(sf::RenderWindow&) = 0;

private:
	sf::Text m_text;
	//sf::RectangleShape m_rectangle;
	//sf::Sprite m_sprite;
};