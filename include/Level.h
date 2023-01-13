#pragma once
#include "Objects/MovingObj.h"
#include "Objects/Erasable.h"
#include "Objects/Pacman.h"
#include <vector>
#include <string>
#include <fstream>
#include <memory>

enum ObjType
{
	COOKIE = '*', DEMON = '&', DOOR = 'D',
	GIFT   = '$', KEY   = '%', PACMAN = 'a',
	WALL   = '#', SPACE = ' '
};

class ResourceManage;

class Level
{
public:
	//Level();
	//~Level();
  //void resetLevel(size_t, size_t);
	//Object* createObject(ObjType, ResourceManage&, size_t, size_t) const;//get char and return pointe to the right object.

	void buildLevel(ResourceManage&, float, float);
	void draw(sf::RenderWindow&) const;
	void setCurrentLevel(ResourceManage&, size_t);
	size_t getRows() const;
	size_t getCols() const;
	bool runLevel(sf::RenderWindow&);

private:
	void chooseBoard(ResourceManage&, size_t);
	void addObject(ObjType, ResourceManage&, size_t, size_t);
	std::unique_ptr<Object> createObject(ObjType, ResourceManage&, const sf::Vector2f&) const;

	std::ifstream* m_current_board = nullptr;
	std::vector<std::string> m_level_txt;

	//std::unique_ptr<MovingObj> m_player;
	std::unique_ptr<Pacman> m_player;
	//Pacman* m_player = nullptr;
	std::vector<std::unique_ptr<Object>> m_level;
	std::vector<std::unique_ptr<MovingObj>> m_demons;

	float m_obj_width = 0;
	float m_obj_height = 0;
	size_t m_level_cols = 0;
	size_t m_level_rows = 0;
};