#pragma once
#include "gameNode.h"
#include "tileNode.h"
#include "button.h"
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

class tile : public gameNode
{
private:
	button*           _button;
	tagTile           _tiles[TILEX * TILEY];
	vector<int>		  _vDragTile;
	tagDragRect       _drag;
	POINT             _currentTile; //인덱스
	RECT              _currentRect;           
	RECT              _dragTile;    // 마우스 포인터 마우스 안에있을 때


	// --------- 팔레트 변수
	RECT              _sampleTileUI; // 팔레트 그림 있는곳
	tagSampleTile     _sampleTile[SAMPLETILEX * SAMPLETILEY];
	// --------- 팔레트 변수

	vector<tagObject*> _vObject;


	// --------- 맵 이동 변수
	tagMapMove    _mapMove[4];
	MAPMOVE       _currentMove;
	// --------- 맵 이동 변수

	int           _saveTime;
	int			  _dragNumX;
	int			  _dragNumY;
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
	void addObject();
	void mapMove();

	TERRAIN terrainSelect(int frameX, int frameY);
	OBJECT  objectSelect(int frameX, int frameY);

};

