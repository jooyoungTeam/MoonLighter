#include "stdafx.h"
#include "shopStage.h"
#include "player.h"

HRESULT shopStage::init()
{
	_backGround = ImageManager::GetInstance()->AddImage("shop_background", L"Image/Shop/shop_background.png");
	ImageManager::GetInstance()->AddImage("shop_mid", L"Image/Shop/shop_mid.png");
	ImageManager::GetInstance()->AddImage("shop_first", L"Image/Shop/shop_first.png");
	ImageManager::GetInstance()->AddFrameImage("shop_door", L"Image/Shop/shop_door.png",5,1);
	_celler = ImageManager::GetInstance()->AddFrameImage("shop_cellere", L"Image/Shop/celler.png", 66, 1);

	CAMERAMANAGER->settingCamera(0, 0, WINSIZEX, WINSIZEY, 0, 0, 1600 - WINSIZEX, 1400 - WINSIZEY);
	loadMap();

	_npcM = new shopNPCManager;
	_npcM->init();
	
	_doorRC = RectMakePivot(Vector2(WINSIZEX / 2 + 80, 1100), Vector2(50, 100), Pivot::Center);

	disPlaySet();

	_doorFrameTimer = 0;
	_doorIndex = 0;
	_doorState = DOOR_CLOSE;
	_cellerFrameTimer = 0;
	_cellerIndex = _celler->GetMaxFrameX() - 1;

	_interactionRC = RectMakePivot(Vector2(670,920),Vector2(200,200),Pivot::Center);

	return S_OK;
}

void shopStage::render()
{
	//CAMERAMANAGER->zOrderRender(_backGround, 0, 0, 1400, 1.f, 1.0f);
	CAMERAMANAGER->render(_backGround, 0, 0, 1.f, 1.0f);
	// ================================ 이 사이에 NPC, 플레이어 넣을것 ===================================

	_player->render();
	_npcM->render();
	_display1->render();
	_display2->render();
	_display3->render();
	_display4->render();

	// ================================ 이 사이에 NPC, 플레이어 넣을것 ===================================
	//CAMERAMANAGER->rectangle(_interactionRC, D2D1::ColorF::AliceBlue, 1.f, 2.f);
	CAMERAMANAGER->zOrderRender(ImageManager::GetInstance()->FindImage("shop_mid"), WINSIZEX / 2 + 8, 605,800, 1.f, 1.3f);    
	CAMERAMANAGER->zOrderRender(ImageManager::GetInstance()->FindImage("shop_first"), WINSIZEX / 2 - 2, 1158,1300, 1.f, 1.3f);
	CAMERAMANAGER->frameRender(ImageManager::GetInstance()->FindImage("shop_door"), WINSIZEX / 2 + 80, 1109, _doorIndex, 0 ,1.2f,1.f);

	CAMERAMANAGER->zOrderFrameRender(_celler, WINSIZEX / 2 + 160, 830,830, _cellerIndex, 0,2.f,1.f);

	if (isCollision(_interactionRC.GetRect(), _player->getPlayerRc().GetRect()))
	{
		CAMERAMANAGER->render(ImageManager::GetInstance()->FindImage("J"), _player->getX() - 32, _player->getY() - 100, 1.f);
	}

	CAMERAMANAGER->zOrderALLRender();
	//CAMERAMANAGER->frameRender(_celler, WINSIZEX / 2 + 160, 830, _cellerIndex,0,1.5,1.f);
	//CAMERAMANAGER->rectangle(_doorRC, D2D1::ColorF::Red, 1.f, 2.f);
	renderMap();

}

void shopStage::update()
{
	RECT rc;
	if (IntersectRect(&rc, &_interactionRC.GetRect(), &_player->getPlayerRc().GetRect()) && !INVENTORY->getIsInven())
	{
		if (KEYMANAGER->isOnceKeyDown('J'))
		{
			INVENTORY->setIsInven(true);
			INVENTORY->setState(INVEN_STATE::SHOP);
		}
	}

	if (!INVENTORY->getIsInven())
	{
		if (_npcM->getVnpc().size() > 2)
		{
			_isMaxNpc = true;
		}
		else
		{
			_isMaxNpc = false;
		}

		if (!_isMaxNpc)
		{
			_npcAddCount++;

			if (_npcAddCount > 400)
			{
				int rendType = RND->getInt(3);

				switch (rendType)
				{
				case 0:
					_npcM->npcAdd(NPC_NOMAL, _unMoveTile);
					break;

				case 1:
					_npcM->npcAdd(NPC_HERO, _unMoveTile);
					break;

				case 2:
					_npcM->npcAdd(NPC_RICH, _unMoveTile);
					break;
				}

				_npcAddCount = 0;
			}
		}

		_player->update();
		_player->tileCollision(_attribute, _tile, SHOPTILEX);
		_npcM->update();
		npcProcess();
		doorUpdate();
		disPlayUpdate();

		_cellerFrameTimer++;
		if (_cellerFrameTimer > 3)
		{
			if (_cellerIndex < _celler->GetMaxFrameX() - 1)
			{
				_cellerIndex++;
				_isCeller = true;
			}
			else
			{
				_isCeller = false;
			}
			_cellerFrameTimer = 0;
		}
	}

	
	CAMERAMANAGER->setX(_player->getX());
	CAMERAMANAGER->setY(_player->getY());
	
}

