#include "stdafx.h"
#include "tile.h"

HRESULT tile::init()
{
	_tileSize[0] = 60;
	_tileSize[1] = 49;
	CAMERAMANAGER->settingCamera(0, 0, WINSIZEX, WINSIZEY, 0, 0, _tileSize[0] * TILESIZE - WINSIZEX, _tileSize[1] * TILESIZE - WINSIZEY);
	_player = new player;
	_player->init(500, 500);
	_mapImg = ImageManager::GetInstance()->AddImage("townMap", L"Image/Map/townMap.png");

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
		_miniMap = RectMakePivot(Vector2(10, WINSIZEY - 210), Vector2(_tileSize[0] * TILESIZE * 0.05f, _tileSize[1] * TILESIZE * 0.05f), Pivot::LeftTop);
		_miniMapMove = RectMakePivot(Vector2(10, WINSIZEY - 210), Vector2(WINSIZEX * 0.05f, WINSIZEY * 0.05f), Pivot::LeftTop);
	}

	{
		_leftRightButton[0] = RectMakeCenter(WINSIZEX - 321, 230, 70, 70);
		_leftRightButton[1] = RectMakeCenter(WINSIZEX - 220, 230, 70, 70);
	}


	_button = new button;
	_button->init();
	setup();
	return S_OK;
}

