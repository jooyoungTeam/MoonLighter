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
	_x = 600;
	_y = 300;
	_rc = RectMakePivot(Vector2(_x, _y), Vector2(50, 50), Pivot::Center);
	_bulletDelay = 0;
	setEnemy();

	_bullet = new bullet;
	_bullet->init();
	
	_test = false;
	


	return S_OK;
}

void enemyManager::release()
{
	SAFE_DELETE(_bullet);
}

void enemyManager::update()
{
	_bulletDelay++;
	for (int i = 0; i < _vEnemy.size(); ++i)
	{
		_vEnemy[i]->update();
		_vEnemy[i]->playerCheck(_x, _y, _rc);	
	}
	for (int i = 0; i < _vEnemy.size(); ++i)
	{
		if (_vEnemy[i]->getEnemyType() == ENEMY_RED_SLIME)
		{
			if (_vEnemy[i]->getIsCol())
			{
				_test = true;
			}
			if (!_vEnemy[i]->getIsCol())
			{
				_test = false;
			}
		}
	}
	if (!_test)
	{
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


	}

	if (_bulletDelay > 90)
	{
		potBullet();
	}
	playerCol();
	_bullet->update();
	//cout << _testCount << endl;

	for (int i = 0; i < _vEnemy.size(); ++i)
	{
		if (_vEnemy[i]->getRealDead())
		{
			enemyDead(i);
		}
	}


	_rc = RectMakePivot(Vector2(_x, _y), Vector2(50, 50), Pivot::Center);
}

void enemyManager::render()
{
	for (int i = 0; i < _vEnemy.size(); ++i)
	{
		_vEnemy[i]->render();
	}
	_bullet->render();

	D2DRenderer::GetInstance()->DrawRectangle(_rc, D2DRenderer::DefaultBrush::Black, 1.f);
}

void enemyManager::setEnemy()
{
	int i = 1;

	enemy* redS1;
	redS1 = new redSlime;
	redS1->playerCheck(_x, _y, _rc);
	redS1->init(i, 200, 200, 70, 70, ENEMY_RED_SLIME);
	_vEnemy.push_back(redS1);

	i++;

	enemy* gol1;
	gol1 = new golem;
	gol1->playerCheck(_x, _y, _rc);
	gol1->init(i, 700, 500, 80 , 100, ENEMY_GOLEM);
	_vEnemy.push_back(gol1);

	
	i++;

	enemy* pot1;
	pot1 = new pot;
	pot1->playerCheck(_x, _y, _rc);
	pot1->init(i , 1200, 500, 50, 50, ENEMY_POT);
	_vEnemy.push_back(pot1);

	
	i++;


	enemy* pot2;
	pot2 = new pot;
	pot2->playerCheck(_x, _y, _rc);
	pot2->init(i, 200, 300, 50, 50, ENEMY_POT);
	pot2->setPotDirection(POT_RIGHT);
	_vEnemy.push_back(pot2);

	
	i++;

	enemy* yelS1;
	yelS1 = new anotherSlime;
	yelS1->playerCheck(_x, _y, _rc);
	yelS1->init(i , 200, 100, 30, 30, ENEMY_YELLOW_SLIME);
	_vEnemy.push_back(yelS1);

	i++;

	enemy* bleS1;
	bleS1 = new anotherSlime;
	bleS1->playerCheck(_x, _y, _rc);
	bleS1->init(i, 400, 100, 30, 30, ENEMY_BLUE_SLIME);
	_vEnemy.push_back(bleS1);



}

void enemyManager::potBullet()
{
	_bulletDelay = 0;
	for (int i = 0; i < _vEnemy.size(); ++i)
	{
		if (_vEnemy[i]->getEnemyType() == ENEMY_POT)
		{
			if (_vEnemy[i]->getPotDirection() == POT_LEFT)
			{
				_bullet->fire(_vEnemy[i]->getX(), _vEnemy[i]->getY(), PI, 3.f);
			}
			if (_vEnemy[i]->getPotDirection() == POT_RIGHT)
			{
				_bullet->fire(_vEnemy[i]->getX(), _vEnemy[i]->getY(), PI2, 3.f);
			}
			if (_vEnemy[i]->getPotDirection() == POT_TOP)
			{
				_bullet->fire(_vEnemy[i]->getX(), _vEnemy[i]->getY(), PI * 2.5, 3.f);
			}
			if (_vEnemy[i]->getPotDirection() == POT_BOTTOM)
			{
				_bullet->fire(_vEnemy[i]->getX(), _vEnemy[i]->getY(), PI *3.5, 3.f);
			}

		}
	}
}

void enemyManager::playerCol()
{
	for (int i = 0; i < _vEnemy.size(); ++i)
	{
		if (_vEnemy[i]->getState() != _vEnemy[i]->getDead())
		{
			if (PtInRect(&_vEnemy[i]->getEnemyRect().GetRect(), _ptMouse))
			{
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					_vEnemy[i]->setSaveHP(_vEnemy[i]->getBar().width);
					_vEnemy[i]->setHP();
					_vEnemy[i]->setIsHit(true);
					_vEnemy[i]->setBarAlpha(1.0);
					//_vEnemy[i]->setState(_vEnemy[i]->getHit());
					if (_vEnemy[i]->getCurHP() <= 0)
					{
						_vEnemy[i]->setOnceAni(true);
					}
				}
			}
		}
	}
}

void enemyManager::bulletCol()
{
}

void enemyManager::enemyDead(int arr)
{
	
	_vEnemy.erase(_vEnemy.begin() + arr);
	
}
