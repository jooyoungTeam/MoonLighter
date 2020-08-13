#include "stdafx.h"
#include "boss.h"

void boss::set()
{
	_isBossAttack = _isBossAttackEnd = 0; 
	_bossAttackCount = 0;
	ZeroMemory(&_attack1, sizeof(tagAttack1));
	_attack1.x = _pX;
	_attack1.y = -40;
	_attack1.speed = 8.f;
	_attack1.img = ImageManager::GetInstance()->FindImage("bossHand");
	_attack2.angle = 40.f;
	_attack2.index = 5;
	_attack2.img = ImageManager::GetInstance()->FindImage("bossLong");
}

void boss::render()
{
	//_img->aniRender(Vector2(_x, _y), _motion, 1.25f);
	CAMERAMANAGER->aniRender(_img, _x, _y, _motion, 1.6f);
	CAMERAMANAGER->frameRender(_attack1.img, _attack1.x, _attack1.y, _attack1.index, 0);
	_attack1.img->SetScale(1.6f);
	CAMERAMANAGER->frameRender(_attack2.img, _attack2.x, _attack2.y, _attack2.index, 0);
	_attack2.img->SetAngle(_attack2.angle);
	_attack2.img->SetScale(1.6f);
	//_attack1.img->FrameRender(Vector2(_attack1.x, _attack1.y), _attack1.index, 0);
	//_attack1.img->SetScale(1.5f);
	//_attack2.img->FrameRender(Vector2(_attack2.x, _attack2.y), _attack2.index, 0);
	//_attack2.img->SetScale(1.5f);
	//_attack2.img->SetAngle(_attack2.angle);
	//D2DRenderer::GetInstance()->FillRectangle(_attack2.rc, D2D1::ColorF::Black, 0.7f);
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
	attack2_1();
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
	if (_attack2.index >= 5)
	
	{

		if (!KEYANIMANAGER->findAnimation(_index, "bossHandFly3")->isPlay())
		{
			_motion = KEYANIMANAGER->findAnimation(_index, "boss");
			_img = ImageManager::GetInstance()->FindImage("boss");
			_motion->start();
			//_state = _idle;
			_isBossAttackEnd = false;
			_isAttack = false;
			_attackDelay = 0;
		}
	}
}

void boss::attack1_1()
{
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
			if (_attack1.y > -40)
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

void boss::attack2_1()
{
	_attack2.aniDelayCount++;
	if (_attack2.aniDelayCount >4)
	{
		_attack2.index--;
		_attack2.aniDelayCount = 0;
	}
	_attack2.x = _x - 120;
	_attack2.y = _y;
	_attack2.width = 10;
	_attack2.height = 10;
	_attack2.rc = RectMakePivot(Vector2(_attack2.x, _attack2.y), Vector2(_attack2.width, _attack2.height), Pivot::LeftTop);

	if (_attack2.index <= 0)
	{
		_attack2.index = 0;
	}
	if (!_attack2.isBottom)
	{
		cout << _attack2.angle << endl;
		_attack2.angle--;
		if (_attack2.angle <= -60.f)
		{
			_attack2.isBottom = true;
		}
	}
	if (_attack2.isBottom)
	{
		_attack2.angle++;
		{
			if (_attack2.angle >= 40.f)
			{
				_attack2.isBottom = false;
				_attack2.count++;
			}
		}
	}
	if (_attack2.count > 3)
	{
		if (_attack2.aniDelayCount > 4)
		{
			_attack2.index++;
			_attack2.aniDelayCount = 0;
		}
		if (_attack2.index >= 5)
		{
			_attack2.index = 5;
			_attack2.count = 0;
		}
	}
	
}

