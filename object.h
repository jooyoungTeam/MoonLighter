#pragma once
#include "gameNode.h"
class object : public gameNode
{
private:
public:
	object() {}
	~object() {}
public:
	HRESULT init();
	void render();
	void update();
	void release();

};

