#pragma once

class Pacman;

class SuperPacman : public Pacman
{
public:
	SuperPacman();
	~SuperPacman();

	void move() override;
	void collusion() override;

private:

};
