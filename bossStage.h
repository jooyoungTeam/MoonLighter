#pragma once
#include "gameNode.h"
#include "player.h"
#include "enemyManager.h"
class bossStage : public gameNode
{
private:
	Image*  _mapImg;
	player*  _player;
	enemyManager* _enemy;

public:

	HRESULT init();
	void    render();
	void    update();
	void    release();
};

