#pragma once
#include "gameNode.h"
#include "redSlime.h"
#include "anotherSlime.h"
#include "golem.h"
#include "pot.h"
#include "boss.h"
#include "bullet.h"

class player;

class enemyManager : public gameNode
{
private:
	vector<enemy*> _vEnemy;
	vector<enemy*>::iterator _viEnemy;
	enemy* _enemy;
	player* _player;

	bullet* _bullet;

	FloatRect _rc;
	float _x, _y;
	float _angle;
	float _bulletAngle;
	int _bulletDelay;
	int _bulletWait;
	int _bulletTimer;	//¾ó¸¶³ª ½òÁö
	bool _test;




public:
	enemyManager();
	~enemyManager();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setEnemy1();
	void setEnemy2();
	void setBoss();
	void potBullet();
	void playerCol();
	void bulletCol();
	void enemyDead(int arr);

	enemy* getEnemy() { return _enemy; }
	FloatRect getPlayerRc() { return _rc; }
	void setPlayerLink(player* player) { _player = player; }
};

