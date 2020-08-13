#include "stdafx.h"
#include "boss.h"

void boss::set()
{
	_isBossAttack = _isBossAttackEnd = 0; 
	_bossAttackCount = 0;
	ZeroMemory(&_attack1, sizeof(tagAttack1));
	ZeroMemory(&_attack2, sizeof(tagAttack1));
	ZeroMemory(&_attack3, sizeof(tagAttack1));
	//ZeroMemory(&_attack2Rc, sizeof(tagAttackRect));
	_attack1.x = _pX;
	_attack1.y = -40;
	_attack1.speed = 8.f;
	_attack1.img = ImageManager::GetInstance()->FindImage("bossHand");
	_attack2.angle = 40.f;
	_attack2.index = 5;
	_leftTop.x = 1420;
	_leftTop.y = 515;
	_rightTop.x = 1440;
	_rightTop.y = 510;
	_leftBottom.x = 846;
	_leftBottom.y = 1185;
	_rightBottom.x = 866;
	_rightBottom.y = 1185;
	_attack2.img = ImageManager::GetInstance()->FindImage("bossLong");
	_attack2.hole = ImageManager::GetInstance()->FindImage("bossLong2");
}

void boss::render()
{
	//_img->aniRender(Vector2(_x, _y), _motion, 1.25f);

	CAMERAMANAGER->aniRender(_img, _x, _y, _motion, 1.6f);
	CAMERAMANAGER->frameRender(_attack1.img, _attack1.x, _attack1.y, _attack1.index, 0);
	_attack1.img->SetScale(1.6f);
	CAMERAMANAGER->frameRender(_attack2.img, _attack2.x, _attack2.y, 0, 0);
	_attack2.img->SetAngle(_attack2.angle);
	_attack2.img->SetScale(1.6f);
	//D2DRenderer::GetInstance()->DrawRotationFillRectangle(_attack2.attackRc, D2D1::ColorF::Black, _attack2.angle);
	CAMERAMANAGER->line(_leftTop, _rightTop, D2D1::ColorF::Black, 2.0f);
	CAMERAMANAGER->line(_rightTop, _rightBottom, D2D1::ColorF::Black, 2.0f);
	CAMERAMANAGER->line(_rightBottom, _leftBottom, D2D1::ColorF::Black, 2.0f);
	CAMERAMANAGER->line(_leftBottom, _leftTop, D2D1::ColorF::Black, 2.0f);
	
	//for (int i = 0; i < 10; +\+i)
	//{
	//	//D2DRenderer::GetInstance()->FillRectangle(_attack2Rc[i].rc, D2D1::ColorF::Black, 0.7f);
	//	CAMERAMANAGER->fillRectangle(_attack2.attackRc, D2D1::ColorF::Red, 1.0f);
	//}
	//_attack1.img->FrameRender(Vector2(_attack1.x, _attack1.y), _attack1.index, 0);
	//_attack1.img->SetScale(1.5f);
	//_attack2.img->FrameRender(Vector2(_attack2.x, _attack2.y), _attack2.index, 0);
	//_attack2.img->SetScale(1.5f);
	//_attack2.img->SetAngle(_attack2.angle);
	//D2DRenderer::GetInstance()->FillRectangle(_attack2.rc, D2D1::ColorF::Black, 0.7f);
}

void boss::attack()
{
	if (!_attack3.isBottom)
	{

		attack3();
	}
	else
	{
		attack2_1();
		attack2Angle();
	}
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
		_attack2.aniDelayCount++;
		attack2_1();
		if (!KEYANIMANAGER->findAnimation(_index, "bossHandFly2")->isPlay() && _attack2.count > 1)
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
		_attack2.aniDelayCount++;
		if (_attack2.aniDelayCount > 4)
		{
			_attack2.index++;
			_attack2.aniDelayCount = 0;
		}
		if (_attack2.index >= 5)
		{
			_attack2.index = 5;
			_attack2.count = 0;
			_attack2.delay++;
		}
		if (_attack2.delay > 210)
		{
			_attack2.x = -100;
			_attack2.y = -100;
			_attack2.delay = 0;
		}
		if (!KEYANIMANAGER->findAnimation(_index, "bossHandFly3")->isPlay())
		{
			_motion = KEYANIMANAGER->findAnimation(_index, "boss");
			_img = ImageManager::GetInstance()->FindImage("boss");
			_motion->start();
			_state = _idle;
			_isBossAttackEnd = false;
			_isAttack = false;
			_attackDelay = 0;
			_attack3.isBottom = false;
		}
	}
}

void boss::attack3()
{
	if (!_isAttack)
	{
		_img = ImageManager::GetInstance()->FindImage("bossHandFly");
		_motion = KEYANIMANAGER->findAnimation(_index, "bossAttack3");
		_motion->start();
		_isAttack = true;
		_onceAni = true;
	}
	if (_onceAni)
	{
		if (!KEYANIMANAGER->findAnimation(_index, "bossAttack3")->isPlay())
		{
			_img = ImageManager::GetInstance()->FindImage("boss");
			_motion = KEYANIMANAGER->findAnimation(_index, "boss");
			_motion->start();
			_onceAni = false;
			_attackDelay = 0;
		}
	}
	if (!_onceAni)
	{
		cout << _attack3.delay << endl;
		_attack3.delay++;
		if (_attack3.delay > 300)
		{
			_isAttack = false;
			_attack3.delay = 0;
			_attack3.isBottom = true;
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
		if (_attack1.aniDelayCount > 3)
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
	_attack2.delay = 0;
	_attack2.aniDelayCount++;
	if (_attack2.aniDelayCount >4)
	{
		_attack2.index--;
		_attack2.aniDelayCount = 0;
	}

	_attack2.x = _x - 140;
	_attack2.y = _y;
	_attack2.width = 10;
	_attack2.height = 10;
	_attack2.rc = RectMakePivot(Vector2(_attack2.x, _attack2.y), Vector2(_attack2.width, _attack2.height), Pivot::LeftTop);
	_attack2.attackRc = RectMakePivot(Vector2(_attack2.x, _attack2.y), Vector2(50, 400), Pivot::LeftTop);


	if (_attack2.index <= 0)
	{
		_attack2.index = 0;
	}
	if (!_attack2.isBottom)
	{
		_attack2.angle--;
		_leftBottom.x+=14.5;
		_rightBottom.x+=14.5;
		_leftTop.x+=0.5;
		_rightTop.x+=0.5;
		if (_attack2.angle <= -60.f)
		{
			_attack2.isBottom = true;
		}
	}
	if (_attack2.isBottom)
	{
		_attack2.angle++;
		_leftBottom.x -= 14.5;
		_rightBottom.x -= 14.5;
		_leftTop.x -= 0.5;
		_rightTop.x-=0.5;
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
			_isBossAttackEnd = true;
		}
	}

}

void boss::attack3_1()
{
}

void boss::attack2Angle()
{
	float angle1 = getAngle(_leftBottom.x, _leftBottom.y, _leftTop.x, _leftTop.y);
	float angle2 = getAngle(_rightBottom.x, _rightBottom.y, _rightTop.x, _rightTop.y);

	float angle3 = getAngle(_leftBottom.x, _leftBottom.y, _pX, _pY);
	float angle4 = getAngle(_rightBottom.x, _rightBottom.y, _pX, _pY);

	if (angle1 > angle3 && angle2 < angle4 && _pY > _leftTop.y && _pY < _leftBottom.y)
	{
		_isHandCol = true;
	}
	else
	{
		_isHandCol = false;
	}

}
