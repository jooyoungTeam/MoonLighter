#pragma once
#include"enemy.h"
class redSlime : public enemy
{
private:
	int _attackCount;
	int _bigSlimeCount;
	int _speed;	
public:
	redSlime() { _attackCount = 0; _speed = 5; _bigSlimeCount = 0; }
	~redSlime() {}
	virtual void attack();
	virtual void enemyMove();
	virtual void dead();
};

