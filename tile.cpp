#include "stdafx.h"
#include "tile.h"

HRESULT tile::init()
{
	ImageManager::GetInstance()->AddFrameImage("mapTiles", L"mapTiles.png", SAMPLETILEX, SAMPLETILEY);
	ImageManager::GetInstance()->AddImage("map1", L"Image/map/map1.png");
	CAMERAMANAGER->settingCamera(0, 0, WINSIZEX, WINSIZEY, 0, 0, TILESIZEX - WINSIZEX, TILESIZEY - WINSIZEY);
	imageLoad();
	{
		_sampleTileUI.right = WINSIZEX;
		_sampleTileUI.bottom = WINSIZEY;
		_sampleTileUI.top = 0;
		_sampleTileUI.left = WINSIZEX - 510;
	}
	{
		_mapMove[MOVE_LEFT].rc.left = 0;
		_mapMove[MOVE_LEFT].rc.right = 100;
		_mapMove[MOVE_LEFT].rc.top = 0;
		_mapMove[MOVE_LEFT].rc.bottom = WINSIZEY;

		_mapMove[MOVE_RIGHT].rc.left = WINSIZEX - 610;
		_mapMove[MOVE_RIGHT].rc.right = WINSIZEX - 510;
		_mapMove[MOVE_RIGHT].rc.top = 0;
		_mapMove[MOVE_RIGHT].rc.bottom = WINSIZEY;

		_mapMove[MOVE_UP].rc.left = 0;
		_mapMove[MOVE_UP].rc.right = WINSIZEX - 510;
		_mapMove[MOVE_UP].rc.top = 0;
		_mapMove[MOVE_UP].rc.bottom = 100;

		_mapMove[MOVE_DOWN].rc.left = 0;
		_mapMove[MOVE_DOWN].rc.right = WINSIZEX - 510;
		_mapMove[MOVE_DOWN].rc.top = WINSIZEY - 100;
		_mapMove[MOVE_DOWN].rc.bottom = WINSIZEY;
		_currentMove = MOVE_NULL;
	}



	_button = new button;
	_button->init();
	setup();
	return S_OK;
}

void tile::render()
{
	// 그리는곳
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		CAMERAMANAGER->rectangle(_tiles[i].rc, D2D1::ColorF::Black, 1.0f);
		if (_tiles[i].terrain != TR_NONE)
		{
			Vector2 vec((_tiles[i].rc.left + _tiles[i].rc.right) * 0.5f, (_tiles[i].rc.top + _tiles[i].rc.bottom) * 0.5f);

			CAMERAMANAGER->frameRender(ImageManager::GetInstance()->FindImage("mapTiles"), vec.x, vec.y, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
		}
		//ImageManager::GetInstance()->FindImage("mapTiles")->FrameRender(vec, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
	
		if (_tiles[i].isDrag)
		{
			CAMERAMANAGER->rectangle(_tiles[i].rc, D2D1::ColorF::LimeGreen, 1.0f, 5);
		}
	}


	// 선택중인 렉트
	{
		CAMERAMANAGER->rectangle(_dragTile, D2D1::ColorF::LimeGreen, 1.0f, 5);
	}
	// ---------------- 오브젝트
	//for (int i = 0; i < TILEX * TILEY; ++i)
	//{
	//
	//	if (_tiles[i].object == OBJ_NONE) continue;
	//
	//	Vector2 vec((_tiles[i].rc.left + _tiles[i].rc.right) * 0.5f, (_tiles[i].rc.top + _tiles[i].rc.bottom) * 0.5f);
	//	//ImageManager::GetInstance()->FindImage("mapTiles")->FrameRender(vec, _tiles[i].objFrameX, _tiles[i].objFrameY);
	//}

	D2DRenderer::GetInstance()->FillRectangle(_sampleTileUI, D2D1::ColorF::White, 1);
	D2DRenderer::GetInstance()->DrawRectangle(_sampleTileUI, D2D1::ColorF::Black, 1);

	// 팔레트
	for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
	{
		D2DRenderer::GetInstance()->DrawRectangle(_sampleTile[i].rc, D2D1::ColorF::Black, 1.0f);
		Vector2 vec((_sampleTile[i].rc.left + _sampleTile[i].rc.right) * 0.5f, (_sampleTile[i].rc.top + _sampleTile[i].rc.bottom) * 0.5f);

		if (_button->getType() == BUTTON_TERRAIN)
		{
			ImageManager::GetInstance()->FindImage("mapTiles")->FrameRender(vec, _sampleTile[i].terrainFrameX, _sampleTile[i].terrainFrameY);
		}
		else if (_button->getType() == BUTTON_OBJECT)
		{
			//ImageManager::GetInstance()->FindImage("의자")->Render(vec);
		}

	}


	_button->render();

	// ------------------ 마지막 렌더 ------------------------------------ 

	D2DRenderer::GetInstance()->DrawRectangle(_currentRect, D2D1::ColorF::LimeGreen, 1.0f, 5);

	if (_drag.isDraw)
	{
		//D2DRenderer::GetInstance()->DrawRectangle(_drag.rc, D2D1::ColorF::SteelBlue, 1, 1);
		//D2DRenderer::GetInstance()->FillRectangle(_drag.rc, D2D1::ColorF::SteelBlue, 0.5f);
	}

	// 맵 이동
	for (int i = 0; i < 4; i++)
	{
		if (i == (int)_currentMove)
		{
			D2DRenderer::GetInstance()->FillRectangle(_mapMove[i].rc, D2D1::ColorF::Silver, 0.3f);
		}
	}

}

