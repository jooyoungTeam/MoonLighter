#pragma once
#include "gameNode.h"
#include "player.h"
class shopStage : public gameNode
{
private:
	player* _player;
public:
	shopStage() {}
	~shopStage() {}

	HRESULT init();
	void render();
	void update();
	void release();

};

