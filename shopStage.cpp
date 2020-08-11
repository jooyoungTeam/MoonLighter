#include "stdafx.h"
#include "shopStage.h"

HRESULT shopStage::init()
{
	_backGround = ImageManager::GetInstance()->AddImage("shop_background", L"Image/Shop/shop_background.png");
	ImageManager::GetInstance()->AddImage("shop_mid", L"Image/Shop/shop_mid.png");
	ImageManager::GetInstance()->AddImage("shop_first", L"Image/Shop/shop_first.png");
	CAMERAMANAGER->settingCamera(0, 0, WINSIZEX, WINSIZEY, 0, 0, 1600 - WINSIZEX, 1500 - WINSIZEY);

	_player = new player;
	_player->init();

	return S_OK;
}

void shopStage::render()
{
	_backGround->SetScale(1.15f);
	_backGround->Render(Vector2(_backGround->GetWidth() / 2, -200));

	_player->render();

	ImageManager::GetInstance()->FindImage("shop_mid")->SetScale(1.15f);
	ImageManager::GetInstance()->FindImage("shop_mid")->Render(Vector2(WINSIZEX/2 - 55, 213));

	ImageManager::GetInstance()->FindImage("shop_first")->SetScale(1.15f);
	ImageManager::GetInstance()->FindImage("shop_first")->Render(Vector2(WINSIZEX / 2 - 65, 762));
}

void shopStage::update()
{
	_player->update();
}

void shopStage::release()
{

}