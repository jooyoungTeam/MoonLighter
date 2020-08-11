#include "stdafx.h"
#include "shopStage.h"

HRESULT shopStage::init()
{
	_backGround = ImageManager::GetInstance()->AddImage("shop_background", L"Image/Shop/shop_background.png");
	ImageManager::GetInstance()->AddImage("shop_mid", L"Image/Shop/shop_mid.png");
	ImageManager::GetInstance()->AddImage("shop_first", L"Image/Shop/shop_first.png");
	CAMERAMANAGER->settingCamera(0, 0, WINSIZEX, WINSIZEY, 0, 0, 1600 - WINSIZEX, 1400 - WINSIZEY);

	_player = new player;
	_player->init();

	return S_OK;
}

void shopStage::render()
{
	CAMERAMANAGER->render(_backGround, _backGround->GetWidth() / 2, 200, 1.15f, 1.0f);

	_player->render();

	CAMERAMANAGER->render(ImageManager::GetInstance()->FindImage("shop_mid"), WINSIZEX / 2 - 55, 613, 1.15f, 1.0f);
	//ImageManager::GetInstance()->FindImage("shop_mid")->Render(Vector2(WINSIZEX/2 - 55, 213));

	CAMERAMANAGER->render(ImageManager::GetInstance()->FindImage("shop_first"), WINSIZEX / 2 - 65, 1162, 1.15f, 1.0f);
	//ImageManager::GetInstance()->FindImage("shop_first")->Render(Vector2(WINSIZEX / 2 - 65, 762));
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