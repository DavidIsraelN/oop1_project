#include "LevelManager.h"
#include <SFML/Graphics.hpp>
#include "Colors.h"

//-------------------------------------------------------------------
LevelManager::LevelManager(const float w_width, const float w_height, const float inf_h)
  : m_win_width(w_width), m_win_height(w_height), m_info_height(inf_h),
  m_current_level(w_width, w_height), m_info(w_width, w_height, inf_h),
      m_game_over("GAME OVER", ResourceManager::Resource().getFont(), w_height / 9),
      m_game_over_score("", ResourceManager::Resource().getFont(), w_height / 15) { }

//-------------------------------------------------------------------
bool LevelManager::run(sf::RenderWindow& window)
{
  sf::Clock clock;

  while (window.isOpen()) 
  {
    //window.setFramerateLimit(60);
    window.clear(DeepRed);
    m_current_level.draw(window);
    m_info.draw(window);
    window.display();

    for (auto event = sf::Event{}; window.pollEvent(event); )
      switch (event.type)
      {
      case sf::Event::Closed:
        window.close();
        return false;

      case sf::Event::KeyPressed:
        if (event.key.code == sf::Keyboard::Escape) return true;
        m_current_level.setDirection(event.key.code);
        break;
      }

    levelAction(clock.restart());
    setLevel(window);
  }
}

//-------------------------------------------------------------------
void LevelManager::levelAction(const sf::Time& deltaTime)
{
  m_current_level.moveObjects(deltaTime);
  m_current_level.handleCollision();
  m_timer.updateTimer(deltaTime);
  m_current_level.erase();
  m_info.setInfo(m_current_level, m_timer);
}

//-------------------------------------------------------------------
void LevelManager::setLevel(sf::RenderWindow& window)
{
  if (m_current_level.isOver())
    nextLevel(window);

  else if (m_timer.isOver())
  {
    resetLevel(window);
    m_timer.setStart(m_current_level.getLevelNum());
  }
}

//-------------------------------------------------------------------
void LevelManager::nextLevel(sf::RenderWindow& window)
{
  if (m_current_level.getLevelNum() < LEVELS)
    chooseNewLevel(m_current_level.getLevelNum() + 1, m_current_level.getPacmanLife(), m_current_level.getPacmanScore());
  else
    gameOver(window);
}

//-------------------------------------------------------------------
void LevelManager::resetLevel(sf::RenderWindow& window)
{
  m_current_level.pacmanLifeReduction();
  if (m_current_level.getPacmanLife() == 0)
    gameOver(window);


}

//-------------------------------------------------------------------
void LevelManager::gameOver(sf::RenderWindow& window)
{
  buildGameOverScreen();
  while (window.isOpen())
  {
    window.clear(DeepRed);
    window.draw(m_game_over);
    window.draw(m_game_over_score);
    window.display();

    if (auto event = sf::Event{}; window.waitEvent(event))
      if (event.type == sf::Event::Closed)
        window.close();
  }
}

//-------------------------------------------------------------------
void LevelManager::chooseNewLevel(size_t level_num, size_t life, size_t score)
{
  m_current_level.setCurrentLevel(level_num);
  m_current_level.setPacmanLife(life);
  m_current_level.setPacmanScore(score);
  m_timer.setStart(level_num);
  Sound::Sounds().Play(SoundIndex::START);
}

//-------------------------------------------------------------------
void LevelManager::buildGameOverScreen()
{
  m_game_over.setFillColor(DeepRed);
  m_game_over.setOutlineThickness(6);
  m_game_over.setOutlineColor(sf::Color::White);
  m_game_over.setPosition(m_win_width / 2, m_win_height / 2.6);
  m_game_over.setLetterSpacing(2);
  m_game_over.setOrigin(m_game_over.getGlobalBounds().width / 2, m_game_over.getGlobalBounds().height / 2);

  m_game_over_score.setFillColor(sf::Color::White);
  m_game_over_score.setPosition(m_win_width / 2, m_win_height / 1.6);
  m_game_over_score.setString("Your Score Is: " + std::to_string(m_current_level.getPacmanScore()));
  m_game_over_score.setOrigin(m_game_over_score.getGlobalBounds().width / 2, m_game_over_score.getGlobalBounds().height / 2);
}