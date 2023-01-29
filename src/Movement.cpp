#include "Movement.h"
#include "Objects/MovingObj.h"
#include "Level.h"

//-------------------------------------------------------------------
bool RegularMovement::isLegal(const sf::Vector2f& movement, const Level& level,
	MovingObj& obj, float win_height, float win_width)
{
	obj.moveObj(movement, win_height, win_width);
	auto collide = (!level.collideWithWall(obj) && !level.collideWithDoor(obj));
	obj.moveObj(-movement, win_height, win_width);
	return collide;
}

//-------------------------------------------------------------------
bool SPacmanMovement::isLegal(const sf::Vector2f& movement, const Level& level,
	MovingObj& obj, float win_height, float win_width)
{
	obj.moveObj(movement, win_height, win_width);
	auto collide = !level.collideWithWall(obj);
	obj.moveObj(-movement, win_height, win_width);
	return collide;
}
