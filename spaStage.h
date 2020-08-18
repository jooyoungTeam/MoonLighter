#pragma once
#include "gameNode.h"
#include "objectManager.h"
#include "tile.h"
#define DUNTILEX 32
#define DUNTILEY 18

class spaStage : public gameNode
{
	class player*     _player;

	DWORD             _attribute[DUNTILEX * DUNTILEY];
	tagTile			  _tile[DUNTILEX * DUNTILEY];
	objectManager*    _objectManager;

public:
	spaStage() {}
	~spaStage() {}
public:

	HRESULT init();
	void render();
	void update();
	void release();

	void setPlayerLink(player* player) { _player = player; };
	void loadMap();
	void renderMap();
};

