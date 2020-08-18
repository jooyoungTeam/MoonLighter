#pragma once
#include "gameNode.h"
#include "tile.h"
#include "objectManager.h"

#define TOWNTILEX 60
#define TOWNTILEY 49
class townStage : public gameNode
{
private:
	Image*            _mapImg;

	DWORD             _attribute[TOWNTILEX * TOWNTILEY];
	tagTile			  _tile[TOWNTILEX * TOWNTILEY];
	objectManager*    _objectManager;
	class player*     _player;
public:
	townStage() {}
	~townStage() {}
public:
	HRESULT init();
	void    update();
	void    render();
	void    release();

	void setPlayerLink(player* player) { _player = player; };
	void    loadMap();
	void    mapToolRender();
};

