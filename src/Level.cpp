#include "Level.h"
#include "Objects/Cookie.h"
#include "Objects/Door.h"
#include "Objects/Key.h"
#include "Objects/Demon.h"
#include "Objects/SuperPGift.h"
#include "Objects/TimeGift.h"
#include "Objects/LifeGift.h"
#include "Objects/FreezeGift.h"

//-------------------------------------------------------------------
Level::Level(float w_width, float w_height)
    : m_win_width(w_width), m_win_height(w_height) { }

//-------------------------------------------------------------------
void Level::clearLevel()
{
  m_erasable_obj.clear();
  m_erasable_obj.resize(4);
  m_demons.clear();
  m_walls.clear();
}

//-------------------------------------------------------------------
void Level::setCurrentLevel(size_t board_num)
{
  m_level_num = board_num;
  chooseLevel();
  resetLevel();
}

//-------------------------------------------------------------------
void Level::resetLevel()
{
  m_current_board->setDimensions();
  buildLevel();
  m_current_board->backToStart();
}

//-------------------------------------------------------------------
void Level::chooseLevel()
{
  m_current_board = std::make_unique<LevelReader>(
    (m_level_num == 1) ? ResourceManager::Resource().getTxtFile(TxtIndex::LEVEL1)
    : (m_level_num == 2) ? ResourceManager::Resource().getTxtFile(TxtIndex::LEVEL2)
    : ResourceManager::Resource().getTxtFile(TxtIndex::LEVEL3));
}

//-------------------------------------------------------------------
void Level::buildLevel()
{
  srand(time(NULL));
  clearLevel();
  m_obj_width = m_win_width / m_current_board->getCols();
  m_obj_height = m_win_height / m_current_board->getRows();

  for (auto i = size_t(0); i < m_current_board->getRows(); ++i)
    for (auto j = size_t(0); j < m_current_board->getCols(); ++j)
    {
      char c = m_current_board->getChar();
      if (c == char(ObjType::SPACE)) { continue; };
      addObject(ObjType(c), i, j);
    }
}

//-------------------------------------------------------------------
void Level::addObject(ObjType type, size_t i, size_t j)
{
  auto x_pos = m_obj_width * j + m_obj_width / 2;
  auto y_pos = m_obj_height * i + m_obj_height / 2;
  auto position = sf::Vector2f({ x_pos, y_pos });

  switch (type)
  {
  case ObjType::PACMAN:
    m_pacman = std::make_unique<Pacman>(position, m_obj_width, m_obj_height); break;

  case ObjType::DEMON:
    m_demons.push_back(std::make_unique<Demon>(position, m_obj_width, m_obj_height)); break;

  case ObjType::WALL:
    m_walls.push_back(std::make_unique<Wall>(position, m_obj_width, m_obj_height)); break;

  case ObjType::COOKIE:
    m_erasable_obj[size_t(ObjIndex::COOKIE)].push_back(
      std::make_unique<Cookie>(position, m_obj_width, m_obj_height));break;

  case ObjType::GIFT:
    m_erasable_obj[size_t(ObjIndex::GIFT)].push_back(chooseRandomGift(position)); break;

  case ObjType::DOOR:
    m_erasable_obj[size_t(ObjIndex::DOOR)].push_back(
      std::make_unique<Door>(position, m_obj_width, m_obj_height)); break;

  case ObjType::KEY:
    m_erasable_obj[size_t(ObjIndex::KEY)].push_back(std::make_unique<Key>(position, m_obj_width, m_obj_height));
  }
}

//-------------------------------------------------------------------
std::unique_ptr<Gift> Level::chooseRandomGift(const sf::Vector2f& position) const
{
  auto choice = rand() % 8;
  switch (choice)
  {
  case 0: case 1: case 2: return std::make_unique<SuperPGift>(position, m_obj_width, m_obj_height);
  case 3: case 4:         return std::make_unique<FreezeGift>(position, m_obj_width, m_obj_height);
  case 5: case 6:         return std::make_unique<TimeGift>(position, m_obj_width, m_obj_height);
  case 7:                 return std::make_unique<LifeGift>(position, m_obj_width, m_obj_height);
  }
}

//-------------------------------------------------------------------
bool Level::isOver() const
{
  return m_erasable_obj[size_t(ObjIndex::COOKIE)].empty();
}

//-------------------------------------------------------------------
void Level::draw(sf::RenderWindow& window) const
{
  for (auto i = size_t(0); i < m_walls.size(); ++i)
    m_walls[i]->draw(window);
  for (auto i = size_t(0); i < m_erasable_obj.size(); ++i)
    for (auto j = size_t(0); j < m_erasable_obj[i].size(); ++j)
      m_erasable_obj[i][j]->draw(window);
  m_pacman->draw(window);
  for (auto i = size_t(0); i < m_demons.size(); ++i)
    m_demons[i]->draw(window);
}

