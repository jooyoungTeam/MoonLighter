#pragma once
#include "gameNode.h"
#include "tile.h"
#include <vector>
#include <string>

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

struct astarTile
{
	int idX;		//Ÿ���� �ε��� X
	int idY;		//Ÿ���� �ε��� Y

	POINT center;	//Ÿ���� ���� ��

	//F = G + H
	//F == �� �Ÿ� ���(totalCost)
	//G == ���������κ��� ���� ������ ���
	//H == ���� ������ ������ ���� ���

	float totalCost;		//F
	float costFromStart;	//G
	float costToGoal;		//H

	bool isOpen;		//�����ֳ�?

	astarTile* parentNode;	//���� ���� ��� (����)
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
	//��ü Ÿ���� ���� ����
	vector<astarTile*>			_vTotalList;
	vector<astarTile*>::iterator _viTotalList;

	//�� �� �ִ� Ÿ���� ���� ����
	vector<astarTile*>			_vOpenList;
	vector<astarTile*>::iterator _viOpenList;

	vector<astarTile*>			_vCloseList;
	vector<astarTile*>::iterator _viCloseList;

	vector<astarTile*>			_vOldCloseList;
	vector<astarTile*>::iterator _vOldiCloseList;

	vector<POINT>				_vUnMoveTile;

	astarTile* _startTile;		//���� Ÿ��
	astarTile* _endTile;			//�� Ÿ��
	astarTile* _currentTile;		//���� Ÿ��(���)

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

	int _rndX;
	int _rndY;

	bool _isNPC;
	bool _changePoint;
public:
	aStar();
	~aStar();

	// �� �ƴ� �װ�
	HRESULT init(int totalTileX, int totalTileY, int playerX, int playerY, int enemyX, int enemyY, vector<POINT> unMoveTile, bool npc);

	//Ÿ�� ���� �Լ�
	void setTiles();

	//�� �� �ִ� ���� ã�Ƽ� ���� �Լ�
	vector<astarTile*> addOpenList(astarTile* currentTile);

	//���� ��� ã�� �Լ�
	void pathFinder(astarTile* currentTile);

	void release();

	vector<astarTile*> getVClose() { return _vCloseList; }
	vector<astarTile*> getVOldClose() { return _vOldCloseList; }
	int getRndX() { return _rndX; }
	int getRndY() { return _rndY; }

	int getMoveIndex() { return _moveIndex; }
	void setMoveIndex(int moveIndex) { _moveIndex = moveIndex; }

	void update(int playerTileX, int playerTileY, int enemyTileX, int enemyTileY);
	void render();

	void changeWayPoint() { _changePoint = true; 	_moveIndex = 0; }
};

