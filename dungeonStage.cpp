#include "stdafx.h"
#include "dungeonStage.h"

HRESULT dungeonStage::init()
{
	CAMERAMANAGER->settingCamera(0, 0, WINSIZEX, WINSIZEY, 0, 0, 1600 - WINSIZEX, 900 - WINSIZEY);
	ImageManager::GetInstance()->AddImage("dungeonBackground", L"Image/map/dungeon_background.png");

	return S_OK;
}

void dungeonStage::render()
{

	CAMERAMANAGER->render(ImageManager::GetInstance()->FindImage("dungeonBackground"), 0, 0);
}

void dungeonStage::update()
{
}

void dungeonStage::release()
{
}
