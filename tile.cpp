#include "stdafx.h"
#include "tile.h"

HRESULT tile::init()
{
	_tileSize[0] = 100;
	_tileSize[1] = 100;
	selectTileSizeInit();

	CAMERAMANAGER->settingCamera(0, 0, WINSIZEX, WINSIZEY, 0, 0, _tileSize[0] * TILESIZE - WINSIZEX, _tileSize[1] * TILESIZE - WINSIZEY);
	_objectManager = new objectManager;
	_objectManager->init();

	_miniMap1 = new miniMap;
	_miniMap1->init(_tileSize[0], _tileSize[1]);

	imageLoad();
	_palette = new palette;
	_palette->init();


	_button = new button;
	_button->init();
	setup();
	return S_OK;
}

void tile::render()
{
	if (_mapImg != NULL)
	{
		CAMERAMANAGER->render(_mapImg, 0, 0, 1);
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

			CAMERAMANAGER->rectangle(_vTile[index].rc, D2D1::ColorF::Black, 1.0f);
			if (_vTile[index].terrain != TR_NONE && _vTile[index].pos == POS_NONE)
			{
				Vector2 vec((_vTile[index].rc.left + _vTile[index].rc.right) * 0.5f, (_vTile[index].rc.top + _vTile[index].rc.bottom) * 0.5f);
				CAMERAMANAGER->frameRender(ImageManager::GetInstance()->FindImage("mapTiles"), vec.x, vec.y, _vTile[index].terrainFrameX, _vTile[index].terrainFrameY);
			}

			if (KEYMANAGER->isToggleKey('V'))
			{
				if (_vTile[index].pos != POS_NONE)
				{
					Vector2 vec((_vTile[index].rc.left + _vTile[index].rc.right) * 0.5f, (_vTile[index].rc.top + _vTile[index].rc.bottom) * 0.5f);
					CAMERAMANAGER->frameRender(ImageManager::GetInstance()->FindImage("mapTiles"), vec.x, vec.y, _vTile[index].terrainFrameX, _vTile[index].terrainFrameY);
				}
				if (_vTile[index].terrain == TR_WALL || _vTile[index].isColTile)
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


	_objectManager->objectRender();
	// 선택중인 렉트
	{
		CAMERAMANAGER->rectangle(_dragTile, D2D1::ColorF::LimeGreen, 1.0f, 5);
	}


	if (_palette->getIsActive() == true) //팔레트가 있을 때 
	{
		ImageManager::GetInstance()->FindImage("sampleUI")->Render(Vector2(_palette->getSampleUIRect().left, _palette->getSampleUIRect().top));

		// 팔레트
		if (_button->getType() == BUTTON_TERRAIN)
		{
			_palette->sampleTileRender();
		}
		else if (_button->getType() == BUTTON_OBJECT)
		{
			_objectManager->sampleObjectPageRender();
		}
		selectTileSizeRender();

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

	POINT pos;
	pos.x = CAMERAMANAGER->getX();
	pos.y = CAMERAMANAGER->getY();
	_miniMap1->render(_objectManager, pos);



	_objectManager->currentObjectRender();

	// 팔레트 껐다켰다하는 렉트
	ImageManager::GetInstance()->FindImage("sampleUIOnOff")->Render(Vector2(_palette->getSampleOnOffRect().left, _palette->getSampleOnOffRect().top));
}

void tile::update()
{
	mapMove();
	setMap();
	drag();
	saveLoad();
	autoTile();
}

void tile::release()
{
	_vTile.clear();
}

void tile::selectTileSizeInit()
{
	_selectTileSize[0].rc = RectMakeCenter(WINSIZEX / 2 + 450, WINSIZEY / 2 + 100, 100, 100);
	_selectTileSize[0].tileSizeX = 100;
	_selectTileSize[0].tileSizeY = 100;
	_selectTileSize[0].str = L"100 x 100";

	_selectTileSize[1].rc = RectMakeCenter(WINSIZEX / 2 + 450 + 120, WINSIZEY / 2 + 100, 100, 100);
	_selectTileSize[1].tileSizeX = 75;
	_selectTileSize[1].tileSizeY = 75;
	_selectTileSize[1].str = L"75 x 75";

	_selectTileSize[2].rc = RectMakeCenter(WINSIZEX / 2 + 450, WINSIZEY / 2 + 220, 100, 100);
	_selectTileSize[2].tileSizeX = 50;
	_selectTileSize[2].tileSizeY = 50;
	_selectTileSize[2].str = L"50 x 50";

	_selectTileSize[3].rc = RectMakeCenter(WINSIZEX / 2 + 450 + 120, WINSIZEY / 2 + 220, 100, 100);
	_selectTileSize[3].tileSizeX = 30;
	_selectTileSize[3].tileSizeY = 30;
	_selectTileSize[3].str = L"30 x 30";
}

void tile::selectTileSize()
{
	if (_button->getType() == BUTTON_SELECTSIZE)
	{
		for (int i = 0; i < 4; i++)
		{
			if (PtInRect(&_selectTileSize[i].rc, _ptMouse))
			{
				_tileSize[0] = _selectTileSize[i].tileSizeX;
				_tileSize[1] = _selectTileSize[i].tileSizeY;
				release();
				setup();
				_miniMap1->init(_tileSize[0], _tileSize[1]);

				CAMERAMANAGER->settingCamera(0, 0, WINSIZEX, WINSIZEY, 0, 0, _tileSize[0] * TILESIZE - WINSIZEX, _tileSize[1] * TILESIZE - WINSIZEY);
				break;
			}
		}
	}
}

void tile::selectTileSizeRender()
{
	if (_button->getType() == BUTTON_SELECTSIZE)
	{
		for (int i = 0; i < 4; i++)
		{
			D2DRenderer::GetInstance()->DrawRectangle(_selectTileSize[i].rc, D2D1::ColorF::Black, 1.0f, 2);
			D2DRenderer::GetInstance()->RenderText(_selectTileSize[i].rc.left + 5, _selectTileSize[i].rc.top + 40, _selectTileSize[i].str, 20);
		}
	}
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

		for (int i = 0; i < _tileSize[0] * _tileSize[1]; i++)
		{
			if (isCollision(_drag.rc, _vTile[i].rc))
			{
				if (_button->getType() == BUTTON_TERRAIN)
				{
					_vTile[i].terrainFrameX = _currentTile.x;
					_vTile[i].terrainFrameY = _currentTile.y;
					_vTile[i].isColTile = false;
					_vTile[i].terrain = terrainSelect(_currentTile.x, _currentTile.y);
					_vTile[i].pos = posSelect(_currentTile.x, _currentTile.y);
					_miniMap1->setIsDraw(i, true);
				}

				else if (_button->getType() == BUTTON_ERASE_TERRAIN)
				{
					_vTile[i].isColTile = false;
					_vTile[i].terrain = TR_NONE;
					_miniMap1->setIsDraw(i, false);
				}
				else if (_button->getType() == BUTTON_COLLISION)
				{
					_vTile[i].isColTile = true;
				}


			}
			_vTile[i].isDrag = false;
		}

	}

}

void tile::setup()
{

	for (int i = 0; i < _tileSize[1]; i++)
	{
		for (int j = 0; j < _tileSize[0]; j++)
		{
			tagTile temp;
			temp.rc = RectMake(j * TILESIZE, i * TILESIZE, TILESIZE, TILESIZE);
			temp.isDrag = false;
			temp.idX = j;
			temp.idY = i;
			temp.isColTile = false;
			_vTile.push_back(temp);
		}
	}


	for (int i = 0; i < _tileSize[1] * _tileSize[0]; ++i)
	{
		_vTile[i].terrainFrameX = 8;
		_vTile[i].terrainFrameY = 4;
		_vTile[i].terrain = terrainSelect(_vTile[i].terrainFrameX, _vTile[i].terrainFrameY);
		_vTile[i].pos = posSelect(_vTile[i].terrainFrameX, _vTile[i].terrainFrameY);
	}
}

void tile::setMap()
{
	POINT pt = _ptMouse;
	pt.x += CAMERAMANAGER->getLeft();
	pt.y += CAMERAMANAGER->getTop();
	_palette->sampleOnOff();

	// 선택할 때 범위
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (_palette->getIsActive() == true)
		{
			if (_button->getType() == BUTTON_TERRAIN)
			{
				_palette->selectTile(_currentTile, _currentRect);
			}
			else if (_button->getType() == BUTTON_OBJECT)
			{
				_objectManager->sampleObjectPage();
				_objectManager->selectObject();
			}

			selectTileSize();
			_button->update();
		}
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
						_vTile[index].isColTile = false;
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
			_objectManager->eraseObject(pt);
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
					if (_palette->getIsActive() == true)
					{
						if (_ptMouse.x >= WINSIZEX - 618) break;
					}

					if (_button->getType() == BUTTON_TERRAIN)
					{
						_vTile[index].terrainFrameX = _currentTile.x;
						_vTile[index].terrainFrameY = _currentTile.y;
						_vTile[index].terrain = terrainSelect(_currentTile.x, _currentTile.y);
						_vTile[index].pos = posSelect(_currentTile.x, _currentTile.y);
						_miniMap1->setIsDraw(index, true);
					}
					else if (_button->getType() == BUTTON_OBJECT)
					{
						_objectManager->setObject(pt);
					}
					else if (_button->getType() == BUTTON_ERASE_TERRAIN)
					{
						_vTile[index].terrain = TR_NONE;
						_vTile[index].isColTile = false;
						_miniMap1->setIsDraw(index, false);
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
				break;
			}
		}
	}
}

