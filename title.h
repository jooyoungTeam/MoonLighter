#pragma once
#include "gameNode.h"
class title :public gameNode
{
private:

public:
	title() {}
	~title() {}
public:
	HRESULT init();
	void update();
	void render();
	void release();
};

