#include "stdafx.h"
#include "tile.h"

HRESULT tile::init()
{
	CAMERAMANAGER->settingCamera(0, 0, WINSIZEX, WINSIZEY, 0, 0, TILESIZEX - WINSIZEX, TILESIZEY - WINSIZEY);
	imageLoad();
	{
		_sampleTileUI.right = WINSIZEX;
		_sampleTileUI.bottom = WINSIZEY;
		_sampleTileUI.top = 0;
		_sampleTileUI.left = WINSIZEX - 550;


		_sampleTileOnOff.right = WINSIZEX;
		_sampleTileOnOff.left = _sampleTileOnOff.right - 20;
		_sampleTileOnOff.top = WINSIZEY / 2 - 50;
		_sampleTileOnOff.bottom = WINSIZEY / 2 + 50;
	}
	{
		_mapMove[MOVE_LEFT].rc.left = 0;
		_mapMove[MOVE_LEFT].rc.right = 100;
		_mapMove[MOVE_LEFT].rc.top = 0;
		_mapMove[MOVE_LEFT].rc.bottom = WINSIZEY;

		_mapMove[MOVE_RIGHT].rc.left = WINSIZEX - 100;
		_mapMove[MOVE_RIGHT].rc.right = WINSIZEX;
		_mapMove[MOVE_RIGHT].rc.top = 0;
		_mapMove[MOVE_RIGHT].rc.bottom = WINSIZEY;

		_mapMove[MOVE_UP].rc.left = 0;
		_mapMove[MOVE_UP].rc.right = WINSIZEX;
		_mapMove[MOVE_UP].rc.top = 0;
		_mapMove[MOVE_UP].rc.bottom = 100;

		_mapMove[MOVE_DOWN].rc.left = 0;
		_mapMove[MOVE_DOWN].rc.right = WINSIZEX;
		_mapMove[MOVE_DOWN].rc.top = WINSIZEY - 100;
		_mapMove[MOVE_DOWN].rc.bottom = WINSIZEY;
		_currentMove = MOVE_NULL;
	}

	{
		_miniMap = RectMakePivot(Vector2(10, WINSIZEY - 210), Vector2(200, 200), Pivot::LeftTop);
		_miniMapMove = RectMakePivot(Vector2(10, WINSIZEY - 210), Vector2(64, 36), Pivot::LeftTop);
	}

	{
		_leftRightButton[0] = RectMakeCenter(WINSIZEX - 321, 230, 70, 70);
		_leftRightButton[1] = RectMakeCenter(WINSIZEX - 220, 230, 70, 70);
	}

	_currentObject = new tagObject;

	_button = new button;
	_button->init();
	setup();
	return S_OK;
}

