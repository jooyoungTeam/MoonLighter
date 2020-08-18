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

	_cellerFrameTimer = 0;
	_cellerIndex = _celler->GetMaxFrameX() - 1;

	return S_OK;
}

void shopStage::render()
{
	//CAMERAMANAGER->zOrderRender(_backGround, 0, 0, 1400, 1.f, 1.0f);
	CAMERAMANAGER->render(_backGround, 0, 0, 1.f, 1.0f);
	// ================================ 이 사이에 NPC, 플레이어 넣을것 ===================================

	_player->render();

	

	_npcM->render();

	for (int i = 0; i < 4; ++i)
	{
		if (_display[i].it != NULL)
			_display[i].it->cameraRender();

		CAMERAMANAGER->rectangle(_display[i].rc, D2D1::ColorF::Black, 1.f, 2.f);
	}

	// ================================ 이 사이에 NPC, 플레이어 넣을것 ===================================
	CAMERAMANAGER->render(ImageManager::GetInstance()->FindImage("shop_mid"), WINSIZEX / 2 + 17, 613, 1.15f, 1.0f);    
	CAMERAMANAGER->render(ImageManager::GetInstance()->FindImage("shop_first"), WINSIZEX / 2  + 2, 1162, 1.15f, 1.0f);
	CAMERAMANAGER->frameRender(ImageManager::GetInstance()->FindImage("shop_door"), WINSIZEX / 2 + 80, 1109, _doorIndex, 0 ,1.2f,1.f);

	CAMERAMANAGER->zOrderFrameRender(_celler, WINSIZEX / 2 + 160, 830,830, _cellerIndex, 0, 1.5, 1.f);

	CAMERAMANAGER->zOrderALLRender();
	//CAMERAMANAGER->frameRender(_celler, WINSIZEX / 2 + 160, 830, _cellerIndex,0,1.5,1.f);
	//CAMERAMANAGER->rectangle(_doorRC, D2D1::ColorF::Red, 1.f, 2.f);
	renderMap();

}

void shopStage::update()
{
	if (!INVENTORY->getIsInven())
	{
		_player->update();
		
		_npcM->update();

		for (int i = 0; i < 4; ++i)
		{
			if (_display[i].it != NULL)
			{
				_display[i].it->fieldUpdate();
			}
		}

		_cellerFrameTimer++;
		if (_cellerFrameTimer > 7)
		{
			if (_cellerIndex < _celler->GetMaxFrameX() - 1)
			{
				_cellerIndex++;
			}
			_cellerFrameTimer = 0;
		}
	}


	disPlayUpdate();
	
	npcProcess();
	
	CAMERAMANAGER->setX(_player->getX());
	CAMERAMANAGER->setY(_player->getY());
	
	doorUpdate();
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
	_display[0].init(Vector2(635, 870), NULL, 0, 0, false);
	_display[1].init(Vector2(635, 930), NULL, 0, 0, false);
	_display[2].init(Vector2(700, 870), NULL, 0, 0, false);
	_display[3].init(Vector2(700, 930), NULL, 0, 0, false);
}

void shopStage::disPlayUpdate()
{
	for (int i = 0; i < 4; ++i)
	{
		_display[i].count = INVENTORY->getShowCase()[i * 2].count;
		_display[i].it = INVENTORY->getShowCase()[i * 2].item;
		_display[i].settingPrice = INVENTORY->getShowCase()[i * 2].totalPrice;
		_display[i].rightPrice = INVENTORY->getShowCase()[i * 2].originalPrice;


		if (_display[i].it != NULL)
		{
			if(INVENTORY->getIsInven())
				_display[i].it->setItemPos(_display[i].pos.x, _display[i].pos.y);

			_display[i].isActive = true;
			_display[i].it->setShakeY(_display[i].pos.y);
		}
		else
		{
			_display[i].isActive = false;
		}

		RECT temp;
		for (int j = 0; j < _npcM->getVnpc().size(); ++j)
		{
			if(IntersectRect(&temp, &_display[i].rc.GetRect(), &_npcM->getVnpc()[j]->getNPCRect().GetRect()))
			{
				_display[i].isPeople = true;
				break;
			}
			
			if(j == _npcM->getVnpc().size()-1)
				_display[i].isPeople = false;
		}


		if (_display[i].isPeople)
		{
			cout << i << " 번째 : "<< "충돌 O" << endl;
		}
		if (!_display[i].isPeople)
		{
			cout << i << " 번째 : " << "충돌 X" << endl;
		}
	}
}

void shopStage::doorUpdate()
{
	if(KEYMANAGER->isOnceKeyDown('E'))
		_npcM->npcAdd(NPC_NOMAL, _unMoveTile);

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

			if(i == _npcM->getVnpc().size() - 1)
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
		if (_npcM->getVnpc()[i]->getIsCount())
		{
			// 팔았다는 카운터 애니메이션재생
			_cellerIndex = 0;
			_npcM->getVnpc()[i]->setIsCount(false);
		}

		for (int j = 0; j < 4; ++j)
		{
			if (_display[j].isPeople)
			{
				_npcM->getVnpc()[i]->setIsAnotherPerson(j, true);
			}
			else
			{
				_npcM->getVnpc()[i]->setIsAnotherPerson(j, false);
			}
		}

		// 선택한 아이템에 따라 넘겨줌
		if (_display[_npcM->getVnpc()[i]->getRndItem()].it != NULL)
		{
			switch (_npcM->getVnpc()[i]->getRndItem())
			{
			case 0:
				_npcM->getVnpc()[i]->setRightPrice(_display[0].rightPrice);
				_npcM->getVnpc()[i]->setSettingPrice(_display[0].settingPrice);
				break;

			case 1:
				_npcM->getVnpc()[i]->setRightPrice(_display[1].rightPrice);
				_npcM->getVnpc()[i]->setSettingPrice(_display[1].settingPrice);
				break;

			case 2:
				_npcM->getVnpc()[i]->setRightPrice(_display[2].rightPrice);
				_npcM->getVnpc()[i]->setSettingPrice(_display[2].settingPrice);
				break;

			case 3:
				_npcM->getVnpc()[i]->setRightPrice(_display[3].rightPrice);
				_npcM->getVnpc()[i]->setSettingPrice(_display[3].settingPrice);
				break;
			}
		}

		// 구매했을때
		if (_npcM->getVnpc()[i]->getIsBuy())
		{
			_npcM->getVnpc()[i]->setItem(_display[_npcM->getVnpc()[i]->getRndItem()].it->getType());
			INVENTORY->resetShowCase(_npcM->getVnpc()[i]->getRndItem() * 2);
		}
	}
}
