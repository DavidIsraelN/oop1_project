#include "Menu.h"
#include "Buttons/NewGame.h"
#include "Buttons/Help.h"
#include "Buttons/ExitGame.h"

Menu::Menu(sf::Font& font, float width, float height)
{
	m_buttons.push_back(new NewGame(font, width, height));
	m_buttons.push_back(new Help(font, width, height));
	m_buttons.push_back(new ExitGame(font, width, height));
}

void Menu::draw(sf::RenderWindow& window) const
{
	for (auto i = size_t(0); i < m_buttons.size(); ++i)
		m_buttons[i]->draw(window);
}

void Menu::handlClick(const sf::Vector2f& loc, sf::RenderWindow& window) const
{
	for (auto i = size_t(0); i < m_buttons.size(); ++i)
		if(m_buttons[i]->clickMe(loc))
		  m_buttons[i]->action(window);
}
