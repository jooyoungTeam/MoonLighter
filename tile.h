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

	DWORD             _attribute[TILEX * TILEY];

	// --------- 팔레트 변수 --------- //
	RECT                _sampleTileUI; // 팔레트 그림 있는곳
	tagSampleTile       _sampleTile[SAMPLETILEX * SAMPLETILEY];
	RECT                _sampleTileOnOff;
	bool                _isActive;
	// --------- 팔레트 변수 --------- //


	// --------- object ---------- //
	RECT               _leftRightButton[2];
	tagSampleObject    _sampleObject[4];
	OBJECT 	           _currentSampleObject;    //현재 보고있는 오브젝트 넘버
	vector<tagObject*> _object;
	tagObject*         _currentObject;          //선택한 오브젝트
	bool               _isSelectObject;
	// --------- object ---------- //


	// --------- 미니맵 변수	
	FloatRect     _miniMap;
	FloatRect     _miniMapMove;
	// --------- 미니맵 변수	

	// ----------- 던전맵 변수
	tagTile           _dungeonTiles[TILEX * TILEY];
	DWORD             _dungeonAttribute[TILEX * TILEY];
	// ----------- 던전맵 변수

	// ----------- 마을 맵 변수
	tagTile           _townTiles[TILEX * TILEY];
	DWORD             _townAttribute[TILEX * TILEY];
	// ----------- 마을 맵 변수


	int           _saveTime;
	int			  _dragNumX;
	int			  _dragNumY;

	int           _nowIndex;
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
	void selectObject();
	void eraseObject(int arrNum);

	void mapMove();
	void sampleOnOff();

	// ----------------------------------
	void saveDungeonMap();
	void saveTownMap();
	void renderDungeonMap();

	void loadDungeonMap();
	void loadTownMap();
	void renderTownMap();
	// ----------------------------------

	tagTile* getDungeonTile() { return _dungeonTiles; }
	DWORD* getDungeonAttribute() { return _dungeonAttribute; }

	TERRAIN terrainSelect(int frameX, int frameY);

};

