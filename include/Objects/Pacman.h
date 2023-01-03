#pragma once

class MovingObj;

class Pacman : public MovingObj
{
public:
	Pacman();
	~Pacman();

	void move() override;
	void collusion() override;

private:

};
