#include "InfoBar.h"
#include "Colors.h"
#include "ResourceManager.h"
#include "Level.h"

//-------------------------------------------------------------------
InfoBar::InfoBar(float w_width, float w_height, float inf_h)
    : m_timer("00:00", ResourceManager::Resource().getFont(FontIndex::PACMAN), inf_h / 1.2),
      m_level("LEVEL  ", ResourceManager::Resource().getFont(FontIndex::PACMAN), inf_h / 1.4),
      m_score("SCORE  ", ResourceManager::Resource().getFont(FontIndex::PACMAN), inf_h / 1.4)
{
  setLifeVector(w_width, w_height, inf_h);
  setInfoBar(w_width, w_height, inf_h);
}

//-------------------------------------------------------------------
void InfoBar::setLifeVector(float w_width, float w_height, float inf_h)
{
  for (auto i = size_t(0); i < 4; ++i)
  {
    m_pacman_icon.push_back(sf::Sprite(ResourceManager::Resource().getObjTexture(ObjIndex::PACMAN_OPEN)));
    m_pacman_icon[i].setScale(inf_h / m_pacman_icon[i].getGlobalBounds().width / 2,
      inf_h / m_pacman_icon[i].getGlobalBounds().height / 2);
    m_pacman_icon[i].setOrigin(m_pacman_icon[i].getLocalBounds().width / 2,
      m_pacman_icon[i].getLocalBounds().height / 2);
    m_pacman_icon[i].setPosition(w_width / 40 + i * w_width / 23, w_height + inf_h / 2);
  }
}

//-------------------------------------------------------------------
void InfoBar::setInfoBar(float w_width, float w_height, float inf_h)
{
  m_rect.setSize({ w_width, inf_h });
  m_rect.setPosition({ 0, w_height });
  m_rect.setFillColor(SoftRed);

  m_timer.setFillColor(DeepRed);
  m_score.setFillColor(DeepRed);
  m_level.setFillColor(DeepRed);

  m_timer.setPosition(w_width / 2, w_height + inf_h / 5.5);
  m_score.setPosition(3 * w_width / 4, w_height + inf_h / 4.5);
  m_level.setPosition(w_width / 4, w_height + inf_h / 4.5);

  m_timer.setOrigin(m_timer.getLocalBounds().width / 2, m_timer.getLocalBounds().height / 2);
  m_score.setOrigin(m_score.getLocalBounds().width / 2, m_score.getLocalBounds().height / 2);
  m_level.setOrigin(m_level.getLocalBounds().width / 2, m_level.getLocalBounds().height / 2);
}

//-------------------------------------------------------------------
void InfoBar::draw(sf::RenderWindow & window) const
{
  window.draw(m_rect);
  window.draw(m_timer);
  window.draw(m_level);
  window.draw(m_score);
  drawLife(window);
}

//-------------------------------------------------------------------
void InfoBar::drawLife(sf::RenderWindow & window) const
{
  for(auto i = size_t(0); i < m_life - 1 && i < m_pacman_icon.size(); ++i)
    window.draw(m_pacman_icon[i]);
}

//-------------------------------------------------------------------
void InfoBar::setInfo(const Level& level, const Timer& timer)
{
  m_life = level.getPacmanLife();
  m_timer.setString(timer.getTimer());
  m_timer.setFillColor(timer.getColor());
  m_level.setString("LEVEL " + std::to_string(level.getLevelNum()));
  m_score.setString("SCORE " + std::to_string(level.getPacmanScore()));
}
