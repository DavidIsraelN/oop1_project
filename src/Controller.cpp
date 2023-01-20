#include "Controller.h"
#include <SFML/Audio.hpp>
#include "ResourceManager.h"
#include "Sound.h"

//-------------------------------------------------------------------
Controller::Controller()
  : m_window(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT + INFO_HEIGHT), "PACMAN"),
  m_menu(WIN_WIDTH, WIN_HEIGHT + INFO_HEIGHT), m_levels(WIN_WIDTH, WIN_HEIGHT, INFO_HEIGHT)
{
  auto icon = ResourceManager::Resource()->getIcon();
  m_window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

//-------------------------------------------------------------------
void Controller::run()
{
  Sound::Sounds()->Play(SoundIndex::START);
  if (m_menu.run(m_window, m_levels, false))
    while (m_window.isOpen())
      runGame();
}

//-------------------------------------------------------------------
void Controller::runGame()
{
  while (m_window.isOpen()) {
    if (m_levels.run(m_window))
      if (m_menu.run(m_window, m_levels, true))
        return;
  }
}







  //m_game_start.play();
  //	std::cout << m_level.getRows() << std::endl;
  //	std::cout << m_level.getCols() << std::endl;

  //while (m_window.isOpen()) {
  //	m_window.clear(DarkBlue);
  //	m_level.draw(m_window);
  //	m_window.display();

  //	auto event = sf::Event{};
  //	while (m_window.pollEvent(event))
  //		switch (event.type)
  //		{
  //		case sf::Event::Closed:
  //			m_window.close();
  //			break;

  //		case sf::Event::KeyPressed:
  //			if (event.key.code == sf::Keyboard::Escape)
  //				if (runMenu())
  //					return;
  //			sf::Clock c;
  //			//m_player.setDirection(event.key.code);
  //			const auto deltaTime = c.restart();
  //			//m_player.move(deltaTime);
  //			//m_monster.move(deltaTime);
  //			break;


  //		}
  //}


////-------------------------------------------------------------------
//bool Controller::runMenu(bool back)
//{
//  while (m_window.isOpen())
//  {
//    //return m_menu.run(m_window, back);
//    m_window.clear(MAIN_COLOR); // chack semi..
//    m_menu.draw(m_window, back);
//    m_window.display();
//
//    if (auto event = sf::Event{}; m_window.waitEvent(event))
//      switch (event.type)
//      {
//      case sf::Event::Closed:
//        m_window.close();
//        return false;
//
//      case sf::Event::MouseButtonReleased:
//      {
//        auto loc = m_window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
//        if (m_menu.handleClick(loc, m_window, m_levels))
//          return true;
//        if (back && m_menu.back(loc)) return false;
//      }
//
//      case sf::Event::KeyReleased:
//      case sf::Event::KeyPressed:
//      {
//        if (event.key.code == sf::Keyboard::BackSpace)
//        {
//        }
//      }
//      }
//  }
//}
// 
////-------------------------------------------------------------------
//void Controller::chooseNewLevel(size_t level_num)
//{
//  m_level.setCurrentLevel(level_num);
//}
