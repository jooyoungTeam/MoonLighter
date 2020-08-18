#include "stdafx.h"
#include "stageManager.h"
#include "tile.h"
#include "title.h"
HRESULT stageManager::init()
{
	_player = new player;
	_player->init(500, 500);
	_ui = new UI;
	_ui->init();
	_itemMg = new itemManager;
	INVENTORY->init();

	_town = new townStage;
	_boss = new bossStage;
	_shop = new shopStage;

	_dungeon = new dungeonStage;
	_ui->getPlayerMemoryAddressLink(_player);
	INVENTORY->getPlayerMemoryAddressLink(_player);

	SCENEMANAGER->addScene("Å¸ÀÌÆ²¾À", new title);

	SCENEMANAGER->addScene("Å¸ÀÏ¾À", new tile);
	SCENEMANAGER->addScene("¼¥¾À", _shop);
	SCENEMANAGER->addScene("´øÀü¾À", _dungeon);
	SCENEMANAGER->addScene("¸¶À»¾À",	_town);
	SCENEMANAGER->addScene("º¸½º¾À", _boss);



	_dungeon->setPlayerLink(_player);
	_town->setPlayerLink(_player);
	_boss->setPlayerLink(_player);
	_shop->setPlayerLink(_player);
	SCENEMANAGER->changeScene("Å¸ÀÌÆ²¾À");

	return S_OK;
}

void stageManager::render()
{
	SCENEMANAGER->render();
	_ui->render();
	//_itemMg->render();
	if (INVENTORY->getIsInven()) INVENTORY->render();
}

void stageManager::update()
{
	FloatRect _test;
	_test = RectMakePivot(Vector2(_ptMouse.x, _ptMouse.y), Vector2(50, 50), Pivot::Center);

	SCENEMANAGER->update();

	KEYANIMANAGER->update();

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
		_itemMg->setItem(ITEMBUNDLE::SLIME_BLUE, WINSIZEX / 2, WINSIZEY / 2);
	}

	if (KEYMANAGER->isOnceKeyDown('U'))
	{
		_itemMg->setItem(ITEMBUNDLE::GOLEM_POT, WINSIZEX / 2, WINSIZEY / 2);
	}

	if (KEYMANAGER->isOnceKeyDown('T'))
	{
		_itemMg->setItem(ITEMBUNDLE::GOLEM_KING, WINSIZEX / 2, WINSIZEY / 2);
	}

	_itemMg->update();

	RECT temp;

	for (int i = 0; i < _itemMg->getVItem().size(); ++i)
	{
		_itemMg->getVItem()[i]->update();
		_itemMg->getVItem()[i]->follow(_test);

		if (IntersectRect(&temp, &_test.GetRect(), &_itemMg->getVItem()[i]->getRc().GetRect()))
		{
			if (INVENTORY->putItem(_itemMg->getVItem()[i]))
			{
				_itemMg->erase(i);
			}
			return;
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
}

void stageManager::release()
{
	SCENEMANAGER->release();
}
