#pragma once
#include "StaticObj.h"

//class StaticObj;

class Erasable : public StaticObj
{
public:
//	Erasable();
//	~Erasable();
	bool isDel();

private:
	bool m_obj_del = false;
};
