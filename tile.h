#pragma once
#include "gameNode.h"
#include "tileNode.h"
#include "button.h"
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

class tile : public gameNode
{
private:
	button*       _button;
	tagTile       _tiles[TILEX * TILEY];
	tagSampleTile _sampleTile[SAMPLETILEX * SAMPLETILEY];
	tagDragRect   _drag;
	POINT         _currentTile; //ÀÎµ¦½º
	RECT          _currentRect;           
	RECT          _dragTile;
	RECT          _sampleTileUI;

	// --------- ¸Ê ÀÌµ¿ º¯¼ö
	tagMapMove    _mapMove[4];
	MAPMOVE       _currentMove;
	// --------- ¸Ê ÀÌµ¿ º¯¼ö

	int           _saveTime;
public:
	tile() {}
	~tile() {}

	HRESULT init();
	void    render();
	void    update();
	void    release();
public:
	void drag();
	void setup();
	void setMap();
	void save();
	void load();
	void imageLoad();
	void mapMove();
	
	TERRAIN terrainSelect(int frameX, int frameY);
	OBJECT  objectSelect(int frameX, int frameY);

};

