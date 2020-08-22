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
	// 시작점 셋팅
	_startTile = new astarTile;
	_startTile->init(_playerTileX, _playerTileY);
	_startTile->attribute = "start";


	// 끝점 셋팅
	_endTile = new astarTile;
	_endTile->init(_enemyTileX, _enemyTileY);
	_endTile->attribute = "end";

	// 현재 타일은 시작타일로
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
	// 못가는 타일 셋팅
	for (int i = 0; i < _vUnMoveTile.size(); ++i)
	{
		_vTotalList[_vUnMoveTile[i].y * _totalTileX + _vUnMoveTile[i].x]->attribute = "wall";
		_vTotalList[_vUnMoveTile[i].y * _totalTileX + _vUnMoveTile[i].x]->isOpen = false;

	}
}

vector<astarTile*> aStar::addOpenList(astarTile* currentTile)
{
	//  1 2 3  좌표 (currentTile->idX, currentTile->idY)는 5번에 해당
	//  4 5 6  따라서 좌표 (startX, startY)는 1번에 해당
	//  7 8 9  1번부터 차례대로 9번까지 for문 돌려 탐색

	int startX = currentTile->idX - 1;
	int startY = currentTile->idY - 1;

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			// 맨 윗줄일 경우, 맨 아랫줄일 경우 검사 x
			if (startY == -1 && i == 0)					continue;
			if (startY == _totalTileY - 2 && i == 2)	continue;
			if (startY == _totalTileY - 1 && i == 1)	continue;
			if (startY == _totalTileY - 1 && i == 2)	continue;

			astarTile* node = _vTotalList[(startY * _totalTileX) + startX + j + (i * _totalTileX)];

			//예외처리 
			if (!node->isOpen)				continue;	// 열려있지 않을 길인 경우 패스
			if (node->attribute == "start") continue;	// 시작점인 경우 패스
			if (node->attribute == "wall")	continue;	// 벽인 경우 패스


			//현재 타일을 계속 갱신해준다
			node->parentNode = _currentTile;


			// 이미 오픈리스트에 들어가 있는 타일인 경우 벡터에 넣지 않음
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
	// NPC일 경우
	if (!_isNPC)
	{
		// 탐색이 4이상 넘어가면 return (성능 향상위해)
		if (_vCloseList.size() > 6)
		{
			// 최단경로 벡터 초기화 후
			if (!_end)
			{
				_vShortestList.clear();
				_vShortestList.push_back(_endTile);
			}

			// 부모노드가 없을 때 까지 탐색하면서 최단경로에 하나씩 넣어줌
			while (_currentTile->parentNode != NULL)
			{
				_vShortestList.push_back(_currentTile);
				_currentTile = _currentTile->parentNode;
			}

			// 가야할 Index 초기화
			if (!_end)
			{
				_moveIndex = _vShortestList.size() - 1;
			}

			_end = true;
			return;
		}
	}

	// 비교하기 매우 쉽게 임의의 경로비용을 설정해둠
	float tempTotalCost = 5000;
	astarTile* tempTile = NULL;

	// 오픈 리스트 벡터 안에서 가장 빠른 경로 찾기
	for (int i = 0; i < addOpenList(currentTile).size(); ++i)
	{
		// H값 연산
		_vOpenList[i]->costToGoal = (abs(_endTile->idX - _vOpenList[i]->idX) + abs(_endTile->idY - _vOpenList[i]->idY)) * 10 ;

		POINT center1 = _vOpenList[i]->parentNode->center;
		POINT center2 = _vOpenList[i]->center;

		// 거리비교해서 타일의 크기보다 크면 G값 셋팅 ( 대각선의 경우 14, 직선인 경우 10 )
		_vOpenList[i]->costFromStart = (getDistance(center1.x, center1.y, center2.x, center2.y) > TILESIZE) ? 14 : 10;

		// F값 = G + H
		_vOpenList[i]->totalCost = _vOpenList[i]->costToGoal + _vOpenList[i]->costFromStart;

		// 경로비용이 가장 작은 애로 계속 갱신한다
		if (tempTotalCost > _vOpenList[i]->totalCost)
		{
			tempTotalCost = _vOpenList[i]->totalCost;
			tempTile = _vOpenList[i];
		}


		// 이미 오픈리스트에 들어가 있는 타일인 경우 벡터에 넣지 않음
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

	// 만약 임시 타일이 끝인 경우 탐색 종료
	if (tempTile->attribute == "end")
	{
		// 최단경로 벡터 초기화 후
		if (!_end)
		{
			_vShortestList.clear();
			_vShortestList.push_back(_endTile);
		}

		// 부모노드가 없을 때 까지 탐색하면서 최단경로에 하나씩 넣어줌
		while (_currentTile->parentNode != NULL)
		{
			_vShortestList.push_back(_currentTile);
			_currentTile = _currentTile->parentNode;
		}

		// 가야할 Index 초기화
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


	//too much closed to me <- 나한테 너무 가까워요
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
	// 시작점과 목표점 업데이트
	_playerTileX = playerTileX;
	_playerTileY = playerTileY;
	_enemyTileX = enemyTileX;
	_enemyTileY = enemyTileY;


	// 몬스터일 경우
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
	// NPC일 경우
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
	// 최단 경로 랜더
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
