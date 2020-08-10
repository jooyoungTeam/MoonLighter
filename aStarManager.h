#pragma once
#include "singletonBase.h"
#include "tile.h"
#include <vector>
#include <string>

#define TILENUMX (WINSIZEX / TILESIZE)
#define TILENUMY (WINSIZEY / TILESIZE)

class aStarManager : public singletonBase<aStarManager>
{
private:
	

public:
	aStarManager() {}
	~aStarManager() {}

public:
	HRESULT init();
	void render();
	void update();
	void release();

	void setPlayerPos();
	void setEnemyPos();
};

