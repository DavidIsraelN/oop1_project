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

Level::Level(const float w_width, const float w_height, const float inf_h)
    : m_win_width(w_width), m_win_height(w_height), m_info_height(inf_h),
      m_info(w_width, w_height, inf_h) { }

void Level::buildLevel()
{
  m_erasable_obj.clear();
  m_erasable_obj.resize(4);
  m_demons.clear();
  m_walls.clear();
  m_obj_width = m_win_width / m_level_cols;
  m_obj_height = m_win_height / m_level_rows;

  for (auto i = size_t(0); i < m_level_txt.size(); ++i)
    for (auto j = size_t(0); j < m_level_txt[i].size(); ++j)
    {
      if (m_level_txt[i][j] == char(ObjType::SPACE)) continue;
      addObject(ObjType(m_level_txt[i][j]), i, j);
      //m_level.push_back(createObject(ObjType(m_level_txt[i][j]), resource, i, j));
    }
}

void Level::addObject(ObjType type, size_t i, size_t j)
{
  auto x_pos = m_obj_width * j + m_obj_width / 2;
  auto y_pos = m_obj_height * i + m_obj_height / 2;
  auto position = sf::Vector2f({ x_pos, y_pos });

  switch (type)
  {
  case ObjType::PACMAN:
    m_player = std::make_unique<Pacman>(position, m_obj_width, m_obj_height);
    //*m_player = Pacman(*resource.getPacmanT(), position, m_obj_width, m_obj_height);
    break;

  case ObjType::DEMON:
    m_demons.push_back(std::make_unique<Demon>(position, m_obj_width, m_obj_height));
    break;

  case ObjType::WALL:
    m_walls.push_back(std::make_unique<Wall>(position, m_obj_width, m_obj_height));
    break;

  case ObjType::COOKIE:
    m_erasable_obj[size_t(ObjIndex::COOKIE)].push_back(std::make_unique<Cookie>(position, m_obj_width, m_obj_height));
    break;

  case ObjType::GIFT:
    m_erasable_obj[size_t(ObjIndex::GIFT)].push_back(std::make_unique<Gift>(position, m_obj_width, m_obj_height));
    break;

  case ObjType::DOOR:
    m_erasable_obj[size_t(ObjIndex::DOOR)].push_back(std::make_unique<Door>(position, m_obj_width, m_obj_height));
    break;

  case ObjType::KEY:
    m_erasable_obj[size_t(ObjIndex::KEY)].push_back(std::make_unique<Key>(position, m_obj_width, m_obj_height));
  }
  //  default:
  //    m_erasable_obj[].push_back(createObject(type, position));
  //
}

//std::unique_ptr<Erasable> Level::createObject(ObjType type, const sf::Vector2f& position) const
//{
//  switch (type)
//  {
//  case ObjType::COOKIE:
//    return std::make_unique<Cookie>(position, m_obj_width, m_obj_height);
//  case ObjType::GIFT:
//    return std::make_unique<Gift>(position, m_obj_width, m_obj_height);
//  case ObjType::DOOR:
//    return std::make_unique<Door>(position, m_obj_width, m_obj_height);
//  case ObjType::KEY:
//    return std::make_unique<Key>(position, m_obj_width, m_obj_height);
//  }
//}

void Level::draw(sf::RenderWindow& window) const
{
  for (auto i = size_t(0); i < m_walls.size(); ++i)
    m_walls[i]->draw(window);
  for (auto i = size_t(0); i < m_erasable_obj.size(); ++i)
    for (auto j = size_t(0); j < m_erasable_obj[i].size(); ++j)
      m_erasable_obj[i][j]->draw(window);
  for (auto i = size_t(0); i < m_demons.size(); ++i)
    m_demons[i]->draw(window);
  m_player->draw(window);
  m_info.draw(window);
  //m_timer.draw(window);
//  drawStatusBar(window);
}

//void Level::drawStatusBar(sf::RenderWindow& window) const
//{
////  window.draw(m_info_rect);
////
////
//////  for (auto i = size_t(0); i < m_player->getLife(); ++i)
//////
////  window.draw(sf::Text(std::to_string(m_player->getLife()), *ResourceManage::Resource()->getFont(), m_info_height / 2));
//}

void Level::setCurrentLevel(size_t board_num)
{
  m_level_num = board_num;
  chooseBoard();
  std::string line;
  std::getline(*m_current_board, line);
  auto size = std::istringstream(line);
  size >> m_level_rows >> m_level_cols;

  m_level_txt.clear();
  for (int i = 0; i < m_level_rows; ++i)
    if (std::getline(*m_current_board, line))
      m_level_txt.push_back(line);

  m_current_board->seekg(0, m_current_board->beg);

//  m_info = std::make_unique<InfoBar>(WIN_HEIGHT);
//  m_timer = std::make_unique<Timer>();
  m_timer.setStart(board_num);
}

void Level::chooseBoard()
{
  m_current_board = (m_level_num == 1) ? ResourceManage::Resource()->getBoard1() :
                    (m_level_num == 2) ? ResourceManage::Resource()->getBoard2() :
                    ResourceManage::Resource()->getBoard3();
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
    m_timer.setTimer(elapsed.getElapsedTime().asSeconds());
    handleCollision();
    for (auto i = size_t(0); i < m_erasable_obj.size(); ++i)
//      std::cout << m_erasable_obj.size();
      std::erase_if(m_erasable_obj[i], [] (const auto& m_erasable_obj) {return m_erasable_obj->isDel();});
    m_info.setValues(m_player->getLife(), m_timer.getTimer(), m_level_num, m_player->getScore());
  }
}

bool Level::collideWithWallOrDoor(MovingObj& moving_obj) const {
  for (auto i = size_t(0); i < m_walls.size(); ++i)
    if (m_walls[i]->collidesWith(moving_obj))
      return true;

  for (auto i = size_t(0); i < m_erasable_obj[size_t(ObjIndex::DOOR)].size(); ++i)
    if (m_erasable_obj[size_t(ObjIndex::DOOR)][i]->collidesWith(moving_obj))
      return true;

  return false;
}

void Level::handleCollision()
{
  for (auto i = size_t(0); i < m_erasable_obj.size(); ++i)
    for (auto j = size_t(0); j < m_erasable_obj[i].size(); ++j)
      if(m_erasable_obj[i][j]->collidesWith(*m_player))
        m_player->collide(*m_erasable_obj[i][j]);
}

//for (auto i = size_t(0); i < m_walls.size(); ++i)
//	if (m_level[i]->getGlobalBounds().contains(loc))
//		return WALL;

//for (auto i = size_t(0); i < m_demons.size(); ++i)
//	if (m_level[i]->getGlobalBounds().contains(loc))
//		return DEMON;








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
//		return new Key(/*resource.getKeyT()*/m_key_texture, position, m_obj_width, m_obj_height);
//	case WALL:
//		return new Wall(/*resource.getWallT()*/m_wall_texture, position, m_obj_width, m_obj_height);
//	}
//}
