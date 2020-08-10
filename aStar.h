#pragma once
#include "gameNode.h"
#include "tile.h"
#include <vector>
#include <string>

class aStar : public gameNode
{
	//��ü Ÿ���� ���� ����
	vector<tile*>			_vTotalList;
	vector<tile*>::iterator _viTotalList;

	//�� �� �ִ� Ÿ���� ���� ����
	vector<tile*>			_vOpenList;
	vector<tile*>::iterator _viOpenList;

	vector<tile*>			_vCloseList;
	vector<tile*>::iterator _viCloseList;

	tile* _startTile;		//���� Ÿ��
	tile* _endTile;			//�� Ÿ��
	tile* _currentTile;		//���� Ÿ��(���)

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

	// �� �ƴ� �װ�
	HRESULT init();

	//Ÿ�� ���� �Լ�
	void setTiles(int targetX, int targetY);

	//�� �� �ִ� ���� ã�Ƽ� ���� �Լ�
	vector<tile*> addOpenList(tile* currentTile);

	//���� ��� ã�� �Լ�
	void pathFinder(tile* currentTile);

	void release();
	void update();
	void render();

	void move();
};

