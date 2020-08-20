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
	_bulletTimer = 0;
	_index = 0;
	_bullet = new bullet;
	for (int i = 0; i < _vEnemy.size(); ++i)
	{
		if (_vEnemy[i]->getEnemyType() == ENEMY_POT)
		{
			_bullet->init("bullet");
		}
		if (_vEnemy[i]->getEnemyType() == ENEMY_BOSS)
		{
			_bullet->init("bossBullet");
		}
	}

	_playerStop = false;


	return S_OK;
}

void enemyManager::release()
{
	SAFE_DELETE(_bullet);
	//SOUNDMANAGER->release();
}

void enemyManager::update()
{
	if (_player->getPlayerMoveTrap())
	{
		cout << "플레이어 멈춰" << endl;
	}
	if (!_player->getPlayerMoveTrap())
	{
		cout << "플레이어 움직 움직" << endl;
	}
	_x = _player->getX();
	_y = _player->getY();
	//EFFECTMANAGER->play("bossTornadoEffect", _player->getX(), _player->getY());
	_rc = _player->getPlayerRc();
	_bulletDelay++;
	for (int i = 0; i < _vEnemy.size(); ++i)
	{
		_vEnemy[i]->update();
		_vEnemy[i]->playerCheck(_x, _y, _rc, _player->getPlayerMoveTrap());

	}
	for (int i = 0; i < _vEnemy.size(); ++i)
	{
		_angle = getAngle(_player->getX(), _player->getY(), _vEnemy[i]->getX(), _vEnemy[i]->getY());
		_bulletAngle = getAngle(_vEnemy[i]->getX(), _vEnemy[i]->getY(), _player->getX(), _player->getY());
		if (_vEnemy[i]->getEnemyType() == ENEMY_RED_SLIME)
		{
			if (_vEnemy[i]->getIsCol())
			{
				_player->setPlayerMoveTrap(true);
				//_player->getPlayerMoveTrap() = true;
			}
			/*if (!_vEnemy[i]->getIsCol())
			{
				_player->setPlayerMoveTrap(false);
			}*/
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
	_bullet->update();
	if (_bulletDelay > _bulletWait)
	{
		potBullet();
	}
	playerCol();
	bulletCol();
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
	//gol1->playerCheck(_x, _y, _rc);
	gol1->init(700, 500, 80, 100, ENEMY_GOLEM);
	_vEnemy.push_back(gol1);

	enemy* gol12;
	gol12 = new golem;
	//gol12->playerCheck(_x, _y, _rc);
	gol12->init(800, 500, 80, 100, ENEMY_GOLEM);
	_vEnemy.push_back(gol12);

	enemy* pot1;
	pot1 = new pot;
	//pot1->playerCheck(_x, _y, _rc);
	pot1->init(1200, 500, 50, 50, ENEMY_POT);
	_vEnemy.push_back(pot1);

	enemy* pot22;
	pot22 = new pot;
	//pot22->playerCheck(_x, _y, _rc);
	pot22->init(1200, 700, 50, 50, ENEMY_POT);
	_vEnemy.push_back(pot22);



	enemy* pot2;
	pot2 = new pot;
	//pot2->playerCheck(_x, _y, _rc);
	pot2->init(200, 300, 50, 50, ENEMY_POT);
	pot2->setPotDirection(POT_RIGHT);
	_vEnemy.push_back(pot2);

	enemy* gost;
	gost = new pot;
	//gost->playerCheck(_x, _y, _rc);
	gost->init(-300, -300, 50, 50, ENEMY_POT);
	gost->setPotDirection(POT_RIGHT);
	_vEnemy.push_back(gost);


}

void enemyManager::setEnemy2()
{



	enemy* redS1;
	redS1 = new redSlime;
	//redS1->playerCheck(_x, _y, _rc);
	redS1->init(200, 200, 70, 70, ENEMY_RED_SLIME);
	_vEnemy.push_back(redS1);


	enemy* yelS1;
	yelS1 = new anotherSlime;
	//yelS1->playerCheck(_x, _y, _rc);
	yelS1->init(200, 100, 30, 30, ENEMY_YELLOW_SLIME);
	_vEnemy.push_back(yelS1);


	enemy* bleS1;
	bleS1 = new anotherSlime;
	//bleS1->playerCheck(_x, _y, _rc);
	bleS1->init(400, 100, 30, 30, ENEMY_BLUE_SLIME);
	_vEnemy.push_back(bleS1);



}

void enemyManager::setBoss()
{
	enemy* boss1;
	boss1 = new boss;
	//boss1->playerCheck(_x, _y, _rc);
	boss1->init(1360, 300, 590, 650, ENEMY_BOSS);
	_vEnemy.push_back(boss1);
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
			SOUNDMANAGER->play("총알쏘기", 1.0f);
		}
		//cout << _bulletTimer << endl;
		if (_vEnemy[i]->getEnemyType() == ENEMY_BOSS && _vEnemy[i]->getState() == _vEnemy[i]->getAttack())
		{
			if (_vEnemy[i]->getBossPattern() == BOSS_BULLET_FIRE)
			{
				float random = RND->getFromFloatTo(2.5, 3.8);
				_bullet->manyFire(_vEnemy[i]->getX(), _vEnemy[i]->getY(), random, 5.f, 10);
				_bulletTimer++;
				SOUNDMANAGER->play("레드슬라임공격", 1.0f);
				if (_bulletTimer > 10)
				{
					_bullet->getVBullet().clear();
					//cout << " = ==" << endl;
					//b->setPatternCheck(false);
					_vEnemy[i]->setPatternCheck(false);
					_vEnemy[i]->setState(_vEnemy[i]->getIdle());
					_vEnemy[i]->setAttackDelay(0);
					_bulletTimer = 0;
				}
			}
			if (_vEnemy[i]->getBossPattern() == BOSS_BULLET_PFIRE)
			{
				_bullet->fire(_vEnemy[i]->getX(), _vEnemy[i]->getY(), _bulletAngle, 10.0f);
				_bulletTimer++;
				SOUNDMANAGER->play("레드슬라임공격", 1.0f);
				if (_bulletTimer > 20)
				{
					_bullet->getVBullet().clear();
					//b->setPatternCheck(false);
					_vEnemy[i]->setPatternCheck(false);
					_vEnemy[i]->setState(_vEnemy[i]->getIdle());
					_vEnemy[i]->setAttackDelay(0);
					_bulletTimer = 0;
				}
			}
		}


	}
}

