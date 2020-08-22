#include "stdafx.h"
#include "aStar.h"

aStar::aStar()
{
}

aStar::~aStar()
{
}

HRESULT aStar::init(int totalTileX, int totalTileY, int playerX, int playerY, int enemyX, int enemyY, vector<POINT> unMoveTile, bool npc)
{
	_totalTileX = totalTileX;
	_totalTileY = totalTileY;

	_playerTileX = playerX;
	_playerTileY = playerY;
	
	_enemyTileX = enemyX;
	_enemyTileY = enemyY;
	
	_rndX = RND->getFromIntTo(-30, 30);
	_rndY = RND->getFromIntTo(-30, 30);

	_isNPC = npc;

	_vUnMoveTile = unMoveTile;

	setTiles();

	return S_OK;
}

void aStar::setTiles()
{
	// ������ ����
	_startTile = new astarTile;
	_startTile->init(_playerTileX, _playerTileY);
	_startTile->attribute = "start";


	// ���� ����
	_endTile = new astarTile;
	_endTile->init(_enemyTileX, _enemyTileY);
	_endTile->attribute = "end";

	// ���� Ÿ���� ����Ÿ�Ϸ�
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

	//cout << _vUnMoveTile.size() << endl;
	// ������ Ÿ�� ����
	for (int i = 0; i < _vUnMoveTile.size(); ++i)
	{
		_vTotalList[_vUnMoveTile[i].y * _totalTileX + _vUnMoveTile[i].x]->attribute = "wall";
		_vTotalList[_vUnMoveTile[i].y * _totalTileX + _vUnMoveTile[i].x]->isOpen = false;

	}
}

vector<astarTile*> aStar::addOpenList(astarTile* currentTile)
{
	//  1 2 3  ��ǥ (currentTile->idX, currentTile->idY)�� 5���� �ش�
	//  4 5 6  ���� ��ǥ (startX, startY)�� 1���� �ش�
	//  7 8 9  1������ ���ʴ�� 9������ for�� ���� Ž��

	int startX = currentTile->idX - 1;
	int startY = currentTile->idY - 1;

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			// �� ������ ���, �� �Ʒ����� ��� �˻� x
			if (startY == -1 && i == 0)					continue;
			if (startY == _totalTileY - 2 && i == 2)	continue;
			if (startY == _totalTileY - 1 && i == 1)	continue;
			if (startY == _totalTileY - 1 && i == 2)	continue;

			astarTile* node = _vTotalList[(startY * _totalTileX) + startX + j + (i * _totalTileX)];

			//����ó�� 
			if (!node->isOpen)				continue;	// �������� ���� ���� ��� �н�
			if (node->attribute == "start") continue;	// �������� ��� �н�
			if (node->attribute == "wall")	continue;	// ���� ��� �н�


			//���� Ÿ���� ��� �������ش�
			node->parentNode = _currentTile;


			// �̹� ���¸���Ʈ�� �� �ִ� Ÿ���� ��� ���Ϳ� ���� ����
			bool addObj = true;

			for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
			{
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
	// NPC�� ���
	if (!_isNPC)
	{
		// Ž���� 4�̻� �Ѿ�� return (���� �������)
		if (_vCloseList.size() > 6)
		{
			// �ִܰ�� ���� �ʱ�ȭ ��
			if (!_end)
			{
				_vShortestList.clear();
				_vShortestList.push_back(_endTile);
			}

			// �θ��尡 ���� �� ���� Ž���ϸ鼭 �ִܰ�ο� �ϳ��� �־���
			while (_currentTile->parentNode != NULL)
			{
				_vShortestList.push_back(_currentTile);
				_currentTile = _currentTile->parentNode;
			}

			// ������ Index �ʱ�ȭ
			if (!_end)
			{
				_moveIndex = _vShortestList.size() - 1;
			}

			_end = true;
			return;
		}
	}

	// ���ϱ� �ſ� ���� ������ ��κ���� �����ص�
	float tempTotalCost = 5000;
	astarTile* tempTile = NULL;

	// ���� ����Ʈ ���� �ȿ��� ���� ���� ��� ã��
	for (int i = 0; i < addOpenList(currentTile).size(); ++i)
	{
		// H�� ����
		_vOpenList[i]->costToGoal = (abs(_endTile->idX - _vOpenList[i]->idX) + abs(_endTile->idY - _vOpenList[i]->idY)) * 10 ;

		POINT center1 = _vOpenList[i]->parentNode->center;
		POINT center2 = _vOpenList[i]->center;

		// �Ÿ����ؼ� Ÿ���� ũ�⺸�� ũ�� G�� ���� ( �밢���� ��� 14, ������ ��� 10 )
		_vOpenList[i]->costFromStart = (getDistance(center1.x, center1.y, center2.x, center2.y) > TILESIZE) ? 14 : 10;

		// F�� = G + H
		_vOpenList[i]->totalCost = _vOpenList[i]->costToGoal + _vOpenList[i]->costFromStart;

		// ��κ���� ���� ���� �ַ� ��� �����Ѵ�
		if (tempTotalCost > _vOpenList[i]->totalCost)
		{
			tempTotalCost = _vOpenList[i]->totalCost;
			tempTile = _vOpenList[i];
		}


		// �̹� ���¸���Ʈ�� �� �ִ� Ÿ���� ��� ���Ϳ� ���� ����
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

	// ���� �ӽ� Ÿ���� ���� ��� Ž�� ����
	if (tempTile->attribute == "end")
	{
		// �ִܰ�� ���� �ʱ�ȭ ��
		if (!_end)
		{
			_vShortestList.clear();
			_vShortestList.push_back(_endTile);
		}

		// �θ��尡 ���� �� ���� Ž���ϸ鼭 �ִܰ�ο� �ϳ��� �־���
		while (_currentTile->parentNode != NULL)
		{
			_vShortestList.push_back(_currentTile);
			_currentTile = _currentTile->parentNode;
		}

		// ������ Index �ʱ�ȭ
		if (!_end)
		{
			_moveIndex = _vShortestList.size() - 1;
		}

		_end = true;
		return;
	}
	else
	{
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
}

void aStar::release()
{
	_vTotalList.clear();
	_vOpenList.clear();
	_vCloseList.clear();
}

void aStar::update(int playerTileX, int playerTileY, int enemyTileX, int enemyTileY)
{
	// �������� ��ǥ�� ������Ʈ
	_playerTileX = playerTileX;
	_playerTileY = playerTileY;
	_enemyTileX = enemyTileX;
	_enemyTileY = enemyTileY;


	// ������ ���
	if (!_isNPC)
	{
		_aStarTimer++;
		if (_aStarTimer > 50)
		{
			_rndX = RND->getFromIntTo(-30, 30);
			_rndY = RND->getFromIntTo(-30, 30);
			release();
			setTiles();
			_aStarTimer = 0;
		}

	}
	// NPC�� ���
	else
	{
		if (_changePoint)
		{
			_changePoint = false;
			release();
			setTiles();
		}
	}

	pathFinder(_currentTile);
}

void aStar::render()
{
	// �ִ� ��� ����
	if (KEYMANAGER->isToggleKey('V'))
	{
		for (int i = 0; i < _vShortestList.size(); ++i)
		{
			RECT temp;
			temp = RectMakeCenter(_vShortestList[i]->center.x, _vShortestList[i]->center.y, 50, 50);

			CAMERAMANAGER->rectangle(temp, D2D1::ColorF::Red, 5.f);
		}
	}
}
