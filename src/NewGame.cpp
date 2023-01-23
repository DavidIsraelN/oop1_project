#include "Buttons/NewGame.h"
#include "Buttons/ChooseLevel.h"
#include "Buttons/Back.h"

//-------------------------------------------------------------------
NewGame::NewGame(float width, float height) :
    Button("New Game", { width / 2 , height / 2.7f }, height / 30, SoftYellow),
    m_levels_rect({ width, height }), m_window_width(width), m_window_height(height)
{
  bulidLevelsTxt();
  m_levels.push_back(std::make_unique<Back>(sf::Vector2f({ width - width / 16 , height / 25 }), height / 45));
  m_levels.push_back(std::make_unique<ChooseLevel>(sf::Vector2f({ width / 2 , height / 2.7f }), height / 30, 1));
  m_levels.push_back(std::make_unique<ChooseLevel>(sf::Vector2f({ width / 2 , height / 2    }), height / 30, 2));
  m_levels.push_back(std::make_unique<ChooseLevel>(sf::Vector2f({ width / 2 , height / 1.6f }), height / 30, 3));
}

//-------------------------------------------------------------------
void NewGame::bulidLevelsTxt()
{
  m_levels_txt = sf::Text("Choose Level", ResourceManager::Resource().getFont(), m_window_height / 20);
  m_levels_txt.setPosition({ m_window_width / 2, m_window_height / 5 });
  m_levels_txt.setOrigin(m_levels_txt.getLocalBounds().width / 2, m_levels_txt.getLocalBounds().height / 2);
  m_levels_txt.setFillColor(sf::Color::White);
  m_levels_txt.setStyle(sf::Text::Underlined);
  m_levels_rect.setFillColor(SemiSoftYellow);
}

//-------------------------------------------------------------------
bool NewGame::action(sf::RenderWindow& window, LevelManager& level_m)
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

      case sf::Event::KeyPressed:
        switch (event.key.code) {
        case sf::Keyboard::Escape:
        case sf::Keyboard::B:      return false;
        case sf::Keyboard::Num1:   return m_levels[1]->action(window, level_m);
        case sf::Keyboard::Num2:   return m_levels[2]->action(window, level_m);
        case sf::Keyboard::Num3:   return m_levels[3]->action(window, level_m);
        }

      case sf::Event::MouseButtonReleased:
        auto loc = window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
        for (auto i = size_t(0); i < m_levels.size(); ++i)
          if (m_levels[i]->clickMe(loc))
            return m_levels[i]->action(window, level_m);
      }
  }
}

//-------------------------------------------------------------------
void NewGame::drawLevels(sf::RenderWindow& window) const
{
  window.clear(DeepRed);
  window.draw(m_levels_rect);
  window.draw(m_levels_txt);
  for (auto i = size_t(0); i < m_levels.size(); ++i)
    m_levels[i]->draw(window);
  window.display();
}
