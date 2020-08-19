#include "stdafx.h"
#include "stageManager.h"
#include "tile.h"
#include "title.h"
HRESULT stageManager::init()
{
	_player = new player;
	_player->init(981, 442);
	_ui = new UI;
	_ui->init();
	_itemMg = new itemManager;
	INVENTORY->init();

	_town = new townStage;
	_boss = new bossStage;
	_shop = new shopStage;
	_dungeon = new dungeonStage;
	_dungeon2 = new dungeonStage2;
	_spa = new spaStage;
	_enterence = new enterenceStage;

	_ui->getPlayerMemoryAddressLink(_player);
	//_ui->getBossMemoryAddressLink(_boss);
	INVENTORY->getPlayerMemoryAddressLink(_player);

	SCENEMANAGER->addScene("Å¸ÀÌÆ²¾À", new title);

	SCENEMANAGER->addScene("Å¸ÀÏ¾À", new tile);
	SCENEMANAGER->addScene("¼¥¾À", _shop);
	SCENEMANAGER->addScene("´øÀü¾À", _dungeon);
	SCENEMANAGER->addScene("¸¶À»¾À",	_town);
	SCENEMANAGER->addScene("º¸½º¾À", _boss);
	SCENEMANAGER->addScene("´øÀü¾À2", _dungeon2);
	SCENEMANAGER->addScene("½ºÆÄ¾À", _spa);
	SCENEMANAGER->addScene("´øÀüÀÔ±¸¾À", _enterence);



	_dungeon->setPlayerLink(_player);
	_dungeon2->setPlayerLink(_player);
	_spa->setPlayerLink(_player);
	_enterence->setPlayerLink(_player);
	_town->setPlayerLink(_player);
	_boss->setPlayerLink(_player);
	_shop->setPlayerLink(_player);
	SCENEMANAGER->changeScene("Å¸ÀÌÆ²¾À");

	return S_OK;
}

void stageManager::render()
{
	SCENEMANAGER->render();
	
	if (SCENEMANAGER->getCurrentScene() != "Å¸ÀÌÆ²¾À" && SCENEMANAGER->getCurrentScene() != "Å¸ÀÏ¾À")
	{
		_itemMg->render();
		_ui->render();
		if (INVENTORY->getIsInven()) INVENTORY->render(); 
	}
}

void stageManager::update()
{
	SCENEMANAGER->update();

	KEYANIMANAGER->update();

	if (SCENEMANAGER->getCurrentScene() != "Å¸ÀÌÆ²¾À" && SCENEMANAGER->getCurrentScene() != "Å¸ÀÏ¾À")
	{
		if (INVENTORY->getIsInven()) INVENTORY->update();

		if (!INVENTORY->getIsInven() && KEYMANAGER->isOnceKeyDown('I'))
		{
			INVENTORY->setIsInven(true);
			_ui->setUIScene(CURRENT_SCENE::INVENTORY_OPEN);
			INVENTORY->setState(INVEN_STATE::NOTE);
		}

		if (INVENTORY->getIsInven() && KEYMANAGER->isOnceKeyDown('I'))
		{
			INVENTORY->setIsInven(false);
			_ui->setUIScene(CURRENT_SCENE::TEMP);
			INVENTORY->closeInven();
		}

		if (!INVENTORY->getIsInven() && KEYMANAGER->isOnceKeyDown('O'))
		{
			INVENTORY->setIsInven(true);
			_ui->setUIScene(CURRENT_SCENE::SHOP_SALE);
			INVENTORY->setState(INVEN_STATE::SHOP);
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

		_itemMg->update();
		_ui->update();

		if (KEYMANAGER->isOnceKeyDown('Y'))
		{
			_itemMg->setItem(ITEMBUNDLE::SLIME_RED, WINSIZEX / 2, WINSIZEY / 2);
		}

		RECT temp;

		for (int i = 0; i < _itemMg->getVItem().size(); ++i)
		{
			_itemMg->getVItem()[i]->update();
			_itemMg->getVItem()[i]->follow(_player->getPlayerRc());

			if (IntersectRect(&temp, &_player->getPlayerRc().GetRect(), &_itemMg->getVItem()[i]->getRc().GetRect()))
			{
				if (INVENTORY->putItem(_itemMg->getVItem()[i]))
				{
					_itemMg->erase(i);
				}
				return;
			}
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		SCENEMANAGER->changeScene("Å¸ÀÏ¾À");
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		SCENEMANAGER->changeScene("¸¶À»¾À");
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F3))
	{
		SCENEMANAGER->changeScene("´øÀü¾À");
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F4))
	{
		SCENEMANAGER->changeScene("¼¥¾À");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F5))
	{
		SCENEMANAGER->changeScene("º¸½º¾À");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F6))
	{
		SCENEMANAGER->changeScene("´øÀü¾À2");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F7))
	{
		SCENEMANAGER->changeScene("½ºÆÄ¾À");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F8))
	{
		SCENEMANAGER->changeScene("´øÀüÀÔ±¸¾À");
		_player->setPlayerPos(WINSIZEX / 2, WINSIZEY / 2);
	}
}

void stageManager::release()
{
	SCENEMANAGER->release();
}
