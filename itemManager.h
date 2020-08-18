#pragma once
#include "gameNode.h"
#include "item.h"

class itemManager :	public gameNode
{
private:
	item* _item;
	vector<item*> _vItem;

public:
	itemManager() {}
	~itemManager() {}

	HRESULT init();
	void release();
	void update();
	void render();

	void setItem(ITEMBUNDLE bundle, float x, float y);
	void popItem(ITEMTYPE type, float x, float y);
	void erase(int arrNum);

	vector<item*> getVItem() { return _vItem; }
};

