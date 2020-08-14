#pragma once
#include "gameNode.h"
class objectManager : public gameNode
{
private:

public:
	objectManager() {}
	~objectManager() {}
public:
	HRESULT init();
	void render();
	void update();
	void release();

};

