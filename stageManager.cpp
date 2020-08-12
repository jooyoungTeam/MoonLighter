#include "stdafx.h"
#include "stageManager.h"
#include "tile.h"
#include "title.h"
#include "shopStage.h"
#include "dungeonStage.h"
#include "townStage.h"

HRESULT stageManager::init()
{
	_ui = new UI;
	_ui->init();

	_inven = new inventory;
	_inven->init();
	_isInven = false;

	_itemMg = new itemManager;

	_ui->getInvenMemoryAddressLink(_inven);
	_inven->getUIMemoryAddressLink(_ui);

	SCENEMANAGER->addScene("Å¸ÀÌÆ²¾À", new title);

	SCENEMANAGER->addScene("Å¸ÀÏ¾À", new tile);
	SCENEMANAGER->addScene("¼¥¾À", new shopStage);
	SCENEMANAGER->addScene("´øÀü¾À", new dungeonStage);
	SCENEMANAGER->addScene("¸¶À»¾À", new townStage);

	SCENEMANAGER->changeScene("Å¸ÀÌÆ²¾À");

	return S_OK;
}

void stageManager::render()
{
	SCENEMANAGER->render();
	//ui->render();
	if (_isInven) _inven->render();
}


void stageManager::update()
{
	if(!_isInven) SCENEMANAGER->update();

	if (!_isInven && KEYMANAGER->isOnceKeyDown('I'))
	{
		_isInven = true;
		_ui->setUIScene(CURRENT_SCENE::INVENTORY);
		_inven->setState(INVEN_STATE::NOTE);
	}

	if (_isInven && KEYMANAGER->isOnceKeyDown('I'))
	{
		_isInven = false;
		_ui->setUIScene(CURRENT_SCENE::TEMP);
		_inven->setSale(false);
	}

	if (_isInven) _inven->update();

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
}

void stageManager::release()
{
	SCENEMANAGER->release();
}
