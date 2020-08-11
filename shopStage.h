#pragma once
#include "gameNode.h"
#include "player.h"
#include "shopNPC.h"
#include "tile.h"

enum doorState
{
	DOOR_CLOSE,
	DOOR_OPENING,
	DOOR_CLOSING,
	DOOR_DELAY
};

class shopStage : public gameNode
{
private:
	Image* _backGround;
	doorState _doorState;
	player* _player;
	shopNPC* _shopNPC;
	POINT _wayPoint[4];
	POINT _buyPoint;

	int	  _doorFrameTimer;
	int   _doorIndex;

	bool  _enterNPC;
public:
	shopStage() {}
	~shopStage() {}

	HRESULT init();
	void render();
	void update();
	void release();

	void doorUpdate();
};

