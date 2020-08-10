#pragma once
#include "gameNode.h"
#include "player.h"
#include "tile.h"
class shopStage : public gameNode
{
private:
	player* _player;
	tile* _tile;

	tagTile           _dungeonTiles[TILEX * TILEY];
	DWORD             _dungeonAttribute[TILEX * TILEY];
public:
	shopStage() {}
	~shopStage() {}

	HRESULT init();
	void render();
	void update();
	void release();

	void loadDungeonMap();
	void renderDungeonMap();
};

