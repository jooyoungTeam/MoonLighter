#pragma once
#include "gameNode.h"
#include "tileNode.h"
#include "button.h"
#include "objectManager.h"
#include "palette.h"
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

class tile : public gameNode
{
private:
	button*           _button;
	vector<tagTile>   _vTile;
	vector<tagTile>   _vAttribute;
	int				  _tileSize[2];
	tagDragRect       _drag;
	POINT             _currentTile; //인덱스
	RECT              _currentRect;
	RECT              _dragTile;    // 마우스 포인터 마우스 안에있을 때
	objectManager*    _objectManager;
	palette*          _palette;
	// --------- 미니맵 변수	
	FloatRect     _miniMap;
	FloatRect     _miniMapMove;
	// --------- 미니맵 변수	

	int           _saveTime;
	int           _nowIndex;

	// ----------- 임시 변수 ------------ //
	int           _currentLoadType;          // 현재 어느맵을 로드했는지세이브 안꼬이게
	Image*        _mapImg;
	// ----------- 임시 변수 ------------ //
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
	void saveLoad();
	void imageLoad();

	void autoTile();
	void autoTileType(int idx, TERRAIN type);
	void mapMove();

	void saveMap();
	void loadMap();
public:

	TERRAIN terrainSelect(int frameX, int frameY);

};


