#pragma once
#include "gameNode.h"
#include "enemyManager.h"
#include "objectManager.h"
#include "tile.h"

#define DUNTILEX 32
#define DUNTILEY 18

class dungeonStage2 : public gameNode
{
	class player*     _player;
	enemyManager*     _enemy;
	Image*            _mapImg;

	DWORD             _attribute[DUNTILEX * DUNTILEY];
	tagTile			  _tile[DUNTILEX * DUNTILEY];
	int               _doorIndex[2];
	objectManager*    _objectManager;
	class itemManager* _itemManager;

	vector<POINT> _unMoveTile;

public:
	dungeonStage2() {}
	~dungeonStage2() {}
public:
	HRESULT init();
	void render();
	void update();
	void release();

	void setPlayerLink(player* player) { _player = player; };
	void setItemManagerLink(itemManager* im) { _itemManager = im; }
	void loadMap();
	void renderMap();
};

