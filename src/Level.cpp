#include "Level.h"
#include "ResourceManage.h"
#include "Objects/Pacman.h"
#include "Objects/Demon.h"
#include "Objects/Cookie.h"
#include "Objects/Gift.h"
#include "Objects/Wall.h"
#include "Objects/Door.h"
#include "Objects/Key.h"
#include "Colors.h"
#include <sstream>

void Level::buildLevel(ResourceManage& resource, float width, float height)
{
  m_level.clear();
  m_demons.clear();
  m_walls.clear();
  m_obj_width = width / m_level_cols;
  m_obj_height = height / m_level_rows;

  for (auto i = size_t(0); i < m_level_txt.size(); ++i)
    for (auto j = size_t(0); j < m_level_txt[i].size(); ++j)
    {
      if (m_level_txt[i][j] == SPACE) continue;
      addObject(ObjType(m_level_txt[i][j]), resource, i, j);
      //m_level.push_back(createObject(ObjType(m_level_txt[i][j]), resource, i, j));
    }
}

void Level::addObject(ObjType type, ResourceManage& resource, size_t i, size_t j)
{
  auto x_pos = m_obj_width * j + m_obj_width / 2;
  auto y_pos = m_obj_height * i + m_obj_height / 2;
  auto position = sf::Vector2f({ x_pos, y_pos });

  switch (type)
  {
  case PACMAN:
    m_player = std::make_unique<Pacman>(*resource.getPacmanT(), position, m_obj_width, m_obj_height);
    //*m_player = Pacman(*resource.getPacmanT(), position, m_obj_width, m_obj_height);
    break;

  case DEMON:
    m_demons.push_back(std::make_unique<Demon>(*resource.getDemonT(), position, m_obj_width, m_obj_height));
    break;

  case WALL:
    m_walls.push_back(std::make_unique<Wall>(*resource.getWallT(), position, m_obj_width, m_obj_height));
    break;

  default:
    m_level.push_back(createObject(type, resource, position));
  }
}

std::unique_ptr<Erasable> Level::createObject(ObjType type, ResourceManage& resource, const sf::Vector2f& position) const
{
  switch (type)
  {
    //case DEMON:
    //	return std::make_unique<Demon> (*resource.getDemonT(),  position, m_obj_width, m_obj_height);
  case COOKIE:
    return std::make_unique<Cookie>(*resource.getCookieT(), position, m_obj_width, m_obj_height);
  case GIFT:
    return std::make_unique<Gift>(*resource.getGiftT(), position, m_obj_width, m_obj_height);
  case DOOR:
    return std::make_unique<Door>(*resource.getDoorT(), position, m_obj_width, m_obj_height);
  case KEY:
    return std::make_unique<Key>(*resource.getkeyT(), position, m_obj_width, m_obj_height);
    //case WALL:
    //	return std::make_unique<Wall>  (*resource.getWallT(),   position, m_obj_width, m_obj_height);
  }
}

void Level::draw(sf::RenderWindow& window) const
{
  for (auto i = size_t(0); i < m_walls.size(); ++i)
    m_walls[i]->draw(window);
  for (auto i = size_t(0); i < m_level.size(); ++i)
    m_level[i]->draw(window);
  for (auto i = size_t(0); i < m_demons.size(); ++i)
    m_demons[i]->draw(window);
  m_player->draw(window);
  m_timer->draw(window);
}

void Level::setCurrentLevel(ResourceManage& resource, size_t board_num)
{
  chooseBoard(resource, board_num);
  std::string line;
  std::getline(*m_current_board, line);
  auto size = std::istringstream(line);
  size >> m_level_rows >> m_level_cols;

  m_level_txt.clear();
  for (int i = 0; i < m_level_rows; ++i)
    if (std::getline(*m_current_board, line))
      m_level_txt.push_back(line);

  m_current_board->seekg(0, m_current_board->beg);

  m_timer = std::make_unique<Timer>(*resource.getFont());
  m_timer->setStart(board_num);
}

void Level::chooseBoard(ResourceManage& resource, size_t board_num)
{
  m_current_board = (board_num == 1) ? resource.getBoard1() :
                    (board_num == 2) ? resource.getBoard2() : resource.getBoard3();
}

size_t Level::getRows() const {
  return m_level_rows;
}

size_t Level::getCols() const {
  return m_level_cols;
}

bool Level::runLevel(sf::RenderWindow& window)
{
  sf::Clock clock, elapsed;

  while (window.isOpen()) {
    //window.setFramerateLimit(30);
    window.clear(DeepRed);
    draw(window);
    window.display();

    for (auto event = sf::Event{}; window.pollEvent(event); )
      switch (event.type)
      {
      case sf::Event::Closed:
        window.close();
        return false;

      case sf::Event::KeyPressed:
        if (event.key.code == sf::Keyboard::Escape)
          return true;
        m_player->setDirection(event.key.code);
        break;
      }
    //move
    const auto deltaTime = clock.restart();
    //m_player->move(deltaTime, m_level_rows * m_obj_height, m_level_cols * m_obj_width, *this);
    m_player->move(deltaTime, m_obj_height, m_obj_width, m_level_cols, m_level_rows, *this);
    //m_monster.move(deltaTime);
    m_timer->setTimer(elapsed.getElapsedTime().asSeconds());

  }
}

