#pragma once
#include "singletonBase.h"
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
};