void tile::render()
{

	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 33; j++)
		{
			int cullX = CAMERAMANAGER->getLeft() / TILESIZE;
			int cullY = CAMERAMANAGER->getTop() / TILESIZE;


			int index = (i + cullY) * TILEX + (j + cullX);

			CAMERAMANAGER->rectangle(_tiles[index].rc, D2D1::ColorF::Black, 1.0f);
			if (_tiles[index].terrain != TR_NONE)
			{
				Vector2 vec((_tiles[index].rc.left + _tiles[index].rc.right) * 0.5f, (_tiles[index].rc.top + _tiles[index].rc.bottom) * 0.5f);

				CAMERAMANAGER->frameRender(ImageManager::GetInstance()->FindImage("mapTiles"), vec.x, vec.y, _tiles[index].terrainFrameX, _tiles[index].terrainFrameY);
			}

			if (_tiles[index].isDrag)
			{
				CAMERAMANAGER->rectangle(_tiles[index].rc, D2D1::ColorF::LimeGreen, 1.0f, 5);
			}
		}
	}



	for (int i = 0; i < _object.size(); i++) // 오브젝트들 렌더
	{
		CAMERAMANAGER->render(_object[i]->img, _object[i]->rc.left, _object[i]->rc.top);
		CAMERAMANAGER->rectangle(_object[i]->rc, D2D1::ColorF::LimeGreen, 1.0f, 5);
	}



	// 선택중인 렉트
	{
		CAMERAMANAGER->rectangle(_dragTile, D2D1::ColorF::LimeGreen, 1.0f, 5);
	}




	if (_isActive) //팔레트가 있을 때 
	{

		ImageManager::GetInstance()->FindImage("sampleUI")->Render(Vector2(_sampleTileUI.left, _sampleTileUI.top));

		// 팔레트
		if (_button->getType() == BUTTON_TERRAIN)
		{
			for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
			{
				D2DRenderer::GetInstance()->DrawRectangle(_sampleTile[i].rc, D2D1::ColorF::Black, 1.0f);
				Vector2 vec((_sampleTile[i].rc.left + _sampleTile[i].rc.right) * 0.5f, (_sampleTile[i].rc.top + _sampleTile[i].rc.bottom) * 0.5f);
				ImageManager::GetInstance()->FindImage("mapTiles")->FrameRender(vec, _sampleTile[i].terrainFrameX, _sampleTile[i].terrainFrameY);
			}
		}
		else if (_button->getType() == BUTTON_OBJECT)
		{
			if (_currentSampleObject == OBJ_HOUSE)
			{
				ImageManager::GetInstance()->FindImage("objectHouse")->Render(Vector2(WINSIZEX - 505.0f, WINSIZEY * 0.5f - 70));
			}
			else if (_currentSampleObject == OBJ_ARCHITECTURE)
			{
				ImageManager::GetInstance()->FindImage("objectArchitecture")->Render(Vector2(WINSIZEX - 505.0f, WINSIZEY * 0.5f - 70));
			}
			else if (_currentSampleObject == OBJ_DOOR)
			{
				ImageManager::GetInstance()->FindImage("objectDoor")->Render(Vector2(WINSIZEX - 505.0f, WINSIZEY * 0.5f - 70));
			}
		}


		_button->render();

		if (_button->getType() != BUTTON_OBJECT)
			D2DRenderer::GetInstance()->DrawRectangle(_currentRect, D2D1::ColorF::LimeGreen, 1.0f, 5);
		// ------------------ 마지막 렌더 ------------------------------------ 

	}


	// 드래그 할때 생기는 렉트
	if (_drag.isDraw)
	{
		CAMERAMANAGER->rectangle(_drag.rc, D2D1::ColorF::SteelBlue, 1, 1);
		CAMERAMANAGER->fillRectangle(_drag.rc, D2D1::ColorF::SteelBlue, 0.5f);
	}
	wstring str;
	str.assign(_tiles[_nowIndex].str.begin(), _tiles[_nowIndex].str.end());
	D2DRenderer::GetInstance()->RenderText(_ptMouse.x, _ptMouse.y - 15, str, 15, D2DRenderer::DefaultBrush::White);





	// 미니맵
	D2DRenderer::GetInstance()->FillRectangle(_miniMap, D2D1::ColorF::Silver, 0.5f);
	D2DRenderer::GetInstance()->DrawRectangle(_miniMapMove, D2D1::ColorF::Black, 1, 2);

	if (_isSelectObject)
	{
		_currentObject->img->SetAlpha(0.5f);
		_currentObject->img->Render(Vector2(_ptMouse.x, _ptMouse.y));
		_currentObject->rc = RectMake(_ptMouse.x, _ptMouse.y, _currentObject->img->GetWidth(), _currentObject->img->GetHeight());

		D2DRenderer::GetInstance()->FillRectangle(_currentObject->rc, D2D1::ColorF::LimeGreen, 0.4f);

	}


	// 팔레트 껐다켰다하는 렉트
	ImageManager::GetInstance()->FindImage("sampleUIOnOff")->Render(Vector2(_sampleTileOnOff.left, _sampleTileOnOff.top));
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
		int size = _sampleTileUI.right - _sampleTileUI.left;
		cout << size << endl;
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

				if (_currentTile.x == 6 && _currentTile.y == 2)
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

		_sampleTile[i].rc = RectMake(WINSIZEX / 2 + 275 + _sampleTile[i].terrainFrameX * TILESIZE * 1.1f, WINSIZEY / 2 - 80 + _sampleTile[i].terrainFrameY * TILESIZE * 1.1f, TILESIZE, TILESIZE);
	}

	for (int i = 0; i < 4; i++)
	{
		_sampleObject[i].rc = RectMake(WINSIZEX - 505.0f + (i % 2) * 225, WINSIZEY * 0.5f - 70 + (i / 2) * 225, 225, 225);
	}


	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			_tiles[i * TILEX + j].rc = RectMake(j * TILESIZE, i * TILESIZE, TILESIZE, TILESIZE);
			_tiles[i * TILEX + j].isDrag = false;
			_tiles[i * TILEX + j].idX = j;
			_tiles[i * TILEX + j].idY = i;

			char str[10];
			sprintf_s(str, "(%d,%d)", i, j);
			_tiles[i * TILEX + j].str = str;
		}
	}


	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		_tiles[i].terrainFrameX = 8;
		_tiles[i].terrainFrameY = 0;
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
		if (_isActive)
		{
			if (_button->getType() == BUTTON_TERRAIN)
			{
				for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
				{
					if (PtInRect(&_sampleTile[i].rc, _ptMouse))
					{
						_currentTile.x = _sampleTile[i].terrainFrameX;

						_currentTile.y = _sampleTile[i].terrainFrameY;
						_currentRect = RectMake(_sampleTile[i].rc.left, _sampleTile[i].rc.top, TILESIZE, TILESIZE);
						break;
					}
				}
			}
			else if (_button->getType() == BUTTON_OBJECT)
			{
				for (int i = 0; i < 2; i++) // 왼쪽 오른쪽 버튼 눌렀을 때
				{
					if (PtInRect(&_leftRightButton[i], _ptMouse))
					{
						if (i == 0)
						{
							int num = (int)_currentSampleObject;
							num--;
							if (num < 0) num = 0;
							_currentSampleObject = (OBJECT)num;
						}
						else
						{
							int num = (int)_currentSampleObject;
							num++;
							if (num > (int)OBJ_NONE - 1) num = (int)OBJ_NONE - 1;
							_currentSampleObject = (OBJECT)num;
						}
						break;
					}
				}
				selectObject();
			}


			_button->update();
		}
		if (_button->getType() == BUTTON_ERASE)
		{
			for (int i = 0; i < _object.size(); i++)
			{
				if (PtInRect(&_object[i]->rc, pt))
				{
					eraseObject(i);
					break;
				}
			}
			cout << _object.size() << endl;
		}
		sampleOnOff();
	}


	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{

		for (int i = 0; i < 19; i++)
		{
			for (int j = 0; j < 33; j++)
			{
				int cullX = CAMERAMANAGER->getLeft() / TILESIZE;
				int cullY = CAMERAMANAGER->getTop() / TILESIZE;

				int index = (i + cullY) * TILEX + (j + cullX);


				if (PtInRect(&_tiles[index].rc, pt))
				{
					if (_isActive)
					{
						if (_ptMouse.x >= WINSIZEX - 618) break;
					}

					if (_button->getType() == BUTTON_TERRAIN)
					{
						_tiles[index].terrainFrameX = _currentTile.x;
						_tiles[index].terrainFrameY = _currentTile.y;
						_tiles[index].terrain = terrainSelect(_currentTile.x, _currentTile.y);
					}
					else if (_button->getType() == BUTTON_OBJECT)
					{
						if (_isSelectObject)
						{
							tagObject* tempObject = new tagObject;
							tempObject->img = _currentObject->img;

							tempObject->rc.left = _tiles[index].rc.left;
							tempObject->rc.top = _tiles[index].rc.top;
							tempObject->rc.right = tempObject->rc.left + tempObject->img->GetWidth();
							tempObject->rc.bottom = tempObject->rc.top + tempObject->img->GetHeight();
							_canBuild = true;
							for (int k = 0; k < _object.size(); k++)
							{
								RECT rc = tempObject->rc;
								rc.left += 10;
								rc.right -= 10;
								rc.top += 10;
								rc.bottom -= 10;
								if (isCollision(rc, _object[k]->rc))
								{
									_canBuild = false;
								}

							}
							if (_canBuild)
								_object.push_back(tempObject);

							_isSelectObject = false;

						}
					}
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

	}



	// 지금 렉트 검사
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 33; j++)
		{
			int cullX = CAMERAMANAGER->getLeft() / TILESIZE;
			int cullY = CAMERAMANAGER->getTop() / TILESIZE;

			int index = (i + cullY) * TILEX + (j + cullX);
			if (PtInRect(&_tiles[index].rc, pt))
			{
				_dragTile = RectMake(_tiles[index].rc.left, _tiles[index].rc.top, TILESIZE, TILESIZE);
				_nowIndex = index;
				break;
			}
		}
	}
}

