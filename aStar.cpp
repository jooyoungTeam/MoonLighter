#include "stdafx.h"
#include "aStar.h"

aStar::aStar()
{
}

aStar::~aStar()
{
}

HRESULT aStar::init(int totalTileX, int totalTileY, int playerX, int playerY, int enemyX, int enemyY)
{
	_index = 0;
	_count = _start = 0;

	_totalTileX = totalTileX;
	_totalTileY = totalTileY;

	_playerTileX = playerX;
	_playerTileY = playerY;
	
	_enemyTileX = enemyX;
	_enemyTileY = enemyY;
	
	_rndX = RND->getFromIntTo(-30, 30);
	_rndY = RND->getFromIntTo(-30, 30);

	setTiles();

	return S_OK;
}

void aStar::setTiles()
{
	_startTile = new astarTile;
	_startTile->init(_playerTileX, _playerTileY);
	_startTile->attribute = "start";

	_endTile = new astarTile;
	_endTile->init(_enemyTileX, _enemyTileY);
	_endTile->attribute = "end";

	//���� Ÿ���� ����Ÿ�Ϸ�
	_currentTile = _startTile;

	for (int i = 0; i < _totalTileY; ++i)
	{
		for (int j = 0; j < _totalTileX; ++j)
		{
			if (j == _startTile->idX && i == _startTile->idY)
			{
				_startTile->isOpen = true;
				_vTotalList.push_back(_startTile);
				continue;
			}
			if (j == _endTile->idX && i == _endTile->idY)
			{
				_endTile->isOpen = true;
				_vTotalList.push_back(_endTile);
				continue;
			}

			astarTile* node = new astarTile;
			node->init(j, i);
			node->isOpen = true;
			_vTotalList.push_back(node);

		}
	}
}

vector<astarTile*> aStar::addOpenList(astarTile* currentTile)
{
	int startX = currentTile->idX - 1;
	int startY = currentTile->idY - 1;

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			// �� ���� ��� �˻� x
			if (startY == -1 && i == 0) continue;
			// �� �Ʒ��� ��� �˻� x
			if (startY == _totalTileY - 2 && i == 2) continue;
			if ((startY == _totalTileY - 1 && i == 1) || (startY == _totalTileY - 1 && i == 2)) continue;

			astarTile* node = _vTotalList[(startY * _totalTileX) + startX + j + (i * _totalTileX)];

			//����ó�� 
			if (!node->isOpen) continue;
			if (node->attribute == "start") continue;
			if (node->attribute == "wall") continue;


			//���� Ÿ���� ��� �������ش�
			node->parentNode = _currentTile;

			bool addObj = true;

			for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
			{
				//�̹� �� �� �ִٰ� �Ǵ� �� �ִ� (�̹� ���� �ȿ� �ִ� Ÿ���̴�)
				if (*_viOpenList == node)
				{
					addObj = false;
					break;
				}
			}

			if (!addObj) continue;


			_vOpenList.push_back(node);

		}
	}

	return _vOpenList;
}

void aStar::pathFinder(astarTile * currentTile)
{
	if (_vCloseList.size() > 4)
	{
		_end = true;
		return;
	}

	//���ϱ� �ſ� ���� ������ ��κ���� �����ص�
	float tempTotalCost = 5000;
	astarTile* tempTile = NULL;

	//���� ����Ʈ ���� �ȿ��� ���� ���� ��θ� �̾ƺ��ô�
	for (int i = 0; i < addOpenList(currentTile).size(); ++i)
	{
		//H�� ����
		_vOpenList[i]->costToGoal = (abs(_endTile->idX - _vOpenList[i]->idX) + abs(_endTile->idY - _vOpenList[i]->idY)) * 10 ;

		POINT center1 = _vOpenList[i]->parentNode->center;
		POINT center2 = _vOpenList[i]->center;

		_vOpenList[i]->costFromStart = (getDistance(center1.x, center1.y, center2.x, center2.y) > TILESIZE) ? 14 : 10;

		//F ���ߴ�
		_vOpenList[i]->totalCost = _vOpenList[i]->costToGoal + _vOpenList[i]->costFromStart;

		//��κ���� ���� ���� �ַ� ��� �����Ѵ�
		if (tempTotalCost > _vOpenList[i]->totalCost)
		{
			tempTotalCost = _vOpenList[i]->totalCost;
			tempTile = _vOpenList[i];
		}

		bool addObj = true;

		for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
		{
			if (*_viOpenList == tempTile)
			{
				addObj = false;
				break;
			}
		}

		_vOpenList[i]->isOpen = false;
		if (!addObj) continue;

		_vOpenList.push_back(tempTile);
	}


	if (tempTile->attribute == "end")
	{
		while (_currentTile->parentNode != NULL)
		{
			_currentTile = _currentTile->parentNode;
		}
		_end = true;
		return;
	}
	else
	{
		_index = 0;
		_end = false;
	}


	//too much closed to me <- ������ �ʹ� �������
	_vCloseList.push_back(tempTile);

	for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
	{
		if (*_viOpenList == tempTile)
		{
			_viOpenList = _vOpenList.erase(_viOpenList);
			break;
		}
	}

	_currentTile = tempTile;

	//�Լ� ���ο��� �ڱ� �ڽ��� ȣ���ϴ� ���� ����Լ�
	//����Լ��� �ϴ� �ӵ��� �������� �ڵ尡 �ſ� ���������ٴ� ������ ����
	//��ġ�� �����ؾ��ϴ°�
	//���ȣ��� �ҷ��� �޸𸮰� ����(���� �޸�) �� ���� �޸𸮰�
	//�� 1.2�ް��� �ѰԵǸ� �޸� ������ ������ �� ������
	//���� ���� �÷ο� ��� �� (stack overflow)

	//��ġ�� �� ���ø޸� ������� ��ɾ�� ���� ������.

	//pathFinder(_currentTile);
}

void aStar::release()
{
	_vTotalList.clear();
	_vOpenList.clear();
	_vCloseList.clear();
}

void aStar::update(int playerTileX, int playerTileY, int enemyTileX, int enemyTileY)
{
	_playerTileX = playerTileX;
	_playerTileY = playerTileY;
	_enemyTileX = enemyTileX;
	_enemyTileY = enemyTileY;
	_aStarTimer++;

	if (_end)
	{
		_moveIndex = 1;

		_vOldCloseList = _vCloseList;
	}

	if (_aStarTimer > 50)
	{
		_rndX = RND->getFromIntTo(-30, 30);
		_rndY = RND->getFromIntTo(-30, 30);
		release();
		setTiles();
		_aStarTimer = 0;
	}
	pathFinder(_currentTile);
}

void aStar::render()
{
	//for (int i = 0; i < _vOldCloseList.size(); ++i)
	//{
	//	RECT temp;
	//	temp = RectMakeCenter(_vOldCloseList[i]->center.x, _vOldCloseList[i]->center.y, 50, 50);

	//	D2DRenderer::GetInstance()->DrawRectangle(temp, D2D1::ColorF::Blue, 5.f);
	//}
}