void tile::render()
{
	CAMERAMANAGER->render(_mapImg, 0, 0, 1);

	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 33; j++)
		{
			int cullX = CAMERAMANAGER->getLeft() / TILESIZE;
			int cullY = CAMERAMANAGER->getTop() / TILESIZE;
			int index = (i + cullY) * _tileSize[0] + (j + cullX);
			if (index >= _tileSize[0] * _tileSize[1])
				continue;

			CAMERAMANAGER->rectangle(_vTile[index].rc, D2D1::ColorF::Black, 1.0f);
			if (_vTile[index].terrain != TR_NONE)
			{
				Vector2 vec((_vTile[index].rc.left + _vTile[index].rc.right) * 0.5f, (_vTile[index].rc.top + _vTile[index].rc.bottom) * 0.5f);

				CAMERAMANAGER->frameRender(ImageManager::GetInstance()->FindImage("mapTiles"), vec.x, vec.y, _vTile[index].terrainFrameX, _vTile[index].terrainFrameY);
				//CAMERAMANAGER->addFrameRender(ImageManager::GetInstance()->FindImage("mapTiles"), )


				if (_vTile[index].isColTile && _button->getType() == BUTTON_COLLISION)
				{
					CAMERAMANAGER->fillRectangle(_vTile[index].rc, D2D1::ColorF::Red, 0.5f);
				}
			}

			if (_vTile[index].isDrag)
			{
				CAMERAMANAGER->rectangle(_vTile[index].rc, D2D1::ColorF::LimeGreen, 1.0f, 5);
			}


		}
	}


	for (int i = 0; i < _vObject.size(); i++) // 오브젝트들 렌더
	{
		if (_vObject[i].isFrameRender)
		{
			CAMERAMANAGER->zOrderFrameRender(findImg(_vObject[i].type, _vObject[i].imgNumber), (_vObject[i].rc.left + _vObject[i].rc.right) * 0.5f, (_vObject[i].rc.top + _vObject[i].rc.bottom) * 0.5f,
				_vObject[i].rc.bottom, _vObject[i].frameX, 0, _vObject[i].scale, 1);

			_vObject[i].count++;
			_vObject[i].type == OBJ_NPC ? _frameCount = 5 : _frameCount = 10;
			if (_vObject[i].count % _frameCount == 0)
			{
				_vObject[i].count = 0;
				_vObject[i].frameX++;

				if (findImg(_vObject[i].type, _vObject[i].imgNumber)->GetMaxFrameX() <= _vObject[i].frameX)
				{
					_vObject[i].frameX = 0;
				}
			}

		}
		else
		{
			CAMERAMANAGER->zOrderRender(findImg(_vObject[i].type, _vObject[i].imgNumber), _vObject[i].rc.left, _vObject[i].rc.top, _vObject[i].rc.bottom, 1, _vObject[i].scale);
		}
		//CAMERAMANAGER->render(_object[i]->img, _object[i]->rc.left, _object[i]->rc.top, 0.4f);
		//CAMERAMANAGER->rectangle(_object[i]->rc, D2D1::ColorF::LimeGreen, 1.0f, 5);
	}
	CAMERAMANAGER->zOrderALLRender();

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
			else if (_currentSampleObject == OBJ_PLANT)
			{
				ImageManager::GetInstance()->FindImage("objectPlant")->Render(Vector2(WINSIZEX - 505.0f, WINSIZEY * 0.5f - 70));
			}
			else if (_currentSampleObject == OBJ_NPC)
			{
				ImageManager::GetInstance()->FindImage("objectNPC")->Render(Vector2(WINSIZEX - 505.0f, WINSIZEY * 0.5f - 70));
			}
			else if (_currentSampleObject == OBJ_SPA)
			{
				ImageManager::GetInstance()->FindImage("objectSpa")->Render(Vector2(WINSIZEX - 505.0f, WINSIZEY * 0.5f - 70));
			}
		}


		_button->render();

		if (_button->getType() == BUTTON_TERRAIN)
			D2DRenderer::GetInstance()->DrawRectangle(_currentRect, D2D1::ColorF::LimeGreen, 1.0f, 5);
		// ------------------ 마지막 렌더 ------------------------------------ 

	}


	// 드래그 할때 생기는 렉트
	if (_drag.isDraw)
	{
		CAMERAMANAGER->rectangle(_drag.rc, D2D1::ColorF::SteelBlue, 1, 1);
		CAMERAMANAGER->fillRectangle(_drag.rc, D2D1::ColorF::SteelBlue, 0.5f);
	}

	// 미니맵
	D2DRenderer::GetInstance()->FillRectangle(_miniMap, D2D1::ColorF::Silver, 0.5f);
	D2DRenderer::GetInstance()->DrawRectangle(_miniMapMove, D2D1::ColorF::Black, 1, 2);

	if (_isSelectObject)
	{
		findImg(_currentObject.type, _currentObject.imgNumber)->SetAlpha(0.5f);
		if (_currentObject.isFrameRender)
		{
			_currentObject.rc = RectMakeCenter(_ptMouse.x, _ptMouse.y, findImg(_currentObject.type, _currentObject.imgNumber)->GetFrameSize().x *_currentObject.scale,
				findImg(_currentObject.type, _currentObject.imgNumber)->GetFrameSize().y * _currentObject.scale);
			findImg(_currentObject.type, _currentObject.imgNumber)->FrameRender(Vector2((_currentObject.rc.left + _currentObject.rc.right) * 0.5f, (_currentObject.rc.top + _currentObject.rc.bottom) * 0.5f), 1, 0, _currentObject.scale);
		}
		else
		{
			_currentObject.rc = RectMakeCenter(_ptMouse.x, _ptMouse.y, findImg(_currentObject.type, _currentObject.imgNumber)->GetWidth() * _currentObject.scale,
				findImg(_currentObject.type, _currentObject.imgNumber)->GetHeight() * _currentObject.scale);
			findImg(_currentObject.type, _currentObject.imgNumber)->Render(Vector2(_currentObject.rc.left, _currentObject.rc.top), _currentObject.scale);
		}



		D2DRenderer::GetInstance()->FillRectangle(_currentObject.rc, D2D1::ColorF::LimeGreen, 0.4f);

	}

	_player->render();

	// 팔레트 껐다켰다하는 렉트
	ImageManager::GetInstance()->FindImage("sampleUIOnOff")->Render(Vector2(_sampleTileOnOff.left, _sampleTileOnOff.top));
}

