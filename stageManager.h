#pragma once
#include "gameNode.h"
#include "UI.h"
#include "itemManager.h"
#include "player.h"
#include "dungeonStage.h"
#include "bossStage.h"
#include "shopStage.h"
#include "townStage.h"
#include "dungeonStage2.h"
#include "boss.h"
#include "spaStage.h"
#include "enterenceStage.h"
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

class stageManager : public gameNode
{
private:
	player*         _player;
	dungeonStage*   _dungeon;
	shopStage*      _shop;
	townStage*      _town;
	bossStage*      _boss;
	boss* _b;
	dungeonStage2*  _dungeon2;
	spaStage*       _spa;
	enterenceStage* _enterence;
	UI* _ui;
	itemManager* _itemMg;

	ITEMTYPE _type[INVENSPACE];

public:
	stageManager() {}
	~stageManager() {}

public:
	HRESULT init();
	void render();
	void update();
	void release();
};

