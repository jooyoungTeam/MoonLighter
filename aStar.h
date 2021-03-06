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
	}
};

class aStar : public gameNode
{
	//전체 타일을 담을 벡터
	vector<astarTile*>			 _vTotalList;
	vector<astarTile*>::iterator _viTotalList;

	//갈 수 있는 타일을 담을 벡터
	vector<astarTile*>			 _vOpenList;
	vector<astarTile*>::iterator _viOpenList;

	vector<astarTile*>			 _vCloseList;
	vector<astarTile*>::iterator _viCloseList;

	vector<astarTile*>			 _vShortestList;	// 최단 경로
	vector<astarTile*>::iterator _viShortestList; 

	vector<POINT>				 _vUnMoveTile;		// 못가는 타일

	astarTile* _startTile;		// 시작 타일
	astarTile* _endTile;		// 끝 타일
	astarTile* _currentTile;	// 현재 타일(노드)

	int _totalTileX;			// 총 타일 X 개수
	int _totalTileY;			// 총 타일 Y 개수
	int _aStarTimer;			// a* 리셋 타이머
	int _playerTileX;			// 플레이어의 시작 X 좌표 (시작 오브젝트)
	int _playerTileY;			// 플레이어의 시작 Y 좌표 (시작 오브젝트)
	int _enemyTileX;			// 적의 X 좌표 (목적지 오브젝트)
	int _enemyTileY;			// 적의 Y 좌표 (목적지 오브젝트) 
	int _moveIndex;				// 따라갈 타일의 인덱스
	int _rndX;					// 겹치지 않기 위한 난수
	int _rndY;					// 겹치지 않기 위한 난수

	bool _end;					// a* 탐색 완료 여부			
	bool _isNPC;				// NPC인지 몬스터인지
	bool _changePoint;			// 목표 변경여부
public:
	aStar();
	~aStar();

public:
	// (총 타일X 개수, 총 타일Y 개수, 시작 타일X, 시작 타일Y, 목적지 타일X, 목적지 타일Y, 벽이나 오브젝트 등 못움직이는 좌표, NPC여부)
	HRESULT init(int totalTileX, int totalTileY, int playerX, int playerY, int enemyX, int enemyY, vector<POINT> unMoveTile, bool npc);
	void release();
	void update(int playerTileX, int playerTileY, int enemyTileX, int enemyTileY);
	void render();

	// 타일 셋팅 함수
	void setTiles();
	// 갈 수 있는 길을 찾아서 담을 함수
	vector<astarTile*> addOpenList(astarTile* currentTile);
	// 빠른 경로 찾는 함수dsa
	void pathFinder(astarTile* currentTile);
	// 목표 변경 함수
	void changeWayPoint() { _vShortestList.clear(); _changePoint = true; _end = false; }

public:
	// ================== Get ========================
	vector<astarTile*> getVClose() { return _vCloseList; }
	vector<astarTile*> getVShortest() { return _vShortestList; }
	int getRndX() { return _rndX; }
	int getRndY() { return _rndY; }
	int getMoveIndex() { return _moveIndex; }

public:
	// ================== Set ========================
	void setMoveIndex(int moveIndex) { _moveIndex = moveIndex; }

};

