#include "stdafx.h"
#include "stageManager.h"
#include "tile.h"
#include "title.h"
#include "shopStage.h"
#include "dungeonStage.h"

HRESULT stageManager::init()
{
	_itemMg = new itemManager;

	_inven = new inventory;
	_inven->init();

	SCENEMANAGER->addScene("Å¸ÀÌÆ²¾À", new title);

	SCENEMANAGER->addScene("Å¸ÀÏ¾À", new tile);
	SCENEMANAGER->addScene("¼¥¾À", new shopStage);
	SCENEMANAGER->addScene("´øÀü¾À", new dungeonStage);

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

	_inven->update();

	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		SCENEMANAGER->changeScene("Å¸ÀÏ¾À");
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		KEYANIMANAGER->release();
		SCENEMANAGER->changeScene("¼¥¾À");
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F3))
	{
		KEYANIMANAGER->release();
		SCENEMANAGER->changeScene("´øÀü¾À");
	}

}

void stageManager::release()
{
	SCENEMANAGER->release();
}
