#pragma once
#include"enemy.h"


class golem : public enemy
{
private:
	GOLEMDIR _golemDir;
	GOLEMDIR _oldDir;
	FloatRect _shadowRc;//�׸��� ��Ʈ
	float _shadowX, _shadowY;//�׸��� ����
	int _count;
	int _golemCount;

public:
	golem() { _golemCount = 0; }
	~golem() {}

	virtual void render();
	virtual void set();
	virtual void attack();
	virtual void enemyMove();
	virtual void directionCheck();
	void direcitonChange();
	virtual void dead();
	virtual void enemyHit();
	virtual void setShadow();
};

