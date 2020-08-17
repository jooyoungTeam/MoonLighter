#include "stdafx.h"
#include "townStage.h"
#include "player.h"
HRESULT townStage::init()
{
	_mapImg = ImageManager::GetInstance()->AddImage("townMap", L"Image/Map/townMap.png");
	_objectManager = new objectManager;
	_objectManager->init();
	
	CAMERAMANAGER->settingCamera(0, 0, WINSIZEX, WINSIZEY, 0, 0, _mapImg->GetSize().x - WINSIZEX, _mapImg->GetSize().y - WINSIZEY);
	loadMap();
	return S_OK;
}

void townStage::update()
{
	if (!INVENTORY->getIsInven())
	{
		_player->update();
		_player->tileCollision(_townAttribute, _tile);
	}
	CAMERAMANAGER->setXY(_player->getX(), _player->getY());
}

void townStage::render()
{
	mapToolRender();

	_player->render();
}

void townStage::release()
{
}
void townStage::loadMap()
{
	HANDLE file;
	DWORD read;

	int _tileSize[2];
	int size[2];

	// ------------ ≈∏¿œ

	file = CreateFile("townMap.map", GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tileSize, sizeof(int) * 2, &read, NULL);

	ReadFile(file, _tile, sizeof(tagTile) * TOWNTILEX * TOWNTILEY, &read, NULL);

	memset(_townAttribute, 0, sizeof(DWORD) * TOWNTILEX * TOWNTILEY);
	for (int i = 0; i < TOWNTILEX * TOWNTILEY; ++i)
	{
		if (_tile[i].terrain == TR_WALL || _tile[i].isColTile) _townAttribute[i] |= ATTR_UNMOVE;
	}

	CloseHandle(file);

	_objectManager->load(BUTTON_LOAD_TOWN);
}


void townStage::mapToolRender()
{
	CAMERAMANAGER->render(_mapImg, 0, 0, 1);
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 33; j++)
		{
			int cullX = CAMERAMANAGER->getLeft() / TILESIZE;
			int cullY = CAMERAMANAGER->getTop() / TILESIZE;
			int index = (i + cullY) * TOWNTILEX + (j + cullX);
			if (index >= TOWNTILEX * TOWNTILEY)
				continue;

			if (KEYMANAGER->isToggleKey('V'))
			{
				POINT pos;
				pos.x = _player->getShadowX();
				pos.y = _player->getShadowY();
				if (PtInRect(&_tile[index].rc, pos))
				{
					CAMERAMANAGER->fillRectangle(_tile[index].rc, D2D1::ColorF::White, 1);
				}
				else
				{
					CAMERAMANAGER->rectangle(_tile[index].rc, D2D1::ColorF::Black, 1);
				}
				if (_tile[index].isColTile)
				{
					CAMERAMANAGER->fillRectangle(_tile[index].rc, D2D1::ColorF::Red, 0.5f);
				}
			}
		}
	}

	_objectManager->objectRender();
}
