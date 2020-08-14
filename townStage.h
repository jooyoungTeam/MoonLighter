#pragma once
#include "gameNode.h"
#include "player.h"
#include "tile.h"
class townStage : public gameNode
{
private:
	player* _player;

	Image*  _mapImg;
	tile*   _tileClass;
	
	//tagTile           _townTiles[TILEX * TILEY];
	DWORD             _townAttribute[60 * 49];
	tagTile			  _tile[60 * 49];
	vector<tagObject> _vObject;
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
public:
	//void loadMap();
	//void renderMap();
};

