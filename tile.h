#pragma once
#include "gameNode.h"
#include "tileNode.h"
#include "button.h"
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

class tile : public gameNode
{
private:
	button*         _button;
	tagTile         _tiles[TILEX * TILEY];
	vector<int>		_vDragTile;
	tagDragRect     _drag;
	POINT           _currentTile; //�ε���
	RECT            _currentRect;           
	RECT            _dragTile;    // ���콺 ������ ���콺 �ȿ����� ��


	// --------- �ȷ�Ʈ ����
	RECT            _sampleTileUI; // �ȷ�Ʈ �׸� �ִ°�
	RECT            _sampleTileOnOff;
	bool            _isOnOff;
	tagSampleTile   _sampleTile[SAMPLETILEX * SAMPLETILEY];
	// --------- �ȷ�Ʈ ����


	// --------- �� �̵� ����
	tagMapMove    _mapMove[4];
	MAPMOVE       _currentMove;
	// --------- �� �̵� ����

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
	void mapMove();
	void openSampleTile();

	TERRAIN terrainSelect(int frameX, int frameY);
	OBJECT  objectSelect(int frameX, int frameY);

};

