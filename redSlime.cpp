#include "stdafx.h"
#include "redSlime.h"

void redSlime::attack()
{
	_isAttack = true;
	_x += cosf(_attackAngle) * _speed;
	_y += -sinf(_attackAngle) * _speed;
	_attackRc = RectMakePivot(Vector2(_x, _y), Vector2(_width, _height), Pivot::Center);
	
	RECT temp2;
	if (IntersectRect(&temp2, &_pRc.GetRect(), &_attackRc.GetRect()))
	{
		_attackRc = RectMakePivot(Vector2(0, 0), Vector2(0, 0), Pivot::Center);
	}

	RECT temp;
	if (IntersectRect(&temp, &_rc.GetRect(), &_pRc.GetRect()) && !_isCol )
	{
		_attackRc = RectMakePivot(Vector2(0, 0), Vector2(0, 0), Pivot::Center);
		_isCol = true;
		_attackCount = 0;
		_scale = 1.3f;
		_speed = 0;
		_img = ImageManager::GetInstance()->FindImage("slimeAttack");
		_motion->stop();
		_motion = KEYANIMANAGER->findAnimation(  "slimeAttack");
		_motion->start();
		_x = _pX;
		_y = _pY;

	}
	if (_isCol)
	{
		_bigSlimeCount++;
		if (_bigSlimeCount > 100)
		{
			_img = ImageManager::GetInstance()->FindImage("redSlime");
			_motion->stop();
			_motion = KEYANIMANAGER->findAnimation(  "redSlime");
			_motion->start();
			_isAttack = false;
			_state = _idle;
			_attackCount = 0;
			_attackDelay = 0;
			_scale = 1.0f;
			_attackCount = 0;
			_bigSlimeCount = 0;
			_isCol = false;
			return;
		}
	}
	if (!_isCol)
	{
		_speed = 5;
		_attackCount++;
	}
	//if ()
	if (_attackCount > 50)
	{
		_img = ImageManager::GetInstance()->FindImage("redSlime");
		_motion->stop();
		_motion = KEYANIMANAGER->findAnimation(  "redSlime");
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
		_motion = KEYANIMANAGER->findAnimation(  "redSlimeDead");
		_motion->start();
		_onceAni = false;
	}
	if (!KEYANIMANAGER->findAnimation(  "redSlimeDead")->isPlay())
	{
		_realDead = true;
	}
}
