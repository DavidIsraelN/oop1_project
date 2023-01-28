#include "Menu.h"
#include "Buttons/NewGame.h"
#include "Buttons/Help.h"
#include "Buttons/ExitGame.h"
#include "Buttons/Mute.h"

//-------------------------------------------------------------------
Menu::Menu(float width, float height)
  : m_menu(sf::Text("MENU", ResourceManager::Resource().getFont(FontIndex::PACMAN_2) , height / 8)),
  m_back(std::make_unique<Back>(sf::Vector2f({ width - width / 13 , height / 25 }), height / 35))

{
  m_menu.setPosition({ width / 2, height / 6 });
  m_menu.setOrigin(m_menu.getLocalBounds().width / 2, m_menu.getLocalBounds().height / 2);
  m_menu.setFillColor(sf::Color::White);
  m_menu.setStyle(sf::Text::Underlined);

  m_buttons.push_back(std::make_unique<NewGame>(width, height));
  m_buttons.push_back(std::make_unique<Help>(width, height));
  m_buttons.push_back(std::make_unique<ExitGame>(sf::Vector2f(width / 2 , height / 1.3f), height / 15));
  m_buttons.push_back(std::make_unique<Mute>(sf::Vector2f(width / 13 , height / 25), height / 35));
}

//-------------------------------------------------------------------
bool Menu::run(sf::RenderWindow& window, LevelManager& level_m, bool back_button)
{
  m_back_button = back_button;
  while (window.isOpen())
  {
    window.clear(DeepRed); // chack semi..
    draw(window);
    window.display();

    if (auto event = sf::Event{}; window.waitEvent(event))
      switch (event.type)
      {
      case sf::Event::Closed:
        window.close();
        return false;

      case sf::Event::KeyPressed:
        if (handleKey(event.key.code, window, level_m))          return true;
        if (m_back_button && (event.key.code == sf::Keyboard::B
            || event.key.code == sf::Keyboard::Escape))          return false;

      case sf::Event::MouseButtonReleased:
        auto loc = window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
        if (handleClick(loc, window, level_m))  return true;
        if (m_back_button && back(loc))         return false;
      }
  }
}

//-------------------------------------------------------------------
void Menu::draw(sf::RenderWindow& window) const
{
  window.draw(m_menu);
  for (auto i = size_t(0); i < m_buttons.size(); ++i)
    m_buttons[i]->draw(window);

  if (m_back_button)
    m_back->draw(window);
}

//-------------------------------------------------------------------
bool Menu::handleClick(const sf::Vector2f& loc, sf::RenderWindow& window, LevelManager& level_m) const
{
  for (auto i = size_t(0); i < m_buttons.size(); ++i)
    if(m_buttons[i]->clickMe(loc))
      return m_buttons[i]->action(window, level_m);
  return false;
}

//-------------------------------------------------------------------
bool Menu::handleKey(sf::Keyboard::Key key_code, sf::RenderWindow& window, LevelManager& level_m) const
{
  switch (key_code)
  {
  case sf::Keyboard::N:
    return m_buttons[size_t(ButtonIdx::NEW_GAME)]->action(window, level_m);
  case sf::Keyboard::H:
    return m_buttons[size_t(ButtonIdx::HELP)]->action(window, level_m);
  case sf::Keyboard::E:
    return m_buttons[size_t(ButtonIdx::EXIT)]->action(window, level_m);
  case sf::Keyboard::M:
    return m_buttons[size_t(ButtonIdx::MUTE)]->action(window, level_m);
  }
  return false;
}

//-------------------------------------------------------------------
bool Menu::back(const sf::Vector2f& loc) const
{
  if (m_back->clickMe(loc))
    return true;
  return false;
}