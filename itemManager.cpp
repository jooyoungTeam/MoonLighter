#include "stdafx.h"
#include "itemManager.h"
#include "player.h"

HRESULT itemManager::init()
{
	return S_OK;
}

void itemManager::render()
{
	for (int i = 0; i < _vItem.size(); ++i)
	{
		_vItem[i]->cameraRender();
	}
}

void itemManager::update(player* player)
{
	RECT temp;

	for (int i = 0; i < _vItem.size(); ++i)
	{
		_vItem[i]->update();
		_vItem[i]->follow(player->getPlayerRc());

		if (!player->getDeadState() &&
			IntersectRect(&temp, &player->getPlayerRc().GetRect(), &_vItem[i]->getRc().GetRect()))
		{
			if (INVENTORY->putItem(_vItem[i]))
			{
				erase(i);
			}
			return;
		}
	}
}

void itemManager::release()
{
	for (int i = 0; i < _vItem.size(); ++i)
	{
		SAFE_DELETE(_vItem[i]);
	}
	_vItem.clear();
}

void itemManager::setItem(ITEMBUNDLE bundle, float x, float y)
{
	int count = RND->getFromIntTo(2, 3);
	for (int i = 0; i < count; i++)
	{
		int rnd = RND->getInt(10);
		if (rnd >= 6) continue;

		item* material;
		material = new item;
		material->init(bundle, x, y, x + RND->getFromIntTo(-50, 50), y + RND->getInt(50), rnd);

		_vItem.push_back(material);
	}
}

void itemManager::popItem(ITEMTYPE type, float x, float y)
{
	item* material;
	material = new item;
	material->init(type, x, y, x + RND->getFromIntTo(-50, 50), y + RND->getFromIntTo(-50, 50));
	
	_vItem.push_back(material);
}

void itemManager::erase(int arrNum)
{
	_vItem.erase(_vItem.begin() + arrNum);
}
