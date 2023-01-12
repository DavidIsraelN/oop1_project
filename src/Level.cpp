#include "Level.h"
#include "ResourceManage.h"
#include "Objects/Pacman.h"
#include "Objects/Demon.h"
#include "Objects/Cookie.h"
#include "Objects/Gift.h"
#include "Objects/Wall.h"
#include "Objects/Door.h"
#include "Objects/Key.h"
//
//Level::Level()
//{
//	//m_pacman_texture. loadFromFile("pacman.png");
//	//m_demon_texture.  loadFromFile("demon.png");
//	//m_wall_texture.   loadFromFile("wall.jpg");
//	//m_door_texture.   loadFromFile("door.png");
//	//m_gift_texture.   loadFromFile("gift.png");
//	//m_key_texture.    loadFromFile("key.png");
//	//m_cookie_texture. loadFromFile("cookie.png");
//}

//Level::~Level()
//{
//	resetLevel(0, 0);
//}

void Level::buildLevel(Board& board, ResourceManage& resource, float width, float height)
{
	//board.setCurrentLevel(2);
	//resetLevel(board.getRows(), board.getCols());
//	m_level.resize(board.getVector().size());
//	for (auto i = size_t(0); i < m_level.size(); ++i)
//		m_level[i].resize(board.getVector()[i].size(), nullptr);

	m_level.clear();
	m_level_cols = board.getCols();
	m_level_rows = board.getRows();
	m_obj_width = width / m_level_cols;
	m_obj_height = height / m_level_rows;

	for (int i = 0; i < board.getVector().size(); ++i)
		for (int j = 0; j < board.getVector()[i].size(); ++j)
		{
			if (board.getVector()[i][j] == SPACE) continue;
			m_level.push_back(createObject(ObjType(board.getVector()[i][j]), resource, i, j));
		}

	//sf::RenderWindow e(sf::VideoMode(200, 200), "123");
	//auto d = sf::Sprite(resource.getCookieT());
	//while(e.isOpen())
	//{
	//	e.clear();
	//	e.draw(d);
	//	e.display();
	//}

	//for (int i = 0; i < board.getVector().size(); ++i)
	//	for (int j = 0; j < board.getVector()[i].size(); ++j)
	//		m_level[i][j] = buildObject(board.getVector()[i][j], i, j);
}

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

std::unique_ptr<Object> Level::createObject(ObjType type, ResourceManage& resource, size_t i, size_t j) const
//Object* Level::buildObject(char c, size_t i, size_t j) const
{
	auto x_pos = m_obj_width * j + m_obj_width / 2;
	auto y_pos = m_obj_height * i + m_obj_height / 2;
	auto position = sf::Vector2f({ x_pos, y_pos });

	//sf::Texture m;
	//m.loadFromFile("wall.jpg");

	switch (type)
	{
	case PACMAN:
		return std::make_unique<Pacman>(resource.getPacmanT(), position, m_obj_width, m_obj_height);
	case DEMON:
		return std::make_unique<Demon>(resource.getDemonT(), position, m_obj_width, m_obj_height);
	case COOKIE:
		return std::make_unique<Cookie>(resource.getCookieT(), position, m_obj_width, m_obj_height);
	case GIFT:
		return std::make_unique<Gift>(resource.getGiftT(), position, m_obj_width, m_obj_height);
	case DOOR:
		return std::make_unique<Door>(resource.getDoorT(), position, m_obj_width, m_obj_height);
	case KEY:
		return std::make_unique<Key>(resource.getkeyT(), position, m_obj_width, m_obj_height);
	case WALL:
		return std::make_unique<Wall>(resource.getWallT(), position, m_obj_width, m_obj_height);
	}
}

int Level::getRows() {
	return m_level_rows;
}

int Level::getCols() {
	return m_level_cols;
}

void Level::draw(sf::RenderWindow& window) const
{
	for (auto i = size_t(0); i < m_level.size(); ++i)
		//for (auto j = size_t(0); j < m_level[i].size(); ++j)
		{
			//if (!m_level[i][j]) continue;
			m_level[i]->draw(window);
		}
}