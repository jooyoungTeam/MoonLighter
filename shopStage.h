#pragma once
#include "gameNode.h"
class shopStage : public gameNode
{
private:
	
public:
	shopStage() {}
	~shopStage() {}

	HRESULT init();
	void render();
	void update();
	void release();

};

