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
	button*             _button;            // 버튼
	vector<tagTile>     _vTile;             // 타일이 담겨있는 벡터
	int				    _tileSize[2];       // TILEX x TILEY 사이즈
	tagSelectSizeTileUI _selectTileSize[4]; // TILEX x TILEY 사이즈 정하는 구조체
	tagDragRect         _drag;              // 드래그 할 때 어디 드래그 했는지 보여주는 구조체
	POINT               _currentTile;       // 현재 선택한 타일의 좌표
	RECT                _currentRect;       // 현재 선택한 타일의 렉트
	RECT                _dragTile;          // 마우스 포인터 마우스 안에있을 때
	objectManager*      _objectManager;     // 오브젝트
	palette*            _palette;           // 팔레트 -> 그릴때 옆에 샘플그림들
	miniMap*            _miniMap1;          // 미니맵
	Image*              _mapImg;            // 맵에 이미지가 있을 때 필요한 이미지 변수
	int                 _saveTime;          // 세이브 할 때 중복 실행 안되도록 해주는 변수
	int                 _currentLoadType;   // 현재 어느맵을 로드했는지세이브 안꼬이게
public:
	tile() {}
	~tile() {}
public:
	HRESULT init();
	void    render();
	void    update();
	void    release();
public:
	void selectTileSizeInit();                // TILEX x TILEY 사이즈 정해주는 변수의 초기화
	void selectTileSize();                    // TILEX x TILEY 사이즈 정해주는 함수
	void selectTileSizeRender();              // 버튼 클릭시 랜더
	void drag();                              // 드래그
	void setup();                             // 타일 초기화
	void setMap();                            // 타일을 찍어줄 때 매프레임마다 도는 함수
	void autoTile();                          // 오토타일
	void autoTileType(int idx, TERRAIN type); // 오토 타일시 주변 타일 검출해주는 함수
	void mapMove();                           // 맵 이동 함수
public:
	void saveLoad();            
	void saveMap(int num);		
	void loadMap(int num);      
	void imageLoad();           
public:

	TERRAIN terrainSelect(int frameX, int frameY);
	ACTIVEPOS posSelect(int frameX, int frameY);
};


