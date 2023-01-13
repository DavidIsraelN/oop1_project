#include "Menu.h"
#include "Buttons/NewGame.h"
#include "Buttons/Help.h"
#include "Buttons/ExitGame.h"
#include "Buttons/Mute.h"

Menu::Menu(sf::Font& font, std::ifstream* help_file, float width, float height)
	: m_menu(sf::Text("MENU", font , height / 20))
{
	m_menu.setPosition({ width / 2, height / 5 });
	m_menu.setOrigin(m_menu.getLocalBounds().width / 2, m_menu.getLocalBounds().height / 2);
	m_menu.setFillColor(sf::Color::White);
	m_menu.setStyle(sf::Text::Underlined);
	
	m_buttons.push_back(std::make_unique<NewGame>(font, width, height));
	m_buttons.push_back(std::make_unique<Help>(font, help_file, width, height));
	m_buttons.push_back(std::make_unique<ExitGame>(font, width, height));
	m_buttons.push_back(std::make_unique<Mute>(font, sf::Vector2f({ 50 , 30 }), height / 45));
}

void Menu::draw(sf::RenderWindow& window) const
{
	window.draw(m_menu);
	for (auto i = size_t(0); i < m_buttons.size(); ++i)
		m_buttons[i]->draw(window);
}

bool Menu::handleClick(const sf::Vector2f& loc, sf::RenderWindow& window, Controller& c) const
{
	for (auto i = size_t(0); i < m_buttons.size(); ++i)
		if(m_buttons[i]->clickMe(loc))
		  return m_buttons[i]->action(window, c);
    return false;
}