bool Level::collideWithWall(const MovingObj& moving_obj) const
{
  for (auto i = size_t(0); i < m_walls.size(); ++i)
    if (m_walls[i]->collidesWith(moving_obj))
      return true;
  return false;

  //for (auto i = size_t(0); i < m_walls.size(); ++i)
  //	if (m_level[i]->getGlobalBounds().contains(loc))
  //		return WALL;

  //for (auto i = size_t(0); i < m_demons.size(); ++i)
  //	if (m_level[i]->getGlobalBounds().contains(loc))
  //		return DEMON;
}












//Level::Level()
//{
//	m_pacman_texture. loadFromFile("pacman.png");
//	m_demon_texture.  loadFromFile("demon.png");
//	m_wall_texture.   loadFromFile("wall.jpg");
//	m_door_texture.   loadFromFile("door.png");
//	m_gift_texture.   loadFromFile("gift.png");
//	m_key_texture.    loadFromFile("key.png");
//	m_cookie_texture. loadFromFile("cookie.png");
//}

//Level::~Level()
//{
//	resetLevel(0, 0);
//}

//void Level::buildLevel(/*Board& board,*/ ResourceManage& resource, float width, float height)
//{
//	//board.setCurrentLevel(2);
//	//resetLevel(board.getRows(), board.getCols());
////	m_level.resize(board.getVector().size());
////	for (auto i = size_t(0); i < m_level.size(); ++i)
////		m_level[i].resize(board.getVector()[i].size(), nullptr);
//
//	m_level.clear();
//	//m_level_cols = board.getCols();
//	//m_level_rows = board.getRows();
//	m_obj_width = width / m_level_cols;
//	m_obj_height = height / m_level_rows;
//
//	//for (int i = 0; i < board.getVector().size(); ++i)
//	//	for (int j = 0; j < board.getVector()[i].size(); ++j)
//	for (auto i = size_t(0); i < m_level_txt.size(); ++i)
//		for (auto j = size_t(0); j < m_level_txt[i].size(); ++j)
//		{
//			if (m_level_txt[i][j] == SPACE) continue;
//			m_level.push_back(createObject(ObjType(m_level_txt[i][j]), resource, i, j));
//		}
//
//	//sf::RenderWindow e(sf::VideoMode(200, 200), "123");
//	//auto d = sf::Sprite(resource.getCookieT());
//	//while(e.isOpen())
//	//{
//	//	e.clear();
//	//	e.draw(d);
//	//	e.display();
//	//}
//
//	//for (int i = 0; i < board.getVector().size(); ++i)
//	//	for (int j = 0; j < board.getVector()[i].size(); ++j)
//	//		m_level[i][j] = buildObject(board.getVector()[i][j], i, j);
//}

//void Level::resetLevel(size_t rows, size_t cols)
//{
//	//for (auto i = size_t(0); i < m_level.size(); ++i)
//	//	for (auto j = size_t(0); j < m_level[i].size(); ++j)
//	//	{
//	//		if (!m_level[i][j]) continue;
//	//		delete m_level[i][j];
//	//		m_level[i][j] = nullptr;
//	//	}
//
//	m_level_rows = rows;
//	m_level_cols = cols;
//
//	m_level.resize(rows);
//	for (auto i = size_t(0); i < rows; ++i)
//		m_level[i].resize(cols, nullptr);
//}

//Object* Level::createObject(ObjType type, ResourceManage& resource, size_t i, size_t j) const
//{
//	auto x_pos = m_obj_width * j + m_obj_width / 2;
//	auto y_pos = m_obj_height * i + m_obj_height / 2;
//	auto position = sf::Vector2f({ x_pos, y_pos });
//
//	//sf::Texture m;
//	//m.loadFromFile("wall.jpg");
//
//	switch (type)
//	{
//	case PACMAN:
//		return new Pacman(*resource.getPacmanT()/*m_pacman_texture*/, position, m_obj_width, m_obj_height);
//	case DEMON:
//		return new Demon(/*resource.getDemonT()*/m_demon_texture, position, m_obj_width, m_obj_height);
//	case COOKIE:
//		return new Cookie(/*resource.getCookieT()*/m_cookie_texture, position, m_obj_width, m_obj_height);
//	case GIFT:
//		return new Gift(/*resource.getGiftT()*/m_gift_texture, position, m_obj_width, m_obj_height);
//	case DOOR:
//		return new Door(/*resource.getDoorT()*/m_door_texture, position, m_obj_width, m_obj_height);
//	case KEY:
//		return new Key(/*resource.getkeyT()*/m_key_texture, position, m_obj_width, m_obj_height);
//	case WALL:
//		return new Wall(/*resource.getWallT()*/m_wall_texture, position, m_obj_width, m_obj_height);
//	}
//}
