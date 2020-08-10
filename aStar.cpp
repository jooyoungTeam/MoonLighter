#include "stdafx.h"
#include "aStar.h"
//
//aStar::aStar()
//{
//}
//
//aStar::~aStar()
//{
//}
//
//HRESULT aStar::init()
//{
//	_index = 0;
//	_count = _start = 0;
//	_enemyX = 100, _enemyY = WINSIZEY / 2;
//
//	_player = RectMakeCenter(WINSIZEX - 100, WINSIZEY / 2, 25, 25);
//	_enemy = RectMakeCenter(_enemyX, _enemyY, 25, 25);
//
//	setTiles(_enemyX, _enemyY);
//
//	return S_OK;
//}
//
//void aStar::setTiles(int targetX, int targetY)
//{
//	_index = 0;
//	for (int i = 0; i < _vTotalList.size(); ++i)
//	{
//		SAFE_RELEASE(_vTotalList[i]);
//	}
//	_vTotalList.clear();
//	for (int i = 0; i < _vOpenList.size(); ++i)
//	{
//		SAFE_RELEASE(_vOpenList[i]);
//	}
//	_vOpenList.clear();
//	for (int i = 0; i < _vCloseList.size(); ++i)
//	{
//		SAFE_RELEASE(_vCloseList[i]);
//	}
//	_vCloseList.clear();
//
//	_enemyTileX = _enemyX / TILEWIDTH;
//	_enemyTileY = _enemyY / TILEHEIGHT;
//
//	_startTile = new tile;
//	_startTile->init(_enemyTileX, _enemyTileY);
//	_startTile->setAttribute("start");
//
//	_playerTileX = _player.left / TILEWIDTH;
//	_playerTileY = _player.top / TILEHEIGHT;
//
//	_endTile = new tile;
//	_endTile->init(_playerTileX, _playerTileY);
//	_endTile->setAttribute("end");
//
//	//���� Ÿ���� ����Ÿ�Ϸ�
//	_currentTile = _startTile;
//
//	for (int i = 0; i < TILENUMY; ++i)
//	{
//		for (int j = 0; j < TILENUMX; ++j)
//		{
//			if (j == _startTile->getIdX() && i == _startTile->getIdY())
//			{
//				_startTile->setColor(RGB(0, 255, 255));
//				_startTile->setIsOpen(true);
//				_vTotalList.push_back(_startTile);
//				continue;
//			}
//			if (j == _endTile->getIdX() && i == _endTile->getIdY())
//			{
//				_endTile->setColor(RGB(10, 120, 55));
//				_endTile->setIsOpen(true);
//				_vTotalList.push_back(_endTile);
//				continue;
//			}
//
//			tile* node = new tile;
//			node->init(j, i);
//			node->setIsOpen(true);
//			_vTotalList.push_back(node);
//
//		}
//	}
//}
//
//vector<tile*> aStar::addOpenList(tile * currentTile)
//{
//	int startX = currentTile->getIdX() - 1;
//	int startY = currentTile->getIdY() - 1;
//
//	for (int i = 0; i < 3; ++i)
//	{
//		for (int j = 0; j < 3; ++j)
//		{
//			// �� ���� ��� �˻� x
//			if (startY == -1 && i == 0) continue;
//			// �� �Ʒ��� ��� �˻� x
//			if (startY == 23 && i == 2) continue;
//
//			tile* node = _vTotalList[(startY * TILENUMX) + startX + j + (i * TILENUMX)];
//
//			//����ó�� 
//			if (!node->getIsOpen()) continue;
//			if (node->getAttribute() == "start") continue;
//			if (node->getAttribute() == "wall") continue;
//
//
//			//���� Ÿ���� ��� �������ش�
//			node->setParentNode(_currentTile);
//
//			bool addObj = true;
//
//			for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
//			{
//				//�̹� �� �� �ִٰ� �Ǵ� �� �ִ� (�̹� ���� �ȿ� �ִ� Ÿ���̴�)
//				if (*_viOpenList == node)
//				{
//					addObj = false;
//					break;
//				}
//			}
//
//
//			if (node->getAttribute() != "end") node->setColor(RGB(128, 64, 28));
//
//			if (!addObj) continue;
//
//
//			_vOpenList.push_back(node);
//
//		}
//	}
//
//	return _vOpenList;
//}
//
//void aStar::pathFinder(tile * currentTile)
//{
//	//���ϱ� �ſ� ���� ������ ��κ���� �����ص�
//	float tempTotalCost = 5000;
//	tile* tempTile = NULL;
//
//	//���� ����Ʈ ���� �ȿ��� ���� ���� ��θ� �̾ƺ��ô�
//	for (int i = 0; i < addOpenList(currentTile).size(); ++i)
//	{
//		//H�� ����
//		_vOpenList[i]->setCostToGoal(
//			(abs(_endTile->getIdX() - _vOpenList[i]->getIdX()) +
//				abs(_endTile->getIdY() - _vOpenList[i]->getIdY())) * 10
//		);
//
//		POINT center1 = _vOpenList[i]->getParentNode()->getCenter();
//		POINT center2 = _vOpenList[i]->getCenter();
//
//		_vOpenList[i]->setCostFromStart((getDistance(center1.x, center1.y, center2.x, center2.y) > TILEWIDTH) ? 14 : 10);
//
//		//F ���ߴ�
//		_vOpenList[i]->setTotalCost(_vOpenList[i]->getCostToGoal() +
//			_vOpenList[i]->getCostFromStart());
//
//		//��κ���� ���� ���� �ַ� ��� �����Ѵ�
//		if (tempTotalCost > _vOpenList[i]->getTotalCost())
//		{
//			tempTotalCost = _vOpenList[i]->getTotalCost();
//			tempTile = _vOpenList[i];
//		}
//
//		bool addObj = true;
//		for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
//		{
//			if (*_viOpenList == tempTile)
//			{
//				addObj = false;
//				break;
//			}
//		}
//
//		_vOpenList[i]->setIsOpen(false);
//		if (!addObj) continue;
//
//		_vOpenList.push_back(tempTile);
//	}
//
//	if (tempTile->getAttribute() == "end")
//	{
//		while (_currentTile->getParentNode() != NULL)
//		{
//			_currentTile->setColor(RGB(22, 14, 128));
//			_currentTile = _currentTile->getParentNode();
//		}
//		_end = true;
//		return;
//	}
//	else
//	{
//		_index = 0;
//		_end = false;
//	}
//
//	//too much closed to me <- ������ �ʹ� �������
//	_vCloseList.push_back(tempTile);
//
//	for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
//	{
//		if (*_viOpenList == tempTile)
//		{
//			_viOpenList = _vOpenList.erase(_viOpenList);
//			break;
//		}
//	}
//
//	_currentTile = tempTile;
//
//	//�Լ� ���ο��� �ڱ� �ڽ��� ȣ���ϴ� ���� ����Լ�
//	//����Լ��� �ϴ� �ӵ��� �������� �ڵ尡 �ſ� ���������ٴ� ������ ����
//	//��ġ�� �����ؾ��ϴ°�
//	//���ȣ��� �ҷ��� �޸𸮰� ����(���� �޸�) �� ���� �޸𸮰�
//	//�� 1.2�ް��� �ѰԵǸ� �޸� ������ ������ �� ������
//	//���� ���� �÷ο� ��� �� (stack overflow)
//
//	//��ġ�� �� ���ø޸� ������� ��ɾ�� ���� ������.
//
//	//pathFinder(_currentTile);
//}
//
//void aStar::release()
//{
//}
//
//void aStar::update()
//{
//	move();
//	_aStarTimer++;
//
//	_enemyTileX = _enemy.left / TILEWIDTH;
//	_enemyTileY = _enemy.top / TILEHEIGHT;
//
//	_playerTileX = _player.left / TILEWIDTH;
//	_playerTileY = _player.top / TILEHEIGHT;
//
//
//	if (KEYMANAGER->isStayKeyDown('A'))
//	{
//		_player.left -= 5;
//		_player.right -= 5;
//	}
//	if (KEYMANAGER->isStayKeyDown('D'))
//	{
//		_player.left += 5;
//		_player.right += 5;
//	}
//	if (KEYMANAGER->isStayKeyDown('W'))
//	{
//		_player.top -= 5;
//		_player.bottom -= 5;
//	}
//	if (KEYMANAGER->isStayKeyDown('S'))
//	{
//		_player.top += 5;
//		_player.bottom += 5;
//	}
//
//	if (_aStarTimer > 25)
//	{
//		setTiles(_playerTileX, _playerTileY);
//		_aStarTimer = 0;
//	}
//	pathFinder(_currentTile);
//
//	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
//	{
//		for (int i = 0; i < _vTotalList.size(); ++i)
//		{
//			if (PtInRect(&_vTotalList[i]->getRect(), _ptMouse))
//			{
//				if (_vTotalList[i]->getAttribute() == "start") continue;
//				if (_vTotalList[i]->getAttribute() == "end") continue;
//
//				_vTotalList[i]->setIsOpen(false);
//				_vTotalList[i]->setAttribute("wall");
//				_vTotalList[i]->setColor(RGB(230, 140, 200));
//				break;
//			}
//		}
//	}
//	if (KEYMANAGER->isStayKeyDown(VK_RBUTTON))
//	{
//		for (int i = 0; i < _vTotalList.size(); ++i)
//		{
//			if (PtInRect(&_vTotalList[i]->getRect(), _ptMouse))
//			{
//				if (_vTotalList[i]->getAttribute() == "start") continue;
//				if (_vTotalList[i]->getAttribute() == "end") continue;
//
//				_vTotalList[i]->setIsOpen(true);
//				_vTotalList[i]->setAttribute("null");
//				_vTotalList[i]->setColor(RGB(250, 150, 0)
//				);
//				break;
//			}
//		}
//	}
//
//
//	cout << _enemyX << endl;
//	_enemy = RectMakeCenter(_enemyX, _enemyY, 25, 25);
//}
//
//void aStar::render()
//{
//	for (int i = 0; i < _vTotalList.size(); ++i)
//	{
//		_vTotalList[i]->render();
//	}
//
//	Rectangle(getMemDC(), _player);
//	Rectangle(getMemDC(), _enemy);
//}
//
//void aStar::move()
//{
//	if (_vCloseList.size() > 1)
//	{
//		_enemyAnlge = getAngle(_enemyX, _enemyY, _vCloseList[_index]->getCenter().x, _vCloseList[_index]->getCenter().y);
//
//		_enemyX += cos(_enemyAnlge) * 3;
//		_enemyY -= sin(_enemyAnlge) * 3;
//		if (getDistance(_enemyX, _enemyY, _vCloseList[_index]->getCenter().x, _vCloseList[_index]->getCenter().y) < 3)
//		{
//			if (_index < _vCloseList.size() - 1)
//				_index++;
//		}
//	}
//}
