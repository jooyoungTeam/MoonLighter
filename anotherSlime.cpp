#include "stdafx.h"
#include "anotherSlime.h"

void anotherSlime::attack()
{
	if (!_pang)
	{
		_attackCount++;
		_isAttack = true;
		_x += cosf(_attackAngle) * 3;
		_y += -sinf(_attackAngle) * 3;
		if (!_isPlayerHit)
		{
			_attackRc = RectMakePivot(Vector2(_x, _y), Vector2(_width, _height), Pivot::Center);
		}

		//RECT temp;
		//if (IntersectRect(&temp, &_pRc.GetRect(), &_attackRc.GetRect()))
		//{
		//	_attackRc = RectMakePivot(Vector2(0, 0), Vector2(0, 0), Pivot::Center);
		//}

		if (_attackCount > 25)
		{
			_isAttack = false;
			_state = _idle;
			_attackCount = 0;
			_attackDelay = 0;
		}



		if (((getDistance(_x, _y, _pX, _pY)) < 200) && _type == ENEMY_YELLOW_SLIME && !_once)
		{
			_yRandom = RND->getFromIntTo(0, 30);

			if (_yRandom == 4)
			{
				_img = ImageManager::GetInstance()->FindImage("yellowSlimePang");
				_motion->stop();
				_motion = KEYANIMANAGER->findAnimation("yellowSlimePang");
				_motion->start();
				_once = true;
				_pang = true;

				if (!_isPlayerHit)
				{
					_attackRc = RectMakePivot(Vector2(_x, _y), Vector2(100, 100), Pivot::Center);
				}
			}
		}

	}
	else
	{
		if (!KEYANIMANAGER->findAnimation("yellowSlimePang")->isPlay())
		{
			_realDead = true;
		}
	}
	//if (_pang)
	//{
	//	if (!_motion->isPlay())
	//	{
	//		_motion->stop();
	//	}
	//}
}

void anotherSlime::enemyMove()
{
}

void anotherSlime::dead()
{
	if (_onceAni)
	{
		cout << "ต้" << endl;
		if (_type == ENEMY_YELLOW_SLIME)
		{
			_img = ImageManager::GetInstance()->FindImage("yellowSlimeDead");
			_motion->stop();
			_motion = KEYANIMANAGER->findAnimation("yellowSlimeDead");
			_motion->start();
			_onceAni = false;
		}
		if (_type == ENEMY_BLUE_SLIME)
		{
			_img = ImageManager::GetInstance()->FindImage("blueSlimeDead");
			_motion->stop();
			_motion = KEYANIMANAGER->findAnimation("blueSlimeDead");
			_motion->start();
			_onceAni = false;
		}

	}
	else
	{

		if (_type == ENEMY_YELLOW_SLIME)
		{
			if (!_motion->isPlay())
			{
				_realDead = true;
			}
		}
		if (_type == ENEMY_BLUE_SLIME)
		{
			if (!_motion->isPlay())
			{
				_realDead = true;
			}
		}
	}
}
