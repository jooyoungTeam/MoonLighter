#include "stdafx.h"
#include "shopStage.h"

HRESULT shopStage::init()
{
	CAMERAMANAGER->settingCamera(0, 0, WINSIZEX, WINSIZEY, 0, 0, 2000 - WINSIZEX, 2056 - WINSIZEY);
	ImageManager::GetInstance()->AddImage("shopBackground", L"Image/map/shop_background.png");

	CAMERAMANAGER->setX(1300);
	CAMERAMANAGER->setY(700);

	_player = new player;
	_player->init();
	return S_OK;
}

void shopStage::render()
{
	CAMERAMANAGER->render(ImageManager::GetInstance()->FindImage("shopBackground"),0,0);

	_player->render();
}

void shopStage::update()
{
	_player->update();

	CAMERAMANAGER->setX(_player->getX());
	CAMERAMANAGER->setY(_player->getY());
}

void shopStage::release()
{
}
