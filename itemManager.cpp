#include "stdafx.h"
#include "itemManager.h"

HRESULT itemManager::init()
{
	return S_OK;
}

void itemManager::release()
{
	for (int i = 0; i < _vItem.size(); ++i)
	{
		SAFE_DELETE(_vItem[i]);
	}
	_vItem.clear();
}

void itemManager::update()
{
	for (int i = 0; i < _vItem.size(); ++i)
	{
		_vItem[i]->update();
	}
}

void itemManager::render()
{
	for (int i = 0; i < _vItem.size(); ++i)
	{
		_vItem[i]->render();
	}
}

void itemManager::setItem(ITEMTYPE type, float x, float y)
{
	item* material;
	material = new item;
	material->init(type, x, y);

	_vItem.push_back(material);
}

void itemManager::erase(int arrNum)
{
	_vItem.erase(_vItem.begin() + arrNum);
}
