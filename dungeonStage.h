#pragma once
#include "gameNode.h"
#include "enemyManager.h"
#include "tile.h"

class dungeonStage : public gameNode
{
private:
	enemyManager* _enemy;
	tile*         _tile;

	tagTile           _dungeonTiles[TILEX * TILEY];
	DWORD             _dungeonAttribute[TILEX * TILEY];

public:
	HRESULT init();
	void render();
	void update();
	void release();


	void loadDungeonMap();
	void renderDungeonMap();
};