void tile::update()
{

	mapMove();
	setMap();
	drag();
	save();
	load();

}

void tile::release()
{
}

void tile::drag()
{
	// ---------------- 시작점 --------------------- //
	if (KEYMANAGER->isOnceKeyDown(VK_LSHIFT))
	{
		_drag.isDraw = true;
		_drag.startPos = _ptMouse;
		_drag.startPos.x += CAMERAMANAGER->getLeft();
		_drag.startPos.y += CAMERAMANAGER->getTop();
	}

	if (KEYMANAGER->isStayKeyDown(VK_LSHIFT))
	{
		_drag.isDraw = true;
		_drag.endPos = _ptMouse;
		_drag.endPos.x += CAMERAMANAGER->getLeft();
		_drag.endPos.y += CAMERAMANAGER->getTop();

		if (_drag.startPos.x < _drag.endPos.x && _drag.startPos.y < _drag.endPos.y)
		{
			_drag.rc.left = _drag.startPos.x;
			_drag.rc.top = _drag.startPos.y;
			_drag.rc.right = _ptMouse.x + CAMERAMANAGER->getLeft();
			_drag.rc.bottom = _ptMouse.y + CAMERAMANAGER->getTop();
		}
		else if (_drag.startPos.x > _drag.endPos.x && _drag.startPos.y < _drag.endPos.y)
		{
			_drag.rc.left = _ptMouse.x + CAMERAMANAGER->getLeft();
			_drag.rc.top = _drag.startPos.y;
			_drag.rc.right = _drag.startPos.x;
			_drag.rc.bottom = _ptMouse.y + CAMERAMANAGER->getTop();
		}
		else if (_drag.startPos.x < _drag.endPos.x && _drag.startPos.y > _drag.endPos.y)
		{
			_drag.rc.left = _drag.startPos.x;
			_drag.rc.top = _ptMouse.y + CAMERAMANAGER->getTop();
			_drag.rc.right = _ptMouse.x + CAMERAMANAGER->getLeft();
			_drag.rc.bottom = _drag.startPos.y;
		}
		else
		{
			_drag.rc.left = _ptMouse.x + CAMERAMANAGER->getLeft();
			_drag.rc.top = _ptMouse.y + CAMERAMANAGER->getTop();
			_drag.rc.right = _drag.startPos.x;
			_drag.rc.bottom = _drag.startPos.y;
		}


		for (int i = 0; i < TILEX * TILEY; i++)
		{
			if (isCollision(_drag.rc, _tiles[i].rc))
			{
				_tiles[i].isDrag = true;
			}
			else
			{
				_tiles[i].isDrag = false;
			}
		}

	}
	if (KEYMANAGER->isOnceKeyUp(VK_LSHIFT))
	{
		_drag.isDraw = false;


		for (int i = 0; i < TILEX * TILEY; i++)
		{
			if (isCollision(_drag.rc, _tiles[i].rc))
			{
				if (_button->getType() == BUTTON_TERRAIN)
				{
					_tiles[i].terrainFrameX = _currentTile.x;
					_tiles[i].terrainFrameY = _currentTile.y;
					_tiles[i].terrain = terrainSelect(_currentTile.x, _currentTile.y);
				}
				
				//else if (_button->getType() == BUTTON_OBJECT)
				//{
				//	_tiles[i].objFrameX = _currentTile.x;
				//	_tiles[i].objFrameY = _currentTile.y;
				//
				//	_tiles[i].object = objectSelect(_currentTile.x, _currentTile.y);
				//}
				//else if (_button->getType() == BUTTON_CLEAR)
				//{
				//	_tiles[i].objFrameX = NULL;
				//	_tiles[i].objFrameY = NULL;
				//	_tiles[i].object = OBJ_NONE;
				//}


				if(_currentTile.x == 6 && _currentTile.y == 2)
					_vDragTile.push_back(i);
			}
			_tiles[i].isDrag = false;
		}

		if (_vDragTile.size() > 0)
		{
			float tempWidth = _tiles[_vDragTile[_vDragTile.size() - 1]].rc.right - _tiles[_vDragTile[0]].rc.left;
			float tempHeight = _tiles[_vDragTile[_vDragTile.size() - 1]].rc.bottom - _tiles[_vDragTile[0]].rc.top;
			
			_dragNumX = tempWidth / TILESIZE;
			_dragNumY = tempHeight / TILESIZE;

			for (int i = 0; i < _vDragTile.size(); i++)
			{
				if (_button->getType() == BUTTON_TERRAIN)
				{
					// 첫번째
					if (i == 0)
					{
						_tiles[_vDragTile[i]].terrainFrameX = 0;
						_tiles[_vDragTile[i]].terrainFrameY = 0;
						_tiles[i].terrain = terrainSelect(4, 0);
						continue;
					}
					// 윗줄
					if (i > 0 && i < _dragNumX - 1)
					{
						_tiles[_vDragTile[i]].terrainFrameX = 7;
						_tiles[_vDragTile[i]].terrainFrameY = 0;
						_tiles[i].terrain = terrainSelect(4, 0);
						continue;
					}
					// 오른쪽 위
					if (i == _dragNumX - 1)
					{
						_tiles[_vDragTile[i]].terrainFrameX = 6;
						_tiles[_vDragTile[i]].terrainFrameY = 0;
						_tiles[i].terrain = terrainSelect(4, 0);
						continue;
					}
					// 왼쪽 밑
					if (i == _vDragTile.size() - _dragNumX)
					{
						_tiles[_vDragTile[i]].terrainFrameX = 2;
						_tiles[_vDragTile[i]].terrainFrameY = 0;
						_tiles[i].terrain = terrainSelect(4, 0);
						continue;
					}
					// 밑줄
					if (i > _vDragTile.size() - _dragNumX && i < _vDragTile.size() - 1)
					{
						_tiles[_vDragTile[i]].terrainFrameX = 3;
						_tiles[_vDragTile[i]].terrainFrameY = 0;
						_tiles[i].terrain = terrainSelect(4, 0);
						continue;
					}
					// 마지막
					if (i == _vDragTile.size() - 1)
					{
						_tiles[_vDragTile[i]].terrainFrameX = 4;
						_tiles[_vDragTile[i]].terrainFrameY = 0;
						_tiles[i].terrain = terrainSelect(4, 0);
						continue;
					}

					// 왼쪽 줄
					if (i % _dragNumX == 0)
					{
						_tiles[_vDragTile[i]].terrainFrameX = 1;
						_tiles[_vDragTile[i]].terrainFrameY = 0;
						_tiles[i].terrain = terrainSelect(4, 0);
						continue;
					}
					// 오른쪽 줄
					if (i % _dragNumX == _dragNumX - 1)
					{
						_tiles[_vDragTile[i]].terrainFrameX = 5;
						_tiles[_vDragTile[i]].terrainFrameY = 0;
						_tiles[i].terrain = terrainSelect(4, 0);
						continue;
					}


					_tiles[_vDragTile[i]].terrainFrameX = 8;
					_tiles[_vDragTile[i]].terrainFrameY = 0;
					_tiles[_vDragTile[i]].terrain = terrainSelect(_currentTile.x, _currentTile.y);
				}

			}
			_vDragTile.clear();
		}
	}

}

