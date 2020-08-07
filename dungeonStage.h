#pragma once
#include "gameNode.h"
#include "enemyManager.h"
class dungeonStage : public gameNode
{
private:
	enemyManager* _enemy;
public:
	HRESULT init();
	void render();
	void update();
	void release();
};

