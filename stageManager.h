#pragma once
#include "gameNode.h"
#include "UI.h"
#include "inventory.h"
#include "itemManager.h"

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

class stageManager : public gameNode
{
private:
	UI* _ui;
	inventory* _inven;
	itemManager* _itemMg;

public:
	stageManager() {}
	~stageManager() {}

public:
	HRESULT init();
	void render();
	void update();
	void release();
};

