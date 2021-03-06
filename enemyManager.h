#pragma once
#include "gameNode.h"
#include "redSlime.h"
#include "anotherSlime.h"
#include "golem.h"
#include "pot.h"
#include "boss.h"
#include "bullet.h"

class player;
class itemManager;
class enemyManager : public gameNode
{
private:

	itemManager* _itemManager;
	vector<enemy*> _vEnemy;
	vector<enemy*>::iterator _viEnemy;
	player* _player;

	bullet* _bullet;

	FloatRect _rc;
	float _x, _y;
	float _angle;
	float _bulletAngle;
	int _bulletDis;
	int _bulletDelay;
	int _bulletWait;
	int _bulletTimer;	//�󸶳� ����
	int _index;
	int _bowCount;
	int _test;
	bool _bowChange;
	bool _playerStop;
	bool _bossHit;

	vector<POINT> _unMoveTile;


public:
	enemyManager();
	~enemyManager();

	virtual HRESULT init(vector<POINT> unMoveTile);
	virtual void release();
	virtual void update();
	virtual void render();

	void setEnemy1(vector<POINT> unMoveTile);
	void setEnemy2(vector<POINT> unMoveTile);
	void setBoss();
	void potBullet();
	void playerCol();
	void bulletCol();
	void enemyDead(int arr);

	FloatRect getPlayerRc() { return _rc; }
	void setPlayerLink(player* player) { _player = player; }
	void setItemManagerLink(itemManager* im) { _itemManager = im; }
	bool getPlayerStop() { return _playerStop; }
	bool getBossHit() { return _bossHit; }

	vector<enemy*> _getVEnemy() { return _vEnemy; }

};

