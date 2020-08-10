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
	RECT rc;

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

		rc = RectMakeCenter(center.x, center.y, TILESIZE, TILESIZE);
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
public:
	aStar();
	~aStar();

	// �� �ƴ� �װ�
	HRESULT init(int totalTileX, int totalTileY);

	//Ÿ�� ���� �Լ�
	void setTiles();

	//�� �� �ִ� ���� ã�Ƽ� ���� �Լ�
	vector<astarTile*> addOpenList(astarTile* currentTile);

	//���� ��� ã�� �Լ�
	void pathFinder(astarTile* currentTile);

	void release();

	vector<astarTile*> getVClose() { return _vCloseList; }
	int getMoveIndex() { return _moveIndex; }
	void setMoveIndex(int moveIndex) { _moveIndex = moveIndex; }

	void update(int playerTileX, int playerTileY, int enemyTileX, int enemyTileY);
	void render();
};

