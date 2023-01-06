#include "Buttons/ChooseLevel.h"
#include <iostream>
#include <string>
#include "Colors.h"

ChooseLevel::ChooseLevel(sf::Font& font, float width, float height, char level_num)
	: Button("Level " + level_num, font, { width / 2 , height / 2.7f }, height / 30, SoftYellow)
	/*m_level_num(std::stoi(level_num))*/ { }
