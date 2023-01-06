#pragma once
#include "Button.h"
#include <vector>

class ChooseLevel : public Button
{
public:
	ChooseLevel(sf::Font&, float, float, char);
	void action(sf::RenderWindow&) override;

private:
	size_t m_level_num;
	//std::vector<Button*> m_levels;
};
