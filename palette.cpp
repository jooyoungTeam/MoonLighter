#include "stdafx.h"
#include "palette.h"

HRESULT palette::init()
{
	_sampleTileUI.right = WINSIZEX;
	_sampleTileUI.bottom = WINSIZEY;
	_sampleTileUI.top = 0;
	_sampleTileUI.left = WINSIZEX - 550;

	_sampleTileOnOff.right = WINSIZEX;
	_sampleTileOnOff.left = _sampleTileOnOff.right - 20;
	_sampleTileOnOff.top = WINSIZEY / 2 - 50;
	_sampleTileOnOff.bottom = WINSIZEY / 2 + 50;

	_isActive = false;
	for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
	{
		_sampleTile[i].terrainFrameX = i % SAMPLETILEX;
		_sampleTile[i].terrainFrameY = i / SAMPLETILEX;

		_sampleTile[i].rc = RectMake(WINSIZEX / 2 + 275 + _sampleTile[i].terrainFrameX * TILESIZE * 1.1f, WINSIZEY / 2 - 80 + _sampleTile[i].terrainFrameY * TILESIZE * 1.1f, TILESIZE, TILESIZE);
	}

	return S_OK;
}

void palette::update()
{
}

void palette::render()
{
}

void palette::release()
{
}

void palette::sampleTileRender()
{
	for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
	{
		D2DRenderer::GetInstance()->DrawRectangle(_sampleTile[i].rc, D2D1::ColorF::Black, 1.0f);
		Vector2 vec((_sampleTile[i].rc.left + _sampleTile[i].rc.right) * 0.5f, (_sampleTile[i].rc.top + _sampleTile[i].rc.bottom) * 0.5f);
		ImageManager::GetInstance()->FindImage("mapTiles")->FrameRender(vec, _sampleTile[i].terrainFrameX, _sampleTile[i].terrainFrameY);
	}
}

void palette::selectTile(POINT & currentPos, RECT & currentRect)
{
	for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
	{
		if (PtInRect(&_sampleTile[i].rc, _ptMouse))
		{
			currentPos.x = _sampleTile[i].terrainFrameX;
			currentPos.y = _sampleTile[i].terrainFrameY;
			currentRect = RectMake(_sampleTile[i].rc.left, _sampleTile[i].rc.top, TILESIZE, TILESIZE);
			break;
		}
	}
}

void palette::sampleOnOff()
{
	if (KEYMANAGER->isOnceKeyDown('F'))
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
