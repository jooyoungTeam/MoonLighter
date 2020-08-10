#pragma once
#include "gameNode.h"
#include "item.h"

class itemManager :	public gameNode
{
private:
	vector<item*> _vItem;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void setItem();
	void erase();

	vector<item*> getVItem() { return _vItem; }
};

