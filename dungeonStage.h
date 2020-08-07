#pragma once
#include "gameNode.h"
#include "enemyManager.h"
#include "player.h"
class dungeonStage : public gameNode
{
private:
	enemyManager* _enemy;
	player* _player;
public:
	HRESULT init();
	void render();
	void update();
	void release();
};

