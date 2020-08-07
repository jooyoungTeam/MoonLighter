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
	int i = 0;

	enemy* redS;
	redS = new redSlime;
	redS->init(i, 200 + i* 2, 200, 50, 50, ENEMY_RED_SLIME, "test");
	_vEnemy.push_back(redS);

	i++;

	enemy* yelS;
	yelS = new anotherSlime;
	yelS->init(i, 200 + i* 2, 500, 50, 50, ENEMY_YELLOW_SLIME, "test");
	_vEnemy.push_back(yelS);

	i++;

	enemy* yelS2;
	yelS2 = new anotherSlime;
	yelS2->init(i , 200 + i * 2, 00, 50, 50, ENEMY_YELLOW_SLIME, "test");
	_vEnemy.push_back(yelS2);

	i++;


	enemy* yelS3;
	yelS3 = new anotherSlime;
	yelS3->init(i, 200 + i * 2, 300, 50, 50, ENEMY_BLUE_SLIME, "test");
	_vEnemy.push_back(yelS3);

	i++;

	enemy* yelS4;
	yelS4 = new anotherSlime;
	yelS4->init(i , 200 + i * 2, 100, 50, 50, ENEMY_YELLOW_SLIME, "test");
	_vEnemy.push_back(yelS4);



}
