#pragma once

class Batton;

class Exit : public Batton
{
public:
	Exit();
	~Exit();
	void action() override;

private:

};