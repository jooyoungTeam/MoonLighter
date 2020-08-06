#include "stdafx.h"
#include "tile.h"

HRESULT tile::init()
{
	imageLoad();
	
	ImageManager::GetInstance()->AddFrameImage("mapTiles", L"mapTiles.png", SAMPLETILEX, SAMPLETILEY);
	_button = new button;
	_button->init();
	setup();
	return S_OK;
}

void tile::render()
{
	_button->render();

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


	// 그리는곳
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		//D2DRenderer::GetInstance()->DrawRectangle(_tiles[i].rc, D2D1::ColorF::Black, 1.0f);
		Vector2 vec((_tiles[i].rc.left + _tiles[i].rc.right) * 0.5f, (_tiles[i].rc.top + _tiles[i].rc.bottom) * 0.5f);
		ImageManager::GetInstance()->FindImage("mapTiles")->FrameRender(vec, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);

		if (_tiles[i].isDrag)
		{
			D2DRenderer::GetInstance()->DrawRectangle(_tiles[i].rc, D2D1::ColorF::LimeGreen, 1.0f, 5);
		}
	}

	// 선택중인 렉트
	{
		D2DRenderer::GetInstance()->DrawRectangle(_currentRect, D2D1::ColorF::LimeGreen, 1.0f, 5);
		D2DRenderer::GetInstance()->DrawRectangle(_dragTile, D2D1::ColorF::LimeGreen, 1.0f, 5);
	}

	for (int i = 0; i < TILEX * TILEY; ++i)
	{

		if (_tiles[i].object == OBJ_NONE) continue;


		Vector2 vec((_tiles[i].rc.left + _tiles[i].rc.right) * 0.5f, (_tiles[i].rc.top + _tiles[i].rc.bottom) * 0.5f);
		ImageManager::GetInstance()->FindImage("mapTiles")->FrameRender(vec, _tiles[i].objFrameX, _tiles[i].objFrameY);
	}

	// ------------------ 마지막 렌더 ------------------------------------ 
	if (_drag.isDraw)
	{
		D2DRenderer::GetInstance()->DrawRectangle(_drag.rc, D2D1::ColorF::SteelBlue, 1, 1);
		D2DRenderer::GetInstance()->FillRectangle(_drag.rc, D2D1::ColorF::SteelBlue, 0.5f);
	}

}

void tile::update()
{
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
	if (KEYMANAGER->isOnceKeyDown(VK_LSHIFT))
	{
		_drag.isDraw = true;
		_drag.startPos = _ptMouse;
	}

	if (KEYMANAGER->isStayKeyDown(VK_LSHIFT))
	{
		_drag.isDraw = true;
		_drag.endPos = _ptMouse;

		if (_drag.startPos.x < _drag.endPos.x && _drag.startPos.y < _drag.endPos.y)
		{
			_drag.rc.left = _drag.startPos.x;
			_drag.rc.top = _drag.startPos.y;
			_drag.rc.right = _ptMouse.x;
			_drag.rc.bottom = _ptMouse.y;
		}
		else if (_drag.startPos.x > _drag.endPos.x && _drag.startPos.y < _drag.endPos.y)
		{
			_drag.rc.left = _ptMouse.x;
			_drag.rc.top = _drag.startPos.y;
			_drag.rc.right = _drag.startPos.x;
			_drag.rc.bottom = _ptMouse.y;
		}
		else if (_drag.startPos.x < _drag.endPos.x && _drag.startPos.y > _drag.endPos.y)
		{
			_drag.rc.left = _drag.startPos.x;
			_drag.rc.top = _ptMouse.y;
			_drag.rc.right = _ptMouse.x;
			_drag.rc.bottom = _drag.startPos.y;
		}
		else
		{
			_drag.rc.left = _ptMouse.x;
			_drag.rc.top = _ptMouse.y;
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
				else if (_button->getType() == BUTTON_OBJECT)
				{
					_tiles[i].objFrameX = _currentTile.x;
					_tiles[i].objFrameY = _currentTile.y;

					_tiles[i].object = objectSelect(_currentTile.x, _currentTile.y);
				}
				else if (_button->getType() == BUTTON_CLEAR)
				{
					_tiles[i].objFrameX = NULL;
					_tiles[i].objFrameY = NULL;
					_tiles[i].object = OBJ_NONE;
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

		_sampleTile[i].rc = RectMake(WINSIZEX / 2 + _sampleTile[i].terrainFrameX * TILESIZE * 1.1f, 10 + _sampleTile[i].terrainFrameY * TILESIZE * 1.1f, TILESIZE, TILESIZE);
	}

	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			_tiles[i * TILEX + j].rc = RectMake(10 + j * TILESIZE, 10 + i * TILESIZE, TILESIZE, TILESIZE);
			_tiles[i * TILEX + j].isDrag = false;
		}
	}


	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		_tiles[i].terrainFrameX = 8;
		_tiles[i].terrainFrameY = 0;
		_tiles[i].objFrameX = 0;
		_tiles[i].objFrameY = 0;
		_tiles[i].terrain = terrainSelect(_tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
		_tiles[i].object = OBJ_NONE;
	}
}

void tile::setMap()
{

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
				_currentRect = RectMake(WINSIZEX / 2 + _currentTile.x * TILESIZE * 1.1f, 10 + _currentTile.y * TILESIZE * 1.1f, 32, 32);
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
			_dragTile = RectMake(_sampleTile[i].rc.left, _sampleTile[i].rc.top, 32, 32);
			break;
		}
	}


	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < TILEX * TILEY; i++)
		{
			if (PtInRect(&_tiles[i].rc, _ptMouse))
			{
				if (_button->getType() == BUTTON_TERRAIN)
				{
					_tiles[i].terrainFrameX = _currentTile.x;
					_tiles[i].terrainFrameY = _currentTile.y;
					_tiles[i].terrain = terrainSelect(_currentTile.x, _currentTile.y);
				}
				else if (_button->getType() == BUTTON_OBJECT)
				{
					_tiles[i].objFrameX = _currentTile.x;
					_tiles[i].objFrameY = _currentTile.y;

					_tiles[i].object = objectSelect(_currentTile.x, _currentTile.y);
				}
				else if (_button->getType() == BUTTON_CLEAR)
				{
					_tiles[i].objFrameX = NULL;
					_tiles[i].objFrameY = NULL;
					_tiles[i].object = OBJ_NONE;
				}
				break;
			}
		}
	}



	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (PtInRect(&_tiles[i].rc, _ptMouse))
		{
			_dragTile = RectMake(_tiles[i].rc.left, _tiles[i].rc.top, 32, 32);
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

}


TERRAIN tile::terrainSelect(int frameX, int frameY)
{
	if (frameX == 1 && frameY == 0) return TR_CEMENT;
	if (frameX == 2 && frameY == 0) return TR_DESERT;
	if (frameX == 3 && frameY == 0) return TR_GRASS;
	if (frameX == 4 && frameY == 0) return TR_WATER;

	return TR_GRASS;
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
