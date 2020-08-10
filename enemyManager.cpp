#include "stdafx.h"
#include "enemyManager.h"

enemyManager::enemyManager()
{
}

enemyManager::~enemyManager()
{
}

HRESULT enemyManager::init()
{
	setEnemy();
	_x = 600;
	_y = 300;
	_rc = RectMakePivot(Vector2(_x, _y), Vector2(50, 50), Pivot::Center);


	return S_OK;
}

void enemyManager::release()
{
}

void enemyManager::update()
{
	for (int i = 0; i < _vEnemy.size(); ++i)
	{
		_vEnemy[i]->update();
		_vEnemy[i]->playerCheck(_x, _y);	//나중에 여기에 플레이어 위치 넣어주셈
	}

	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		for (int i = 0; i < _vEnemy.size(); ++i)
		{
			_vEnemy[i]->setChange(true);
		}
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_y -= 2;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_y += 2;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_x -= 2;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_x += 2;
	}

	_rc = RectMakePivot(Vector2(_x, _y), Vector2(50, 50), Pivot::Center);
}

void enemyManager::render()
{
	for (int i = 0; i < _vEnemy.size(); ++i)
	{
		_vEnemy[i]->render();
	}

	D2DRenderer::GetInstance()->DrawRectangle(_rc, D2DRenderer::DefaultBrush::Black, 1.f);
}

void enemyManager::setEnemy()
{
	int i = 0;

	enemy* redS;
	redS = new redSlime;
	redS->init(i, 200, 200, 70, 70, ENEMY_RED_SLIME, "test");
	_vEnemy.push_back(redS);

	i++;

	enemy* yelS;
	yelS = new golem;
	yelS->init(i, 700, 500, 80 , 100, ENEMY_GOLEM, "test");
	_vEnemy.push_back(yelS);

	/*i++;

	enemy* yelS2;
	yelS2 = new anotherSlime;
	yelS2->init(i , 200, 00, 50, 50, ENEMY_YELLOW_SLIME, "test");
	_vEnemy.push_back(yelS2);

	i++;


	enemy* yelS3;
	yelS3 = new anotherSlime;
	yelS3->init(i, 200, 300, 50, 50, ENEMY_BLUE_SLIME, "test");
	_vEnemy.push_back(yelS3);

	i++;

	enemy* yelS4;
	yelS4 = new anotherSlime;
	yelS4->init(i , 200, 100, 50, 50, ENEMY_YELLOW_SLIME, "test");
	_vEnemy.push_back(yelS4);*/



}
