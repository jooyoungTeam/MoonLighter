#pragma once
#include "gameNode.h"
#include "UI.h"
#include "itemManager.h"
#include "player.h"
#include "dungeonStage.h"
#include "bossStage.h"
#include "shopStage.h"
#include "townStage.h"
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

class stageManager : public gameNode
{
private:
	player*       _player;
	dungeonStage* _dungeon;
	shopStage*    _shop;
	townStage*    _town;
	bossStage*    _boss;


	UI* _ui;
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

