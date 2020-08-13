#include "stdafx.h"
#include "stageManager.h"
#include "tile.h"
#include "title.h"
#include "shopStage.h"
#include "dungeonStage.h"
#include "townStage.h"
#include "bossStage.h"
HRESULT stageManager::init()
{
	_ui = new UI;
	_ui->init();
	_itemMg = new itemManager;
	INVENTORY->init();

	_player = new player;

	_ui->getPlayerMemoryAddressLink(_player);
	INVENTORY->getPlayerMemoryAddressLink(_player);

	SCENEMANAGER->addScene("Å¸ÀÌÆ²¾À", new title);

	SCENEMANAGER->addScene("Å¸ÀÏ¾À", new tile);
	SCENEMANAGER->addScene("¼¥¾À", new shopStage);
	SCENEMANAGER->addScene("´øÀü¾À", new dungeonStage);
	SCENEMANAGER->addScene("¸¶À»¾À", new townStage);
	SCENEMANAGER->addScene("º¸½º¾À", new bossStage);



	SCENEMANAGER->changeScene("Å¸ÀÌÆ²¾À");

	return S_OK;
}

void stageManager::render()
{
	SCENEMANAGER->render();
	//_ui->render();
	if (INVENTORY->getIsInven()) INVENTORY->render();
}


void stageManager::update()
{
	FloatRect _test;
	_test = RectMakePivot(Vector2(_ptMouse.x, _ptMouse.y), Vector2(50, 50), Pivot::Center);

	SCENEMANAGER->update();

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

	if (INVENTORY->getIsInven()) INVENTORY->update();

	if (KEYMANAGER->isOnceKeyDown('Y'))
	{
		_itemMg->setItem(ITEMTYPE::SLIME_RED, 200 + RND->getInt(50), 200 + RND->getInt(50));
	}

	if (KEYMANAGER->isOnceKeyDown('U'))
	{
		_itemMg->setItem(ITEMTYPE::BROKEN_SWORD, 200 + RND->getInt(50), 200 + RND->getInt(50));
	}

	if (KEYMANAGER->isOnceKeyDown('T'))
	{
		_itemMg->setItem(ITEMTYPE::POTION_S, 200 + RND->getInt(50), 200 + RND->getInt(50));
	}

	_itemMg->update();

	for (int i = 0; i < _itemMg->getVItem().size(); ++i)
	{
		if (_test.left - _itemMg->getVItem()[i]->getRc().left < 30 && _test.top - _itemMg->getVItem()[i]->getRc().top < 30)
		{
			INVENTORY->putItem(_itemMg->getVItem()[i]);
			_itemMg->erase(i);
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		SCENEMANAGER->changeScene("Å¸ÀÏ¾À");
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		KEYANIMANAGER->release();
		SCENEMANAGER->changeScene("¸¶À»¾À");
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F3))
	{
		KEYANIMANAGER->release();
		SCENEMANAGER->changeScene("´øÀü¾À");
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F4))
	{
		KEYANIMANAGER->release();
		SCENEMANAGER->changeScene("¼¥¾À");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F5))
	{
		KEYANIMANAGER->release();
		SCENEMANAGER->changeScene("º¸½º¾À");
	}
}

void stageManager::release()
{
	SCENEMANAGER->release();
}
