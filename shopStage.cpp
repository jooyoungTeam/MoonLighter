#include "stdafx.h"
#include "shopStage.h"

HRESULT shopStage::init()
{
	_backGround = ImageManager::GetInstance()->AddImage("shop_background", L"Image/Shop/shop_background.png");
	ImageManager::GetInstance()->AddImage("shop_mid", L"Image/Shop/shop_mid.png");
	ImageManager::GetInstance()->AddImage("shop_first", L"Image/Shop/shop_first.png");
	ImageManager::GetInstance()->AddFrameImage("shop_door", L"Image/Shop/shop_door.png",5,1);

	CAMERAMANAGER->settingCamera(0, 0, WINSIZEX, WINSIZEY, 0, 0, 1600 - WINSIZEX, 1400 - WINSIZEY);

	_player = new player;
	_player->init(WINSIZEX / 2 + 110, 400);

	_shopNPC = new shopNPC;
	_shopNPC->init();
		

	disPlaySet();

	_doorFrameTimer = 0;
	_doorIndex = 0;

	return S_OK;
}

void shopStage::render()
{
	CAMERAMANAGER->render(_backGround, _backGround->GetWidth() / 2, 200, 1.15f, 1.0f);
	// ================================ 이 사이에 NPC, 플레이어 넣을것 ===================================
	_player->render();



	if(_enterNPC)
		_shopNPC->render();

	for (int i = 0; i < 4; ++i)
	{
		if (_display[i].it != NULL)
			_display[i].it->cameraRender();
	}

	// ================================ 이 사이에 NPC, 플레이어 넣을것 ===================================
	CAMERAMANAGER->render(ImageManager::GetInstance()->FindImage("shop_mid"), WINSIZEX / 2 - 55, 613, 1.15f, 1.0f);    
	CAMERAMANAGER->render(ImageManager::GetInstance()->FindImage("shop_first"), WINSIZEX / 2 - 65, 1162, 1.15f, 1.0f);
	CAMERAMANAGER->frameRender(ImageManager::GetInstance()->FindImage("shop_door"), WINSIZEX / 2 + 10, 1109, _doorIndex, 0 ,1.2f,1.f);
}

void shopStage::update()
{
	_player->update();

	if(INVENTORY->getState() == INVEN_STATE::SHOP)
		disPlayUpdate();
	
	buyItem();

	for (int i = 0; i < 4; ++i)
	{
		if (_display[i].it != NULL)
		{
			_display[i].it->fieldUpdate();
		}
	}

	if(_enterNPC)
		_shopNPC->updadte();
	
	CAMERAMANAGER->setX(_player->getX());
	CAMERAMANAGER->setY(_player->getY());
	
	doorUpdate();
}

void shopStage::release()
{

}

void shopStage::disPlaySet()
{
	_display[0].init(Vector2(565, 870), NULL, 0, 0, false);
	_display[1].init(Vector2(565, 930), NULL, 0, 0, false);
	_display[2].init(Vector2(630, 870), NULL, 0, 0, false);
	_display[3].init(Vector2(630, 930), NULL, 0, 0, false);
}

void shopStage::disPlayUpdate()
{
	for (int i = 0; i < 4; ++i)
	{
		_display[i].count = INVENTORY->getShowCase()[i].count;
		_display[i].it = INVENTORY->getShowCase()[i].item;
		_display[i].settingPrice = INVENTORY->getShowCase()[i].price;

		if (_display[i].it != NULL)
			_display[i].it->setItemPos(_display[i].pos.x, _display[i].pos.y);
	}
}

void shopStage::doorUpdate()
{
	switch (_doorState)
	{
	case DOOR_CLOSE:
		if (KEYMANAGER->isOnceKeyDown('E'))
		{
			_doorState = DOOR_OPENING;
		}
		break;
	case DOOR_OPENING:
		_doorFrameTimer++;
		if (_doorFrameTimer > 5)
		{
			_doorIndex++;

			if (_doorIndex == 4)
				_doorState = DOOR_DELAY;

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
	case DOOR_DELAY:
		_enterNPC = true;
		_doorFrameTimer++;

		if (_doorFrameTimer > 130)
		{
			_doorState = DOOR_CLOSING;
			_doorFrameTimer = 0;
		}
		break;
	}
}

void shopStage::buyItem()
{
	if (_display[_shopNPC->getRndItem()].it != NULL)
	{
		switch (_shopNPC->getRndItem())
		{
		case 0:
			_shopNPC->setRightPrice(_display[0].it->getPrice());
			_shopNPC->setSettingPrice(_display[0].settingPrice);
			break;

		case 1:
			_shopNPC->setRightPrice(_display[1].it->getPrice());
			_shopNPC->setSettingPrice(_display[1].settingPrice);
			break;

		case 2:
			_shopNPC->setRightPrice(_display[2].it->getPrice());
			_shopNPC->setSettingPrice(_display[2].settingPrice);
			break;

		case 3:
			_shopNPC->setRightPrice(_display[3].it->getPrice());
			_shopNPC->setSettingPrice(_display[3].settingPrice);
			break;
		}
	}

	if (_shopNPC->getIsBuy())
	{
		_shopNPC->setItem(_display[_shopNPC->getRndItem()].it);
		_display[_shopNPC->getRndItem()].it = NULL;
	}
}
