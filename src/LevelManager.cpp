#include "LevelManager.h"
#include <SFML/Graphics.hpp>
#include "Colors.h"

//-------------------------------------------------------------------
LevelManager::LevelManager(const float w_width, const float w_height, const float inf_h)
    : m_win_width(w_width), m_win_height(w_height), m_game_over(w_width, w_height),
      m_current_level(w_width, w_height), m_info(w_width, w_height, inf_h) { }

//-------------------------------------------------------------------
bool LevelManager::run(sf::RenderWindow& window)
{
  sf::Clock clock;

  while (window.isOpen())
  {
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
        if (event.key.code == sf::Keyboard::Escape) {
          Sound::Sounds().Stop(SoundIndex::S_PACMAN);
          return true; }
        else m_current_level.setDirection(event.key.code);
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
  m_current_level.handleCollision(m_timer);
  m_current_level.erase();
  m_timer.updateTimer(deltaTime);
  m_info.setInfo(m_current_level, m_timer);
}

//-------------------------------------------------------------------
void LevelManager::setLevel(sf::RenderWindow& window)
{
  if (m_current_level.isOver())
    nextLevel(window);

  else if (m_timer.isOver())
  {
    Sound::Sounds().Play(SoundIndex::DEATH);
    resetLevel();
    m_timer.setStart(m_current_level.getLevelNum());
  }
  else if (m_current_level.getPacmanLife() <= 0)
    gameOver(window);
}

//-------------------------------------------------------------------
void LevelManager::nextLevel(sf::RenderWindow& window)
{
  m_current_level.addFinalScore();
  if (m_current_level.getLevelNum() < LEVELS)
    chooseNewLevel(m_current_level.getLevelNum() + 1,
                   m_current_level.getPacmanLife(),
                   m_current_level.getPacmanScore());
  else
    gameOver(window);
}

//-------------------------------------------------------------------
void LevelManager::resetLevel()
{
  auto life = m_current_level.getPacmanLife() - 1;
  auto score = m_current_level.getPacmanScore();
  m_current_level.resetLevel();
  m_current_level.setPacmanLife(life);
  m_current_level.setPacmanScore(score);
}

//-------------------------------------------------------------------
void LevelManager::gameOver(sf::RenderWindow& window)
{
  Sound::Sounds().Stop(SoundIndex::S_PACMAN);
  m_game_over.setScore(m_current_level.getPacmanScore());
  m_game_over.draw(window);
}

//-------------------------------------------------------------------
void LevelManager::chooseNewLevel(size_t level_num, size_t life, size_t score)
{
  m_current_level.setCurrentLevel(level_num);
  m_current_level.setPacmanLife(life);
  m_current_level.setPacmanScore(score);
  m_timer.setStart(level_num);
  Sound::Sounds().Play(SoundIndex::LEVEL_RUN);
}
