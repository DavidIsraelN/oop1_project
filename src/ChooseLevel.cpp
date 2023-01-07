#include "Buttons/ChooseLevel.h"
#include "Colors.h"
#include <iostream>

ChooseLevel::ChooseLevel(sf::Font& font, const sf::Vector2f& position, size_t size, char level_num)
	: Button(std::string("Level ") + level_num, font, position, size, SoftYellow),
	m_level_num(level_num - '0') { }

void ChooseLevel::action(sf::RenderWindow& window)
{

}