#include "stdafx.h"
#include "dungeonStage2.h"
#include "itemManager.h"
#include "player.h"
HRESULT dungeonStage2::init()
{
	_mapImg = ImageManager::GetInstance()->AddImage("dungeon_background", L"Image/Map/dungeon_background.png");
	CAMERAMANAGER->settingCamera(0, 0, WINSIZEX, WINSIZEY, 0, 0, 1600 - WINSIZEX, 900 - WINSIZEY);

	_objectManager = new objectManager;
	loadMap();
	_enemy = new enemyManager;
	_enemy->setPlayerLink(_player);
	_enemy->setItemManagerLink(_itemManager);
	_enemy->setEnemy2(_unMoveTile);

	_enemy->init(_unMoveTile);

	CAMERAMANAGER->setXY(WINSIZEX / 2, WINSIZEY / 2);

	return S_OK;
}

void dungeonStage2::render()
{
	renderMap();
	_player->render();
	_enemy->render();

}

void dungeonStage2::update()
{
	CAMERAMANAGER->setXY(WINSIZEX / 2, WINSIZEY / 2);
	if (!INVENTORY->getIsInven())
	{
		_player->update();
		_player->tileCollision(_attribute, _tile, DUNTILEX);
		_enemy->update();
		if (_enemy->_getVEnemy().size() <= 0)
		{
			_objectManager->setIsDoorOpen(true);
			_attribute[_doorIndex[0]] = TP_ENTERENCE;
			_attribute[_doorIndex[1]] = TP_ENTERENCE;
		}
	}

}

void dungeonStage2::release()
{
	_itemManager->release();
}

void dungeonStage2::loadMap()
{
	HANDLE file;
	DWORD read;

	int _tileSize[2];
	int size[2];

	// ------------ Ÿ��

	file = CreateFile("dungeon2.map", GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tileSize, sizeof(int) * 2, &read, NULL);

	ReadFile(file, _tile, sizeof(tagTile) * DUNTILEX * DUNTILEY, &read, NULL);

	memset(_attribute, 0, sizeof(DWORD) * DUNTILEX * DUNTILEY);
	int index = 0;
	for (int i = 0; i < DUNTILEX * DUNTILEY; ++i)
	{
		if (_tile[i].terrain == TR_WALL || _tile[i].isColTile)
		{
			_attribute[i] |= ATTR_UNMOVE;
			_unMoveTile.push_back(PointMake(_tile[i].idX, _tile[i].idY));
		}
		if (_tile[i].pos == POS_ENTERENCE)
		{
			_attribute[i] |= ATTR_UNMOVE;	 // �� �������� Ÿ��
			_unMoveTile.push_back(PointMake(_tile[i].idX, _tile[i].idY));
			_doorIndex[index++] = i;
		}

	}

	CloseHandle(file);

	_objectManager->load(BUTTON_LOAD_DUNGEON,2);
}

void dungeonStage2::renderMap()
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

			if (_tile[index].terrain != TR_NONE && _tile[index].pos == POS_NONE)
			{
				Vector2 vec((_tile[index].rc.left + _tile[index].rc.right) * 0.5f, (_tile[index].rc.top + _tile[index].rc.bottom) * 0.5f);
				CAMERAMANAGER->frameRender(ImageManager::GetInstance()->FindImage("mapTiles"), vec.x, vec.y,
					_tile[index].terrainFrameX, _tile[index].terrainFrameY);
			}

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