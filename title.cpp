#include "stdafx.h"
#include "title.h"

HRESULT title::init()
{
	return S_OK;
}

void title::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		SCENEMANAGER->changeScene("Å¸ÀÏ¾À");
	}
	
	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		SCENEMANAGER->changeScene("¼¥¾À");
	}


}

void title::render()
{
}

void title::release()
{
}
