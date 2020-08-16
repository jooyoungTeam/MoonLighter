#pragma once
#include "gameNode.h"
#include "enemyManager.h"
#include "tile.h"

class dungeonStage : public gameNode
{
private:
	class player*     _player;
	enemyManager*     _enemy;

	tile*             _tileClass;
	DWORD             _attribute[32 * 18];
	tagTile			  _tile[32 * 18];
	vector<tagObject> _vObject;
public:
	HRESULT init();
	void render();
	void update();
	void release();

	void setPlayerLink(player* player) { _player = player; };
	void loadDungeonMap();
	void renderDungeonMap();
};

