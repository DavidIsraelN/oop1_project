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
    setNextLevel(window);
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
void LevelManager::setNextLevel(sf::RenderWindow& window)
{
  if (m_timer.isOver())
  {
    m_current_level.pacmanLifeReduction();
    if (m_current_level.getPacmanLife() == 0)
      gameOver(window);
    m_timer.setStart(m_current_level.getLevelNum());
  }

  if (!m_current_level.isOver()) return;
  if (m_current_level.getLevelNum() < LEVELS)
    chooseNewLevel(m_current_level.getLevelNum() + 1);
  else
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
void LevelManager::chooseNewLevel(size_t level_num)
{
  m_current_level.setCurrentLevel(level_num);
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


////-------------------------------------------------------------------
//void LevelManager::levelAction(sf::Time deltaTime, sf::Clock elapsed)
//{
//  m_current_level.moveObj(deltaTime);
//  m_current_level.handleCollision();
//  m_timer.updateTimer(elapsed.getElapsedTime().asSeconds());
//  m_current_level.erase();
//  m_info.setInfo(m_current_level, m_timer.getTimer());
//}
////-------------------------------------------------------------------
//void LevelManager::move(sf::Time deltaTime)
//{
//
//  //m_player->move(deltaTime, m_level_rows * m_obj_height, m_level_cols * m_obj_width, *this);
//  m_player->move(deltaTime, m_obj_height, m_obj_width, m_level_cols, m_level_rows, *this);
//  //m_monster.move(deltaTime);
//  for (auto i = size_t(0); i < m_erasable_obj.size(); ++i)
//    //      std::cout << m_erasable_obj.size();
//    std::erase_if(m_erasable_obj[i], [](const auto& m_erasable_obj) {return m_erasable_obj->isDel(); });
//  if (m_erasable_obj[size_t(ObjIndex::KEY)].size() < m_erasable_obj[size_t(ObjIndex::DOOR)].size())
//    delDoor();
//
//}
////
//////-------------------------------------------------------------------
////bool LevelManager::collideWithWallOrDoor(MovingObj& moving_obj) const {
////  for (auto i = size_t(0); i < m_walls.size(); ++i)
////    if (m_walls[i]->collidesWith(moving_obj))
////      return true;
////
////  for (auto i = size_t(0); i < m_erasable_obj[size_t(ObjIndex::DOOR)].size(); ++i)
////    if (m_erasable_obj[size_t(ObjIndex::DOOR)][i]->collidesWith(moving_obj))
////      return true;
////
////  return false;
////}
////
////void LevelManager::handleCollision()
////{
////  for (auto i = size_t(0); i < m_erasable_obj.size(); ++i)
////    for (auto j = size_t(0); j < m_erasable_obj[i].size(); ++j)
////      if(m_erasable_obj[i][j]->collidesWith(*m_player))
////        m_player->collide(*m_erasable_obj[i][j]);
////}
////
////void LevelManager::delDoor()
////{
////  srand(time(0));
////  auto choice = (rand() % m_erasable_obj[size_t(ObjIndex::DOOR)].size());
////  m_erasable_obj[size_t(ObjIndex::DOOR)][choice]->delObj();
////  //std::erase_if(m_erasable_obj[size_t(ObjIndex::DOOR)], [] (const auto& m_erasable_obj) {return m_erasable_obj->isDel();});
////}
//















////-------------------------------------------------------------------
//void LevelManager::buildLevel()
//{
//  m_current_level.set
//  clearLevel();
//  m_obj_width = m_win_width / m_level_cols;
//  m_obj_height = m_win_height / m_level_rows;
//
//  for (auto i = size_t(0); i < m_level_rows; ++i)
//    for (auto j = size_t(0); j < m_level_cols; ++j)
//    {
//      char c = m_current_board->get();
//      if (c == '\n') { --j;  continue; }
//      if (c == char(ObjType::SPACE)) continue;
//      addObject(ObjType(c), i, j);
//    }
//}

//

////-------------------------------------------------------------------
//void LevelManager::setCurrentLevel(size_t board_num)
//{
//  m_level_num = board_num;
//  chooselevel();
//  std::string line;
//  std::getline(*m_current_board, line);
//  auto size = std::istringstream(line);
//  size >> m_level_rows >> m_level_cols;
//
//  buildLevel();
//  m_current_board->seekg(0, m_current_board->beg);
//  m_timer.setStart(board_num);
//}
//
////-------------------------------------------------------------------
//void LevelManager::chooselevel()
//{
//  m_current_board = (m_level_num == 1) ? &ResourceManager::Resource().getTxtFile(TxtIndex::LEVEL1) :
//    (m_level_num == 2) ? &ResourceManager::Resource().getTxtFile(TxtIndex::LEVEL2) :
//    &ResourceManager::Resource().getTxtFile(TxtIndex::LEVEL3);
//}

////-------------------------------------------------------------------
//size_t Level::getRows() const {
//  return m_level_rows;
//}
//
////-------------------------------------------------------------------
//size_t Level::getCols() const {
//  return m_level_cols;
//}


//-------------------------------------------------------------------
//void LevelManager::addObject(ObjType type, size_t i, size_t j)
//{
//  auto x_pos = m_obj_width * j + m_obj_width / 2;
//  auto y_pos = m_obj_height * i + m_obj_height / 2;
//  auto position = sf::Vector2f({ x_pos, y_pos });
//  
//  switch (type)
//  {
//  case ObjType::PACMAN:
//    m_player = std::make_unique<Pacman>(position, m_obj_width, m_obj_height);
//    break;
//
//  case ObjType::DEMON:
//    m_demons.push_back(std::make_unique<Demon>(position, m_obj_width, m_obj_height));
//    break;
//
//  case ObjType::WALL:
//    m_walls.push_back(std::make_unique<Wall>(position, m_obj_width, m_obj_height));
//    break;
//
//  case ObjType::COOKIE:
//    m_erasable_obj[size_t(ObjIndex::COOKIE)].push_back(std::make_unique<Cookie>(position, m_obj_width, m_obj_height));
//    break;
//
//  case ObjType::GIFT:
//    m_erasable_obj[size_t(ObjIndex::GIFT)].push_back(std::make_unique<Gift>(position, m_obj_width, m_obj_height));
//    break;
//
//  case ObjType::DOOR:
//    m_erasable_obj[size_t(ObjIndex::DOOR)].push_back(std::make_unique<Door>(position, m_obj_width, m_obj_height));
//    break;
//
//  case ObjType::KEY:
//    m_erasable_obj[size_t(ObjIndex::KEY)].push_back(std::make_unique<Key>(position, m_obj_width, m_obj_height));
//  }
//}
//
////-------------------------------------------------------------------
//void LevelManager::draw(sf::RenderWindow& window) const
//{
//  for (auto i = size_t(0); i < m_walls.size(); ++i)
//    m_walls[i]->draw(window);
//  for (auto i = size_t(0); i < m_erasable_obj.size(); ++i)
//    for (auto j = size_t(0); j < m_erasable_obj[i].size(); ++j)
//      m_erasable_obj[i][j]->draw(window);
//  for (auto i = size_t(0); i < m_demons.size(); ++i)
//    m_demons[i]->draw(window);
//  m_player->draw(window);
//  m_info.draw(window);
//}




//void Level::drawStatusBar(sf::RenderWindow& window) const
//{
////  window.draw(m_info_rect);
////
////
//////  for (auto i = size_t(0); i < m_player->getLife(); ++i)
//////
////  window.draw(sf::Text(std::to_string(m_player->getLife()), *ResourceManager::Resource().getFont(), m_info_height / 2));
//}



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

//void Level::buildLevel(/*Board& board,*/ ResourceManager& resource, float width, float height)
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

//Object* Level::createObject(ObjType type, ResourceManager& resource, size_t i, size_t j) const
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