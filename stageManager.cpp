#include "stdafx.h"
#include "stageManager.h"
#include "tile.h"
#include "title.h"
#include "shopStage.h"

HRESULT stageManager::init()
{
	SCENEMANAGER->addScene("Å¸ÀÌÆ²¾À", new title);

	SCENEMANAGER->addScene("Å¸ÀÏ¾À", new tile);
	SCENEMANAGER->addScene("¼¥¾À", new shopStage);


	SCENEMANAGER->changeScene("Å¸ÀÌÆ²¾À");
	return S_OK;
}

void stageManager::render()
{
	SCENEMANAGER->render();
}

void stageManager::update()
{
	SCENEMANAGER->update();
}

void stageManager::release()
{
	SCENEMANAGER->release();
}
