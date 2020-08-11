#pragma once
#include "gameNode.h"
#include "player.h"
#include "tile.h"
class shopStage : public gameNode
{
private:
	Image* _backGround;

	player* _player;

	POINT _wayPoint[4];
	POINT _buyPoint;

public:
	shopStage() {}
	~shopStage() {}

	HRESULT init();
	void render();
	void update();
	void release();
};

