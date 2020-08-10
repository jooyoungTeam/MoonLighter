#pragma once
#include "singletonBase.h"
#include "aStar.h"
#include <vector>
#include <string>

struct tagTotalAstar
{
	int enemyX;
	int enemyY;
	aStar* astar;
};

class aStarManager : public singletonBase<aStarManager>
{
private:
	vector<tagTotalAstar*> _aStar;
	int _playerX;
	int _playerY;

public:
	aStarManager() {}
	~aStarManager() {}

public:
	HRESULT init();
	void render();
	void update();
	void release();
};

