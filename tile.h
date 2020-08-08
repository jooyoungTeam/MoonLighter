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
	POINT             _currentTile; //�ε���
	RECT              _currentRect;           
	RECT              _dragTile;    // ���콺 ������ ���콺 �ȿ����� ��

	DWORD             _attribute[TILEX * TILEY];

	// --------- �ȷ�Ʈ ����
	RECT              _sampleTileUI; // �ȷ�Ʈ �׸� �ִ°�
	tagSampleTile     _sampleTile[SAMPLETILEX * SAMPLETILEY];
	RECT              _sampleTileOnOff;
	bool              _isActive;
	// --------- �ȷ�Ʈ ����

	vector<tagObject*> _vObject;


	// --------- �� �̵� ����
	tagMapMove    _mapMove[4];
	MAPMOVE       _currentMove;
	// --------- �� �̵� ����

	// --------- �̴ϸ� ����
	
	FloatRect     _miniMap;
	FloatRect     _miniMapMove;

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
	void save();
	void load();
	void imageLoad();
	void loadDungeonMap();
	void renderDungeonMap();
	
	void addObject();
	void mapMove();
	void sampleOnOff();
	void miniMap();

	tagTile* getTile() { return _tiles; }
	DWORD* getAttribute() { return _attribute; }

	TERRAIN terrainSelect(int frameX, int frameY);
	OBJECT  objectSelect(int frameX, int frameY);

};