void tile::update()
{
	mapMove();
	setMap();
	drag();
	saveLoad();
	_player->update();

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

		for (int i = 0; i < _tileSize[0] * _tileSize[1]; i++)
		{
			if (isCollision(_drag.rc, _vTile[i].rc))
			{
				_vTile[i].isDrag = true;
			}
			else
			{
				_vTile[i].isDrag = false;
			}
		}

	}
	if (KEYMANAGER->isOnceKeyUp(VK_LSHIFT))
	{
		_drag.isDraw = false;


		if (_button->getType() == BUTTON_ERASE_OBJECT)
		{
			for (int i = 0; i < _vObject.size(); i++)
			{
				if (isCollision(_drag.rc, _vObject[i].rc))
				{
					eraseObject(i);
				}
			}
		}


		for (int i = 0; i < _tileSize[0] * _tileSize[1]; i++)
		{
			if (isCollision(_drag.rc, _vTile[i].rc))
			{
				if (_button->getType() == BUTTON_TERRAIN)
				{
					_vTile[i].terrainFrameX = _currentTile.x;
					_vTile[i].terrainFrameY = _currentTile.y;
					_vTile[i].terrain = terrainSelect(_currentTile.x, _currentTile.y);
				}

				else if (_button->getType() == BUTTON_ERASE_TERRAIN)
				{
					_vTile[i].terrainFrameX = _currentTile.x;
					_vTile[i].terrainFrameY = _currentTile.y;
					_vTile[i].terrain = TR_NONE;
				}
				else if (_button->getType() == BUTTON_COLLISION)
				{
					_vTile[i].isColTile = true;
					_vTile[i].terrain = TR_COLLISION;
				}


			}
			_vTile[i].isDrag = false;
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


	for (int i = 0; i < _tileSize[1]; i++)
	{
		for (int j = 0; j < _tileSize[0]; j++)
		{
			tagTile temp;
			temp.rc = RectMake(j * TILESIZE, i * TILESIZE, TILESIZE, TILESIZE);
			temp.isDrag = false;
			temp.idX = j;
			temp.idY = i;

			_vTile.push_back(temp);
		}
	}


	for (int i = 0; i < _tileSize[1] * _tileSize[0]; ++i)
	{
		_vTile[i].terrainFrameX = 8;
		_vTile[i].terrainFrameY = 0;
		_vTile[i].terrain = terrainSelect(_vTile[i].terrainFrameX, _vTile[i].terrainFrameY);

		// ---------- 임시
		_vTile[i].terrain = TR_NONE;
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

		sampleOnOff();
	}

	if (KEYMANAGER->isStayKeyDown(VK_RBUTTON))
	{
		if (_button->getType() == BUTTON_COLLISION)
		{
			for (int i = 0; i < 19; i++)
			{
				for (int j = 0; j < 33; j++)
				{
					int cullX = CAMERAMANAGER->getLeft() / TILESIZE;
					int cullY = CAMERAMANAGER->getTop() / TILESIZE;
					int index = (i + cullY) * _tileSize[0] + (j + cullX);
					if (index >= _tileSize[0] * _tileSize[1])
						continue;
					if (PtInRect(&_vTile[index].rc, pt))
					{
						_vTile[index].terrain = TR_NONE;
						break;
					}
				}
			}
		}

	}



	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{

		if (_button->getType() == BUTTON_ERASE_OBJECT)
		{
			for (int i = 0; i < _vObject.size(); i++)
			{
				if (PtInRect(&_vObject[i].rc, pt))
				{
					eraseObject(i);
					break;
				}
			}
		}

		for (int i = 0; i < 19; i++)
		{
			for (int j = 0; j < 33; j++)
			{
				int cullX = CAMERAMANAGER->getLeft() / TILESIZE;
				int cullY = CAMERAMANAGER->getTop() / TILESIZE;

				int index = (i + cullY) * _tileSize[0] + (j + cullX);
				if (index >= _tileSize[0] * _tileSize[1])
					continue;

				if (PtInRect(&_vTile[index].rc, pt))
				{
					if (_isActive)
					{
						if (_ptMouse.x >= WINSIZEX - 618) break;
					}

					if (_button->getType() == BUTTON_TERRAIN)
					{
						_vTile[index].terrainFrameX = _currentTile.x;
						_vTile[index].terrainFrameY = _currentTile.y;
						_vTile[index].terrain = terrainSelect(_currentTile.x, _currentTile.y);
					}
					else if (_button->getType() == BUTTON_OBJECT)
					{
						if (_isSelectObject)
						{
							int w = (_currentObject.rc.right - _currentObject.rc.left) / 2;
							int h = (_currentObject.rc.bottom - _currentObject.rc.top) / 2;
							tagObject tempObject = _currentObject;
							tempObject.rc.left = pt.x - w;
							tempObject.rc.top = pt.y - h;
							tempObject.frameX = 0;

							if (tempObject.isFrameRender)
							{
								tempObject.rc.right = tempObject.rc.left + findImg(tempObject.type, tempObject.imgNumber)->GetFrameSize().x * tempObject.scale;
								tempObject.rc.bottom = tempObject.rc.top + findImg(tempObject.type, tempObject.imgNumber)->GetFrameSize().y * tempObject.scale;
							}
							else
							{
								tempObject.rc.right = tempObject.rc.left + findImg(tempObject.type, tempObject.imgNumber)->GetWidth() * tempObject.scale;
								tempObject.rc.bottom = tempObject.rc.top + findImg(tempObject.type, tempObject.imgNumber)->GetHeight() * tempObject.scale;
							}
							_vObject.push_back(tempObject);
							_isSelectObject = false;
						}
					}
					else if (_button->getType() == BUTTON_ERASE_TERRAIN)
					{
						_vTile[index].terrain = TR_NONE;
					}

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

			int index = (i + cullY) * _tileSize[0] + (j + cullX);
			if (index >= _tileSize[0] * _tileSize[1])
				continue;
			if (PtInRect(&_vTile[index].rc, pt))
			{
				_dragTile = RectMake(_vTile[index].rc.left, _vTile[index].rc.top, TILESIZE, TILESIZE);
				_nowIndex = index;
				break;
			}
		}
	}
}

void tile::saveLoad()
{
	saveMap();
	loadMap();
}

void tile::imageLoad()
{
	//ImageManager::GetInstance()

	ImageManager::GetInstance()->AddImage("objectPlant", L"Object/objectPlant.png");
	ImageManager::GetInstance()->AddImage("objectNPC", L"Object/objectNPC.png");
	ImageManager::GetInstance()->AddImage("object_door1", L"Object/object_door1.png");
	ImageManager::GetInstance()->AddImage("object_door2", L"Object/object_door2.png");
	ImageManager::GetInstance()->AddImage("object_door3", L"Object/object_door3.png");
	ImageManager::GetInstance()->AddImage("object_door4", L"Object/object_door4.png");
	ImageManager::GetInstance()->AddImage("objectSpa", L"Object/objectSpa.png");
	ImageManager::GetInstance()->AddImage("plant_flower", L"Object/plant_flower.png");
	ImageManager::GetInstance()->AddImage("spa", L"Object/spa.png");

	ImageManager::GetInstance()->AddFrameImage("plant_tree1", L"Object/plant_tree1.png", 35, 1);
	ImageManager::GetInstance()->AddFrameImage("plant_tree2", L"Object/plant_tree2.png", 35, 1);
	ImageManager::GetInstance()->AddFrameImage("plant_fountain1", L"Object/plant_fountain1.png", 9, 1);
	ImageManager::GetInstance()->AddFrameImage("Object_build_Bottom1", L"Object/Object_build_Bottom1.png", 53, 1);

	ImageManager::GetInstance()->AddFrameImage("npc_1", L"Object/npc_1.png", 17, 1);
	ImageManager::GetInstance()->AddFrameImage("npc_2", L"Object/npc_2.png", 54, 1);
	ImageManager::GetInstance()->AddFrameImage("npc_3", L"Object/npc_3.png", 24, 1);
	ImageManager::GetInstance()->AddFrameImage("npc_4", L"Object/npc_4.png", 49, 1);

}


void tile::loadMap()
{
	if (_button->getType() == BUTTON_LOAD_TOWN)
	{
		HANDLE file;
		DWORD read;

		int size[2];
		// ------------ 타일

		if (_vTile.size() > 0)
			_vTile.clear();
		if (_vObject.size() > 0)
			_vObject.clear();

		file = CreateFile("townMap.map", GENERIC_READ, NULL, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		ReadFile(file, _tileSize, sizeof(int) * 2, &read, NULL); //32 * 18 ==>> 1600 x 900 사이즈

		tagTile* temTile = new tagTile[_tileSize[0] * _tileSize[1]];
		ReadFile(file, temTile, sizeof(tagTile) * _tileSize[0] * _tileSize[1], &read, NULL); //32 * 18 ==>> 1600 x 900 사이즈

		for (int i = 0; i < _tileSize[0] * _tileSize[1]; i++)
		{
			_vTile.push_back(temTile[i]);
		}

		ReadFile(file, size, sizeof(int) * 2, &read, NULL); //32 * 18 ==>> 1600 x 900 사이즈
		// ------------ 오브젝트		
		tagObject* temp = new tagObject[size[1]];
		ReadFile(file, temp, sizeof(tagObject) * size[1], &read, NULL); //32 * 18 ==>> 1600 x 900 사이즈
		for (int i = 0; i < size[1]; i++)
		{
			_vObject.push_back(temp[i]);
		}

		//memset(_townAttribute, 0, sizeof(DWORD) * TILEX * TILEY);
		//for (int i = 0; i < TILEX * TILEY; ++i)
		//{
		//	if (_townTiles[i].terrain == TR_WALL) _townAttribute[i] |= ATTR_UNMOVE;
		//}

		CloseHandle(file);



		_button->setType(BUTTON_TERRAIN);
	}


}

void tile::saveMap()
{
	if (_button->getType() == BUTTON_SAVE_TOWN)
	{
		_saveTime++;
		if (_saveTime % 50 == 0)
		{
			// ----------------- 중복 실행 안되도록 여기에 입력
			HANDLE file;
			DWORD write;
			_tileSize[0] = 60;
			_tileSize[1] = 49;
			// ----------------- 타일 ----------------- //
			tagTile* tempTile = new tagTile[60 * 49];
			for (int i = 0; i < _vTile.size(); i++)
			{
				tempTile[i] = _vTile[i];
			}
			// ----------------- 타일 ----------------- //

			// ----------------- 오브젝트 ----------------- //
			int size[2] = { 1,_vObject.size() };
			tagObject* temp = new tagObject[_vObject.size()];
			for (int i = 0; i < _vObject.size(); i++)
			{
				temp[i] = _vObject[i];
			}
			// ----------------- 오브젝트 ----------------- //

			file = CreateFile("townMap.map", GENERIC_WRITE, NULL, NULL,
				CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

			WriteFile(file, _tileSize, sizeof(int) * 2, &write, NULL);
			WriteFile(file, tempTile, sizeof(tagTile) * 60 * 49, &write, NULL);
			WriteFile(file, size, sizeof(int) * 2, &write, NULL);
			WriteFile(file, temp, sizeof(tagObject) * _vObject.size(), &write, NULL);

			CloseHandle(file);

			_saveTime = 0;
			_button->setType(BUTTON_TERRAIN);
		}
	}
}



void tile::selectObject()
{
	for (int i = 0; i < 4; i++)
	{
		if (PtInRect(&_sampleObject[i].rc, _ptMouse))
		{
			_currentObject.scale = 1;
			_currentObject.type = _currentSampleObject;
			_isSelectObject = true;
			_currentObject.imgNumber = i;
			if (_currentSampleObject == OBJ_HOUSE)
			{
				_currentObject.isFrameRender = false;
				if (i == 0)
				{
					_currentObject.scale = 1.7f;
					_currentObject.isFrameRender = true;
				}

				else if (i == 2)
				{
					_currentObject.scale = 1.2f;
				}
				break;
			}

			else if (_currentSampleObject == OBJ_ARCHITECTURE)
			{
				_currentObject.isFrameRender = false;
				if (i == 2)
				{
					_currentObject.scale = 5.0f;
				}

				break;
			}
			else if (_currentSampleObject == OBJ_DOOR)
			{
				_currentObject.isFrameRender = false;
				break;
			}
			else if (_currentSampleObject == OBJ_PLANT)
			{
				_currentObject.isFrameRender = true;
				if (i == 0)
				{
					_currentObject.scale = 1.5f;
				}
				if (i == 1)
				{
					_currentObject.scale = 2.5f;
				}
				if (i == 2)
				{
					_currentObject.scale = 1.5f;
				}
				if (i == 3)
				{
					_currentObject.scale = 2.3f;
					_currentObject.isFrameRender = false;
				}

				break;
			}
			else if (_currentSampleObject == OBJ_NPC)
			{
				_currentObject.isFrameRender = true;
				break;
			}
			else if (_currentSampleObject == OBJ_SPA)
			{
				_currentObject.isFrameRender = false;
				break;
			}


		}

	}
}

void tile::eraseObject(int arrNum)
{
	_vObject.erase(_vObject.begin() + arrNum);
}

void tile::mapMove()
{
	//if (KEYMANAGER->isStayKeyDown('W'))	CAMERAMANAGER->setY(CAMERAMANAGER->getY() - 5);
	//if (KEYMANAGER->isStayKeyDown('S'))	CAMERAMANAGER->setY(CAMERAMANAGER->getY() + 5);
	//if (KEYMANAGER->isStayKeyDown('A'))	CAMERAMANAGER->setX(CAMERAMANAGER->getX() - 5);
	//if (KEYMANAGER->isStayKeyDown('D'))	CAMERAMANAGER->setX(CAMERAMANAGER->getX() + 5);

	CAMERAMANAGER->setXY(_player->getX(), _player->getY());

	float x = CAMERAMANAGER->getLeft() * 0.05f;
	float y = CAMERAMANAGER->getTop() * 0.05f;
	_miniMapMove = RectMakePivot(Vector2(10 + x, WINSIZEY - 210 + y), Vector2(WINSIZEX * 0.05f, WINSIZEY * 0.05f), Pivot::LeftTop);
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
	}
	else
	{
		_sampleTileOnOff.right = WINSIZEX;
		_sampleTileOnOff.left = WINSIZEX - 20;
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
		if (frameX == i && frameY == 2) return TR_GRASS;

		// 네번째 줄
		if (frameX == i && frameY == 3) return TR_GRASS;

		// 다섯번째 줄
		if (frameX == i && frameY == 4) return TR_GRASS;
	}

	return TR_NONE;
}

Image * tile::findImg(OBJECT type, int imgNum)
{
	Image* img = ImageManager::GetInstance()->FindImage("plant_tree1");
	if (type == OBJ_HOUSE)
	{
		if (imgNum == 0)			         img = ImageManager::GetInstance()->FindImage("Object_build_Bottom1");
		else if (imgNum == 1)		         img = ImageManager::GetInstance()->FindImage("build_Bottom2");
		else if (imgNum == 2)		         img = ImageManager::GetInstance()->FindImage("build_Shop");
		else if (imgNum == 3)		         img = ImageManager::GetInstance()->FindImage("build_Enchant");

	}
	else if (type == OBJ_ARCHITECTURE)
	{
		if (imgNum == 0)			         img = ImageManager::GetInstance()->FindImage("build_Well");
		else if (imgNum == 1)		         img = ImageManager::GetInstance()->FindImage("buildBoard");
		else if (imgNum == 2)		         img = ImageManager::GetInstance()->FindImage("build_fountain");
		else if (imgNum == 3)		         img = ImageManager::GetInstance()->FindImage("bench");
	}
	else if (type == OBJ_DOOR)
	{
		if (imgNum == 0)					 img = ImageManager::GetInstance()->FindImage("object_door1");
		else if (imgNum == 1)				 img = ImageManager::GetInstance()->FindImage("object_door2");
		else if (imgNum == 2)				 img = ImageManager::GetInstance()->FindImage("object_door3");
		else if (imgNum == 3)				 img = ImageManager::GetInstance()->FindImage("object_door4");
	}
	else if (type == OBJ_PLANT)
	{

		if (imgNum == 0)			          img = ImageManager::GetInstance()->FindImage("plant_tree1");
		else if (imgNum == 1)		          img = ImageManager::GetInstance()->FindImage("plant_fountain1");
		else if (imgNum == 2)		          img = ImageManager::GetInstance()->FindImage("plant_tree2");
		else if (imgNum == 3)		          img = ImageManager::GetInstance()->FindImage("plant_flower");
	}
	else if (type == OBJ_NPC)
	{
		if (imgNum == 0)		              img = ImageManager::GetInstance()->FindImage("npc_1");
		else if (imgNum == 1)	              img = ImageManager::GetInstance()->FindImage("npc_2");
		else if (imgNum == 2)	              img = ImageManager::GetInstance()->FindImage("npc_3");
		else if (imgNum == 3)	              img = ImageManager::GetInstance()->FindImage("npc_4");

	}
	else if (type == OBJ_SPA)
	{
		if (imgNum == 0 || imgNum == 1 || imgNum == 2 || imgNum == 3)			img = ImageManager::GetInstance()->FindImage("spa");

	}

	return img;
}
