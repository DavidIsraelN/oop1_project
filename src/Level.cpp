#include "Level.h"
#include "Objects/Pacman.h"
#include "Objects/Demon.h"
#include "Objects/Cookie.h"
#include "Objects/Door.h"
#include "Objects/Key.h"
#include "Objects/SuperPGift.h"
#include "Objects/TimeGift.h"
#include "Objects/LifeGift.h"
#include "Objects/FreezeGift.h"
#include <sstream>
#include <time.h>

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
  resetLevel();
}

//-------------------------------------------------------------------
void Level::resetLevel()
{
  buildLevel();
  m_current_board->seekg(0, m_current_board->beg);
}

//-------------------------------------------------------------------
void Level::chooseLevel()
{
  m_current_board = (m_level_num == 1) ? &ResourceManager::Resource().getTxtFile(TxtIndex::LEVEL1)
                                       : (m_level_num == 2) ? &ResourceManager::Resource().getTxtFile(TxtIndex::LEVEL2)
                                                            : &ResourceManager::Resource().getTxtFile(TxtIndex::LEVEL3);

  //m_current_board =
  //  (m_level_num == 1) ? std::make_unique<std::ifstream>(ResourceManager::Resource().getTxtFile(TxtIndex::LEVEL1))
  //: (m_level_num == 2) ? std::make_unique<std::ifstream>(ResourceManager::Resource().getTxtFile(TxtIndex::LEVEL2))
  //: /*(level_num == 3)*/ std::make_unique<std::ifstream>(ResourceManager::Resource().getTxtFile(TxtIndex::LEVEL3));

}

