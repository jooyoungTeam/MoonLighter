#include "stdafx.h"
#include "boss.h"

void boss::set()
{
	_isBossAttack = _isBossAttackEnd = 0; 
	_bossAttackCount = 0;
	ZeroMemory(&_attack1, sizeof(tagAttack1));
	_attack1.x = _pX;
	_attack1.y = -30;
	_attack1.speed = 8.f;
	_attack1.img = ImageManager::GetInstance()->FindImage("bossHand");
}

void boss::render()
{
	_img->aniRender(Vector2(_x, _y), _motion, 1.25f);
	_attack1.img->FrameRender(Vector2(_attack1.x, _attack1.y), _attack1.index, 0);
	_attack1.img->SetScale(1.25f);
	D2DRenderer::GetInstance()->FillRectangle(_attack1.attackRc, D2D1::ColorF::Tomato, 0.7f);
}

void boss::attack()
{
	attack1();
}

void boss::dead()
{
	if (!_isBossAttackEnd)
	{
		_img = ImageManager::GetInstance()->FindImage("bossHit");
		_motion = KEYANIMANAGER->findAnimation(_index, "bossHit");
		_motion->start();
		_isBossAttackEnd = true;
		_onceAni = true;
		_isBossAttack = false;
	}
	if (_onceAni && !_isBossAttack)
	{
		if (!KEYANIMANAGER->findAnimation(_index, "bossHit")->isPlay())
		{
			_img = ImageManager::GetInstance()->FindImage("bossDead");
			_motion = KEYANIMANAGER->findAnimation(_index, "bossDead");
			_motion->start();
			_isBossAttack = true;
			_onceAni = true;
		}
	}
}

void boss::enemyHit()
{
	if (!_isBossAttackEnd)
	{
		_img = ImageManager::GetInstance()->FindImage("BossUp");
		_motion = KEYANIMANAGER->findAnimation(_index, "BossDown");
		_motion->start();
		_isBossAttackEnd = true;
		_onceAni = true;
		_isBossAttack = false;
	}
	if (_onceAni && !_isBossAttack)
	{
		if (!KEYANIMANAGER->findAnimation(_index, "BossDown")->isPlay())
		{
			_img = ImageManager::GetInstance()->FindImage("BossUp");
			_motion = KEYANIMANAGER->findAnimation(_index, "BossUp");
			_motion->start();
			_isBossAttack = true;
			_onceAni = true;
		}
	}
	if (_isBossAttack && _onceAni)
	{
		if (!KEYANIMANAGER->findAnimation(_index, "BossUp")->isPlay())
		{
			cout << "emdmd" << endl;
			_motion = KEYANIMANAGER->findAnimation(_index, "boss");
			_img = ImageManager::GetInstance()->FindImage("boss");
			_motion->start();
			_state = _idle;
			//_isBossAttackEnd = false;
		}
	}
}

void boss::attack1()
{
	if (!_isAttack)
	{
		_img = ImageManager::GetInstance()->FindImage("bossAttack");
		_motion = KEYANIMANAGER->findAnimation(_index, "bossAttack");
		_motion->start();
		_isAttack = true;
		_onceAni = true;
		_isBossAttack = false;
	}
	if (_onceAni && !_isBossAttack)
	{
		if (!KEYANIMANAGER->findAnimation(_index, "bossAttack")->isPlay())
		{
			_img = ImageManager::GetInstance()->FindImage("bossAttackIdle");
			_motion = KEYANIMANAGER->findAnimation(_index, "bossAttackIdle");
			_motion->start();
			_isBossAttack = true;
			_onceAni = false;
		}
	}
	if (_isBossAttack && !_onceAni)
	{
		_attack1.onceImage = true;
		attack1_1();
		//_bossAttackCount++;
		if (_attack1.count >= 8)
		{
			_onceAni = true;
			_isBossAttack = true;
		}
	}
	if (_onceAni && _isBossAttack)
	{
		_img = ImageManager::GetInstance()->FindImage("bossHandCome");
		_motion = KEYANIMANAGER->findAnimation(_index, "bossHandCome");
		_motion->start();
		_isBossAttackEnd = true;
		//_bossAttackCount = 0;
		_onceAni = false;
		_isBossAttack = false;
	}
	if (_isBossAttackEnd)
	{
		if (!KEYANIMANAGER->findAnimation(_index, "bossHandCome")->isPlay())
		{
			cout << "emdmd" << endl;
			_motion = KEYANIMANAGER->findAnimation(_index, "boss");
			_img = ImageManager::GetInstance()->FindImage("boss");
			_motion->start();
			_state = _idle;
			_attackDelay = 0;
			_attack1.count = 0;
			_isAttack = false;
			_isBossAttackEnd = false;
		}
	}
}

