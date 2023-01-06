#include "Controller.h"

Controller::Controller(sf::Font& font) : m_window(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT + INFO_HEIGHT), "Pacman Game"),
                          m_font(font), m_menu(font, WIN_WIDTH, WIN_HEIGHT + INFO_HEIGHT)
{
  //m_font.loadFromFile("Arial.ttf");
  //m_menu = Menu(m_font, WIN_WIDTH, WIN_HEIGHT + INFO_HEIGHT);
}


void Controller::run()
{
  while (m_window.isOpen())
  {
    m_window.clear(DarkBlue);
    m_menu.draw(m_window);
    //m_level.draw(m_window);
    m_window.display();

    if (auto event = sf::Event{}; m_window.waitEvent(event))
      switch (event.type) 
      {
      case sf::Event::Closed:
        m_window.close();
        break;

      case sf::Event::MouseButtonReleased:
      {
        auto loc = m_window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
        m_menu.handlClick(loc, m_window);
        break;
      }

      case sf::Event::KeyReleased:
      {

      }}

  }
}

void Controller::run1() 
{
 

    m_level.buildLevel(m_my_board, WIN_WIDTH, WIN_HEIGHT);

    std::cout << m_level.getRows() << std::endl;
    std::cout << m_level.getCols() << std::endl;

    while (m_window.isOpen()) {
        m_window.clear(DarkBlue);
        //m_menu.draw(m_window);
        m_level.draw(m_window);
        m_window.display();

        auto event = sf::Event{};
        while(m_window.pollEvent(event))
            switch (event.type) {
                case sf::Event::Closed:
                    m_window.close();
            }
        
    }
}