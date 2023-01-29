#include "Controller.h"
//#include <SFML/Audio.hpp>
#include "ResourceManager.h"
#include "Sound.h"

//-------------------------------------------------------------------
Controller::Controller()
  : m_window(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT + INFO_HEIGHT), "PACMAN"),
   m_levels(WIN_WIDTH, WIN_HEIGHT, INFO_HEIGHT), m_menu(WIN_WIDTH, WIN_HEIGHT + INFO_HEIGHT)
{
  auto icon = ResourceManager::Resource().getIcon();
  m_window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

//-------------------------------------------------------------------
void Controller::run()
{
  Sound::Sounds().Play(SoundIndex::START);
  if (m_menu.run(m_window, m_levels, false))
    runGame();
}

//-------------------------------------------------------------------
void Controller::runGame()
{
  while (m_window.isOpen())
    if (m_levels.run(m_window))
      (m_menu.run(m_window, m_levels, true));
}
