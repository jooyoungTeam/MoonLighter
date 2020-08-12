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
	vector<astarTile*>			 _vTotalList;
	vector<astarTile*>::iterator _viTotalList;

	//�� �� �ִ� Ÿ���� ���� ����
	vector<astarTile*>			 _vOpenList;
	vector<astarTile*>::iterator _viOpenList;

	vector<astarTile*>			 _vCloseList;
	vector<astarTile*>::iterator _viCloseList;

	vector<astarTile*>			 _vShortestList;	// �ִ� ���
	vector<astarTile*>::iterator _viShortestList; 

	vector<POINT>				 _vUnMoveTile;		// ������ Ÿ��

	astarTile* _startTile;		// ���� Ÿ��
	astarTile* _endTile;		// �� Ÿ��
	astarTile* _currentTile;	// ���� Ÿ��(���)

	int _totalTileX;			// �� Ÿ�� X ����
	int _totalTileY;			// �� Ÿ�� Y ����
	int _aStarTimer;			// a* ���� Ÿ�̸�
	int _playerTileX;			// �÷��̾��� ���� X ��ǥ (���� ������Ʈ)
	int _playerTileY;			// �÷��̾��� ���� Y ��ǥ (���� ������Ʈ)
	int _enemyTileX;			// ���� X ��ǥ (������ ������Ʈ)
	int _enemyTileY;			// ���� Y ��ǥ (������ ������Ʈ) 
	int _moveIndex;				// ���� Ÿ���� �ε���
	int _rndX;					// ��ġ�� �ʱ� ���� ����
	int _rndY;					// ��ġ�� �ʱ� ���� ����

	bool _end;					// a* Ž�� �Ϸ� ����			
	bool _isNPC;				// NPC���� ��������
	bool _changePoint;			// ��ǥ ���濩��
public:
	aStar();
	~aStar();

public:
	// (�� Ÿ��X ����, �� Ÿ��Y ����, ���� Ÿ��X, ���� Ÿ��Y, ������ Ÿ��X, ������ Ÿ��Y, ���̳� ������Ʈ �� �������̴� ��ǥ, NPC����)
	HRESULT init(int totalTileX, int totalTileY, int playerX, int playerY, int enemyX, int enemyY, vector<POINT> unMoveTile, bool npc);
	void release();
	void update(int playerTileX, int playerTileY, int enemyTileX, int enemyTileY);
	void render();

	// Ÿ�� ���� �Լ�
	void setTiles();
	// �� �� �ִ� ���� ã�Ƽ� ���� �Լ�
	vector<astarTile*> addOpenList(astarTile* currentTile);
	// ���� ��� ã�� �Լ�dsa
	void pathFinder(astarTile* currentTile);
	// ��ǥ ���� �Լ�
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

