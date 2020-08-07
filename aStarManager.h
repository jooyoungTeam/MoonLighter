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


public:
	aStarManager() {}
	~aStarManager() {}

public:
	HRESULT init();
	void render();
	void update();
	void release();

	//Ÿ�� ���� �Լ�
	void setTiles(int targetX, int targetY);
	//�� �� �ִ� ���� ã�Ƽ� ���� �Լ�
	vector<tile*> addOpenList(tile* currentTile);
	//���� ��� ã�� �Լ�
	void pathFinder(tile* currentTile);
};

