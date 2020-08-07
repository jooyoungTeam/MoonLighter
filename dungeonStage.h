#pragma once
#include "gameNode.h"
class dungeonStage : public gameNode
{
private:
public:
	HRESULT init();
	void render();
	void update();
	void release();
};