void enemyManager::playerCol()
{
	RECT temp;

	if (_player->getplayerCurrentHp() <= 0)
	{
		_player->setPlayerCurrentHp(0);
	}

	//검충돌
	for (int i = 0; i < _vEnemy.size(); ++i)
	{
		if (IntersectRect(&temp, &_vEnemy[i]->getEnemyRect().GetRect(), &_player->getPlayerAttackRc().GetRect()))
		{
			EFFECTMANAGER->play("swordEffect1", (temp.left + temp.right) / 2, ((temp.top + temp.bottom) / 2) + 10);
			_vEnemy[i]->setEnemyAttack(30);
			//	CAMERAMANAGER->shakeCamera(5, 10);
			_player->setAttackRc(0, 0, 0, 0);
			if (_vEnemy[i]->getEnemyType() == ENEMY_BLUE_SLIME || _vEnemy[i]->getEnemyType() == ENEMY_RED_SLIME || _vEnemy[i]->getEnemyType() == ENEMY_YELLOW_SLIME)
			{
				SOUNDMANAGER->play("슬라임맞음", 1.0f);
			}
			if (_vEnemy[i]->getEnemyType() == ENEMY_GOLEM)
			{
				SOUNDMANAGER->play("골렘맞음", 1.0f);
			}
			if (_vEnemy[i]->getEnemyType() == ENEMY_POT)
			{
				SOUNDMANAGER->play("총알장전", 1.0f);
			}
			if (_vEnemy[i]->getEnemyType() == ENEMY_BOSS	)
			{
				SOUNDMANAGER->play("보스맞음", 1.0f);
			}
		}
		//활충돌
		for (int j = 0; j < _player->getArrow()->getVArrow().size(); ++j)
		{
			if (IntersectRect(&temp, &_vEnemy[i]->getEnemyRect().GetRect(), &_player->getArrow()->getVArrow()[j].rc.GetRect()))
			{
				if (_player->getArrow()->getVArrow()[j].isPowerShot)
				{
					_vEnemy[i]->setEnemyAttack(_player->getArrow()->getVArrow()[j].arrowDamage);
				}
				else
				{
					_vEnemy[i]->setEnemyAttack(_player->getArrow()->getVArrow()[j].arrowDamage);
					_player->getArrow()->playerRemoveArrow(j);
				}
				if (_vEnemy[i]->getEnemyType() == ENEMY_BLUE_SLIME || _vEnemy[i]->getEnemyType() == ENEMY_RED_SLIME || _vEnemy[i]->getEnemyType() == ENEMY_YELLOW_SLIME)
				{
					SOUNDMANAGER->play("슬라임맞음", 1.0f);
				}
				if (_vEnemy[i]->getEnemyType() == ENEMY_GOLEM)
				{
					SOUNDMANAGER->play("골렘맞음", 1.0f);
				}
				if (_vEnemy[i]->getEnemyType() == ENEMY_POT)
				{
					SOUNDMANAGER->play("총알장전", 1.0f);
				}
				if (_vEnemy[i]->getEnemyType() == ENEMY_BOSS)
				{
					SOUNDMANAGER->play("보스맞음", 1.0f);
				}
				//CAMERAMANAGER->shakeCamera(5, 10);
				//_player->se(0, 0, 0, 0);
				break;
			}
		}
		if (IntersectRect(&temp, &_vEnemy[i]->getEnemyAttackRect().GetRect(), &_player->getPlayerRc().GetRect()) && _vEnemy[i]->getState() == _vEnemy[i]->getAttack()
			&& _player->getCurrectState() != _player->getRollState())
		{
			_vEnemy[i]->setIsPlayerHit(true);
			//_player->setCurrentState(_());

			if (_player->getCurrectState() == _player->getShieldState())
			{
				_player->setPlayerCurrentHp(_player->getplayerCurrentHp() - 5);
			}
			else
			{
				_player->setPlayerCurrentHp(_player->getplayerCurrentHp() - 10);
			}


			_player->setEnemyCol(true);

			_vEnemy[i]->setAttackRect(0, 0, 0, 0);
		}
		if (_vEnemy[i]->getIsPull())
		{
			/*	if (_vEnemy[i]->getOnceEffect())
				{
					EFFECTMANAGER->play("bossTornadoEffect", _player->getX(), _player->getY());
					_vEnemy[i]->setOnceEffect(false);
					cout << "ㄷㄹ" << endl;
				}*/
			_player->setX(_player->getX() + cosf(_angle) * 10);
			_player->setY(_player->getY() - sinf(_angle) * 10);
			_player->setShadowX(_player->getShadowX() + cosf(_angle) * 10);
			_player->setShadowY(_player->getShadowY() - sinf(_angle) * 10);
		}
		if (_vEnemy[i]->getIsPush())
		{
			/*if (_vEnemy[i]->getOnceEffect())
			{
				EFFECTMANAGER->play("bossPullEffect", _player->getX(), _player->getY());
				_vEnemy[i]->setOnceEffect(false);
				cout << "왜.." << endl;
			}*/
			_player->setX(_player->getX() + cosf(_bulletAngle) * 10);
			_player->setY(_player->getY() - sinf(_bulletAngle) * 10);
			_player->setShadowX(_player->getShadowX() + cosf(_bulletAngle) * 10);
			_player->setShadowY(_player->getShadowY() - sinf(_bulletAngle) * 10);
		}


		boss* b = dynamic_cast<boss*>(_vEnemy[i]);
		if (b == NULL) continue;
		//cout << b->playerCol() << endl;
		if (b->playerCol() && _vEnemy[i]->getState() == _vEnemy[i]->getAttack()
			&& _player->getCurrectState() != _player->getRollState())
		{
			if (_player->getCurrectState() == _player->getShieldState())
			{
				_player->setPlayerCurrentHp(_player->getplayerCurrentHp() - 10);
			}
			else
			{
				_player->setPlayerCurrentHp(_player->getplayerCurrentHp() - 20);
			}


			_player->setEnemyCol(true);
		}
		RECT tempRc = _player->getShadowRc().GetRect();
		if (b->playerStop(tempRc))
		{
			float x = (tempRc.right + tempRc.left) * 0.5f;
			float y = (tempRc.bottom + tempRc.top) * 0.5f;
			_player->setPlayerPos(x, y);

		}

	}

}

