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
	}

	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		for (int i = 0; i < _vEnemy.size(); ++i)
		{
			_vEnemy[i]->setChange(true);
		}
	}

}

void enemyManager::render()
{
	for (int i = 0; i < _vEnemy.size(); ++i)
	{
		_vEnemy[i]->render();
	}
}

void enemyManager::setEnemy()
{
	enemy* redS;
	redS = new redSlime;
	redS->init(0, 200, 200, 50, 50, ENEMY_RED_SLIME, "test");
	_vEnemy.push_back(redS);

	enemy* yelS;
	yelS = new anotherSlime;
	yelS->init(1, 500, 500, 50, 50, ENEMY_YELLOW_SLIME, "test");
	_vEnemy.push_back(yelS);

	enemy* yelS2;
	yelS2 = new anotherSlime;
	yelS2->init(2, 500, 00, 50, 50, ENEMY_YELLOW_SLIME, "test");
	_vEnemy.push_back(yelS2);


	enemy* yelS3;
	yelS3 = new anotherSlime;
	yelS3->init(3, 500, 300, 50, 50, ENEMY_BLUE_SLIME, "test");
	_vEnemy.push_back(yelS3);

	enemy* yelS4;
	yelS4 = new anotherSlime;
	yelS4->init(4, 500, 100, 50, 50, ENEMY_YELLOW_SLIME, "test");
	_vEnemy.push_back(yelS4);
}
