#pragma once
#include "gameNode.h"
#include "tile.h"
#include <vector>
#include <string>

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

struct astarTile
{
	int idX;		//타일의 인덱스 X
	int idY;		//타일의 인덱스 Y

	POINT center;	//타일의 중점 값
	RECT rc;

	//F = G + H
	//F == 총 거리 비용(totalCost)
	//G == 시작점으로부터 현재 노드까지 비용
	//H == 현재 노드부터 도착점 까지 비용

	float totalCost;		//F
	float costFromStart;	//G
	float costToGoal;		//H

	bool isOpen;		//갈수있냐?

	astarTile* parentNode;	//제일 상위 노드 (갱신)
	string attribute;

	void init(int X, int Y)
	{
		totalCost = 0;
		costFromStart = 0;
		costToGoal = 0;
		parentNode = NULL;

		idX = X;
		idY = Y;

		center = PointMake(idX * TILESIZE + (TILESIZE / 2), idY * TILESIZE + (TILESIZE / 2));

		rc = RectMakeCenter(center.x, center.y, TILESIZE, TILESIZE);
	}
};

class aStar : public gameNode
{
	//전체 타일을 담을 벡터
	vector<astarTile*>			_vTotalList;
	vector<astarTile*>::iterator _viTotalList;

	//갈 수 있는 타일을 담을 벡터
	vector<astarTile*>			_vOpenList;
	vector<astarTile*>::iterator _viOpenList;

	vector<astarTile*>			_vCloseList;
	vector<astarTile*>::iterator _viCloseList;

	astarTile* _startTile;		//시작 타일
	astarTile* _endTile;			//끝 타일
	astarTile* _currentTile;		//현재 타일(노드)

	int _totalTileX;
	int _totalTileY;

	int _count;
	int _aStarTimer;
	int _index;

	bool _start;
	bool _end;

	int _playerTileX;
	int _playerTileY;

	int _enemyTileX;
	int _enemyTileY;

	int _moveIndex;
public:
	aStar();
	~aStar();

	// 다 아는 그거
	HRESULT init(int totalTileX, int totalTileY);

	//타일 셋팅 함수
	void setTiles();

	//갈 수 있는 길을 찾아서 담을 함수
	vector<astarTile*> addOpenList(astarTile* currentTile);

	//빠른 경로 찾는 함수
	void pathFinder(astarTile* currentTile);

	void release();

	vector<astarTile*> getVClose() { return _vCloseList; }
	int getMoveIndex() { return _moveIndex; }
	void setMoveIndex(int moveIndex) { _moveIndex = moveIndex; }

	void update(int playerTileX, int playerTileY, int enemyTileX, int enemyTileY);
	void render();
};

