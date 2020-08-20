#pragma once
#include "gameNode.h"
#include "enemyManager.h"
#include "objectManager.h"
#include "miniMap.h"

#define BOSSTILEX 60
#define BOSSTILEY 41


class bossStage : public gameNode
{
private:
	Image*            _mapImg;
	class player*     _player;
	enemyManager*     _enemy;
	miniMap*          _miniMap;
	objectManager*    _objectManager;
	DWORD             _attribute[BOSSTILEX * BOSSTILEY];
	tagTile			  _tile[BOSSTILEX * BOSSTILEY];
	class UI*         _ui;
	class itemManager* _itemManager;
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
	void setPlayerLink(player* player) { _player = player; }
	void setItemManagerLink(itemManager* im) { _itemManager = im; }
	void setUILink(UI* ui) { _ui = ui; }
};
