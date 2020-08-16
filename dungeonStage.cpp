#include "stdafx.h"
#include "dungeonStage.h"
#include "player.h"
HRESULT dungeonStage::init()
{
	CAMERAMANAGER->settingCamera(0, 0, WINSIZEX, WINSIZEY, 0, 0, 1600 - WINSIZEX, 900 - WINSIZEY);
	//ImageManager::GetInstance()->AddImage("dungeonBackground", L"Image/map/dungeon_background.png");
	_tileClass = new tile;
	_tileClass->init();
	loadDungeonMap();
	_player->init(500, 500);
	//_enemy = new enemyManager;
	//_enemy->setPlayerLink(_player);
	//_enemy->init();

	CAMERAMANAGER->setXY(WINSIZEX / 2, WINSIZEY / 2);
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

	CAMERAMANAGER->setXY(WINSIZEX / 2, WINSIZEY / 2);
	if (!INVENTORY->getIsInven())
	{
		_player->update();
		//_enemy->update();
	}

}

void dungeonStage::release()
{

}

void dungeonStage::loadDungeonMap()
{
	HANDLE file;
	DWORD read;

	int _tileSize[2];
	int size[2];

	// ------------ 타일

	file = CreateFile("dungeon3.map", GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tileSize, sizeof(int) * 2, &read, NULL);

	ReadFile(file, _tile, sizeof(tagTile) * 32 * 18, &read, NULL);

	ReadFile(file, size, sizeof(int) * 2, &read, NULL);
	// ------------ 오브젝트		
	tagObject* temp = new tagObject[size[1]];
	ReadFile(file, temp, sizeof(tagObject) * size[1], &read, NULL);
	for (int i = 0; i < size[1]; i++)
	{
		_vObject.push_back(temp[i]);
	}

	memset(_attribute, 0, sizeof(DWORD) * 32 * 18);
	for (int i = 0; i < 32 * 18; ++i)
	{
		if (_tile[i].terrain == TR_WALL || _tile[i].isColTile) _attribute[i] |= ATTR_UNMOVE;
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
			int index = (i + cullY) * 32 + (j + cullX);
			if (index >= 32 * 18)
				continue;
			if (_tile[index].terrain != TR_NONE)
			{
				Vector2 vec((_tile[index].rc.left + _tile[index].rc.right) * 0.5f, (_tile[index].rc.top + _tile[index].rc.bottom) * 0.5f);
				CAMERAMANAGER->frameRender(ImageManager::GetInstance()->FindImage("mapTiles"), vec.x, vec.y, _tile[index].terrainFrameX, _tile[index].terrainFrameY);
			}
			if (KEYMANAGER->isToggleKey('V'))
			{
				CAMERAMANAGER->rectangle(_tile[index].rc, D2D1::ColorF::Black, 1);
				if (_tile[index].isColTile)
				{
					CAMERAMANAGER->fillRectangle(_tile[index].rc, D2D1::ColorF::Red, 0.5f);
				}
			}
		}
	}


	for (int i = 0; i < _vObject.size(); i++) // 오브젝트들 렌더
	{
		if (_vObject[i].isFrameRender)
		{
			CAMERAMANAGER->zOrderFrameRender(_tileClass->findImg(_vObject[i].type, _vObject[i].imgNumber), (_vObject[i].rc.left + _vObject[i].rc.right) * 0.5f, (_vObject[i].rc.top + _vObject[i].rc.bottom) * 0.5f,
				_vObject[i].rc.bottom, _vObject[i].frameX, 0, _vObject[i].scale, 1);

			_vObject[i].count++;
			int frameCount;
			_vObject[i].type == OBJ_NPC ? frameCount = 5 : frameCount = 10;
			if (_vObject[i].count % frameCount == 0)
			{
				_vObject[i].count = 0;
				_vObject[i].frameX++;

				if (_tileClass->findImg(_vObject[i].type, _vObject[i].imgNumber)->GetMaxFrameX() <= _vObject[i].frameX)
				{
					_vObject[i].frameX = 0;
				}
			}

		}
		else
		{
			CAMERAMANAGER->zOrderRender(_tileClass->findImg(_vObject[i].type, _vObject[i].imgNumber), _vObject[i].rc.left, _vObject[i].rc.top, _vObject[i].rc.bottom, 1, _vObject[i].scale);
		};
	}
	CAMERAMANAGER->zOrderALLRender();


}