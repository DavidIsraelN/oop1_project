#pragma once

class Object;

class MovingObj : public Objrct
{
public:
	virtual void move() = 0;
	virtual void collusion() = 0;
};