void tile::save()
{
	if (_button->getType() == BUTTON_SAVE)
	{

		_saveTime++;
		if (_saveTime % 50 == 0)
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
	ImageManager::GetInstance()->AddImage("집1", L"Object/build_Bottom1.png");
	ImageManager::GetInstance()->AddImage("집2", L"Object/build_Bottom2.png");
	ImageManager::GetInstance()->AddImage("샵", L"Object/build_Shop.png");
	ImageManager::GetInstance()->AddFrameImage("나무", L"Object/tree.png", 4, 1);
	ImageManager::GetInstance()->AddFrameImage("mapTiles", L"mapTiles.png", SAMPLETILEX, SAMPLETILEY);
	ImageManager::GetInstance()->AddImage("map1", L"Image/map/map1.png");
	ImageManager::GetInstance()->AddImage("sampleUI", L"Object/sampleUI.png");
	ImageManager::GetInstance()->AddImage("sampleUIOnOff", L"Object/sampleUIOnOff.png");
	ImageManager::GetInstance()->AddImage("objectArchitecture", L"Object/objectArchitecture.png");
	ImageManager::GetInstance()->AddImage("objectDoor", L"Object/objectDoor.png");
	ImageManager::GetInstance()->AddImage("objectHouse", L"Object/objectHouse.png");

	ImageManager::GetInstance()->AddImage("build_Bottom1", L"Object/build_Bottom1.png");
	ImageManager::GetInstance()->AddImage("build_Bottom2", L"Object/build_Bottom2.png");
	ImageManager::GetInstance()->AddImage("build_Shop", L"Object/build_Shop.png");
	ImageManager::GetInstance()->AddImage("build_Enchant", L"Object/build_Enchant.png");

	ImageManager::GetInstance()->AddImage("build_Well", L"Object/build_Well.png");
	ImageManager::GetInstance()->AddImage("buildBoard", L"Object/buildBoard.png");
	ImageManager::GetInstance()->AddImage("build_fountain", L"Object/build_fountain.png");
	ImageManager::GetInstance()->AddImage("bench", L"Object/bench.png");


	//ImageManager::GetInstance()

}

void tile::loadDungeonMap()
{
	HANDLE file;
	DWORD read;

	file = CreateFile("dungeonMap.map", GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _dungeonTiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL); //32 * 18 ==>> 1600 x 900 사이즈

	memset(_dungeonAttribute, 0, sizeof(DWORD) * TILEX * TILEY);
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		if (_dungeonTiles[i].terrain == TR_WALL) _dungeonAttribute[i] |= ATTR_UNMOVE;
	}

	CloseHandle(file);
}

