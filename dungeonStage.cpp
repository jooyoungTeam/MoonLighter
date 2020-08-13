#include "stdafx.h"
#include "dungeonStage.h"

HRESULT dungeonStage::init()
{
	CAMERAMANAGER->settingCamera(0, 0, WINSIZEX, WINSIZEY, 0, 0, 1600 - WINSIZEX, 900 - WINSIZEY);
	//ImageManager::GetInstance()->AddImage("dungeonBackground", L"Image/map/dungeon_background.png");
	_tile = new tile;
	_tile->imageLoad();

	_player = new player;
	_player->init(500, 500);
	//_enemy = new enemyManager;
	//_enemy->setPlayerLink(_player);
	//_enemy->init();


	//loadDungeonMap();
	


	return S_OK;
}

void dungeonStage::render()
{
	renderDungeonMap();
	//CAMERAMANAGER->render(ImageManager::GetInstance()->FindImage("dungeonBackground"), 0, 0);
	_player->render();
	//_enemy->render();

	//D2DRenderer::GetInstance()->DrawRectangle(_rc, D2DRenderer::DefaultBrush::Black, 1.f);
}

void dungeonStage::update()
{
	_player->update();
	//_enemy->update();

	//CAMERAMANAGER->setX();
	//CAMERAMANAGER->
	if (!INVENTORY->getIsInven())
	{
		_player->update();
		_enemy->update();

	}
	//_rc = RectMakePivot(Vector2(_x, _y), Vector2(50, 50), Pivot::Center);

}

void dungeonStage::release()
{

}

void dungeonStage::loadDungeonMap()
{
	HANDLE file;
	DWORD read;

	file = CreateFile("dungeonMap.map", GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _dungeonTiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL); //32 * 18 ==>> 1600 x 900 ªÁ¿Ã¡Ó

	memset(_dungeonAttribute, 0, sizeof(DWORD) * TILEX * TILEY);

	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		if (_dungeonTiles[i].terrain == TR_WALL) _dungeonAttribute[i] |= ATTR_UNMOVE;
	}

	CloseHandle(file);
}

void dungeonStage::renderDungeonMap()
{
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 33; j++)
		{
			int cullX = CAMERAMANAGER->getLeft() / TILESIZE;
			int cullY = CAMERAMANAGER->getTop() / TILESIZE;

			int index = (i + cullY) * TILEX + (j + cullX);

			if (_dungeonTiles[index].terrain != TR_NONE)
			{
				Vector2 vec((_dungeonTiles[index].rc.left + _dungeonTiles[index].rc.right) * 0.5f, (_dungeonTiles[index].rc.top + _dungeonTiles[index].rc.bottom) * 0.5f);

				CAMERAMANAGER->frameRender(ImageManager::GetInstance()->FindImage("mapTiles"), vec.x, vec.y, _dungeonTiles[index].terrainFrameX, _dungeonTiles[index].terrainFrameY);

				//CAMERAMANAGER->rectangle(_dungeonTiles[index].rc, D2D1::ColorF::Black, 1.0f);

				/*	char str2[10];
					sprintf_s(str2, "(%d,%d)", _dungeonTiles[index].idX, _dungeonTiles[index].idY);

					string tempStr = str2;

					wstring str;
					str.assign(tempStr.begin(), tempStr.end());

					D2DRenderer::GetInstance()->RenderText(_dungeonTiles[index].rc.left, _dungeonTiles[index].rc.top, str, 15, D2DRenderer::DefaultBrush::White);*/
			}


		}
	}
}