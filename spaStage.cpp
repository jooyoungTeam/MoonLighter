#include "stdafx.h"
#include "spaStage.h"

#include "player.h"
HRESULT spaStage::init()
{
	_mapImg = ImageManager::GetInstance()->AddImage("dungeon_background", L"Image/Map/dungeon_background.png");
	CAMERAMANAGER->settingCamera(0, 0, WINSIZEX, WINSIZEY, 0, 0, 1600 - WINSIZEX, 900 - WINSIZEY);

	_objectManager = new objectManager;
	_objectManager->setIsDoorOpen(true);
	loadMap();

	CAMERAMANAGER->setXY(WINSIZEX / 2, WINSIZEY / 2);



	return S_OK;
}

void spaStage::render()
{
	renderMap();
	_player->render();

}

void spaStage::update()
{
	CAMERAMANAGER->setXY(WINSIZEX / 2, WINSIZEY / 2);
	if (!INVENTORY->getIsInven())
	{
		_player->update();
		_player->tileCollision(_attribute, _tile, DUNTILEX);
		//_enemy->update();
	}
	POINT p;
	p.x = _player->getX();
	p.y = _player->getY();
	if (_objectManager->isPlayerSpaIn(p))
	{
		if (!SOUNDMANAGER->isPlaySound("healing"))
		SOUNDMANAGER->play("healing", 1.0f);
		_player->setTransform(true);
		_spaCount++;
		if (_spaCount > 1)
		{
			_player->setPlayerCurrentHp(_player->getplayerCurrentHp() + 1);
			_spaCount = 0;
			if (_player->getPlayerMaxHp() <= _player->getplayerCurrentHp())
			{
				_player->setPlayerCurrentHp(_player->getPlayerMaxHp());
			}
		}

	}
	else
	{
		_player->setTransform(false);
	}
}

void spaStage::release()
{

}

void spaStage::loadMap()
{
	HANDLE file;
	DWORD read;

	int _tileSize[2];
	int size[2];

	// ------------ 타일

	file = CreateFile("spa.map", GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tileSize, sizeof(int) * 2, &read, NULL);

	ReadFile(file, _tile, sizeof(tagTile) * DUNTILEX * DUNTILEY, &read, NULL);

	memset(_attribute, 0, sizeof(DWORD) * DUNTILEX * DUNTILEY);
	for (int i = 0; i < DUNTILEX * DUNTILEY; ++i)
	{
		if (_tile[i].terrain == TR_WALL || _tile[i].isColTile) _attribute[i] |= ATTR_UNMOVE;
		if (_tile[i].pos == POS_ENTERENCE) _attribute[i] |= TP_ENTERENCE;	 // 씬 변경해줄 타일
		if (_tile[i].pos == POS_BOSS)      _attribute[i] |= TP_BOSS;	 // 씬 변경해줄 타일
	}

	CloseHandle(file);

	_objectManager->load(BUTTON_LOAD_DUNGEON, 3);
}

void spaStage::renderMap()
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


	_objectManager->objectRender();
	if (KEYMANAGER->isToggleKey('V'))
	{

		float x = WINSIZEX / 2 -10;
		float y = WINSIZEY / 2;
		float r = 180;
		CAMERAMANAGER->fillEllipse(x, y, r, D2D1::ColorF::Red, 0.5f);
	}
}