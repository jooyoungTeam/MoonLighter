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

	//현재 타일은 시작타일로
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
			// 맨 위일 경우 검사 x
			if (startY == -1 && i == 0) continue;
			// 맨 아래일 경우 검사 x
			if (startY == _totalTileY - 2 && i == 2) continue;
			if ((startY == _totalTileY - 1 && i == 1) || (startY == _totalTileY - 1 && i == 2)) continue;

			astarTile* node = _vTotalList[(startY * _totalTileX) + startX + j + (i * _totalTileX)];

			//예외처리 
			if (!node->isOpen) continue;
			if (node->attribute == "start") continue;
			if (node->attribute == "wall") continue;


			//현재 타일을 계속 갱신해준다
			node->parentNode = _currentTile;

			bool addObj = true;

			for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
			{
				//이미 갈 수 있다고 판단 된 애다 (이미 벡터 안에 있는 타일이다)
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
		return;
	}

	//비교하기 매우 쉽게 임의의 경로비용을 설정해둠
	float tempTotalCost = 5000;
	astarTile* tempTile = NULL;

	//오픈 리스트 벡터 안에서 가장 빠른 경로를 뽑아봅시다
	for (int i = 0; i < addOpenList(currentTile).size(); ++i)
	{
		//H값 연산
		_vOpenList[i]->costToGoal = (abs(_endTile->idX - _vOpenList[i]->idX) + abs(_endTile->idY - _vOpenList[i]->idY)) * 10 ;

		POINT center1 = _vOpenList[i]->parentNode->center;
		POINT center2 = _vOpenList[i]->center;

		_vOpenList[i]->costFromStart = (getDistance(center1.x, center1.y, center2.x, center2.y) > TILESIZE) ? 14 : 10;

		//F 구했다
		_vOpenList[i]->totalCost = _vOpenList[i]->costToGoal + _vOpenList[i]->costFromStart;

		//경로비용이 가장 작은 애로 계속 갱신한다
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

	//함수 내부에서 자기 자신을 호출하는 것이 재귀함수
	//재귀함수는 일단 속도가 느리지만 코드가 매우 단촐해진다는 장점이 있음
	//그치만 주의해야하는게
	//재귀호출시 소량의 메모리가 쌓임(스택 메모리) 이 스택 메모리가
	//약 1.2메가를 넘게되면 메모리 오버로 터지는 이 현상을
	//스택 오버 플로우 라고 함 (stack overflow)

	//그치만 이 스택메모리 사이즈는 명령어로 조절 가능함.

	pathFinder(_currentTile);
}

void aStar::release()
{
	for (int i = 0; i < _vTotalList.size(); ++i)
	{
		SAFE_DELETE(_vTotalList[i]);
	}
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

	if (_aStarTimer > 50)
	{
		release();
		setTiles();
		pathFinder(_currentTile);
		_moveIndex = 0;
		_aStarTimer = 0;
	}
}

void aStar::render()
{
	for (int i = 0; i < _vCloseList.size(); ++i)
	{
		D2DRenderer::GetInstance()->DrawRectangle(_vCloseList[i]->rc, D2D1::ColorF::Blue, 5.f);
	}
}
