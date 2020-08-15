#pragma once
#include"enemy.h"
class anotherSlime : public enemy
{
private:
	int _attackCount;		//길게 이동할거
	int _yRandom;
	bool _once;
	bool _pang;
public:
	anotherSlime() { _attackCount = 0; }
	~anotherSlime() {}
	virtual void attack();
	virtual void enemyMove();
	virtual void dead();
};

