#pragma once
#include "gameNode.h"
#include "player.h"
class bossStage : public gameNode
{
private:
	Image*  _mapImg;
	player*  _player;

public:

	HRESULT init();
	void    render();
	void    update();
	void    release();
};

