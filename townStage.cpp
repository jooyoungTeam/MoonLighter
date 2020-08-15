#include "stdafx.h"
#include "townStage.h"

HRESULT townStage::init()
{
	_mapImg = ImageManager::GetInstance()->AddImage("townMap", L"Image/Map/townMap.png");
	_tileClass = new tile;
	_tileClass->init();
	loadMap();
	CAMERAMANAGER->settingCamera(0, 0, WINSIZEX, WINSIZEY, 0, 0, (_mapImg->GetSize().x) - WINSIZEX, _mapImg->GetSize().y - WINSIZEY);
	_player = new player;
	_player->init(500, 500);
	return S_OK;
}

void townStage::update()
{
	if (!INVENTORY->getIsInven())
	{
		_player->update();
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

	// ------------ 타일

	file = CreateFile("townMap.map", GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tileSize, sizeof(int) * 2, &read, NULL);

	ReadFile(file, _tile, sizeof(tagTile) * 60 * 49, &read, NULL);

	ReadFile(file, size, sizeof(int) * 2, &read, NULL);
	// ------------ 오브젝트		
	tagObject* temp = new tagObject[size[1]];
	ReadFile(file, temp, sizeof(tagObject) * size[1], &read, NULL);
	for (int i = 0; i < size[1]; i++)
	{
		_vObject.push_back(temp[i]);
	}

	memset(_townAttribute, 0, sizeof(DWORD) * 60 * 49);
	for (int i = 0; i < 60 * 49; ++i)
	{
		if (_tile[i].terrain == TR_WALL || _tile[i].isColTile) _townAttribute[i] |= ATTR_UNMOVE;
	}

	CloseHandle(file);

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
			int index = (i + cullY) * 60 + (j + cullX);
			if (index >= 60 * 49)
				continue;

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
		}
		//CAMERAMANAGER->render(_object[i]->img, _object[i]->rc.left, _object[i]->rc.top, 0.4f);
		//CAMERAMANAGER->rectangle(_object[i]->rc, D2D1::ColorF::LimeGreen, 1.0f, 5);
	}
	CAMERAMANAGER->zOrderALLRender();


}