void tile::setup()
{
	for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
	{
		_sampleTile[i].terrainFrameX = i % SAMPLETILEX;
		_sampleTile[i].terrainFrameY = i / SAMPLETILEX;

		_sampleTile[i].rc = RectMake(WINSIZEX / 2 + 300 + _sampleTile[i].terrainFrameX * TILESIZE * 1.1f, 30 + _sampleTile[i].terrainFrameY * TILESIZE * 1.1f, TILESIZE, TILESIZE);
	}

	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			_tiles[i * TILEX + j].rc = RectMake(j * TILESIZE, i * TILESIZE, TILESIZE, TILESIZE);
			_tiles[i * TILEX + j].isDrag = false;
		}
	}


	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		_tiles[i].terrainFrameX = 8;
		_tiles[i].terrainFrameY = 2;
		_tiles[i].terrain = terrainSelect(_tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
	}
}

void tile::setMap()
{
	POINT pt = _ptMouse;
	pt.x += CAMERAMANAGER->getLeft();
	pt.y += CAMERAMANAGER->getTop();

	// 선택할 때 범위
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
		{
			if (PtInRect(&_sampleTile[i].rc, _ptMouse))
			{
				_currentTile.x = _sampleTile[i].terrainFrameX;

				cout << _sampleTile[i].terrainFrameX << endl;
				_currentTile.y = _sampleTile[i].terrainFrameY;
				_currentRect = RectMake(_sampleTile[i].rc.left, _sampleTile[i].rc.top, TILESIZE, TILESIZE);
				break;
			}
		}

		_button->update();
	}
	// 그냥 지나갈 때 범위 선택
	for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
	{
		if (PtInRect(&_sampleTile[i].rc, _ptMouse))
		{
			_dragTile = RectMake(_sampleTile[i].rc.left, _sampleTile[i].rc.top, TILESIZE, TILESIZE);
			break;
		}
	}


	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < TILEX * TILEY; i++)
		{
			if (PtInRect(&_tiles[i].rc, pt) && _ptMouse.x <= WINSIZEX - 618)
			{
				if (_button->getType() == BUTTON_TERRAIN)
				{
					_tiles[i].terrainFrameX = _currentTile.x;
					_tiles[i].terrainFrameY = _currentTile.y;
					_tiles[i].terrain = terrainSelect(_currentTile.x, _currentTile.y);
				}
				//else if (_button->getType() == BUTTON_OBJECT)
				//{
				//	_tiles[i].objFrameX = _currentTile.x;
				//	_tiles[i].objFrameY = _currentTile.y;
				//
				//	_tiles[i].object = objectSelect(_currentTile.x, _currentTile.y);
				//}
				//else if (_button->getType() == BUTTON_CLEAR)
				//{
				//	_tiles[i].objFrameX = NULL;
				//	_tiles[i].objFrameY = NULL;
				//	_tiles[i].object = OBJ_NONE;
				//}
				break;
			}
		}
	}


	

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (PtInRect(&_tiles[i].rc, pt))
		{
			_dragTile = RectMake(_tiles[i].rc.left, _tiles[i].rc.top, TILESIZE, TILESIZE);
			break;
		}
	}
}