void tile::renderDungeonMap()
{

	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 33; j++)
		{
			int cullX = CAMERAMANAGER->getLeft() / TILESIZE;
			int cullY = CAMERAMANAGER->getTop() / TILESIZE;

			int index = (i + cullY) * TILEX + (j + cullX);

			if (_dungeonTiles[index].terrain != TR_NONE)
			{
				Vector2 vec((_dungeonTiles[index].rc.left + _dungeonTiles[index].rc.right) * 0.5f, (_dungeonTiles[index].rc.top + _dungeonTiles[index].rc.bottom) * 0.5f);

				CAMERAMANAGER->frameRender(ImageManager::GetInstance()->FindImage("mapTiles"), vec.x, vec.y, _dungeonTiles[index].terrainFrameX, _dungeonTiles[index].terrainFrameY);

				CAMERAMANAGER->rectangle(_dungeonTiles[index].rc, D2D1::ColorF::Black, 1.0f);
			}


		}
	}



}

void tile::selectObject()
{
	for (int i = 0; i < 4; i++)
	{
		if (PtInRect(&_sampleObject[i].rc, _ptMouse))
		{
			_isSelectObject = true;
			if (_currentSampleObject == OBJ_HOUSE)
			{
				if (i == 0)			_currentObject->img = ImageManager::GetInstance()->FindImage("build_Bottom1");
				else if (i == 1)	_currentObject->img = ImageManager::GetInstance()->FindImage("build_Bottom2");
				else if (i == 2)    _currentObject->img = ImageManager::GetInstance()->FindImage("build_Shop");
				else if (i == 3)    _currentObject->img = ImageManager::GetInstance()->FindImage("build_Enchant");
				break;
			}

			else if (_currentSampleObject == OBJ_ARCHITECTURE)
			{

				if (i == 0)			_currentObject->img = ImageManager::GetInstance()->FindImage("build_Well");
				else if (i == 1)	_currentObject->img = ImageManager::GetInstance()->FindImage("buildBoard");
				else if (i == 2)    _currentObject->img = ImageManager::GetInstance()->FindImage("build_fountain");
				else if (i == 3)    _currentObject->img = ImageManager::GetInstance()->FindImage("bench");
				break;
			}
			else if (_currentSampleObject == OBJ_DOOR)
			{

			}
		}

	}

}

