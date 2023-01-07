#pragma once
#include "Button.h"
#include <vector>
#include <string>

class ChooseLevel : public Button
{
public:
	ChooseLevel(sf::Font&, const sf::Vector2f&, size_t, char);
	void action(sf::RenderWindow&) override;

private:
	size_t m_level_num;

};
