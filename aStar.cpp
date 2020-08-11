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

	_isNPC = npc;

	_vUnMoveTile = unMoveTile;

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

	for (int i = 0; i < _vUnMoveTile.size(); ++i)
	{
		_vTotalList[_vUnMoveTile[i].y * _totalTileX + _vUnMoveTile[i].x]->attribute = "wall";
		_vTotalList[_vUnMoveTile[i].y * _totalTileX + _vUnMoveTile[i].x]->isOpen = false;

	/*	cout << _vTotalList[_vUnMoveTile[i].y * _totalTileY + _vUnMoveTile[i].x]->attribute << endl;
		cout << _vUnMoveTile[i].x << endl;
		cout << _vUnMoveTile[i].y << endl;*/

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
			if (node->attribute == "wall")
			{
				cout << "들어옴" << endl;
				continue;
			}


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
	
	if (!_isNPC)
	{
		if (_vCloseList.size() > 4)
		{
			if(!_end)
				_moveIndex = 0;
			_end = true;
			return;
		}
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
		/*while (_currentTile->parentNode != NULL)
		{
			_currentTile = _currentTile->parentNode;
		}*/
		_vCloseList.push_back(tempTile);
		
		if(!_end)
			_moveIndex = 0;

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
		_vOldCloseList = _vCloseList;
	}

	if (!_isNPC)
	{
		if (_aStarTimer > 50)
		{
			_rndX = RND->getFromIntTo(-30, 30);
			_rndY = RND->getFromIntTo(-30, 30);
			release();
			setTiles();
			_aStarTimer = 0;
		}

	}
	else
	{
		if (_changePoint)
		{
			_changePoint = false;
			release();
			setTiles();
			_aStarTimer = 0;
		}
	}

	pathFinder(_currentTile);
}

void aStar::render()
{
	/*for (int i = 0; i < _vTotalList.size(); ++i)
	{
		if (_vTotalList[i]->attribute == "wall")
		{
			RECT temp;
			temp = RectMakeCenter(_vTotalList[i]->center.x, _vTotalList[i]->center.y, 50, 50);

			CAMERAMANAGER->rectangle(temp, D2D1::ColorF::Green, 5.f);
		}

		else if (_vTotalList[i]->attribute == "start")
		{
			RECT temp;
			temp = RectMakeCenter(_vTotalList[i]->center.x, _vTotalList[i]->center.y, 50, 50);

			CAMERAMANAGER->rectangle(temp, D2D1::ColorF::Yellow, 5.f);
		}

		else if (_vTotalList[i]->attribute == "end")
		{
			RECT temp;
			temp = RectMakeCenter(_vTotalList[i]->center.x, _vTotalList[i]->center.y, 50, 50);

			CAMERAMANAGER->rectangle(temp, D2D1::ColorF::Purple, 5.f);
		}
		else
		{
			RECT temp;
			temp = RectMakeCenter(_vTotalList[i]->center.x, _vTotalList[i]->center.y, 50, 50);

			CAMERAMANAGER->rectangle(temp, D2D1::ColorF::Blue, 5.f);
		}
		
	}*/

	//for (int i = 0; i < _vOldCloseList.size(); ++i)
	//{
	//	RECT temp;
	//	temp = RectMakeCenter(_vOldCloseList[i]->center.x, _vOldCloseList[i]->center.y, 50, 50);

	//	//D2DRenderer::GetInstance()->DrawRectangle(temp, D2D1::ColorF::Blue, 5.f);

	//	CAMERAMANAGER->rectangle(temp, D2D1::ColorF::Red, 5.f);
	//}

	//for (int i = 0; i < _vCloseList.size(); ++i)
	//{
	//	RECT temp;
	//	temp = RectMakeCenter(_vCloseList[i]->center.x, _vCloseList[i]->center.y, 50, 50);

	//	//D2DRenderer::GetInstance()->DrawRectangle(temp, D2D1::ColorF::Blue, 5.f);

	//	CAMERAMANAGER->rectangle(temp, D2D1::ColorF::Red, 5.f);
	//}
}
