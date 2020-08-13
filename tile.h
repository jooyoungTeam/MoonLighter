#pragma once
#include "gameNode.h"
#include "tileNode.h"
#include "button.h"
#include "player.h"
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

class tile : public gameNode
{
private:
	button*           _button;
	tagTile           _tiles[TILEX * TILEY];
	tagDragRect       _drag;
	POINT             _currentTile; //�ε���
	RECT              _currentRect;           
	RECT              _dragTile;    // ���콺 ������ ���콺 �ȿ����� ��

	DWORD             _attribute[TILEX * TILEY];

	// --------- �ȷ�Ʈ ���� --------- //
	RECT                _sampleTileUI; // �ȷ�Ʈ �׸� �ִ°�
	tagSampleTile       _sampleTile[SAMPLETILEX * SAMPLETILEY];
	RECT                _sampleTileOnOff;
	bool                _isActive;
	// --------- �ȷ�Ʈ ���� --------- //


	// --------- object ---------- //
	RECT               _leftRightButton[2];
	tagSampleObject    _sampleObject[4];
	OBJECT 	           _currentSampleObject;    //���� �����ִ� ������Ʈ �ѹ�
	vector<tagObject*> _object;
	tagObject*         _currentObject;          //������ ������Ʈ
	bool               _isSelectObject;
	// --------- object ---------- //


	// --------- �̴ϸ� ����	
	FloatRect     _miniMap;
	FloatRect     _miniMapMove;
	// --------- �̴ϸ� ����	

	// ----------- ������ ����
	tagTile           _dungeonTiles[TILEX * TILEY];
	DWORD             _dungeonAttribute[TILEX * TILEY];
	// ----------- ������ ����

	// ----------- ���� �� ����
	tagTile           _townTiles[TILEX * TILEY];
	DWORD             _townAttribute[TILEX * TILEY];
	// ----------- ���� �� ����

	// ----------- �浹 ó�� Ÿ�Ϸ� �ٲ��� ��Ʈ

	// ----------- �浹 ó�� Ÿ�Ϸ� �ٲ��� ��Ʈ

	int           _frameCount;
	int           _saveTime;
	int			  _dragNumX;
	int			  _dragNumY;
	int           _nowIndex;


	// ----------- �ӽ� ���� ------------ //
	int           _tileX;
	int           _tileY;
	Image*        _mapImg;
	player*       _player;
	// ----------- �ӽ� ���� ------------ //
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

	void autoTile();

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

