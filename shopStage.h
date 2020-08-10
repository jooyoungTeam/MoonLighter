#pragma once
#include "gameNode.h"
#include "player.h"
#include "tile.h"
class shopStage : public gameNode
{
private:
	player* _player;
	tile* _tile;
public:
	shopStage() {}
	~shopStage() {}

	HRESULT init();
	void render();
	void update();
	void release();

};

