#include "stdafx.h"
#include "townStage.h"
#include "player.h"
HRESULT townStage::init()
{
	_mapImg = ImageManager::GetInstance()->AddImage("townMap", L"Image/Map/townMap.png");

	_objectManager = new objectManager;
	_objectManager->init();

	_potionShop = new potionCreate;
	_potionShop->init();

	CAMERAMANAGER->settingCamera(0, 0, WINSIZEX, WINSIZEY, 0, 0, _mapImg->GetSize().x - WINSIZEX, _mapImg->GetSize().y - WINSIZEY);
	loadMap();

	_miniMap = new miniMap;
    _miniMap->init(TOWNTILEX, TOWNTILEY);
	_miniMap->setImage(_mapImg);

	_potionShopRc = RectMakePivot(Vector2(550, (int)_mapImg->GetSize().y - 330), Vector2(200, 200), Pivot::Center);

	_isPotionShop = false;
	return S_OK;
}

void townStage::update()
{
	_miniMap->update();
	if (!INVENTORY->getIsInven() && !_isPotionShop)
	{
		_player->update();
		_player->tileCollision(_attribute, _tile, TOWNTILEX);
	}

	if (KEYMANAGER->isOnceKeyDown('J') && !INVENTORY->getIsInven())
	{
		if (!_isPotionShop)
		{
			_isPotionShop = true;
			_potionShop->setIsActive(true);
		}
		else
		{
			_isPotionShop = false;
			_potionShop->setIsActive(false);
		}
	}


	if (_isPotionShop)
	{
		_potionShop->update();
	}
	if (!_potionShop->getIsActive())
	{
		_isPotionShop = false;
		_potionShop->reset();
	}

	CAMERAMANAGER->setXY(_player->getX(), _player->getY());
}

void townStage::render()
{
	mapToolRender();
	_player->render();

	POINT pos;
	pos.x = _player->getX();
	pos.y = _player->getY();
	_miniMap->render(_objectManager, pos);

	if (_isPotionShop)
	{
		_potionShop->render();
	}
	
	CAMERAMANAGER->rectangle(_potionShopRc, D2D1::ColorF::AliceBlue, 1.f, 2.f);
}

void townStage::release()
{
	//_miniMap->release();
	_potionShop->release();
}
void townStage::loadMap()
{
	HANDLE file;
	DWORD read;

	int _tileSize[2];
	int size[2];
//		^	^
//	\	\ 0 0
//   \     ^ 
//	  \	   \ \
	// ------------ 타일

	file = CreateFile("townMap.map", GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tileSize, sizeof(int) * 2, &read, NULL);

	ReadFile(file, _tile, sizeof(tagTile) * TOWNTILEX * TOWNTILEY, &read, NULL);

	memset(_attribute, 0, sizeof(DWORD) * TOWNTILEX * TOWNTILEY);
	for (int i = 0; i < TOWNTILEX * TOWNTILEY; ++i)
	{
		if (_tile[i].terrain == TR_WALL || _tile[i].isColTile) _attribute[i] |= ATTR_UNMOVE;
		if (_tile[i].pos == POS_SHOP)      _attribute[i] = TP_SHOP;         // 씬 변경해줄 타일
		if (_tile[i].pos == POS_ENTERENCE) _attribute[i] = TP_ENTERENCE;	 // 씬 변경해줄 타일
	}

	CloseHandle(file);
	_objectManager->load(BUTTON_LOAD_TOWN,0);
}


void townStage::mapToolRender()
{
	CAMERAMANAGER->render(_mapImg, 0, 0, 1);

	_objectManager->objectRender();
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

	if (KEYMANAGER->isToggleKey('V'))
	{
		for (int i = 0; i < 3; i++)
		{
			CAMERAMANAGER->fillRectangle(_tile[_player->getColTileIdx()[i]].rc, D2D1::ColorF::White, 1);
		}
	}
	
}
