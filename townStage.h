#pragma once
#include "gameNode.h"
#include "player.h"
#include "tile.h"
#include "objectManager.h"

#define TOWNTILEX 60
#define TOWNTILEY 49
class townStage : public gameNode
{
private:
	player*           _player;
	Image*            _mapImg;

	DWORD             _townAttribute[TOWNTILEX * TOWNTILEY];
	tagTile			  _tile[TOWNTILEX * TOWNTILEY];
	objectManager*    _objectManager;
public:
	townStage() {}
	~townStage() {}
public:
	HRESULT init();
	void    update();
	void    render();
	void    release();

	void    loadMap();
	void    mapToolRender();
};

