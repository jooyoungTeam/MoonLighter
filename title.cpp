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
		SCENEMANAGER->changeScene("Ÿ�Ͼ�");
	}
	
	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		SCENEMANAGER->changeScene("����");
	}


}

void title::render()
{
}

void title::release()
{
}
