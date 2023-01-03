#pragma once

class MovingObj;

class Demon : public MovingObj
{
public:
	Demon();
	~Demon();

	void move() override;
	void collusion() override;

private:

};
