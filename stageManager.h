#pragma once
#include "gameNode.h"
#include "UI.h"
#include "itemManager.h"
#include "player.h"

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

class stageManager : public gameNode
{
private:
	UI* _ui;
	itemManager* _itemMg;
	player* _player;

public:
	stageManager() {}
	~stageManager() {}

public:
	HRESULT init();
	void render();
	void update();
	void release();
};

