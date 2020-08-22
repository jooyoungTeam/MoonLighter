#include "stdafx.h"
#include "miniMap.h"

HRESULT miniMap::init(int x, int y)
{
	_scale = 0.1f;
	_tileSize = _scale * 50;
	_mapY = WINSIZEY - (_tileSize * y) - 10;

	_miniMap = RectMakePivot(Vector2(10, _mapY), Vector2(x * _tileSize, y * _tileSize), Pivot::LeftTop);
	_miniMapMove = RectMakePivot(Vector2(10, _mapY), Vector2(WINSIZEX * _scale, WINSIZEY * _scale), Pivot::LeftTop);

	for (int i = 0; i < x * y; i++)
	{
		tagMiniMap* tempMini = new tagMiniMap;
		tempMini->rc = RectMakePivot(Vector2(10.0f + (i % x) * _tileSize, _mapY + (int)(i / x) * _tileSize), Vector2(_tileSize, _tileSize), Pivot::LeftTop);
		tempMini->isDraw = false;
		_vMiniMap.push_back(tempMini);
	}
	_tileX = x;
	_tileY = y;
	
	return S_OK;
}


void miniMap::render(objectManager* obj, POINT playerPos)
{
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		if (_miniMapImg == NULL)
		{
			D2DRenderer::GetInstance()->FillRectangle(_miniMap, D2D1::ColorF::Silver, 0.5f);
			D2DRenderer::GetInstance()->DrawRectangle(_miniMap, D2D1::ColorF::Black, 1, 2);
		}
		else
		{
			_miniMapImg->Render(Vector2(_miniMap.left, _miniMap.top), _scale);
			D2DRenderer::GetInstance()->DrawRectangle(_miniMap, D2D1::ColorF::Black, 1, 2);
		}

		for (int i = 0; i < _tileX * _tileY; i++)
		{
			if (_vMiniMap[i]->isDraw)
			{
				D2DRenderer::GetInstance()->FillRectangle(_vMiniMap[i]->rc, D2D1::ColorF::Black, 0.5f);
				//if (_miniMapImg == NULL)
				//{
				//	ImageManager::GetInstance()->FindImage("mapTiles")->FrameRender(Vector2(_vMiniMap[i]->rc.left, _vMiniMap[i]->rc.top), _vTile[i].terrainFrameX, _vTile[i].terrainFrameY,_scale);
				//}
				
			}
		}




		for (int i = 0; i < obj->getVObject().size(); i++) // 오브젝트들 렌더
		{
			if (obj->getVObject()[i].isFrameRender)
			{
				obj->findImg(obj->getVObject()[i].type,
					obj->getVObject()[i].imgNumber)->FrameRender(Vector2(10 + (obj->getVObject()[i].rc.left + obj->getVObject()[i].rc.right) * 0.5f * _scale,
						_mapY + (obj->getVObject()[i].rc.top + obj->getVObject()[i].rc.bottom) * 0.5f * _scale
					), 0, 0, obj->getVObject()[i].scale * _scale);

			}
			else
			{
				obj->findImg(obj->getVObject()[i].type,
					obj->getVObject()[i].imgNumber)->Render(Vector2(1 + obj->getVObject()[i].rc.left * _scale, _mapY + obj->getVObject()[i].rc.top * _scale
					), obj->getVObject()[i].scale * _scale);
			}
		}

		D2DRenderer::GetInstance()->DrawRectangle(_miniMapMove, D2D1::ColorF::White, 1, 2);
		if (_miniMapImg != NULL)
		{
			ImageManager::GetInstance()->FindImage("playerDownIdle")->FrameRender(Vector2(10 + playerPos.x * _scale, _mapY + playerPos.y * _scale), 0, 11, _scale * 5);
		}
	}
}

void miniMap::update()
{
	_playerPos.x = 10 + CAMERAMANAGER->getLeft() * _scale;
	_playerPos.y = _mapY + CAMERAMANAGER->getTop() * _scale;

	_miniMapMove = RectMakePivot(Vector2(_playerPos.x, _playerPos.y), Vector2(WINSIZEX * _scale, WINSIZEY * _scale), Pivot::LeftTop);
}

void miniMap::release()
{
	for (int i = 0; i < _vMiniMap.size(); i++)
	{
		SAFE_DELETE(_vMiniMap[i]);
	}
	_vMiniMap.clear();
}
