#include "stdafx.h"
#include "shopStage.h"

HRESULT shopStage::init()
{
	CAMERAMANAGER->settingCamera(0, 0, WINSIZEX, WINSIZEY, 0, 0, 2000 - WINSIZEX, 2056 - WINSIZEY);
	ImageManager::GetInstance()->AddImage("shopBackground", L"Image/map/shop_background.png");

	CAMERAMANAGER->setX(1300);
	CAMERAMANAGER->setY(700);
	return S_OK;
}

void shopStage::render()
{
	CAMERAMANAGER->render(ImageManager::GetInstance()->FindImage("shopBackground"),0,0);
}

void shopStage::update()
{
}

void shopStage::release()
{
}
