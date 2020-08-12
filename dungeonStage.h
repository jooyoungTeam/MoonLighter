#pragma once
#include "gameNode.h"
#include "enemyManager.h"
#include "tile.h"
#include "player.h"

class dungeonStage : public gameNode
{
private:
	player*       _player;
	enemyManager* _enemy;
	tile*         _tile;
	tagTile       _dungeonTiles[TILEX * TILEY];
	DWORD         _dungeonAttribute[TILEX * TILEY];

public:
	HRESULT init();
	void render();
	void update();
	void release();


	void loadDungeonMap();
	void renderDungeonMap();
};

