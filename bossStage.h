#pragma once
#include "gameNode.h"
#include "enemyManager.h"
#include "objectManager.h"

#define BOSSTILEX 60
#define BOSSTILEY 41


class bossStage : public gameNode
{
private:
	Image*  _mapImg;
	class player*  _player;
	enemyManager* _enemy;

	objectManager* _objectManager;
	DWORD             _attribute[BOSSTILEX * BOSSTILEY];
	tagTile			  _tile[BOSSTILEX * BOSSTILEY];
public:
	bossStage() {}
	~bossStage() {}
public:
	HRESULT init();
	void    render();
	void    update();
	void    release();
public:
	void loadMap();
	void renderMap();
	void setPlayerLink(player* player) { _player = player; };
};