void tile::save()
{
	if (_button->getType() == BUTTON_SAVE)
	{
		_saveTime++;
		if (_saveTime % 100 == 0)
		{
			// ----------------- 중복 실행 안되도록 여기에 입력
			HANDLE file;
			DWORD write;

			file = CreateFile("tilemap.map", GENERIC_WRITE, NULL, NULL,
				CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

			WriteFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &write, NULL);

			CloseHandle(file);

			_saveTime = 0;
			_button->setType(BUTTON_TERRAIN);
		}
	}
}

void tile::load()
{
	if (_button->getType() == BUTTON_LOAD)
	{
		HANDLE file;
		DWORD read;

		file = CreateFile("tilemap.map", GENERIC_READ, NULL, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);

		CloseHandle(file);
		_button->setType(BUTTON_TERRAIN);
	}

}

void tile::imageLoad()
{
	ImageManager::GetInstance()->AddImage("의자", L"Object/bench.png");
	ImageManager::GetInstance()->AddImage("표지판", L"Object/potionBoard.png");
	//ImageManager::GetInstance()

}

void tile::addObject()
{
	//tagObject* tempObject;
	//tempObject->img = ImageManager::GetInstance()->FindImage("의자");
	//tempObject->

}

void tile::mapMove()
{

	for (int i = 0; i < 4; i++)
	{
		//_currentMove = MOVE_NULL;
		if (PtInRect(&_mapMove[i].rc, _ptMouse))
		{
			_currentMove = MOVE_NULL;
			if (i == MOVE_LEFT)
			{
				CAMERAMANAGER->setX(CAMERAMANAGER->getX() - 5);
				_currentMove = MOVE_LEFT;
			}
		    if (i == MOVE_RIGHT)
			{
				CAMERAMANAGER->setX(CAMERAMANAGER->getX() + 5);
				_currentMove = MOVE_RIGHT;
			}
			if (i == MOVE_UP)
			{
				CAMERAMANAGER->setY(CAMERAMANAGER->getY() - 5);
				_currentMove = MOVE_UP;
			}
			if (i == MOVE_DOWN)
			{
				CAMERAMANAGER->setY(CAMERAMANAGER->getY() + 5);
				_currentMove = MOVE_DOWN;
			}
		}

	}
}


TERRAIN tile::terrainSelect(int frameX, int frameY)
{
	for (int i = 0; i < 9; i++)
	{
		// 첫번 째 줄
		if(frameX == 8 && frameY == 0) return TR_FLOOR;
		else if(frameX == i && frameY == 0) return TR_WALL;	

		// 두번째 줄
		if (frameX == i && frameY == 1) return TR_GRASS;

		if (frameX == 6 && frameY == 2) return TR_WALL;
	}

	return TR_NONE;
}

OBJECT tile::objectSelect(int frameX, int frameY)
{
	if (frameX == 0 && frameY == 0)  return OBJ_TANK1;
	if (frameX == 0 && frameY == 9)  return OBJ_TANK2;
	if (frameX == 3 && frameY == 3)  return OBJ_BLOCK1;
	if (frameX == 4 && frameY == 4)  return OBJ_BLOCK3;
	if (frameX == 15 && frameY == 3)  return OBJ_BLOCKS;

	return OBJ_BLOCK1;
}