void tile::saveLoad()
{
	saveMap(3);
	loadMap(3);
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
	ImageManager::GetInstance()->AddImage("object_rock1", L"Object/objectRock1.png");
	ImageManager::GetInstance()->AddImage("object_rock2", L"Object/objectRock2.png");
	ImageManager::GetInstance()->AddImage("object_tile1", L"Object/object_Tile1.png");
	ImageManager::GetInstance()->AddImage("object_tile2", L"Object/object_Tile2.png");
	ImageManager::GetInstance()->AddImage("object_tile3", L"Object/object_Tile3.png");



	ImageManager::GetInstance()->AddFrameImage("plant_tree1", L"Object/plant_tree1.png", 35, 1);
	ImageManager::GetInstance()->AddFrameImage("plant_tree2", L"Object/plant_tree2.png", 35, 1);
	ImageManager::GetInstance()->AddFrameImage("plant_fountain1", L"Object/plant_fountain1.png", 9, 1);
	ImageManager::GetInstance()->AddFrameImage("Object_build_Bottom1", L"Object/Object_build_Bottom1.png", 53, 1);

	ImageManager::GetInstance()->AddFrameImage("npc_1", L"Object/npc_1.png", 17, 1);
	ImageManager::GetInstance()->AddFrameImage("npc_2", L"Object/npc_2.png", 54, 1);
	ImageManager::GetInstance()->AddFrameImage("npc_3", L"Object/npc_3.png", 24, 1);
	ImageManager::GetInstance()->AddFrameImage("npc_4", L"Object/npc_4.png", 49, 1);

	ImageManager::GetInstance()->AddImage("objectDungeon1", L"Object/objectDungeon1.png");
	ImageManager::GetInstance()->AddImage("objectDungeon2", L"Object/objectDungeon2.png");
	ImageManager::GetInstance()->AddImage("object_skull1", L"Object/skull1.png");
	ImageManager::GetInstance()->AddImage("object_skull2", L"Object/skull2.png");
	ImageManager::GetInstance()->AddImage("object_skull3", L"Object/skull3.png");
	ImageManager::GetInstance()->AddImage("object_pot", L"Object/pot.png");
	ImageManager::GetInstance()->AddImage("object_pot_slime", L"Object/pot_slime.png");
	ImageManager::GetInstance()->AddImage("object_pillar", L"Object/pillar.png");
	ImageManager::GetInstance()->AddImage("object_smallRock", L"Object/smallRock.png");
	ImageManager::GetInstance()->AddImage("object_smallRock_slime", L"Object/smallRock_slime.png");
	ImageManager::GetInstance()->AddImage("objectTile1", L"Object/objectTile1.png");
	ImageManager::GetInstance()->AddImage("objectTile2", L"Object/objectTile2.png");
	ImageManager::GetInstance()->AddImage("objectTile3", L"Object/objectTile3.png");
	ImageManager::GetInstance()->AddImage("objectTile4", L"Object/objectTile4.png");
	ImageManager::GetInstance()->AddImage("objectTile5", L"Object/objectTile5.png");
	ImageManager::GetInstance()->AddImage("objectTile6", L"Object/objectTile6.png");
	ImageManager::GetInstance()->AddImage("objectTile7", L"Object/objectTile7.png");
	ImageManager::GetInstance()->AddImage("objectTile8", L"Object/objectTile8.png");
	ImageManager::GetInstance()->AddImage("objectTile9", L"Object/objectTile9.png");
	ImageManager::GetInstance()->AddImage("objectTile10", L"Object/objectTile10.png");
	ImageManager::GetInstance()->AddImage("objectTile11", L"Object/objectTile11.png");
	ImageManager::GetInstance()->AddImage("objectTile12", L"Object/objectTile12.png");
	ImageManager::GetInstance()->AddImage("rock1", L"Object/rock1.png");
	ImageManager::GetInstance()->AddImage("rock2", L"Object/rock2.png");
	ImageManager::GetInstance()->AddImage("rock3", L"Object/rock3.png");
	ImageManager::GetInstance()->AddImage("rock4", L"Object/rock4.png");
	ImageManager::GetInstance()->AddImage("rock5", L"Object/rock5.png");
	ImageManager::GetInstance()->AddImage("root1", L"Object/root1.png");
	ImageManager::GetInstance()->AddImage("root2", L"Object/root2.png");


}

