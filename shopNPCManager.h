#pragma once
#include "gameNode.h"
#include "shopNPC.h"

class shopNPCManager : public gameNode
{
private:
	vector<shopNPC*> _vNpc;

public:
	shopNPCManager() {}
	~shopNPCManager() {}
	
public:
	HRESULT init();
	void update();
	void render();
	void release();

	void npcAdd(npcType type);
	void npcErase(int index);
	void npcExit();

public:
	//============================ Get ===========================
	vector<shopNPC*> getVnpc() { return _vNpc; }

public:
	//============================ Set ===========================

};

