#pragma once
#include "gameNode.h"
#include "itemManager.h"
#include "inventory.h"

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

class stageManager : public gameNode
{
private:
	itemManager* _itemMg;
	inventory* _inven;

public:
	stageManager() {}
	~stageManager() {}

public:
	HRESULT init();
	void render();
	void update();
	void release();
};

