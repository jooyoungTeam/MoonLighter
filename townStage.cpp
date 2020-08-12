#include "stdafx.h"
#include "townStage.h"

HRESULT townStage::init()
{
	_mapImg = ImageManager::GetInstance()->AddImage("townMap", L"Image/Map/townMap.png");

	_mapImg->SetSize(Vector2(3500, 2870));
	CAMERAMANAGER->settingCamera(0, 0, WINSIZEX, WINSIZEY, 0, 0, (_mapImg->GetSize().x) - WINSIZEX, _mapImg->GetSize().y - WINSIZEY);
	//loadMap();
	_player = new player;
	_player->init(500,500);
	return S_OK;
}

void townStage::update()
{
	_player->update();
	CAMERAMANAGER->setXY(_player->getX(), _player->getY());
}

void townStage::render()
{
	//renderMap();

	_mapImg->SetSize(Vector2(3500, 2870));
	CAMERAMANAGER->render(_mapImg, 0, 0, 1);
	_player->render();
}

void townStage::release()
{
}
//void townStage::loadMap()
//{
//	HANDLE file;
//	DWORD read;
//
//	file = CreateFile("dungeonMap.map", GENERIC_READ, NULL, NULL,
//		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
//
//	ReadFile(file, _townTiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL); //32 * 18 ==>> 1600 x 900 ªÁ¿Ã¡Ó
//
//	memset(_townAttribute, 0, sizeof(DWORD) * TILEX * TILEY);
//	for (int i = 0; i < TILEX * TILEY; ++i)
//	{
//		if (_townTiles[i].terrain == TR_WALL) _townAttribute[i] |= ATTR_UNMOVE;
//	}
//
//	CloseHandle(file);
//}
//
//void townStage::renderMap()
//{
//
//	for (int i = 0; i < 19; i++)
//	{
//		for (int j = 0; j < 33; j++)
//		{
//			int cullX = CAMERAMANAGER->getLeft() / TILESIZE;
//			int cullY = CAMERAMANAGER->getTop() / TILESIZE;
//
//			int index = (i + cullY) * TILEX + (j + cullX);
//
//			if (_townTiles[index].terrain != TR_NONE)
//			{
//				Vector2 vec((_townTiles[index].rc.left + _townTiles[index].rc.right) * 0.5f, (_townTiles[index].rc.top + _townTiles[index].rc.bottom) * 0.5f);
//
//				CAMERAMANAGER->frameRender(ImageManager::GetInstance()->FindImage("mapTiles"), vec.x, vec.y, _townTiles[index].terrainFrameX, _townTiles[index].terrainFrameY);
//
//				CAMERAMANAGER->rectangle(_townTiles[index].rc, D2D1::ColorF::Black, 1.0f);
//
//			}
//
//
//		}
//	}
//
//
//
//}

