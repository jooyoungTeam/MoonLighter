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

	_itemMg = new itemManager;

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
	if (_inven->getOpen()) _inven->render();
}


void stageManager::update()
{
	if(!_inven->getOpen()) SCENEMANAGER->update();

	if (!_inven->getOpen() && KEYMANAGER->isOnceKeyDown('I'))
	{
		_inven->setOpen(true);
		_inven->setState(INVEN_STATE::NOTE);
	}

	if (_inven->getOpen() && KEYMANAGER->isOnceKeyDown('I'))
	{
		_inven->setOpen(false);
	}

	if (_inven->getOpen()) _inven->update();

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
