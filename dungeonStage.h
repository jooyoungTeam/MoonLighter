#pragma once
#include "gameNode.h"
#include "enemyManager.h"
#include "tile.h"

class dungeonStage : public gameNode
{
private:
	enemyManager* _enemy;
	tile*         _tile;


public:
	HRESULT init();
	void render();
	void update();
	void release();
};

