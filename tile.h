#pragma once
#include "gameNode.h"
#include "tileNode.h"
#include "button.h"
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
	vector<tagObject>  _vObject;
	tagObject          _currentObject;          //������ ������Ʈ
	bool               _isSelectObject;
	// --------- object ---------- //


	// --------- �̴ϸ� ����	
	FloatRect     _miniMap;
	FloatRect     _miniMapMove;
	// --------- �̴ϸ� ����	

	int           _frameCount;
	int           _saveTime;
	int           _nowIndex;

	// ----------- �ӽ� ���� ------------ //
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
	void selectObject();
	void eraseObject(int arrNum);

	void autoTile();

	void mapMove();
	void sampleOnOff();

	void saveMap();

	void loadMap();
	// ----------------------------------

	TERRAIN terrainSelect(int frameX, int frameY);
	Image* findImg(OBJECT type, int imgNum);
};

