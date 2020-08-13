#include "stdafx.h"
#include "tile.h"

HRESULT tile::init()
{
	CAMERAMANAGER->settingCamera(0, 0, WINSIZEX, WINSIZEY, 0, 0, TILESIZEX - WINSIZEX, TILESIZEY - WINSIZEY);
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
	CAMERAMANAGER->render(_mapImg, 0, 0, 1);

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
				//CAMERAMANAGER->addFrameRender(ImageManager::GetInstance()->FindImage("mapTiles"), )


				if (_tiles[index].isColTile && _button->getType() == BUTTON_COLLISION)
					CAMERAMANAGER->fillRectangle(_tiles[index].rc, D2D1::ColorF::Red, 0.5f);
			}

			if (_tiles[index].isDrag)
			{
				CAMERAMANAGER->rectangle(_tiles[index].rc, D2D1::ColorF::LimeGreen, 1.0f, 5);
			}


		}
	}


	for (int i = 0; i < _object.size(); i++) // 오브젝트들 렌더
	{
		if (_object[i]->isFrameRender)
		{
			CAMERAMANAGER->zOrderFrameRender(_object[i]->img, (_object[i]->rc.left + _object[i]->rc.right) * 0.5f, (_object[i]->rc.top + _object[i]->rc.bottom) * 0.5f,
				_object[i]->rc.bottom, _object[i]->frameX, 0, _object[i]->scale, 1);


			_object[i]->count++;
			_object[i]->isFrameRender = true ? _frameCount = 5 : _frameCount = 10;
			if (_object[i]->count % _frameCount == 0)
			{
				_object[i]->count = 0;
				_object[i]->frameX++;

				if (_object[i]->img->GetMaxFrameX() <= _object[i]->frameX)
				{
					_object[i]->frameX = 0;
				}
			}

		}
		else
		{
			CAMERAMANAGER->zOrderRender(_object[i]->img, _object[i]->rc.left, _object[i]->rc.top, _object[i]->rc.bottom, 1, _object[i]->scale);
		}
		//CAMERAMANAGER->render(_object[i]->img, _object[i]->rc.left, _object[i]->rc.top, 0.4f);
		CAMERAMANAGER->rectangle(_object[i]->rc, D2D1::ColorF::LimeGreen, 1.0f, 5);
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
	wstring str;
	str.assign(_tiles[_nowIndex].str.begin(), _tiles[_nowIndex].str.end());
	D2DRenderer::GetInstance()->RenderText(_ptMouse.x, _ptMouse.y - 15, str, 15, D2DRenderer::DefaultBrush::White);

	// 미니맵
	D2DRenderer::GetInstance()->FillRectangle(_miniMap, D2D1::ColorF::Silver, 0.5f);
	D2DRenderer::GetInstance()->DrawRectangle(_miniMapMove, D2D1::ColorF::Black, 1, 2);

	if (_isSelectObject)
	{
		_currentObject->img->SetAlpha(0.5f);
		if (_currentObject->isFrameRender)
		{
			_currentObject->rc = RectMake(_ptMouse.x, _ptMouse.y, _currentObject->img->GetFrameSize().x *_currentObject->scale, _currentObject->img->GetFrameSize().y * _currentObject->scale);
			_currentObject->img->FrameRender(Vector2((_currentObject->rc.left + _currentObject->rc.right) * 0.5f, (_currentObject->rc.top + _currentObject->rc.bottom) * 0.5f), 1, 0,_currentObject->scale);
		}
		else
		{

			_currentObject->rc = RectMake(_ptMouse.x, _ptMouse.y, _currentObject->img->GetWidth() *_currentObject->scale, _currentObject->img->GetHeight() *_currentObject->scale);
			_currentObject->img->Render(Vector2(_ptMouse.x, _ptMouse.y),_currentObject->scale);
		}



		D2DRenderer::GetInstance()->FillRectangle(_currentObject->rc, D2D1::ColorF::LimeGreen, 0.4f);

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


		if (_button->getType() == BUTTON_ERASE_OBJECT)
		{
			for (int i = 0; i < _object.size(); i++)
			{
				if (isCollision(_drag.rc, _object[i]->rc))
				{
					eraseObject(i);
				}
			}
		}


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

				else if (_button->getType() == BUTTON_ERASE_TERRAIN)
				{
					_tiles[i].terrainFrameX = _currentTile.x;
					_tiles[i].terrainFrameY = _currentTile.y;
					_tiles[i].terrain = TR_NONE;
				}
				else if (_button->getType() == BUTTON_COLLISION)
				{
					_tiles[i].isColTile = true;
					_tiles[i].terrain = TR_WALL;
				}


			}
			_tiles[i].isDrag = false;
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

		// ---------- 임시
		_tiles[i].terrain = TR_NONE;
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


	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{

		if (_button->getType() == BUTTON_ERASE_OBJECT)
		{
			for (int i = 0; i < _object.size(); i++)
			{
				if (PtInRect(&_object[i]->rc, pt))
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
							tempObject->isFrameRender = _currentObject->isFrameRender;
							tempObject->rc.left = _tiles[index].rc.left;
							tempObject->rc.top = _tiles[index].rc.top;
							tempObject->frameX = 0;
							tempObject->type = _currentObject->type;
							tempObject->scale = _currentObject->scale;

							if (tempObject->isFrameRender)
							{

								tempObject->rc.right = tempObject->rc.left + tempObject->img->GetFrameSize().x * tempObject->scale;
								tempObject->rc.bottom = tempObject->rc.top + tempObject->img->GetFrameSize().y * tempObject->scale;

							}
							else
							{
								tempObject->rc.right = tempObject->rc.left + tempObject->img->GetWidth() * tempObject->scale;
								tempObject->rc.bottom = tempObject->rc.top + tempObject->img->GetHeight() * tempObject->scale;
							}
							_object.push_back(tempObject);

							_isSelectObject = false;
						}
					}
					else if (_button->getType() == BUTTON_ERASE_TERRAIN)
					{
						_tiles[index].terrain = TR_NONE;
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

void tile::saveLoad()
{
	saveDungeonMap();
	saveTownMap();
	loadDungeonMap();
	loadTownMap();
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

void tile::loadDungeonMap()
{
	if (_button->getType() == BUTTON_LOAD_DUNGEON)
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
		_button->setType(BUTTON_TERRAIN);
	}
}

void tile::loadTownMap()
{
	if (_button->getType() == BUTTON_LOAD_DUNGEON)
	{
		HANDLE file;
		DWORD read;

		file = CreateFile("townMap.map", GENERIC_READ, NULL, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		ReadFile(file, _townTiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL); //32 * 18 ==>> 1600 x 900 사이즈

		memset(_townAttribute, 0, sizeof(DWORD) * TILEX * TILEY);
		for (int i = 0; i < TILEX * TILEY; ++i)
		{
			if (_townTiles[i].terrain == TR_WALL) _townAttribute[i] |= ATTR_UNMOVE;
		}

		CloseHandle(file);
	}
}

void tile::renderTownMap()
{
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 33; j++)
		{
			int cullX = CAMERAMANAGER->getLeft() / TILESIZE;
			int cullY = CAMERAMANAGER->getTop() / TILESIZE;

			int index = (i + cullY) * TILEX + (j + cullX);

			if (_townTiles[index].terrain != TR_NONE)
			{
				Vector2 vec((_townTiles[index].rc.left + _townTiles[index].rc.right) * 0.5f, (_townTiles[index].rc.top + _townTiles[index].rc.bottom) * 0.5f);

				CAMERAMANAGER->frameRender(ImageManager::GetInstance()->FindImage("mapTiles"), vec.x, vec.y, _townTiles[index].terrainFrameX, _townTiles[index].terrainFrameY);

				CAMERAMANAGER->rectangle(_townTiles[index].rc, D2D1::ColorF::Black, 1.0f);
			}


		}
	}

}

void tile::saveDungeonMap()
{
	if (_button->getType() == BUTTON_SAVE_DUNGEON)
	{
		_saveTime++;
		if (_saveTime % 50 == 0)
		{
			// ----------------- 중복 실행 안되도록 여기에 입력
			HANDLE file;
			DWORD write;

			file = CreateFile("dungeonMap.map", GENERIC_WRITE, NULL, NULL,
				CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

			WriteFile(file, _dungeonTiles, sizeof(tagTile) * TILEX * TILEY, &write, NULL);

			CloseHandle(file);

			_saveTime = 0;
			_button->setType(BUTTON_TERRAIN);
		}
	}
}

void tile::saveTownMap()
{
	if (_button->getType() == BUTTON_SAVE_TOWN)
	{
		_saveTime++;
		if (_saveTime % 50 == 0)
		{
			// ----------------- 중복 실행 안되도록 여기에 입력
			HANDLE file;
			DWORD write;

			file = CreateFile("townMap.map", GENERIC_WRITE, NULL, NULL,
				CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

			WriteFile(file, _townTiles, sizeof(tagTile) * TILEX * TILEY, &write, NULL);

			CloseHandle(file);

			_saveTime = 0;
			_button->setType(BUTTON_TERRAIN);
		}
	}
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
			_currentObject->scale = 1;
			_currentObject->type = _currentSampleObject;
			_isSelectObject = true;
			if (_currentSampleObject == OBJ_HOUSE)
			{
				_currentObject->isFrameRender = false;
				if (i == 0)
				{
					_currentObject->img = ImageManager::GetInstance()->FindImage("Object_build_Bottom1");
					_currentObject->isFrameRender = true;
					_currentObject->scale = 1.7f;
				}
				else if (i == 1)	_currentObject->img = ImageManager::GetInstance()->FindImage("build_Bottom2");
				else if (i == 2)    _currentObject->img = ImageManager::GetInstance()->FindImage("build_Shop");
				else if (i == 3)    _currentObject->img = ImageManager::GetInstance()->FindImage("build_Enchant");

				break;
			}

			else if (_currentSampleObject == OBJ_ARCHITECTURE)
			{
				_currentObject->isFrameRender = false;
				if (i == 0)			_currentObject->img = ImageManager::GetInstance()->FindImage("build_Well");
				else if (i == 1)	_currentObject->img = ImageManager::GetInstance()->FindImage("buildBoard");
				else if (i == 2)
				{
					_currentObject->img = ImageManager::GetInstance()->FindImage("build_fountain");
					_currentObject->scale = 2.0f;
				}
				else if (i == 3)    _currentObject->img = ImageManager::GetInstance()->FindImage("bench");

				break;
			}
			else if (_currentSampleObject == OBJ_DOOR)
			{
				_currentObject->isFrameRender = false;
				if (i == 0)			_currentObject->img = ImageManager::GetInstance()->FindImage("object_door1");
				else if (i == 1)	_currentObject->img = ImageManager::GetInstance()->FindImage("object_door2");
				else if (i == 2)    _currentObject->img = ImageManager::GetInstance()->FindImage("object_door3");
				else if (i == 3)    _currentObject->img = ImageManager::GetInstance()->FindImage("object_door4");

				break;
			}
			else if (_currentSampleObject == OBJ_PLANT)
			{
				_currentObject->isFrameRender = true;
				if (i == 0)			_currentObject->img = ImageManager::GetInstance()->FindImage("plant_tree1");
				if (i == 1)
				{
					_currentObject->img = ImageManager::GetInstance()->FindImage("plant_fountain1");
					_currentObject->scale = 2.5f;
				}
				if (i == 2)		    _currentObject->img = ImageManager::GetInstance()->FindImage("plant_tree2");

				break;
			}
			else if (_currentSampleObject == OBJ_NPC)
			{
				_currentObject->isFrameRender = true;
				if (i == 0)			_currentObject->img = ImageManager::GetInstance()->FindImage("npc_1");
				if (i == 1)		    _currentObject->img = ImageManager::GetInstance()->FindImage("npc_2");
				if (i == 2)		    _currentObject->img = ImageManager::GetInstance()->FindImage("npc_3");
				if (i == 3)		    _currentObject->img = ImageManager::GetInstance()->FindImage("npc_4");

				break;
			}
			else if (_currentSampleObject == OBJ_SPA)
			{
				_currentObject->isFrameRender = false;
				if (i == 0 || i == 1 || i == 2 || i == 3)			_currentObject->img = ImageManager::GetInstance()->FindImage("spa");

				break;
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
	//if (KEYMANAGER->isStayKeyDown('W'))	CAMERAMANAGER->setY(CAMERAMANAGER->getY() - 5);
	//if (KEYMANAGER->isStayKeyDown('S'))	CAMERAMANAGER->setY(CAMERAMANAGER->getY() + 5);
	//if (KEYMANAGER->isStayKeyDown('A'))	CAMERAMANAGER->setX(CAMERAMANAGER->getX() - 5);
	//if (KEYMANAGER->isStayKeyDown('D'))	CAMERAMANAGER->setX(CAMERAMANAGER->getX() + 5);

	//CAMERAMANAGER->setXY(_playerX)

	float x = CAMERAMANAGER->getLeft() * 0.04f;
	float y = CAMERAMANAGER->getTop() * 0.04f;
	_miniMapMove = RectMakePivot(Vector2(10 + x, WINSIZEY - 210 + y), Vector2(64, 36), Pivot::LeftTop);
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
