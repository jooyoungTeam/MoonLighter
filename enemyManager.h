#pragma once
#include "gameNode.h"
#include "redSlime.h"
#include "anotherSlime.h"
#include "golem.h"
#include "pot.h"
#include "boss.h"
#include "bullet.h"

class enemyManager : public gameNode
{
private:
	vector<enemy*> _vEnemy;
	vector<enemy*>::iterator _viEnemy;
	enemy* _enemy;

	bullet* _bullet;

	FloatRect _rc;
	float _x, _y;
	int _bulletDelay;



public:
	enemyManager();
	~enemyManager();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setEnemy();
	void potBullet();
	//void setPlayerLink(player* player) { _player = player; }
};

