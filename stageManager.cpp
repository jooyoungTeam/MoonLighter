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

	SCENEMANAGER->addScene("Ÿ��Ʋ��", new title);

	SCENEMANAGER->addScene("Ÿ�Ͼ�", new tile);
	SCENEMANAGER->addScene("����", new shopStage);
	SCENEMANAGER->addScene("������", new dungeonStage);
	SCENEMANAGER->addScene("������", new townStage);

	SCENEMANAGER->changeScene("Ÿ��Ʋ��");

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
		SCENEMANAGER->changeScene("Ÿ�Ͼ�");
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		KEYANIMANAGER->release();
		SCENEMANAGER->changeScene("������");
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F3))
	{
		KEYANIMANAGER->release();
		SCENEMANAGER->changeScene("������");
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F4))
	{
		KEYANIMANAGER->release();
		SCENEMANAGER->changeScene("����");
	}
}

void stageManager::release()
{
	SCENEMANAGER->release();
}
