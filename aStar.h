#pragma once
#include "gameNode.h"
#include "tile.h"
#include <vector>
#include <string>

class aStar : public gameNode
{
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

	int _count;
	int _aStarTimer;
	int _index;
	bool _start;
	bool _end;

	RECT _player;
	int _playerTileX;
	int _playerTileY;

	RECT _enemy;
	int _enemyTileX;
	int _enemyTileY;
	float _enemyX;
	float _enemyY;
	float _enemyAnlge;

public:
	aStar();
	~aStar();

	// 다 아는 그거
	HRESULT init();

	//타일 셋팅 함수
	void setTiles(int targetX, int targetY);

	//갈 수 있는 길을 찾아서 담을 함수
	vector<tile*> addOpenList(tile* currentTile);

	//빠른 경로 찾는 함수
	void pathFinder(tile* currentTile);

	void release();
	void update();
	void render();

	void move();
};

