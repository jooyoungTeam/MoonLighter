#pragma once
#include"enemy.h"
class boss : public enemy	
{
private:
public:
	virtual void attack();
	virtual void enemyMove();
};

