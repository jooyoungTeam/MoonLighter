#include "stdafx.h"
#include "redSlime.h"

void redSlime::attack()
{
	_isAttack = true;
	_x += cosf(_attackAngle) * _speed;
	_y += -sinf(_attackAngle) * _speed;
	if (!_isPlayerHit)
	{
		_attackRc = RectMakePivot(Vector2(_x, _y), Vector2(_width, _height), Pivot::Center);
	}
	//RECT temp2;
	//if (IntersectRect(&temp2, &_pRc.GetRect(), &_attackRc.GetRect()))
	//{
	//	_attackRc = RectMakePivot(Vector2(0, 0), Vector2(0, 0), Pivot::Center);
	//}

	//RECT temp;

	if (_isCol && !_isTie)
	{
		_attackCount = 0;
		_scale = 2.0f;
		_speed = 0;
		_img = ImageManager::GetInstance()->FindImage("slimeAttack");
		_motion->stop();
		_motion = KEYANIMANAGER->findAnimation("slimeAttack");
		SOUNDMANAGER->play("레드슬라임공격", 1.0f);
		_motion->start();
		_x = _pX;
		_y = _pY;
		_isTie = true;
	}

	if (!_isCol && _isTie)
	{
		_img = ImageManager::GetInstance()->FindImage("redSlime");
		_motion->stop();
		_motion = KEYANIMANAGER->findAnimation(  "redSlime");
		_motion->start();
		_isAttack = false;
		_isTie = false;
		_state = _idle;
		_attackCount = 0;
		_attackDelay = 0;
		_scale = 1.0f;
		_attackCount = 0;
		_bigSlimeCount = 0;
		return;
	
	}
	if (!_isCol)
	{
		_speed = 5;
		_attackCount++;
	}
	if (_attackCount > 50)
	{
		_img = ImageManager::GetInstance()->FindImage("redSlime");
		_motion->stop();
		_motion = KEYANIMANAGER->findAnimation("redSlime");
		_motion->start();
		_isAttack = false;
		_state = _idle;
		_attackCount = 0;
		_attackDelay = 0;
		_scale = 1.0f;

		_attackCount = 0;
	}
	
}

void redSlime::enemyMove()
{
}

void redSlime::dead()
{
	if (_onceAni)
	{
		_img = ImageManager::GetInstance()->FindImage("redSlimeDead");
		_motion->stop();
		_motion = KEYANIMANAGER->findAnimation("redSlimeDead");
		_motion->start();
		_onceAni = false;
		SOUNDMANAGER->play("슬라임죽음", 1.0f);
	}
	if (!_motion->isPlay() && !_realDead)
	{
		cout << " 들어옴 " << endl;
		_realDead = true;
	}
}