void boss::attack2()
{
	if (!_isAttack)
	{
		_img = ImageManager::GetInstance()->FindImage("bossHandFly");
		_motion = KEYANIMANAGER->findAnimation(_index, "bossHandFly1");
		_motion->start();
		_isAttack = true;
		_onceAni = true;
		_isBossAttack = false;
	}
	if (_onceAni && !_isBossAttack)
	{
		if (!KEYANIMANAGER->findAnimation(_index, "bossHandFly1")->isPlay())
		{
			_img = ImageManager::GetInstance()->FindImage("bossHandFly");
			_motion = KEYANIMANAGER->findAnimation(_index, "bossHandFly2");
			_motion->start();
			_isBossAttack = true;
			_onceAni = true;
		}
	}
	if (_isBossAttack && _onceAni)
	{
		if (!KEYANIMANAGER->findAnimation(_index, "bossHandFly2")->isPlay())
		{
			_img = ImageManager::GetInstance()->FindImage("bossHandFly");
			_motion = KEYANIMANAGER->findAnimation(_index, "bossHandFly3");
			_motion->start();
			_isBossAttackEnd = true;
			_bossAttackCount = 0;
			_onceAni = false;
			_isBossAttack = false;
		}
	}
	if (_isBossAttackEnd)
	{

		if (!KEYANIMANAGER->findAnimation(_index, "bossHandFly3")->isPlay())
		{
			_motion = KEYANIMANAGER->findAnimation(_index, "boss");
			_img = ImageManager::GetInstance()->FindImage("boss");
			_motion->start();
			_state = _idle;
			_isBossAttackEnd = false;
			_isAttack = false;
			_attackDelay = 0;
		}
	}
}

void boss::attack1_1()
{
	cout << _attack1.index << endl;
	if (!_attack1.isBottom)
	{
		_attack1.xRandom = RND->getFromIntTo(-100, 100);
		_attack1.yRandom = RND->getFromIntTo(-100, 100);
		if (_pY > _attack1.y + _attack1.yRandom)
		{
			_attack1.y += _attack1.speed;
			_attack1.speed += 0.7f;
			_attack1.rc = RectMakePivot(Vector2(_attack1.x, _attack1.y), Vector2(50, 50), Pivot::Center);
		}
		else
		{
			_attack1.index = 2;
			_attack1.isBottom = true;
			_attack1.speed = 8.0f;
			_attack1.attackRc = RectMakePivot(Vector2(_attack1.x, _attack1.y + 30), Vector2(80, 20), Pivot::Center);
		}

	}
	else
	{
		_attack1.delay++;
		_attack1.aniDelayCount++;
		if (_attack1.aniDelayCount > 2)
		{
			_attack1.index++;
			_attack1.aniDelayCount = 0;
		}
		if (_attack1.index >= 18)
		{
			_attack1.index = 18;
		}
		if (_attack1.delay > 50)
		{
			if (_attack1.y > -30)
			{
				_attack1.y -= _attack1.speed;
				_attack1.speed += 0.7f;
				_attack1.rc = RectMakePivot(Vector2(_attack1.x, _attack1.y), Vector2(50, 50), Pivot::Center);
			}
			else
			{
				_attack1.index = 0;
				_attack1.x = _pX + _attack1.xRandom;
				_attack1.speed = 8.0f;
				_attack1.isBottom = false;
				_attack1.count++;
				_attack1.delay = 0;

			}
		}
	}
}

