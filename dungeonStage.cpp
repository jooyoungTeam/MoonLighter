#include "stdafx.h"
#include "dungeonStage.h"

HRESULT dungeonStage::init()
{
	CAMERAMANAGER->settingCamera(0, 0, WINSIZEX, WINSIZEY, 0, 0, 1600 - WINSIZEX, 900 - WINSIZEY);
	ImageManager::GetInstance()->AddImage("dungeonBackground", L"Image/map/dungeon_background.png");

	_enemy = new enemyManager;
	_enemy->init();

	


	return S_OK;
}

void dungeonStage::render()
{

	CAMERAMANAGER->render(ImageManager::GetInstance()->FindImage("dungeonBackground"), 0, 0);
	_enemy->render();

	//D2DRenderer::GetInstance()->DrawRectangle(_rc, D2DRenderer::DefaultBrush::Black, 1.f);
}

void dungeonStage::update()
{
	_enemy->update();
	//_rc = RectMakePivot(Vector2(_x, _y), Vector2(50, 50), Pivot::Center);

}

void dungeonStage::release()
{

}
