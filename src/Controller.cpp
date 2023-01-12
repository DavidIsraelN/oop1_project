#include "Controller.h"
#include <SFML/Audio.hpp>

Controller::Controller() : m_font(m_resources.getFont()), m_reka(*m_resources.getReka()),
  m_window(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT + INFO_HEIGHT), "Pacman Game"),
	m_menu(m_font, m_resources.getHelpFile(), WIN_WIDTH, WIN_HEIGHT + INFO_HEIGHT) { }

void Controller::run()
{
	m_reka.play();
	if (runMenu())
		while (m_window.isOpen())
			runGame();
}

bool Controller::runMenu()
{
	while (m_window.isOpen())
	{
		m_window.clear(DarkBlue);
		m_menu.draw(m_window);
		m_window.display();

		if (auto event = sf::Event{}; m_window.waitEvent(event))
			switch (event.type)
			{
			case sf::Event::Closed:
				m_window.close();
				return false;

			case sf::Event::MouseButtonReleased:
			{
				auto loc = m_window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
				if (m_menu.handleClick(loc, m_window, *this))
					return true;
			}

			case sf::Event::KeyReleased:
			case sf::Event::KeyPressed:
			{
				if (event.key.code == sf::Keyboard::BackSpace)
				{
				}
			}
			}

	}
}

void Controller::runGame()
{
	m_level.buildLevel(/*m_my_board,*/ m_resources, WIN_WIDTH, WIN_HEIGHT);
	m_reka.play();
	//	std::cout << m_level.getRows() << std::endl;
	//	std::cout << m_level.getCols() << std::endl;

	while (m_window.isOpen()) {
		m_window.clear(DarkBlue);
		m_level.draw(m_window);
		m_window.display();

		auto event = sf::Event{};
		while (m_window.pollEvent(event))
			switch (event.type)
			{
			case sf::Event::Closed:
				m_window.close();
				break;

			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape)
					if (runMenu())
						return;
				sf::Clock c;
				//m_player.setDirection(event.key.code);
				const auto deltaTime = c.restart();
				//m_player.move(deltaTime);
				//m_monster.move(deltaTime);
				break;


			}
	}
}

void Controller::chooseNewLevel(size_t level_num)
{
	m_level.setCurrentLevel(m_resources ,level_num);
}

void Controller::play() const
{

}