#pragma once
#include "gameNode.h"
#include "tile.h"

class playGround : public gameNode
{
private:
	tile* _tile;
public:
	playGround();
	~playGround();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

