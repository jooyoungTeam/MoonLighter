#include "stdafx.h"
#include "enterenceStage.h"

#include "player.h"
HRESULT enterenceStage::init()
{
	_mapImg = ImageManager::GetInstance()->AddImage("dungeon_background", L"Image/Map/dungeon_background.png");
	CAMERAMANAGER->settingCamera(0, 0, WINSIZEX, WINSIZEY, 0, 0, 1600 - WINSIZEX, 900 - WINSIZEY);

	_objectManager = new objectManager;
	_objectManager->setIsDoorOpen(true);
	loadMap();

	CAMERAMANAGER->setXY(WINSIZEX / 2, WINSIZEY / 2);



	return S_OK;
}

void enterenceStage::render()
{
	renderMap();
	_player->render();

}

void enterenceStage::update()
{

	CAMERAMANAGER->setXY(WINSIZEX / 2, WINSIZEY / 2);
	if (!INVENTORY->getIsInven())
	{
		_player->update();
		_player->tileCollision(_attribute, _tile, DUNTILEX);
		//_enemy->update();
	}

}

void enterenceStage::release()
{

}

void enterenceStage::loadMap()
{
	HANDLE file;
	DWORD read;

	int _tileSize[2];
	int size[2];

	// ------------ Ÿ��

	file = CreateFile("dungeonEnterence.map", GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tileSize, sizeof(int) * 2, &read, NULL);

	ReadFile(file, _tile, sizeof(tagTile) * DUNTILEX * DUNTILEY, &read, NULL);

	memset(_attribute, 0, sizeof(DWORD) * DUNTILEX * DUNTILEY);
	for (int i = 0; i < DUNTILEX * DUNTILEY; ++i)
	{
		if (_tile[i].terrain == TR_WALL || _tile[i].isColTile) _attribute[i] |= ATTR_UNMOVE;
		if (_tile[i].pos == POS_TOWN) _attribute[i] = TP_TOWN;	 // �� �������� Ÿ��
		if (_tile[i].pos == POS_DUN1) _attribute[i] = TP_DUN1;	 // �� �������� Ÿ��
		if (_tile[i].pos == POS_DUN2) _attribute[i] = TP_DUN2;	 // �� �������� Ÿ��
		if (_tile[i].pos == POS_SPA)  _attribute[i] = TP_SPA;	 // �� �������� Ÿ��
	}

	CloseHandle(file);

	_objectManager->load(BUTTON_LOAD_ENTERENCE, 0);
}

void enterenceStage::renderMap()
{
	CAMERAMANAGER->render(_mapImg, 0, 0, 1);
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 33; j++)
		{
			int cullX = CAMERAMANAGER->getLeft() / TILESIZE;
			int cullY = CAMERAMANAGER->getTop() / TILESIZE;
			int index = (i + cullY) * 32 + (j + cullX);
			if (index >= 32 * 18)
				continue;

			if (KEYMANAGER->isToggleKey('V'))
			{
				CAMERAMANAGER->rectangle(_tile[index].rc, D2D1::ColorF::Black, 1);
				if (_tile[index].isColTile)
				{
					CAMERAMANAGER->fillRectangle(_tile[index].rc, D2D1::ColorF::Red, 0.5f);
				}
				if (_tile[index].pos != POS_NONE)
				{
					Vector2 vec((_tile[index].rc.left + _tile[index].rc.right) * 0.5f, (_tile[index].rc.top + _tile[index].rc.bottom) * 0.5f);

					CAMERAMANAGER->frameRender(ImageManager::GetInstance()->FindImage("mapTiles"), vec.x, vec.y, _tile[index].terrainFrameX, _tile[index].terrainFrameY);
				}
			}
		}
	}


	_objectManager->objectRender();
}