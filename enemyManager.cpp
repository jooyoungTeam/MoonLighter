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
	_bulletWait = 0;
	for (int i = 0; i < _vEnemy.size(); ++i)
	{
		if (_vEnemy[i]->getEnemyType() == ENEMY_POT)
		{
			_bullet = new bullet;
			_bullet->init("bullet");
		}
		if (_vEnemy[i]->getEnemyType() == ENEMY_BOSS)
		{
			_bullet = new bullet;
			_bullet->init("bossBullet");
		}
	}
	
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
		_angle = getAngle(_player->getX(), _player->getY(), _vEnemy[i]->getX(), _vEnemy[i]->getY());
		_bulletAngle = getAngle(_vEnemy[i]->getX(), _vEnemy[i]->getY(), _player->getX(), _player->getY());
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

		if (_vEnemy[i]->getEnemyType() == ENEMY_POT)
		{
			_bulletWait = 90;
		}
		if (_vEnemy[i]->getEnemyType() == ENEMY_BOSS)
		{
			if (_vEnemy[i]->getBossPattern() == BOSS_BULLET_FIRE)
			{
				_bulletWait = 40;
			}
			if (_vEnemy[i]->getBossPattern() == BOSS_BULLET_PFIRE)
			{
				_bulletWait = 30;
			}
		}
	}
	
	if (_bulletDelay > _bulletWait)
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
			break;
		}
	}

	EFFECTMANAGER->update();
}

void enemyManager::render()
{
	for (int i = 0; i < _vEnemy.size(); ++i)
	{
		_vEnemy[i]->render();
		if (_vEnemy[i]->getEnemyType() == ENEMY_POT)
		{
			_bullet->potRender();
		}
		if (_vEnemy[i]->getEnemyType() == ENEMY_BOSS)
		{
			_bullet->bossRender();
		}
	}

	//CAMERAMANAGER->fillRectangle(_rc, D2D1::ColorF::DimGray, 1.0);
	//D2DRenderer::GetInstance()->DrawRectangle(_rc, D2DRenderer::DefaultBrush::Black, 1.f);
	ImageManager::GetInstance()->FindImage("bulletCollision")->SetScale(1.5f);
	EFFECTMANAGER->render();
}

void enemyManager::setEnemy1()
{
	enemy* gol1;
	gol1 = new golem;
	gol1->playerCheck(_x, _y, _rc);
	gol1->init(700, 500, 80, 100, ENEMY_GOLEM);
	_vEnemy.push_back(gol1);

	enemy* gol12;
	gol12 = new golem;
	gol12->playerCheck(_x, _y, _rc);
	gol12->init(800, 500, 80, 100, ENEMY_GOLEM);
	_vEnemy.push_back(gol12);

	enemy* pot1;
	pot1 = new pot;
	pot1->playerCheck(_x, _y, _rc);
	pot1->init(1200, 500, 50, 50, ENEMY_POT);
	_vEnemy.push_back(pot1);

	enemy* pot22;
	pot22 = new pot;
	pot22->playerCheck(_x, _y, _rc);
	pot22->init(1200, 700, 50, 50, ENEMY_POT);
	_vEnemy.push_back(pot22);



	enemy* pot2;
	pot2 = new pot;
	pot2->playerCheck(_x, _y, _rc);
	pot2->init(200, 300, 50, 50, ENEMY_POT);
	pot2->setPotDirection(POT_RIGHT);
	_vEnemy.push_back(pot2);


}

void enemyManager::setEnemy2()
{



	enemy* redS1;
	redS1 = new redSlime;
	redS1->playerCheck(_x, _y, _rc);
	redS1->init(200, 200, 70, 70, ENEMY_RED_SLIME);
	_vEnemy.push_back(redS1);
	
	enemy* redS12;
	redS12 = new redSlime;
	redS12->playerCheck(_x, _y, _rc);
	redS12->init(200, 200, 70, 70, ENEMY_RED_SLIME);
	_vEnemy.push_back(redS12);


	enemy* yelS1;
	yelS1 = new anotherSlime;
	yelS1->playerCheck(_x, _y, _rc);
	yelS1->init(200, 100, 30, 30, ENEMY_YELLOW_SLIME);
	_vEnemy.push_back(yelS1);


	enemy* bleS1;
	bleS1 = new anotherSlime;
	bleS1->playerCheck(_x, _y, _rc);
	bleS1->init(400, 100, 30, 30, ENEMY_BLUE_SLIME);
	_vEnemy.push_back(bleS1);



}

void enemyManager::setBoss()
{
	enemy* boss1;
	boss1 = new boss;
	boss1->playerCheck(_x, _y, _rc);
	boss1->init(1360, 300, 590, 650, ENEMY_BOSS);
	_vEnemy.push_back(boss1);
}

void enemyManager::potBullet()
{
	bool bossChangeAngle;
	int changeCount;
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
			if (_vEnemy[i]->getBossPattern() == BOSS_BULLET_FIRE)
			{
				float random = RND->getFromFloatTo(2.5, 3.8);
				_bullet->manyFire(_vEnemy[i]->getX(), _vEnemy[i]->getY(), random, 5.f, 10);
	
			}
			if (_vEnemy[i]->getBossPattern() == BOSS_BULLET_PFIRE)
			{
				_bullet->fire(_vEnemy[i]->getX(), _vEnemy[i]->getY(), _bulletAngle, 10.0f);
			}
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
			_player->setX(_player->getX() + cosf(_angle) * 10);
			_player->setY(_player->getY() - sinf(_angle) * 10);
			_player->setShadowX(_player->getShadowX() + cosf(_angle) * 10);
			_player->setShadowY(_player->getShadowY() - sinf(_angle) * 10);
		}
		if (_vEnemy[i]->getIsPush())
		{
			_player->setX(_player->getX() + cosf(_angle) * 10);
			_player->setY(_player->getY() - sinf(_angle) * 10);
			_player->setShadowX(_player->getShadowX() + cosf(_angle) * 10);
			_player->setShadowY(_player->getShadowY() - sinf(_angle) * 10);
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
