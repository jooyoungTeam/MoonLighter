#include "stdafx.h"
#include "stageManager.h"
#include "tile.h"
#include "title.h"
HRESULT stageManager::init()
{
	_player = new player;
	_player->init(981, 442);
	INVENTORY->init();
	_ui = new UI;
	_ui->init();
	_itemMg = new itemManager;
	_town = new townStage;
	_boss = new bossStage;
	_shop = new shopStage;
	_dungeon = new dungeonStage;
	_dungeon2 = new dungeonStage2;
	_spa = new spaStage;
	_enterence = new enterenceStage;

	_ui->getPlayerMemoryAddressLink(_player);
	INVENTORY->getPlayerMemoryAddressLink(_player);
	_dungeon->setPlayerLink(_player);
	_dungeon->setItemManagerLink(_itemMg);
	_dungeon2->setPlayerLink(_player);
	_dungeon2->setItemManagerLink(_itemMg);
	_spa->setPlayerLink(_player);
	_enterence->setPlayerLink(_player);
	_town->setPlayerLink(_player);
	_boss->setPlayerLink(_player);
	_boss->setUILink(_ui);
	_boss->setItemManagerLink(_itemMg);
	_shop->setPlayerLink(_player);

	addStage();

	return S_OK;
}

void stageManager::render()
{
	SCENEMANAGER->render();
	
	uiRender();
}

void stageManager::update()
{
	SCENEMANAGER->update();

	KEYANIMANAGER->update();

	uiUpdate();
	tempSceneChange();
}

void stageManager::release()
{
	SCENEMANAGER->release();
}

void stageManager::uiRender()
{
	if (SCENEMANAGER->getCurrentScene() != "≈∏¿Ã∆≤æ¿" && SCENEMANAGER->getCurrentScene() != "≈∏¿œæ¿")
	{
		if (!_town->getIsPotionShop())
		{
			_ui->render();
		}
		ImageManager::GetInstance()->FindImage("UI_gold")->Render(Vector2(0, 0));
		//µ∑¡÷∏”¥œ
		ImageManager::GetInstance()->FindImage("moneyBag")->FrameRender(Vector2(90, 88), 0, _ui->getMonveBagFrame());
		//º“¡ˆ±›
		D2DRenderer::GetInstance()->RenderText(100, 150, to_wstring(INVENTORY->getGold()), 20, D2DRenderer::DefaultBrush::White);

		_itemMg->render();
		if (INVENTORY->getIsInven()) INVENTORY->render();
	}
}

void stageManager::uiUpdate()
{
	if (SCENEMANAGER->getCurrentScene() != "≈∏¿Ã∆≤æ¿" && SCENEMANAGER->getCurrentScene() != "≈∏¿œæ¿")
	{
		if (INVENTORY->getIsInven()) INVENTORY->update();

		if (!_town->getIsPotionShop() && !INVENTORY->getIsInven() && KEYMANAGER->isOnceKeyDown('I'))
		{
			SOUNDMANAGER->play("openInven");
			INVENTORY->setIsInven(true);
			_ui->setUIScene(CURRENT_SCENE::INVENTORY_OPEN);
			INVENTORY->setState(INVEN_STATE::NOTE);
		}

		if (!_town->getIsPotionShop() && INVENTORY->getIsInven() && KEYMANAGER->isOnceKeyDown('I'))
		{
			INVENTORY->setIsInven(false);
			_ui->setUIScene(CURRENT_SCENE::TEMP);
			INVENTORY->closeInven();
		}

		if (KEYMANAGER->isOnceKeyDown('E'))
		{
			INVENTORY->usePotion();
		}

		if (_player->getDeadState())
		{
			if (INVENTORY->getInven()->item == nullptr) return;
			INVENTORY->putType();
			for (int i = 0; i < INVENTORY->getVType().size(); i++)
			{
				_itemMg->popItem(INVENTORY->getVType()[i], _player->getX(), _player->getY());
			}
			INVENTORY->popInven();
		}
		_itemMg->update(_player);
		_ui->update();		

		/*if (KEYMANAGER->isOnceKeyDown('Y'))
		{
			int count = RND->getInt(3);
			if (count == 0) _itemMg->setItem(ITEMBUNDLE::SLIME_RED, _player->getX(), _player->getY());
			if (count == 1) _itemMg->setItem(ITEMBUNDLE::SLIME_BLUE, _player->getX(), _player->getY());
			if (count == 2) _itemMg->setItem(ITEMBUNDLE::SLIME_YELLOW, _player->getX(), _player->getY());

		}*/
	}

}

void stageManager::tempSceneChange()
{
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		SCENEMANAGER->changeScene("≈∏¿œæ¿");
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		SCENEMANAGER->changeScene("∏∂¿ªæ¿");
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F3))
	{
		SCENEMANAGER->changeScene("¥¯¿¸æ¿");
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F4))
	{
		SCENEMANAGER->changeScene("º•æ¿");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F5))
	{
		SCENEMANAGER->changeScene("∫∏Ω∫æ¿");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F6))
	{
		SCENEMANAGER->changeScene("¥¯¿¸æ¿2");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F7))
	{
		SCENEMANAGER->changeScene("Ω∫∆ƒæ¿");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F8))
	{
		SCENEMANAGER->changeScene("¥¯¿¸¿‘±∏æ¿");
		_player->setPlayerPos(WINSIZEX / 2, WINSIZEY / 2);
	}
}

void stageManager::addStage()
{
	SCENEMANAGER->addScene("≈∏¿Ã∆≤æ¿", new title);
	SCENEMANAGER->addScene("≈∏¿œæ¿", new tile);
	SCENEMANAGER->addScene("º•æ¿", _shop);
	SCENEMANAGER->addScene("¥¯¿¸æ¿", _dungeon);
	SCENEMANAGER->addScene("∏∂¿ªæ¿", _town);
	SCENEMANAGER->addScene("∫∏Ω∫æ¿", _boss);
	SCENEMANAGER->addScene("¥¯¿¸æ¿2", _dungeon2);
	SCENEMANAGER->addScene("Ω∫∆ƒæ¿", _spa);
	SCENEMANAGER->addScene("¥¯¿¸¿‘±∏æ¿", _enterence);

	SCENEMANAGER->changeScene("≈∏¿Ã∆≤æ¿");
}
