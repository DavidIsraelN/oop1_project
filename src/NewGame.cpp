#include "Buttons/NewGame.h"
#include "Buttons/ChooseLevel.h"
#include "Colors.h"

NewGame::NewGame(sf::Font& font, float width, float height)
  : Button("New Game", font, { width / 2 , height / 2.7f }, height / 30, SoftYellow)
{
  m_levels.push_back(new ChooseLevel(font, width, height, 1));
  m_levels.push_back(new ChooseLevel(font, width, height, 2));
  m_levels.push_back(new ChooseLevel(font, width, height, 3));
}

void NewGame::action(sf::RenderWindow& window)
{
  selectLevel(window);
}

void NewGame::selectLevel(sf::RenderWindow& window) const
{
  drawLevels(window);
}

void NewGame::drawLevels(sf::RenderWindow& window) const
{
  for (auto i = size_t(0); i < m_levels.size(); ++i)
    m_levels[i]->draw(window);
}