#pragma once
#include"enemy.h"


class golem : public enemy
{
private:
	GOLEMDIR _golemDir;
	GOLEMDIR _oldDir;
	int _count;

public:
	golem() {}
	~golem() {}

	virtual void render();
	virtual void set();
	virtual void attack();
	virtual void enemyMove();
	virtual void directionCheck();
	void direcitonChange();
	virtual void dead();
	virtual void enemyHit();
};

