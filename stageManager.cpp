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

	SCENEMANAGER->addScene("Ÿ��Ʋ��", new title);

	SCENEMANAGER->addScene("Ÿ�Ͼ�", new tile);
	SCENEMANAGER->addScene("����", new shopStage);
	SCENEMANAGER->addScene("������", new dungeonStage);

	SCENEMANAGER->changeScene("Ÿ��Ʋ��");

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
		SCENEMANAGER->changeScene("Ÿ�Ͼ�");
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		KEYANIMANAGER->release();
		SCENEMANAGER->changeScene("����");
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F3))
	{
		KEYANIMANAGER->release();
		SCENEMANAGER->changeScene("������");
	}

}

void stageManager::release()
{
	SCENEMANAGER->release();
}