void tile::loadMap(int num)
{
	if (_button->getType() == BUTTON_LOAD_TOWN || _button->getType() == BUTTON_LOAD_BOSS
		|| _button->getType() == BUTTON_LOAD_SHOP || _button->getType() == BUTTON_LOAD_DUNGEON || _button->getType() == BUTTON_LOAD_ENTERENCE)
	{
		HANDLE file;
		DWORD read;
		const char* fileName;
		fileName = "";
		if (_button->getType() == BUTTON_LOAD_TOWN)
		{
			_currentLoadType = 1;
			_mapImg = ImageManager::GetInstance()->AddImage("townMap", L"Image/Map/townMap.png");
			_miniMap1->setImage(_mapImg);
			fileName = "townMap.map";
		}
		else if (_button->getType() == BUTTON_LOAD_BOSS)
		{
			_currentLoadType = 2;
			_mapImg = ImageManager::GetInstance()->AddImage("bossRoom1", L"Image/map/bossRoom1.png");
			_miniMap1->setImage(_mapImg);
			fileName = "boss.map";
		}
		else if (_button->getType() == BUTTON_LOAD_SHOP)
		{
			_currentLoadType = 3;
			_mapImg = ImageManager::GetInstance()->AddImage("shop_background", L"Image/Shop/shop_background.png");
			_miniMap1->setImage(_mapImg);
			fileName = "shop.map";
		}
		else if (_button->getType() == BUTTON_LOAD_DUNGEON)
		{
			_currentLoadType = 4;
			_mapImg = ImageManager::GetInstance()->AddImage("dungeon_background", L"Image/Map/dungeon_background.png");
			_miniMap1->setImage(_mapImg);
			if (num == 1)
				fileName = "dungeon1.map";
			if (num == 2)
				fileName = "dungeon2.map";
			if (num == 3)
				fileName = "spa.map";
		}
		else if (_button->getType() == BUTTON_LOAD_ENTERENCE)
		{
			_currentLoadType = 5;
			_mapImg = ImageManager::GetInstance()->AddImage("dungeon_background", L"Image/Map/dungeon_background.png");
			_miniMap1->setImage(_mapImg);
			fileName = "dungeonEnterence.map";
		}
		if (_vTile.size() > 0)
			release();

		file = CreateFile(fileName, GENERIC_READ, NULL, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		ReadFile(file, _tileSize, sizeof(int) * 2, &read, NULL);

		tagTile* temTile = new tagTile[_tileSize[0] * _tileSize[1]];
		ReadFile(file, temTile, sizeof(tagTile) * _tileSize[0] * _tileSize[1], &read, NULL);

		for (int i = 0; i < _tileSize[0] * _tileSize[1]; i++)
		{
			_vTile.push_back(temTile[i]);
		}


		CloseHandle(file);

		_objectManager->load(_button->getType(), num);

		_miniMap1->release();
		_miniMap1->init(_tileSize[0], _tileSize[1]);


		CAMERAMANAGER->settingCamera(0, 0, WINSIZEX, WINSIZEY, 0, 0, _tileSize[0] * TILESIZE - WINSIZEX, _tileSize[1] * TILESIZE - WINSIZEY);
		_button->setType(BUTTON_TERRAIN);

	}
}

void tile::saveMap(int num)
{
	if (_currentLoadType == 0) return;
	if (_button->getType() == BUTTON_SAVE_TOWN || _button->getType() == BUTTON_SAVE_BOSS
		|| _button->getType() == BUTTON_SAVE_SHOP || _button->getType() == BUTTON_SAVE_DUNGEON || _button->getType() == BUTTON_SAVE_ENTERENCE)
	{
		_saveTime++;
	}

	if (_saveTime > 50)
	{
		HANDLE file;
		DWORD write;
		const char* fileName;
		fileName = "";
		if (_button->getType() == BUTTON_SAVE_TOWN)
		{
			if (_currentLoadType != 1)
			{
				_saveTime = 0;
				_button->setType(BUTTON_TERRAIN);
				return;
			}
			_tileSize[0] = 60;
			_tileSize[1] = 49;

			fileName = "townMap.map";
		}
		else if (_button->getType() == BUTTON_SAVE_BOSS)
		{
			if (_currentLoadType != 2)
			{
				_saveTime = 0;
				_button->setType(BUTTON_TERRAIN);
				return;
			}
			_tileSize[0] = 60;
			_tileSize[1] = 41;

			fileName = "boss.map";
		}
		else if (_button->getType() == BUTTON_SAVE_SHOP)
		{
			if (_currentLoadType != 3)
			{
				_saveTime = 0;
				_button->setType(BUTTON_TERRAIN);
				return;
			}
			_tileSize[0] = 32;
			_tileSize[1] = 28;

			fileName = "shop.map";
		}
		else if (_button->getType() == BUTTON_SAVE_DUNGEON)
		{
			if (_currentLoadType != 4)
			{
				_saveTime = 0;
				_button->setType(BUTTON_TERRAIN);
				return;
			}
			_tileSize[0] = 32;
			_tileSize[1] = 18;
			if (num == 1)
				fileName = "dungeon1.map";
			if (num == 2)
				fileName = "dungeon2.map";
			if (num == 3)
				fileName = "spa.map";
		}
		else if (_button->getType() == BUTTON_SAVE_ENTERENCE)
		{
			if (_currentLoadType != 5)
			{
				_saveTime = 0;
				_button->setType(BUTTON_TERRAIN);
				return;
			}
			_tileSize[0] = 32;
			_tileSize[1] = 18;

			fileName = "dungeonEnterence.map";
		}
		// ----------------- 타일 ----------------- //
		tagTile* tempTile = new tagTile[_tileSize[0] * _tileSize[1]];
		for (int i = 0; i < _vTile.size(); i++)
		{
			tempTile[i] = _vTile[i];
		}
		// ----------------- 타일 ----------------- //
		file = CreateFile(fileName, GENERIC_WRITE, NULL, NULL,
			CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);


		WriteFile(file, _tileSize, sizeof(int) * 2, &write, NULL);
		WriteFile(file, tempTile, sizeof(tagTile) * _tileSize[0] * _tileSize[1], &write, NULL);

		CloseHandle(file);
		_objectManager->save(_button->getType(), num);

		_saveTime = 0;
		_button->setType(BUTTON_TERRAIN);
	}

}

void tile::autoTile()
{
	if (_button->getType() == BUTTON_AUTO)
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

				autoTileType(index, TR_GRASS);
				autoTileType(index, TR_CEMENT);

			}
		}
		_button->setType(BUTTON_TERRAIN);
	}

}

