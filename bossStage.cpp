#include "stdafx.h"
#include "bossStage.h"
#include "itemManager.h"
#include "player.h"
#include "UI.h"

HRESULT bossStage::init()
{
	_mapImg = ImageManager::GetInstance()->AddImage("bossRoom1", L"Image/map/bossRoom1.png");
	CAMERAMANAGER->settingCamera(0, 0, WINSIZEX, WINSIZEY, 0, 0, 3000 - WINSIZEX, 2050 - WINSIZEY);

	_objectManager = new objectManager;

	_enemy = new enemyManager;
	_enemy->setPlayerLink(_player);
	_enemy->setItemManagerLink(_itemManager);
	_enemy->setBoss();
	_enemy->init();

	for (int i = 0; i < _enemy->_getVEnemy().size(); i++)
	{
		if (_enemy->_getVEnemy()[i]->getEnemyType() == ENEMY_BOSS)
		{
			_ui->setBossHpBar(_enemy->_getVEnemy()[i]->getCurHP());
			break;
		}

	}
	loadMap();

	//SOUNDMANAGER->play("bgm2", 1.0f);

	_miniMap = new miniMap;
	_miniMap->init(BOSSTILEX, BOSSTILEY);
	_miniMap->setImage(_mapImg);
	return S_OK;
}

void bossStage::render()
{
	CAMERAMANAGER->render(_mapImg, 0, 0, 1);
	_player->render();
	_enemy->render();
	renderMap();
	CAMERAMANAGER->zOrderALLRender();

	POINT pos;
	pos.x = _player->getX();
	pos.y = _player->getY();
	_miniMap->render(_objectManager, pos);
}

void bossStage::update()
{
	_miniMap->update();

	for (int i = 0; i < _enemy->_getVEnemy().size(); i++)
	{
		if (_enemy->_getVEnemy()[i]->getEnemyType() == ENEMY_BOSS)
		{
			_ui->setBossHpBar(_enemy->_getVEnemy()[i]->getCurHP());
			break;
		}
	}

	//if (_ui->getBossScene() == BOSS_STAGE::STAGE_START)
	{
		if (!INVENTORY->getIsInven())
		{
			_player->update();
			//_player->tileCollision(_attribute, _tile, BOSSTILEX);
			_enemy->update();
			
		}
	}	
	
	CAMERAMANAGER->setXY(_player->getX(), _player->getY());
}

void bossStage::release()
{
	_itemManager->release();
}

void bossStage::loadMap()
{
	HANDLE file;
	DWORD read;

	int _tileSize[2];
	int size[2];

	// ------------ ≈∏¿œ

	file = CreateFile("boss.map", GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tileSize, sizeof(int) * 2, &read, NULL);

	ReadFile(file, _tile, sizeof(tagTile) * BOSSTILEX * BOSSTILEY, &read, NULL);

	memset(_attribute, 0, sizeof(DWORD) * BOSSTILEX * BOSSTILEY);
	for (int i = 0; i < BOSSTILEX * BOSSTILEY; ++i)
	{
		if (_tile[i].terrain == TR_WALL || _tile[i].isColTile) _attribute[i] |= ATTR_UNMOVE;
	}

	CloseHandle(file);

	_objectManager->load(BUTTON_LOAD_BOSS,0);
}

void bossStage::renderMap()
{
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 33; j++)
		{
			int cullX = CAMERAMANAGER->getLeft() / TILESIZE;
			int cullY = CAMERAMANAGER->getTop() / TILESIZE;
			int index = (i + cullY) * BOSSTILEX + (j + cullX);
			if (index >= BOSSTILEX * BOSSTILEY)
				continue;
			if (_tile[index].terrain != TR_NONE)
			{
				Vector2 vec((_tile[index].rc.left + _tile[index].rc.right) * 0.5f, (_tile[index].rc.top + _tile[index].rc.bottom) * 0.5f);
				CAMERAMANAGER->frameRender(ImageManager::GetInstance()->FindImage("mapTiles"), vec.x, vec.y, _tile[index].terrainFrameX, _tile[index].terrainFrameY);
			}
			if (KEYMANAGER->isToggleKey('V'))
			{
				CAMERAMANAGER->rectangle(_tile[index].rc, D2D1::ColorF::Black, 1);
				if (_tile[index].isColTile)
				{
					CAMERAMANAGER->fillRectangle(_tile[index].rc, D2D1::ColorF::Red, 0.5f);
				}
			}
		}
	}


	//_objectManager->objectRender();
}
