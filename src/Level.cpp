#include "Level.h"
#include "Objects/Pacman.h"
#include "Objects/Demon.h"
#include "Objects/Cookie.h"
#include "Objects/Door.h"
#include "Objects/Key.h"
#include "Objects/Gift.h"
#include <sstream>
#include <time.h>

//#include <thread>
//#include "ResourceManager.h"

//-------------------------------------------------------------------
Level::Level(const float w_width, const float w_height)
  : m_win_width(w_width), m_win_height(w_height) { }

//-------------------------------------------------------------------
void Level::clearLevel()
{
  m_erasable_obj.clear();
  m_erasable_obj.resize(4);
  m_moving_obj.clear();
  m_walls.clear();
}

//-------------------------------------------------------------------
void Level::setCurrentLevel(size_t board_num)
{
  m_level_num = board_num;
  chooseLevel();
  std::string line;
  std::getline(*m_current_board, line);
  auto size = std::istringstream(line);
  size >> m_level_rows >> m_level_cols;

  buildLevel();
  m_current_board->seekg(0, m_current_board->beg);
}

//-------------------------------------------------------------------
void Level::chooseLevel()
{
  m_current_board = (m_level_num == 1) ? &ResourceManager::Resource().getTxtFile(TxtIndex::LEVEL1)
                  : (m_level_num == 2) ? &ResourceManager::Resource().getTxtFile(TxtIndex::LEVEL2)
                                       : &ResourceManager::Resource().getTxtFile(TxtIndex::LEVEL3);
}

//-------------------------------------------------------------------
void Level::buildLevel()
{
  clearLevel();
  m_obj_width = m_win_width / m_level_cols;
  m_obj_height = m_win_height / m_level_rows;

  for (auto i = size_t(0); i < m_level_rows; ++i)
    for (auto j = size_t(0); j < m_level_cols; ++j)
    {
      char c = m_current_board->get();
      if (c == '\n') { --j;  continue; }
      if (c == char(ObjType::SPACE)) continue;
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
    //m_moving_obj.push_back(std::make_unique<Pacman>(position, m_obj_width, m_obj_height)); break;

  case ObjType::DEMON:
    m_moving_obj.push_back(std::make_unique<Demon>(position, m_obj_width, m_obj_height)); break;

  case ObjType::WALL:
    m_walls.push_back(std::make_unique<Wall>(position, m_obj_width, m_obj_height)); break;

  case ObjType::COOKIE:
    m_erasable_obj[size_t(ObjIndex::COOKIE)].push_back(std::make_unique<Cookie>(position, m_obj_width, m_obj_height));break;

  case ObjType::GIFT:
    m_erasable_obj[size_t(ObjIndex::GIFT)].push_back(std::make_unique<Gift>(position, m_obj_width, m_obj_height)); break;

  case ObjType::DOOR:
    m_erasable_obj[size_t(ObjIndex::DOOR)].push_back(std::make_unique<Door>(position, m_obj_width, m_obj_height)); break;

  case ObjType::KEY:
    m_erasable_obj[size_t(ObjIndex::KEY)].push_back(std::make_unique<Key>(position, m_obj_width, m_obj_height));
  }
}

//-------------------------------------------------------------------
bool Level::isOver() const {
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
  for (auto i = size_t(0); i < m_moving_obj.size(); ++i)
    m_moving_obj[i]->draw(window);
}

//-------------------------------------------------------------------
void Level::setDirection(sf::Keyboard::Key key) const
{
  m_pacman->setDirection(key);
}

//-------------------------------------------------------------------
size_t Level::getPacmanLife() const { return m_pacman->getLife(); }

//-------------------------------------------------------------------
void Level::pacmanLifeReduction() { m_pacman->lifeReduction(); }

//-------------------------------------------------------------------
size_t Level::getPacmanScore() const { return m_pacman->getScore(); }

//-------------------------------------------------------------------
void Level::setPacmanScore(const size_t score) { return m_pacman->setScore(score); }

//-------------------------------------------------------------------
size_t Level::getLevelNum() const { return m_level_num; }

//-------------------------------------------------------------------
void Level::moveObjects(const sf::Time& deltaTime) const
{
  //m_pacman->move(deltaTime, m_level_rows * m_obj_height, m_level_cols * m_obj_width, *this);
  m_pacman->move(deltaTime, m_obj_height, m_obj_width, m_level_cols, m_level_rows, *this);
  for (auto i = size_t(0); i < m_moving_obj.size(); ++i)
    m_moving_obj[i]->move(deltaTime);
}

//-------------------------------------------------------------------
void Level::erase()
{
  for (auto i = size_t(0); i < m_erasable_obj.size(); ++i)
    std::erase_if(m_erasable_obj[i], [](const auto& m_erasable_obj) {return m_erasable_obj->isDel(); });

  if (m_erasable_obj[size_t(ObjIndex::KEY)].size() < m_erasable_obj[size_t(ObjIndex::DOOR)].size())
    delDoor();
}

//-------------------------------------------------------------------
bool Level::collideWithWallOrDoor(MovingObj& moving_obj) const 
{
  for (auto i = size_t(0); i < m_walls.size(); ++i)
    if (m_walls[i]->collidesWith(moving_obj)) return true;

  for (auto i = size_t(0); i < m_erasable_obj[size_t(ObjIndex::DOOR)].size(); ++i)
    if (m_erasable_obj[size_t(ObjIndex::DOOR)][i]->collidesWith(moving_obj)) return true;

  return false;
}

//-------------------------------------------------------------------
void Level::handleCollision() const
{
  for (auto i = size_t(0); i < m_erasable_obj.size(); ++i)
    for (auto j = size_t(0); j < m_erasable_obj[i].size(); ++j)
      if(m_erasable_obj[i][j]->collidesWith(*m_pacman))
        m_erasable_obj[i][j]->collide(*m_pacman);
}

//-------------------------------------------------------------------
void Level::delDoor()
{
  srand(time(0));
  auto choice = (rand() % m_erasable_obj[size_t(ObjIndex::DOOR)].size());
  m_erasable_obj[size_t(ObjIndex::DOOR)][choice]->delObj();
  std::erase_if(m_erasable_obj[size_t(ObjIndex::DOOR)], [] (const auto& m_obj) {return m_obj->isDel();});
}