void tile::autoTileType(int idx, TERRAIN type)
{
	int _autoCalc = 0;
	if (_vTile[idx].terrain == type)
	{
		if (_vTile[idx - _tileSize[0]].terrain == type) // 위쪽이 잔디
		{
			_autoCalc += 1;
		}
		if (_vTile[idx + 1].terrain == type)
		{
			_autoCalc += 2;
		}
		if (_vTile[idx + _tileSize[0]].terrain == type)
		{
			_autoCalc += 4;
		}
		if (_vTile[idx - 1].terrain == type)
		{
			_autoCalc += 8;
		}

		if (_autoCalc == 0)
		{
			_vTile[idx].terrainFrameX = 8;
		}
		else if (_autoCalc == 1)
		{
			_vTile[idx].terrainFrameX = 3;
		}
		else if (_autoCalc == 2)
		{
			_vTile[idx].terrainFrameX = 1;
		}
		else if (_autoCalc == 4)
		{
			_vTile[idx].terrainFrameX = 7;
		}
		else if (_autoCalc == 8)
		{
			_vTile[idx].terrainFrameX = 5;
		}
		else if (_autoCalc == 3)
		{
			_vTile[idx].terrainFrameX = 2;
		}
		else if (_autoCalc == 6)
		{
			_vTile[idx].terrainFrameX = 0;
		}
		else if (_autoCalc == 12)
		{
			_vTile[idx].terrainFrameX = 6;
		}
		else if (_autoCalc == 9)
		{
			_vTile[idx].terrainFrameX = 4;
		}
		else if (_autoCalc == 7)
		{
			_vTile[idx].terrainFrameX = 1;
		}
		else if (_autoCalc == 14)
		{
			_vTile[idx].terrainFrameX = 7;
		}
		else if (_autoCalc == 13)
		{
			_vTile[idx].terrainFrameX = 5;
		}
		else if (_autoCalc == 11)
		{
			_vTile[idx].terrainFrameX = 3;
		}

		else if (_autoCalc == 15)
		{
			_vTile[idx].terrainFrameX = 8;
		}
	}


}

