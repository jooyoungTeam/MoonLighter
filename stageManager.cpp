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
	_b = new boss;

	_ui->getPlayerMemoryAddressLink(_player);
	INVENTORY->getPlayerMemoryAddressLink(_player);

	SCENEMANAGER->addScene("Ÿ��Ʋ��", new title);

	SCENEMANAGER->addScene("Ÿ�Ͼ�", new tile);
	SCENEMANAGER->addScene("����", _shop);
	SCENEMANAGER->addScene("������", _dungeon);
	SCENEMANAGER->addScene("������",	_town);
	SCENEMANAGER->addScene("������", _boss);
	SCENEMANAGER->addScene("������2", _dungeon2);
	SCENEMANAGER->addScene("���ľ�", _spa);
	SCENEMANAGER->addScene("�����Ա���", _enterence);



	_dungeon->setPlayerLink(_player);
	_dungeon2->setPlayerLink(_player);
	_spa->setPlayerLink(_player);
	_enterence->setPlayerLink(_player);
	_town->setPlayerLink(_player);
	_boss->setPlayerLink(_player);
	_shop->setPlayerLink(_player);
	SCENEMANAGER->changeScene("Ÿ��Ʋ��");

	return S_OK;
}

void stageManager::render()
{
	SCENEMANAGER->render();
	
	if (SCENEMANAGER->getCurrentScene() != "Ÿ��Ʋ��" && SCENEMANAGER->getCurrentScene() != "Ÿ�Ͼ�")
	{
		if (!_town->getIsPotionShop()) 
		{
			_ui->render();
		}
		ImageManager::GetInstance()->FindImage("UI_gold")->Render(Vector2(0, 0));
		//���ָӴ�
		ImageManager::GetInstance()->FindImage("moneyBag")->FrameRender(Vector2(90, 88), 0, _ui->getMonveBagFrame());
		//������
		D2DRenderer::GetInstance()->RenderText(100, 150, to_wstring(INVENTORY->getGold()), 20, D2DRenderer::DefaultBrush::Black);

		_itemMg->render();
		if (INVENTORY->getIsInven()) INVENTORY->render(); 
	}
}

void stageManager::update()
{
	SCENEMANAGER->update();

	KEYANIMANAGER->update();

	if (SCENEMANAGER->getCurrentScene() != "Ÿ��Ʋ��" && SCENEMANAGER->getCurrentScene() != "Ÿ�Ͼ�")
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

			if (!_player->getDeadState() && 
				IntersectRect(&temp, &_player->getPlayerRc().GetRect(), &_itemMg->getVItem()[i]->getRc().GetRect()))
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
		SCENEMANAGER->changeScene("Ÿ�Ͼ�");
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		SCENEMANAGER->changeScene("������");
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F3))
	{
		SCENEMANAGER->changeScene("������");
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F4))
	{
		SCENEMANAGER->changeScene("����");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F5))
	{
		SCENEMANAGER->changeScene("������");

		for (int i = 0; i < _boss->getEnemyManager()->_getVEnemy().size(); ++i)
		{
			if (_boss->getEnemyManager()->_getVEnemy()[i]->getEnemyType() == ENEMY_BOSS)
			{
				_b = dynamic_cast<boss*>(_boss->getEnemyManager()->_getVEnemy()[i]);

				_ui->getBossMemoryAddressLink(_b);
				break;
			}
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F6))
	{
		SCENEMANAGER->changeScene("������2");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F7))
	{
		SCENEMANAGER->changeScene("���ľ�");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F8))
	{
		SCENEMANAGER->changeScene("�����Ա���");
		_player->setPlayerPos(WINSIZEX / 2, WINSIZEY / 2);
	}
}

void stageManager::release()
{
	SCENEMANAGER->release();
}
