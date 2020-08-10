#pragma once
#include"enemy.h"
enum GOLEMDIR
{
	GOLEM_LEFT,
	GOLEM_RIGHT,
	GOLEM_TOP,
	GOLEM_BOTTOM
};
class golem : public enemy
{
private:
	GOLEMDIR _golemDir;

public:
	golem();
	~golem();
	virtual void set();
	virtual void attack();
	virtual void enemyMove();
};