void tile::mapMove()
{
	if (KEYMANAGER->isStayKeyDown('W'))	CAMERAMANAGER->setY(CAMERAMANAGER->getY() - 10);
	if (KEYMANAGER->isStayKeyDown('S'))	CAMERAMANAGER->setY(CAMERAMANAGER->getY() + 10);
	if (KEYMANAGER->isStayKeyDown('A'))	CAMERAMANAGER->setX(CAMERAMANAGER->getX() - 10);
	if (KEYMANAGER->isStayKeyDown('D'))	CAMERAMANAGER->setX(CAMERAMANAGER->getX() + 10);

	_miniMap1->update();
}

TERRAIN tile::terrainSelect(int frameX, int frameY)
{
	for (int i = 0; i < 9; i++)
	{
		// 첫번째 줄
		if (frameX == 8 && frameY == 0) return TR_FLOOR;
		else if (frameX == i && frameY == 0) return TR_WALL;

		// 두번째 줄
		if (frameX == i && frameY == 1) return TR_CEMENT;

		// 세번째 줄
		if (frameX == i && frameY == 2) return TR_GRASS;

		// 네번째 줄
		if (frameX == i && frameY == 3) return TR_GRASS;

		// 다섯번째 줄
		if (frameX == 8 && frameY == 4) return TR_NONE;
		else if (frameX == i && frameY == 4) return TR_GRASS;

		// 여섯번째 줄
		if (frameX == i && frameY == 5) return TR_POS;
		if (frameX == i && frameY == 6) return TR_WALL;
	}

	return TR_NONE;
}

ACTIVEPOS tile::posSelect(int frameX, int frameY)
{
	if (frameX == 0 && frameY == 5)      return POS_TOWN;
	else if (frameX == 1 && frameY == 5) return POS_SHOP;
	else if (frameX == 2 && frameY == 5) return POS_ENTERENCE;
	else if (frameX == 3 && frameY == 5) return POS_DUN1;
	else if (frameX == 4 && frameY == 5) return POS_DUN2;
	else if (frameX == 5 && frameY == 5) return POS_DUN3;
	else if (frameX == 6 && frameY == 5) return POS_SPA;
	else if (frameX == 7 && frameY == 5) return POS_BOSS;
	else if (frameX == 8 && frameY == 5) return POS_BOSS;

	return POS_NONE;
}

