#include "stdafx.h"
#include "enemyManager.h"
#include "player.h"
#include "boss.h"


enemyManager::enemyManager()
{
}

enemyManager::~enemyManager()
{
}

HRESULT enemyManager::init()
{
	_x = _player->getX();
	_y = _player->getY();
	_rc = _player->getPlayerRc();
	_bulletDelay = 0;
	setEnemy();

	_bullet = new bullet;
	_bullet->init("bullet");
	
	_test = false;


	return S_OK;
}

void enemyManager::release()
{
	SAFE_DELETE(_bullet);
}

void enemyManager::update()
{
	_x = _player->getX();
	_y = _player->getY();
	_rc = _player->getPlayerRc();
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

	if (_bulletDelay > 90)
	{
		potBullet();
	}
	playerCol();
	bulletCol();
	_bullet->update();

	for (int i = 0; i < _vEnemy.size(); ++i)
	{
		if (_vEnemy[i]->getRealDead())
		{
			enemyDead(i);
		}
	}

	EFFECTMANAGER->update();
}

void enemyManager::render()
{
	for (int i = 0; i < _vEnemy.size(); ++i)
	{
		_vEnemy[i]->render();
	}
	_bullet->render();

	//CAMERAMANAGER->fillRectangle(_rc, D2D1::ColorF::DimGray, 1.0);
	//D2DRenderer::GetInstance()->DrawRectangle(_rc, D2DRenderer::DefaultBrush::Black, 1.f);
	ImageManager::GetInstance()->FindImage("bulletCollision")->SetScale(1.5f);
	EFFECTMANAGER->render();
}

void enemyManager::setEnemy()
{
	int i = 1;

	enemy* boss1;
	boss1 = new boss;
	boss1->playerCheck(_x, _y, _rc);
	boss1->init(i, 1360, 300, 590, 650, ENEMY_BOSS);
	_vEnemy.push_back(boss1);


	enemy* redS1;
	redS1 = new redSlime;
	redS1->playerCheck(_x, _y, _rc);
	redS1->init(i, 200, 200, 70, 70, ENEMY_RED_SLIME);
	_vEnemy.push_back(redS1);
	
	enemy* redS12;
	redS12 = new redSlime;
	redS12->playerCheck(_x, _y, _rc);
	redS12->init(i, 200, 200, 70, 70, ENEMY_RED_SLIME);
	_vEnemy.push_back(redS12);



	enemy* gol1;
	gol1 = new golem;
	gol1->playerCheck(_x, _y, _rc);
	gol1->init(i, 700, 500, 80 , 100, ENEMY_GOLEM);
	_vEnemy.push_back(gol1);

	enemy* gol12;
	gol12 = new golem;
	gol12->playerCheck(_x, _y, _rc);
	gol12->init(i, 800, 500, 80, 100, ENEMY_GOLEM);
	_vEnemy.push_back(gol12);
	


	enemy* pot1;
	pot1 = new pot;
	pot1->playerCheck(_x, _y, _rc);
	pot1->init(i , 1200, 500, 50, 50, ENEMY_POT);
	_vEnemy.push_back(pot1);

	enemy* pot22;
	pot22 = new pot;
	pot22->playerCheck(_x, _y, _rc);
	pot22->init(i, 1200, 700, 50, 50, ENEMY_POT);
	_vEnemy.push_back(pot22);
	


	enemy* pot2;
	pot2 = new pot;
	pot2->playerCheck(_x, _y, _rc);
	pot2->init(i, 200, 300, 50, 50, ENEMY_POT);
	pot2->setPotDirection(POT_RIGHT);
	_vEnemy.push_back(pot2);



	enemy* yelS1;
	yelS1 = new anotherSlime;
	yelS1->playerCheck(_x, _y, _rc);
	yelS1->init(i , 200, 100, 30, 30, ENEMY_YELLOW_SLIME);
	_vEnemy.push_back(yelS1);


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

		if (_vEnemy[i]->getEnemyType() == ENEMY_BOSS)
		{

		}
	}
}

void enemyManager::playerCol()
{
	RECT temp;
	for (int i = 0; i < _vEnemy.size(); ++i)
	{

		if (IntersectRect(&temp, &_vEnemy[i]->getEnemyRect().GetRect(), &_player->getPlayerAttackRc().GetRect()))
		{
			_vEnemy[i]->setEnemyAttack();
			_player->setAttackRc(0, 0, 0, 0);
		}
		for (int i = 0; i < _player->getArrow()->getVArrow().size(); ++i)
		{
			if (IntersectRect(&temp, &_vEnemy[i]->getEnemyRect().GetRect(), &_player->getArrow()->getVArrow()[i].rc.GetRect()))
			{
				_vEnemy[i]->setEnemyAttack();
				//_player->se(0, 0, 0, 0);
			}
		}
		if (IntersectRect(&temp, &_vEnemy[i]->getEnemyAttackRect().GetRect(), &_player->getPlayerRc().GetRect()))
		{
			//_player->setCurrentState(_());
			_vEnemy[i]->setAttackRect(0, 0, 0, 0);
		}
		if (_vEnemy[i]->getIsPull())
		{
			float angle = getAngle(_player->getX(), _player->getY(), _vEnemy[i]->getX(), _vEnemy[i]->getY());
			_player->setX(_player->getX() + cosf(angle) * 10);
			_player->setY(_player->getY() - sinf(angle) * 10);
			_player->setShadowX(_player->getShadowX() + cosf(angle) * 10);
			_player->setShadowY(_player->getShadowY() - sinf(angle) * 10);
		}
		if (_vEnemy[i]->getIsPush())
		{
			float angle = getAngle(_vEnemy[i]->getX(), _vEnemy[i]->getY(), _player->getX(), _player->getY());
			_player->setX(_player->getX() + cosf(angle) * 10);
			_player->setY(_player->getY() - sinf(angle) * 10);
			_player->setShadowX(_player->getShadowX() + cosf(angle) * 10);
			_player->setShadowY(_player->getShadowY() - sinf(angle) * 10);
		}
	}


}

void enemyManager::bulletCol()
{
	RECT temp;
	for (int i = 0; i < _bullet->getVBullet().size(); ++i)
	{
		if (IntersectRect(&temp, &_rc.GetRect(), &_bullet->getVBullet()[i].rc.GetRect()))
		{
			ImageManager::GetInstance()->FindImage("bulletCollision")->SetScale(1.5f);
			EFFECTMANAGER->play("bulletCollision", (temp.left + temp.right) / 2, ((temp.top + temp.bottom) / 2) + 10);
			_bullet->remove(i);
		}
	}
}

void enemyManager::enemyDead(int arr)
{
	_vEnemy[arr]->release();
	_vEnemy.erase(_vEnemy.begin() + arr);
	
}