void enemyManager::bulletCol()
{
	RECT temp;

	for (int i = 0; i < _bullet->getVBullet().size(); ++i)
	{
		for (int j = 0; j < _vEnemy.size(); ++j)
		{
			if (_vEnemy[j]->getEnemyType() == ENEMY_POT)
			{
				if (IntersectRect(&temp, &_player->getPlayerRc().GetRect(), &_bullet->getVBullet()[i].rc.GetRect())
					&& _player->getCurrectState() != _player->getRollState())
				{
					ImageManager::GetInstance()->FindImage("bulletCollision")->SetScale(1.5f);
					EFFECTMANAGER->play("bulletCollision", (temp.left + temp.right) / 2, ((temp.top + temp.bottom) / 2) + 10);
					_player->setEnemyCol(true);
					SOUNDMANAGER->play("총알터짐", 1.0f);

					if (_player->getCurrectState() == _player->getShieldState())
					{
						_player->setPlayerCurrentHp(_player->getplayerCurrentHp() - 5);
					}
					else
					{
						_player->setPlayerCurrentHp(_player->getplayerCurrentHp() - 10);
					}

					_bullet->remove(i);
				}
			}

			if (_vEnemy[j]->getEnemyType() == ENEMY_BOSS)
			{
				if (IntersectRect(&temp, &_player->getPlayerRc().GetRect(), &_bullet->getVBullet()[i].rc.GetRect())
					&& _player->getCurrectState() != _player->getRollState())
				{
					SOUNDMANAGER->play("총알터짐", 1.0f);
					if (_player->getCurrectState() == _player->getShieldState())
					{
						_player->setPlayerCurrentHp(_player->getplayerCurrentHp() - 10);
					}
					else
					{
						_player->setPlayerCurrentHp(_player->getplayerCurrentHp() - 20);
					}


					_player->setEnemyCol(true);
					_bullet->remove(i);
				}
			}
		}
	}
}

void enemyManager::enemyDead(int arr)
{
	_vEnemy[arr]->release();
	_vEnemy.erase(_vEnemy.begin() + arr);

}
