#pragma once
#include "singletonBase.h"
#include "tile.h"
#include <vector>
#include <string>

#define TILENUMX (WINSIZEX / TILESIZE)
#define TILENUMY (WINSIZEY / TILESIZE)

class aStarManager : public singletonBase<aStarManager>
{
private:
	//전체 타일을 담을 벡터
	vector<tile*>			_vTotalList;
	vector<tile*>::iterator _viTotalList;

	//갈 수 있는 타일을 담을 벡터
	vector<tile*>			_vOpenList;
	vector<tile*>::iterator _viOpenList;

	vector<tile*>			_vCloseList;
	vector<tile*>::iterator _viCloseList;

	tile* _startTile;		//시작 타일
	tile* _endTile;			//끝 타일
	tile* _currentTile;		//현재 타일(노드)


public:
	aStarManager() {}
	~aStarManager() {}

public:
	HRESULT init();
	void render();
	void update();
	void release();

	//타일 셋팅 함수
	void setTiles(int targetX, int targetY);
	//갈 수 있는 길을 찾아서 담을 함수
	vector<tile*> addOpenList(tile* currentTile);
	//빠른 경로 찾는 함수
	void pathFinder(tile* currentTile);
};