void shopStage::release()
{
	_npcM->release();
}

void shopStage::loadMap()
{
	
	HANDLE file;
	DWORD read;

	int _tileSize[2];
	int size[2];

	// ------------ 타일

	file = CreateFile("shop.map", GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	
	ReadFile(file, _tileSize, sizeof(int) * 2, &read, NULL);

	ReadFile(file, _tile, sizeof(tagTile) * SHOPTILEX * SHOPTILEY, &read, NULL);

	memset(_attribute, 0, sizeof(DWORD) * SHOPTILEX * SHOPTILEY);
	for (int i = 0; i < SHOPTILEX * SHOPTILEY; ++i)
	{
		if (_tile[i].terrain == TR_WALL || _tile[i].isColTile)
		{
			_attribute[i] |= ATTR_UNMOVE;

			_unMoveTile.push_back(PointMake(_tile[i].idX, _tile[i].idY));
		}
		if (_tile[i].pos == POS_TOWN)      _attribute[i] |= TP_TOWN;         // 씬 변경해줄 타일
	}

	CloseHandle(file);
}

void shopStage::renderMap()
{
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 33; j++)
		{
			int cullX = CAMERAMANAGER->getLeft() / TILESIZE;
			int cullY = CAMERAMANAGER->getTop() / TILESIZE;
			int index = (i + cullY) * SHOPTILEX + (j + cullX);
			if (index >= SHOPTILEX * SHOPTILEY)
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

}

void shopStage::disPlaySet()
{
	_display1 = new display;
	_display1->init(0, Vector2(635, 870), NULL, 0, 0, false);

	_display2 = new display;
	_display2->init(1, Vector2(635, 930), NULL, 0, 0, false);

	_display3 = new display;
	_display3->init(2, Vector2(700, 870), NULL, 0, 0, false);

	_display4 = new display;
	_display4->init(3, Vector2(700, 930), NULL, 0, 0, false);
}

void shopStage::disPlayUpdate()
{
	_display1->update();
	_display2->update();
	_display3->update();
	_display4->update();
}

void shopStage::doorUpdate()
{
	switch (_doorState)
	{
	case DOOR_CLOSE:
		RECT temp;
		for (int i = 0; i < _npcM->getVnpc().size(); ++i)
		{
			if (IntersectRect(&temp, &_doorRC.GetRect(), &_npcM->getVnpc()[i]->getNPCRect().GetRect()))
			{
				_doorState = DOOR_OPENING;
			}
		}
		break;
	case DOOR_OPEN:
		if(_npcM->getVnpc().size() == 0) _doorState = DOOR_CLOSING;

		for (int i = 0; i < _npcM->getVnpc().size(); ++i)
		{
			if (IntersectRect(&temp, &_doorRC.GetRect(), &_npcM->getVnpc()[i]->getNPCRect().GetRect()))
			{
				break;
			}

			if (i == _npcM->getVnpc().size() - 1)
				_doorState = DOOR_CLOSING;
		}
		break;
	case DOOR_OPENING:
		_doorFrameTimer++;
		if (_doorFrameTimer > 5)
		{
			_doorIndex++;

			if (_doorIndex == 4)
				_doorState = DOOR_OPEN;

			_doorFrameTimer = 0;
		}
		break;
	case DOOR_CLOSING:
		_doorFrameTimer++;

		if (_doorFrameTimer > 5)
		{
			_doorIndex--;

			if (_doorIndex == 0)
				_doorState = DOOR_CLOSE;

			_doorFrameTimer = 0;
		}
		break;
	}
}

void shopStage::npcProcess()
{
	for (int i = 0; i < _npcM->getVnpc().size(); ++i)
	{
		// 카운터에 도착하면
		if (_npcM->getVnpc()[i]->getIsCount() && !_isCeller)
		{
			// 팔았다는 카운터 애니메이션재생
			_cellerIndex = 0;
			_npcM->getVnpc()[i]->setIsCount(false);
		}
	}
}

void shopStage::npcSet()
{

}