//-------------------------------------------------------------------
void Level::buildLevel()
{
  srand(time(NULL));
  clearLevel();

  std::string line;
  std::getline(*m_current_board, line);
  auto size = std::istringstream(line);
  size >> m_level_rows >> m_level_cols;

  m_obj_width = m_win_width / m_level_cols;
  m_obj_height = m_win_height / m_level_rows;

  for (auto i = size_t(0); i < m_level_rows; ++i)
  {
    m_mat.resize(m_level_rows);
    for (auto j = size_t(0); j < m_level_cols; ++j)
    {
      char c = m_current_board->get();
      if (c == '\n') { --j;  continue; }
      if (c == char(ObjType::SPACE))
      {
        m_mat[i].push_back(0);
        continue;
      };
      addObject(ObjType(c), i, j);
    }
  }
  for (auto i = size_t(0); i < m_level_rows; ++i)
  {
    for (auto j = size_t(0); j < m_level_cols; ++j)
      std::cout << m_mat[i][j] << ' ';
    std::cout << std::endl;
  }
  updateMat();
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
    m_mat[i].push_back(0);
    m_pacman = std::make_unique<Pacman>(position, m_obj_width, m_obj_height); break;
    //m_moving_obj.push_back(std::make_unique<Pacman>(position, m_obj_width, m_obj_height)); break;

  case ObjType::DEMON:
    m_mat[i].push_back(0);
    m_moving_obj.push_back(std::make_unique<Demon>(position, m_obj_width, m_obj_height)); break;

  case ObjType::WALL:
    m_mat[i].push_back(1);
    m_walls.push_back(std::make_unique<Wall>(position, m_obj_width, m_obj_height)); break;

  case ObjType::COOKIE:
    m_mat[i].push_back(0);
    m_erasable_obj[size_t(ObjIndex::COOKIE)].push_back(std::make_unique<Cookie>(position, m_obj_width, m_obj_height));break;

  case ObjType::GIFT:
    m_mat[i].push_back(0);
    m_erasable_obj[size_t(ObjIndex::GIFT)].push_back(chooseRandomGift(position)); break;

  case ObjType::DOOR:
    m_mat[i].push_back(1);
    m_erasable_obj[size_t(ObjIndex::DOOR)].push_back(std::make_unique<Door>(position, m_obj_width, m_obj_height)); break;

  case ObjType::KEY:
    m_mat[i].push_back(0);
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
void Level::setPacmanLife(const size_t life) { return m_pacman->setLife(life); }

//-------------------------------------------------------------------
size_t Level::getLevelNum() const { return m_level_num; }

//-------------------------------------------------------------------
void Level::moveObjects(const sf::Time& delta_time) const
{
  m_pacman->SPacmanClock(delta_time);
  m_pacman->setAnimate(delta_time);
  m_pacman->move(delta_time, *this, m_win_height, m_win_width);

//  for (auto i = size_t(0); i < m_erasable_obj[size_t(ObjIndex::GIFT)].size(); ++i)
//    if (typeid(m_erasable_obj[size_t(ObjIndex::GIFT)][i]) == typeid(FreezeGift)/* &&
//        m_erasable_obj[size_t(ObjIndex::GIFT)][i]->isDel()*/)
//      std::cout << "h";
////      for (auto i = size_t(0); i < m_moving_obj.size(); ++i)
////        m_moving_obj[i]->freeze();

   for (auto i = size_t(0); i < m_moving_obj.size(); ++i)
    m_moving_obj[i]->move(delta_time, *this, m_win_height, m_win_width);
}


void Level::updateMat()
{
//  std::cout << "obj_width: " << m_obj_width << std::endl;
//  std::cout << "obj_height: " << m_obj_height << std::endl;
//
//  auto position = m_pacman->getPosition();
//
//  auto x_pos = position.x;
//  auto y_pos = position.y;
//
//   auto j = (x_pos + m_obj_width / 2) / m_obj_width;
//  std::cout << j << std::endl;
//
//  auto i = (y_pos + m_obj_height / 2) / m_obj_height;
//  std::cout << i << std::endl;

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
void Level::handleCollision() const
{
  for (auto i = size_t(0); i < m_erasable_obj.size(); ++i)
    for (auto j = size_t(0); j < m_erasable_obj[i].size(); ++j)
      if(m_erasable_obj[i][j]->collidesWith(*m_pacman))
        m_erasable_obj[i][j]->collide(*m_pacman);
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
void Level::resetMovingObj()
{
  m_pacman->stopSPacman();
  m_pacman->resetDirections();
  m_pacman->resetPosition();
  for (auto i = size_t(0); i < m_moving_obj.size(); ++i)
    m_moving_obj[i]->resetPosition();
}

sf::Vector2f Level::getObjDimensions() const
{
  return {m_obj_width, m_obj_height};
}

sf::Vector2f Level::getPacmanPosition() const
{
  return {m_pacman->getPosition()};
}

std::vector<std::vector<size_t>> Level::getMat() const
{
  return m_mat;
}

/*
//-------------------------------------------------------------------
void Level::setLevel(size_t board_num)
{
  m_level_num = board_num;
  m_current_board = LevelReader((m_level_num == 1) ? ResourceManager::Resource().getTxtFile(TxtIndex::LEVEL1)
                                : (m_level_num == 2) ? ResourceManager::Resource().getTxtFile(TxtIndex::LEVEL2)
                                                     : ResourceManager::Resource().getTxtFile(TxtIndex::LEVEL3));
  buildLevel();
  m_current_board.backToStart();
}
*/


/*
 class Node
{
public:
 Node(sf::Vector2f& position) : m_position(position) {Node::m_nodes.clear();}
 sf::Vector2f m_position;
 bool up = 0, right = 0,
      left = 0, down = 0;
 static std::vector<Node> m_nodes;
private:

};

for (auto i = size_t(0); i < Node::m_nodes.size(); ++i)
  for (auto j = size_t(0); j < Node::m_nodes.size(); ++j)
  {
    //      {
    //        std::cout << "Node i - step: " << m_nodes[i].m_position.x - m_obj_width << ' '
    //                  << m_nodes[i].m_position.y << std::endl;
    //        std::cout << "Node j: " << m_nodes[j]->m_position.x << ' '
    //                  << m_nodes[j]->m_position.y << std::endl;

    if (Node::m_nodes[i].m_position.x == Node::m_nodes[j]->m_position.x &&
        int(Node::m_nodes[i].m_position.y - m_obj_height) == int(Node::m_nodes[j]->m_position.y))
    {
      Node::m_nodes[i].up = true;
    }
    if (int(Node::m_nodes[i].m_position.x + m_obj_width) == int(Node::m_nodes[j]->m_position.x) &&
        Node::m_nodes[i].m_position.y == Node::m_nodes[j]->m_position.y)
    {
      Node::m_nodes[i].right = true;
    }
    if (Node::m_nodes[i].m_position.x == Node::m_nodes[j]->m_position.x &&
        int(Node::m_nodes[i].m_position.y + m_obj_height) == int(Node::m_nodes[j]->m_position.y))
    {
      Node::m_nodes[i].down = true;
    }
    if (int(Node::m_nodes[i].m_position.x - m_obj_width) == int(Node::m_nodes[j]->m_position.x) &&
        Node::m_nodes[i].m_position.y == Node::m_nodes[j]->m_position.y)
    {
      Node::m_nodes[i].left = true;
    }
  }*/
