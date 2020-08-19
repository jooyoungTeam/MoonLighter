#pragma once
#include"enemy.h"
class pot : public enemy
{
private:
	
public:
	pot() {}
	~pot() {}
	virtual void render();
	virtual void dead();
};

