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

	int _playerTileX;
	int _playerTileY;

	int _enemyTileX;
	int _enemyTileY;
public:
	aStar();
	~aStar();

	// �� �ƴ� �װ�
	HRESULT init();

	//Ÿ�� ���� �Լ�
	void setTiles();

	//�� �� �ִ� ���� ã�Ƽ� ���� �Լ�
	vector<tile*> addOpenList(tile* currentTile);

	//���� ��� ã�� �Լ�
	void pathFinder(tile* currentTile);

	void release();
	void update();
	void render();
};

