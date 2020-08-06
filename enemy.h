#pragma once
#include "gameNode.h"
class enemy :
	public gameNode
{
private:
	FloatRect _rc;
	
	float _x, _y;
	Image* _img;
	animation* _motion;

public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();


};