//-------------------------------------------------------------------
void Level::moveObjects(const sf::Time& delta_time) const
{
  m_pacman->move(delta_time, *this, m_win_height, m_win_width);
  srand(time(0));
  for (auto i = size_t(0); i < m_demons.size(); ++i)
    m_demons[i]->move(delta_time, *this, m_win_height, m_win_width);
}

//-------------------------------------------------------------------
void Level::erase()
{
  auto keys = m_erasable_obj[size_t(ObjIndex::KEY)].size();
  for (auto i = size_t(0); i < m_erasable_obj.size(); ++i)
    std::erase_if(m_erasable_obj[i], [](const auto& m_erasable_obj) {return m_erasable_obj->isDel(); });

  if (m_erasable_obj[size_t(ObjIndex::KEY)].size() < keys) delRandomDoor();
}

//-------------------------------------------------------------------
bool Level::collideWithWall(MovingObj& moving_obj) const
{
  for (auto i = size_t(0); i < m_walls.size(); ++i)
    if (m_walls[i]->collidesWith(moving_obj)) return true;
  return false;
}

//-------------------------------------------------------------------
bool Level::collideWithDoor(MovingObj& moving_obj) const
{
  for (auto i = size_t(0); i < m_erasable_obj[size_t(ObjIndex::DOOR)].size(); ++i)
    if (m_erasable_obj[size_t(ObjIndex::DOOR)][i]->collidesWith(moving_obj)) return true;
  return false;
}

//-------------------------------------------------------------------
void Level::handleCollision(Timer& timer) const
{
  for (auto i = size_t(0); i < m_erasable_obj.size(); ++i)
    for (auto j = size_t(0); j < m_erasable_obj[i].size(); ++j)
      if(m_erasable_obj[i][j]->collidesWith(*m_pacman))
        m_erasable_obj[i][j]->collide(*m_pacman);

  for (auto i = size_t(0); i < m_demons.size(); ++i)
    if (m_demons[i]->collidesWith(*m_pacman)) {
      m_pacman->collide(*m_demons[i]);
      resetMovingObj();
    }
  checkGiftCollision(timer);
}

//-------------------------------------------------------------------
void Level::checkGiftCollision(Timer& timer) const
{
  for (auto i = size_t(0); i < m_erasable_obj[size_t(ObjIndex::GIFT)].size(); ++i)
    if (m_erasable_obj[size_t(ObjIndex::GIFT)][i]->isDel())
    {
      if (typeid(*m_erasable_obj[size_t(ObjIndex::GIFT)][i]) == typeid(FreezeGift))
        freeseDemons();

      else if (typeid(*m_erasable_obj[size_t(ObjIndex::GIFT)][i]) == typeid(TimeGift))
        timer.addTime(20);
    }
}

//-------------------------------------------------------------------
void Level::freeseDemons() const
{
  for (auto i = size_t(0); i < m_demons.size(); ++i)
    m_demons[i]->freeze();
}

//-------------------------------------------------------------------
void Level::resetMovingObj() const
{
  if (m_pacman->isSuperPacman()) return;
  for (auto i = size_t(0); i < m_demons.size(); ++i)
  {
    m_demons[i]->resetPosition();
    m_demons[i]->stopFreeze();
  }
}

//-------------------------------------------------------------------
void Level::delRandomDoor()
{
  if (m_erasable_obj[size_t(ObjIndex::DOOR)].empty()) return;
  srand(time(0));
  auto choice = (rand() % m_erasable_obj[size_t(ObjIndex::DOOR)].size());
  m_erasable_obj[size_t(ObjIndex::DOOR)][choice]->delObj();
  std::erase_if(m_erasable_obj[size_t(ObjIndex::DOOR)], [] (const auto& m_obj) {return m_obj->isDel();});
}

//-------------------------------------------------------------------
sf::Vector2f Level::getPacmanPosition() const { return { m_pacman->getPosition()}; }

//-------------------------------------------------------------------
void Level::setDirection(sf::Keyboard::Key key) const { m_pacman->setDirection(key); }

//-------------------------------------------------------------------
size_t Level::getPacmanLife() const { return m_pacman->getLife(); }

//-------------------------------------------------------------------
size_t Level::getPacmanScore() const { return m_pacman->getScore(); }

//-------------------------------------------------------------------
void Level::setPacmanScore(const size_t score) { return m_pacman->setScore(score); }

//-------------------------------------------------------------------
void Level::setPacmanLife(const size_t life) { return m_pacman->setLife(life); }

//-------------------------------------------------------------------
size_t Level::getLevelNum() const { return m_level_num; }

//-------------------------------------------------------------------
void Level::addFinalScore()
{
  m_pacman->setScore(m_pacman->getScore() + 50 + 2 * m_demons.size());
}
