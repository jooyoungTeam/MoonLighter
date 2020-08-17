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
	POINT             _currentTile; //�ε���
	RECT              _currentRect;
	RECT              _dragTile;    // ���콺 ������ ���콺 �ȿ����� ��
	objectManager*    _objectManager;
	palette*          _palette;
	// --------- �̴ϸ� ����	
	FloatRect     _miniMap;
	FloatRect     _miniMapMove;
	// --------- �̴ϸ� ����	

	int           _saveTime;
	int           _nowIndex;

	// ----------- �ӽ� ���� ------------ //
	int           _currentLoadType;          // ���� ������� �ε��ߴ������̺� �Ȳ��̰�
	Image*        _mapImg;
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

	void autoTile();
	void autoTileType(int idx, TERRAIN type);
	void mapMove();

	void saveMap();
	void loadMap();
public:

	TERRAIN terrainSelect(int frameX, int frameY);

};


