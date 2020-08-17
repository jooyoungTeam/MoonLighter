#include "stdafx.h"
#include "shopNPCManager.h"

HRESULT shopNPCManager::init()
{

	return S_OK;
}

void shopNPCManager::update()
{
	for (int i = 0; i < _vNpc.size(); ++i)
	{
		_vNpc[i]->updadte();
	}

	npcExit();
}

void shopNPCManager::render()
{
	for (int i = 0; i < _vNpc.size(); ++i)
	{
		_vNpc[i]->render();
	}
}

void shopNPCManager::release()
{
	for (int i = 0; i < _vNpc.size(); ++i)
	{
		SAFE_DELETE(_vNpc[i]);
	}
	_vNpc.clear();
}

void shopNPCManager::npcAdd(npcType type, vector<POINT> vUnMove)
{
	shopNPC* tempNpc = new shopNPC;

	tempNpc->init(type, vUnMove);
	_vNpc.push_back(tempNpc);
}

void shopNPCManager::npcErase(int index)
{
	_vNpc.erase(_vNpc.begin() + index);
}

void shopNPCManager::npcExit()
{
	for (int i = 0; i < _vNpc.size(); ++i)
	{
		if (_vNpc[i]->getIsAway())
		{
			npcErase(i);
			break;
		}
	}
}
