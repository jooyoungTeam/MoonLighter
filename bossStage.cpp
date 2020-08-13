#include "stdafx.h"
#include "bossStage.h"

HRESULT bossStage::init()
{
	_mapImg = ImageManager::GetInstance()->AddImage("bossRoom", L"Image/Map/bossRoom.png");
	CAMERAMANAGER->settingCamera(0, 0, WINSIZEX, WINSIZEY, 0, 0,3000 - WINSIZEX, 2030 - WINSIZEY);

	_enemy = new enemyManager;
	_player = new player;
	_player->init(1500,800);
	_enemy->setPlayerLink(_player);

	_enemy->init();
	return S_OK;
}

void bossStage::render()
{
	CAMERAMANAGER->render(_mapImg, 0, 0, 1);
	_player->render();
	_enemy->render();
}

void bossStage::update()
{
	_player->update();
	_enemy->update();
	CAMERAMANAGER->setXY(_player->getX(), _player->getY());
}

void bossStage::release()
{
}
