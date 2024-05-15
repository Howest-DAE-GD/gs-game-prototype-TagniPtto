#pragma once

#include "Entity.h"
class Character:public Entity
{
public:
	Character();
	void ScanSurrounding(const std::vector<Entity*>& surrounding);
	Entity* m_target;
	
};

