#include "stdafx.h"
#include "stageManager.h"
#include "tile.h"
#include "title.h"
#include "shopStage.h"
#include "dungeonStage.h"

HRESULT stageManager::init()
{
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
}

void stageManager::update()
{
	SCENEMANAGER->update();

	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		SCENEMANAGER->changeScene("Ÿ�Ͼ�");
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		SCENEMANAGER->changeScene("����");
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F3))
	{
		SCENEMANAGER->changeScene("������");
	}

}

void stageManager::release()
{
	SCENEMANAGER->release();
}
