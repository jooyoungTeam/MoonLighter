#pragma once
#include "gameNode.h"

class stageManager : public gameNode
{
private:
public:
	stageManager() {}
	~stageManager() {}
public:
	HRESULT init();
	void render();
	void update();
	void release();
};