void tile::eraseObject(int arrNum)
{
	_object.erase(_object.begin() + arrNum);
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

			float x = CAMERAMANAGER->getLeft() * 0.04f;
			float y = CAMERAMANAGER->getTop() * 0.04f;
			_miniMapMove = RectMakePivot(Vector2(10 + x, WINSIZEY - 210 + y), Vector2(64, 36), Pivot::LeftTop);
		}

	}
}

void tile::sampleOnOff()
{
	if (PtInRect(&_sampleTileOnOff, _ptMouse))
	{
		_isActive = !_isActive;
	}


	if (_isActive)
	{
		_sampleTileOnOff.right = _sampleTileUI.left;
		_sampleTileOnOff.left = _sampleTileOnOff.right - 20;

		_mapMove[MOVE_RIGHT].rc.right = _sampleTileOnOff.left;
		_mapMove[MOVE_RIGHT].rc.left = _mapMove[MOVE_RIGHT].rc.right - 100;


		_mapMove[MOVE_UP].rc.right = _sampleTileUI.left;

		_mapMove[MOVE_DOWN].rc.right = _sampleTileUI.left;

	}
	else
	{
		_sampleTileOnOff.right = WINSIZEX;
		_sampleTileOnOff.left = WINSIZEX - 20;

		_mapMove[MOVE_RIGHT].rc.left = WINSIZEX - 100;
		_mapMove[MOVE_RIGHT].rc.right = WINSIZEX;

		_mapMove[MOVE_UP].rc.right = WINSIZEX;

		_mapMove[MOVE_DOWN].rc.right = WINSIZEX;
	}
}



TERRAIN tile::terrainSelect(int frameX, int frameY)
{
	for (int i = 0; i < 9; i++)
	{
		// 첫번째 줄
		if (frameX == 8 && frameY == 0) return TR_FLOOR;
		else if (frameX == i && frameY == 0) return TR_WALL;

		// 두번째 줄
		if (frameX == i && frameY == 1) return TR_GRASS;

		// 세번째 줄
		if (frameX == 6 && frameY == 2) return TR_WALL;
		else if (frameX == i && frameY == 2) return TR_GRASS;
	}

	return TR_NONE;
}
