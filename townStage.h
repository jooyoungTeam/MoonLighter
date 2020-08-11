#pragma once
#include "gameNode.h"
#include "player.h"
#include "tile.h"
class townStage : public gameNode
{
private:
	player* _player;
	tile* _tile;

	tagTile           _townTiles[TILEX * TILEY];
	DWORD             _townAttribute[TILEX * TILEY];
public:
	townStage() {}
	~townStage() {}
public:
	HRESULT init();
	void    update();
	void    render();
	void    release();
public:
	void loadMap();
	void renderMap();
};

