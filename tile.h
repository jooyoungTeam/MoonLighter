#pragma once
#include "gameNode.h"
#include "tileNode.h"
#include "button.h"
#include "objectManager.h"
#include "palette.h"
#include "miniMap.h"
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

class tile : public gameNode
{
private:
	button*             _button;            // ��ư
	vector<tagTile>     _vTile;             // Ÿ���� ����ִ� ����
	int				    _tileSize[2];       // TILEX x TILEY ������
	tagSelectSizeTileUI _selectTileSize[4]; // TILEX x TILEY ������ ���ϴ� ����ü
	tagDragRect         _drag;              // �巡�� �� �� ��� �巡�� �ߴ��� �����ִ� ����ü
	POINT               _currentTile;       // ���� ������ Ÿ���� ��ǥ
	RECT                _currentRect;       // ���� ������ Ÿ���� ��Ʈ
	RECT                _dragTile;          // ���콺 ������ ���콺 �ȿ����� ��
	objectManager*      _objectManager;     // ������Ʈ
	palette*            _palette;           // �ȷ�Ʈ -> �׸��� ���� ���ñ׸���
	miniMap*            _miniMap1;          // �̴ϸ�
	Image*              _mapImg;            // �ʿ� �̹����� ���� �� �ʿ��� �̹��� ����
	int                 _saveTime;          // ���̺� �� �� �ߺ� ���� �ȵǵ��� ���ִ� ����
	int                 _currentLoadType;   // ���� ������� �ε��ߴ������̺� �Ȳ��̰�
public:
	tile() {}
	~tile() {}
public:
	HRESULT init();
	void    render();
	void    update();
	void    release();
public:
	void selectTileSizeInit();                // TILEX x TILEY ������ �����ִ� ������ �ʱ�ȭ
	void selectTileSize();                    // TILEX x TILEY ������ �����ִ� �Լ�
	void selectTileSizeRender();              // ��ư Ŭ���� ����
	void drag();                              // �巡��
	void setup();                             // Ÿ�� �ʱ�ȭ
	void setMap();                            // Ÿ���� ����� �� �������Ӹ��� ���� �Լ�
	void autoTile();                          // ����Ÿ��
	void autoTileType(int idx, TERRAIN type); // ���� Ÿ�Ͻ� �ֺ� Ÿ�� �������ִ� �Լ�
	void mapMove();                           // �� �̵� �Լ�
public:
	void saveLoad();            
	void saveMap(int num);		
	void loadMap(int num);      
	void imageLoad();           
public:

	TERRAIN terrainSelect(int frameX, int frameY);
	ACTIVEPOS posSelect(int frameX, int frameY);
};


