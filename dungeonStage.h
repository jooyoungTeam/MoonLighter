#pragma once
#include "gameNode.h"
#include "enemyManager.h"
#include "objectManager.h"
#include "tile.h"

#define DUNTILEX 32
#define DUNTILEY 18

class dungeonStage : public gameNode
{
private:
	class player*      _player;
	enemyManager*      _enemy;
	Image*             _mapImg;
					   
	DWORD              _attribute[DUNTILEX * DUNTILEY];
	tagTile			   _tile[DUNTILEX * DUNTILEY];
	objectManager*     _objectManager;
	class itemManager* _itemManager;
public:
	dungeonStage() {}
	~dungeonStage() {}
public:
	HRESULT init();
	void render();
	void update();
	void release();

public:
	void setPlayerLink(player* player) { _player = player; }
	void setItemManagerLink(itemManager* im) { _itemManager = im; }
	void loadDungeonMap();
	void renderDungeonMap();
};

