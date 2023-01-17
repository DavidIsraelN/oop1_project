#include "Buttons/NewGame.h"
#include "Buttons/ChooseLevel.h"
#include "Buttons/Back.h"
#include "Colors.h"

NewGame::NewGame(float width, float height) :
    Button("New Game", { width / 2 , height / 2.7f }, height / 30, SoftYellow),
    m_levels_rect({ width, height }), m_window_width(width), m_window_height(height)
{
  bulidLevelsTxt();
  m_levels.push_back(std::make_unique<Back>(sf::Vector2f({ width - 50 , 30 }), height / 45));
  m_levels.push_back(std::make_unique<ChooseLevel>(sf::Vector2f({ width / 2 , height / 2.7f }), height / 30, '1'));
  m_levels.push_back(std::make_unique<ChooseLevel>(sf::Vector2f({ width / 2 , height / 2    }), height / 30, '2'));
  m_levels.push_back(std::make_unique<ChooseLevel>(sf::Vector2f({ width / 2 , height / 1.6f }), height / 30, '3'));
}

void NewGame::bulidLevelsTxt()
{
  m_levels_txt = sf::Text("Choose Level", *ResourceManage::Resource()->getFont(), m_window_height / 20);
  m_levels_txt.setPosition({ m_window_width / 2, m_window_height / 5 });
  m_levels_txt.setOrigin(m_levels_txt.getLocalBounds().width / 2, m_levels_txt.getLocalBounds().height / 2);
  m_levels_txt.setFillColor(sf::Color::White);
  m_levels_txt.setStyle(sf::Text::Underlined);
  m_levels_rect.setFillColor(SemiSoftYellow);
}

bool NewGame::action(sf::RenderWindow& window, Controller& c)
{
  drawLevels(window);
  while (window.isOpen())
  {
    if (auto event = sf::Event{}; window.waitEvent(event))
      switch (event.type)
      {
      case sf::Event::Closed:
        window.close();
        break;

      case sf::Event::MouseButtonReleased:
        auto loc = window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
        for (auto i = size_t(0); i < m_levels.size(); ++i)
          if (m_levels[i]->clickMe(loc))
            return m_levels[i]->action(window, c);
      }
  }
}

void NewGame::drawLevels(sf::RenderWindow& window) const
{
  window.clear(DeepRed);
  window.draw(m_levels_rect);
  window.draw(m_levels_txt);
  for (auto i = size_t(0); i < m_levels.size(); ++i)
    m_levels[i]->draw(window);
  window.display();
}

//
//bool NewGame::handleClick(const sf::Vector2f& loc, sf::RenderWindow& window, Controller& c) const
//{
//  for (auto i = size_t(0); i < m_levels.size(); ++i)
//    if (m_levels[i]->clickMe(loc))
//      return m_levels[i]->action(window, c);
//  return false;
//}