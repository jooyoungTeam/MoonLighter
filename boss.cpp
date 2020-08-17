#include "stdafx.h"
#include "boss.h"

void boss::set()
{
	_bossAttackCount = 0;
	ZeroMemory(&_attack1, sizeof(tagAttack1));
	ZeroMemory(&_attack2, sizeof(tagAttack1));
	ZeroMemory(&_attack3, sizeof(tagAttack1));
	ZeroMemory(&_attack3Rc, sizeof(tagAttackRect));
	ZeroMemory(&_attack3Rc2, sizeof(tagAttackRect));
	_attack1.x = _pX;
	_attack1.y = -40;
	_attack1.speed = 8.f;
	_attack1.img = ImageManager::GetInstance()->FindImage("bossHand");
	_attack2.angle = 40.f;
	_attack2.index = 5;
	_leftTop.x = 1400;
	_leftTop.y = 515;
	_rightTop.x = 1460;
	_rightTop.y = 510;
	_leftBottom.x = 826;
	_leftBottom.y = 1185;
	_rightBottom.x = 886;
	_rightBottom.y = 1185;
	_bossAni = ONE;
	for (int i = 0; i < 13; ++i)
	{
		_attack3Rc[i].rc = RectMakePivot(Vector2(-300, -300), Vector2(0, 0), Pivot::Center);
		_attack3Rc2[i].rc = RectMakePivot(Vector2(-300, -300), Vector2(0, 0), Pivot::Center);
	}

	_attack2.img = ImageManager::GetInstance()->FindImage("bossLong");
	_attack2.hole = ImageManager::GetInstance()->FindImage("bossLong2");
}

void boss::render()
{
	//_img->aniRender(Vector2(_x, _y), _motion, 1.25f);
//	if (KEYANIMANAGER->findAnimation(""))
	CAMERAMANAGER->aniRender(_img, _x, _y, _motion, 2.5f);
	
	//CAMERAMANAGER->fillRectangle(_rc, D2D1::ColorF::Tomato, 0.7f);
	for (int i = 0; i < 13; ++i)
	{
		CAMERAMANAGER->zOrderRender(ImageManager::GetInstance()->FindImage("Boss_Rock0"), _attack3Rc[i].rc.left, _attack3Rc[i].rc.top, _attack3Rc[i].rc.bottom, _attack3Rc[i].alpha, 1.5f);
		CAMERAMANAGER->zOrderRender(ImageManager::GetInstance()->FindImage("Boss_Rock1"), _attack3Rc2[i].rc.left, _attack3Rc2[i].rc.top, _attack3Rc2[i].rc.bottom, _attack3Rc2[i].rockAlpha, 1.5f);
		if (_attack3Rc2[i].rackFall)
		{
			CAMERAMANAGER->render(ImageManager::GetInstance()->FindImage("shadow"), _attack3Rc2[i].x - 65, _attack3Rc2[i].y, _attack3Rc2[i].scale, _attack3Rc2[i].alpha);
		}
			CAMERAMANAGER->fillRectangle(_attack3Rc2[i].attackRc, D2D1::ColorF::Tomato, 1.0f);
			CAMERAMANAGER->fillRectangle(_attack3Rc[i].attackRc, D2D1::ColorF::Tomato, 1.0f);
	}
	CAMERAMANAGER->frameRender(_attack1.img, _attack1.x, _attack1.y, _attack1.index, 0);
	_attack1.img->SetScale(2.5f);
	CAMERAMANAGER->zOrderFrameRender(_attack2.img, _attack2.x, _attack2.y, _leftBottom.y + 300, _attack2.index,0, 2.5f, 1.0f);
	_attack2.img->SetAngle(_attack2.angle);
	CAMERAMANAGER->fillRectangle(_attackRc, D2D1::ColorF::Tomato,0.4f);
	//CAMERAMANAGER->line(_leftTop, _rightTop, D2D1::ColorF::Black, 2.0f);
	//CAMERAMANAGER->line(_rightTop, _rightBottom, D2D1::ColorF::Black, 2.0f);
	//CAMERAMANAGER->line(_rightBottom, _leftBottom, D2D1::ColorF::Black, 2.0f);
	//CAMERAMANAGER->line(_leftBottom, _leftTop, D2D1::ColorF::Black, 2.0f);
	
	CAMERAMANAGER->fillRectangle(_bar.back, D2D1::ColorF::DimGray, 1.0f);
	CAMERAMANAGER->fillRectangle(_bar.middle, D2D1::ColorF::LightSalmon, 1.0f);
	CAMERAMANAGER->fillRectangle(_bar.front, D2D1::ColorF::Tomato, 1.0f);

	EFFECTMANAGER->render();
}

void boss::attack()
{
	_playerCol = playerCol();
	if (_playerCol)
	{
		cout << "플레이어 죽음" << endl;
	}
	cout << _attackTimer << endl;
	if (!_patternCheck)
	{
		_attackTimer = 0;
		_patternRandom = RND->getFromIntTo(0,5);

	//	랜덤으로 공격 받는데 
	//	전에 했던 공격이면 리턴. 다시 받아와라
		if (_patternRandom == _saveRandom)
		{
			attack();
			return;
		}

		if (_patternRandom == 0)
		{
			_bossPattern = HAND_FALL;
		}
		if (_patternRandom == 1)
		{
			if (abs(getDistance(_pX, _pY, _x, _y)) >= 600)
			{
				attack();
				return;
			}
			_bossPattern = ARM_LONG;
		}
		if (_patternRandom == 2)
		{
			_bossPattern = ROCK_FALL;
		}
		if (_patternRandom == 3)
		{
			if (abs(getDistance(_pX, _pY, _x, _y)) <= 600)
			{
				attack();
				return;
			}
			_bossPattern = PLAYER_PULL;
		}
		if (_patternRandom == 4)
		{
			if (abs(getDistance(_pX, _pY, _x, _y)) >= 550)
			{
				attack();
				return;
			}
			_bossPattern = EXPLOSION;
		}
		//공격 뭐할지 결정됐음 나가
		_saveRandom = _patternRandom;
		_bossAni = ONE;
		_patternCheck = true;
		_attack3.isAttack = false;
	}
	if (_bossPattern == HAND_FALL)
	{
		attack1();
	}
	if (_bossPattern == ARM_LONG)
	{
		
		if (!_attack3.isAttack)
		{
			attack3();
		}
		else
		{
			attack2();
			attack2Angle();
		}
	}
	if (_bossPattern == ROCK_FALL)
	{
		attack3();
	}
	if (_bossPattern == PLAYER_PULL)
	{
		attack3();
	}
	if (_bossPattern == EXPLOSION)
	{
		attack4();
	}
}

void boss::dead()
{
	if (_bossAni == ONE)
	{
		_y = 625;
		_img = ImageManager::GetInstance()->FindImage("bossHit");
		_motion = KEYANIMANAGER->findAnimation(_index, "bossHit");
		_motion->start();
		_bossAni = TWO;
	}
	if (_bossAni == TWO)
	{
		if (!KEYANIMANAGER->findAnimation(_index, "bossHit")->isPlay())
		{
			_y = 650;
			_img = ImageManager::GetInstance()->FindImage("bossDead");
			_motion = KEYANIMANAGER->findAnimation(_index, "bossDead");
			_motion->start();
			_bossAni = THREE;
		}
	}
}

void boss::enemyHit()
{
	if (_bossAni == ONE)
	{
		_img = ImageManager::GetInstance()->FindImage("BossUp");
		_motion = KEYANIMANAGER->findAnimation(_index, "BossDown");
		_motion->start();
		_bossAni = TWO;
	}
	if (_bossAni == TWO)
	{
		if (!KEYANIMANAGER->findAnimation(_index, "BossDown")->isPlay())
		{
			_img = ImageManager::GetInstance()->FindImage("BossUp");
			_motion = KEYANIMANAGER->findAnimation(_index, "BossUp");
			_motion->start();
			_bossAni = THREE;
		}
	}
	if (_bossAni == THREE)
	{
		if (!KEYANIMANAGER->findAnimation(_index, "BossUp")->isPlay())
		{
			_motion = KEYANIMANAGER->findAnimation(_index, "boss");
			_img = ImageManager::GetInstance()->FindImage("boss");
			_motion->start();
			_state = _idle;
			_isHit = false;
			_bossAni = ONE;
		}
	}
}

void boss::attack1()
{
	if (_bossAni == ONE)
	{
		_img = ImageManager::GetInstance()->FindImage("bossAttack");
		_motion = KEYANIMANAGER->findAnimation(_index, "bossAttack");
		_motion->start();
		_bossAni = TWO;
	}
	if (_bossAni == TWO)
	{
		if (!KEYANIMANAGER->findAnimation(_index, "bossAttack")->isPlay())
		{
			_img = ImageManager::GetInstance()->FindImage("bossAttackIdle");
			_motion = KEYANIMANAGER->findAnimation(_index, "bossAttackIdle");
			_motion->start();
			_bossAni = THREE;
		}
	}
	if (_bossAni == THREE)
	{
		attack1_1();
		if (_attack1.count >= 3)
		{
			_bossAni = FOUR;
		}
	}
	if (_bossAni == FOUR)
	{
		_img = ImageManager::GetInstance()->FindImage("bossHandCome");
		_motion = KEYANIMANAGER->findAnimation(_index, "bossHandCome");
		_motion->start();
		_bossAni = FIVE;
	}
	if (_bossAni == FIVE)
	{
		if (!KEYANIMANAGER->findAnimation(_index, "bossHandCome")->isPlay())
		{
			_motion = KEYANIMANAGER->findAnimation(_index, "boss");
			_img = ImageManager::GetInstance()->FindImage("boss");
			_motion->start();
			_state = _idle;
			_patternCheck = false;
			_attackDelay = 0;
			_attack1.count = 0;
			_bossAni = ONE;
		}
	}
}

void boss::attack2()
{
	if (_bossAni == ONE)
	{
		_img = ImageManager::GetInstance()->FindImage("bossHandFly");
		_motion = KEYANIMANAGER->findAnimation(_index, "bossHandFly1");
		_motion->start();
		_bossAni = TWO;
	}
	if (_bossAni == TWO)
	{
		if (!KEYANIMANAGER->findAnimation(_index, "bossHandFly1")->isPlay())
		{
			_img = ImageManager::GetInstance()->FindImage("bossHandFly");
			_motion = KEYANIMANAGER->findAnimation(_index, "bossHandFly2");
			_motion->start();
			_bossAni = THREE;
		}
		
	}
	if (_bossAni == THREE)
	{
		attack2_1();
		if (_attack2.count > 2)
		{
			_img = ImageManager::GetInstance()->FindImage("bossHandFly");
			_motion = KEYANIMANAGER->findAnimation(_index, "bossHandFly3");
			_motion->start();
			_bossAttackCount = 0;
			_bossAni = FOUR;
		}
		
	}
	if (_bossAni == FOUR)
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
			_bossAni = FIVE;
		}
	}
	if (_bossAni == FIVE)
	{
		for (int i = 0; i < 13; i++)
		{
			_attack3Rc[i].alpha -= 0.05f;
			_attack3Rc[i].attackRc = RectMakePivot(Vector2(-300, -300), Vector2(0, 0), Pivot::Center);
			_attack2.count = 0;

			if (_attack3Rc[i].alpha <= 0)
			{
				setRock();
				_state = _idle;
				_attackDelay = 0;
				_patternCheck = false;
				_isRockBottom = false;
				_bossAni = ONE;
				_cameraShake = 0;
			}
		}
		
	}
}

void boss::attack3()
{

	if (_bossAni == ONE)
	{
		_img = ImageManager::GetInstance()->FindImage("bossHandFly");
		_motion = KEYANIMANAGER->findAnimation(_index, "bossAttack11");
		_motion->start();
		_bossAni = TWO;
	}
	if (_bossAni == TWO)
	{
		if (!KEYANIMANAGER->findAnimation(_index, "bossAttack11")->isPlay())
		{
			_motion = KEYANIMANAGER->findAnimation(_index, "bossAttack22");
			_motion->start();
			_onceAni = true;
			_bossAni = THREE;
		}

	}
	if (_bossAni == THREE)
	{
		if (!KEYANIMANAGER->findAnimation(_index, "bossAttack22")->isPlay())
		{
			_img = ImageManager::GetInstance()->FindImage("boss");
			_motion = KEYANIMANAGER->findAnimation(_index, "boss");
			_motion->start();
			_attackDelay = 0;
			_bossAni = FOUR;
		}

	}
	if (_bossAni == FOUR)
	{
		if (_bossPattern == ARM_LONG)
		{
			attack3_1();
			_attack3.delay++;
			if (_attack3.delay > 100)
			{
				_attack3.delay = 0;
				_attack3.isAttack = true;
				_bossAni = ONE;
			}
		}
		if (_bossPattern == ROCK_FALL)
		{
			attack3_2();

		}
		if (_bossPattern == PLAYER_PULL)
		{
			attack3_3();
		}
	}
}

void boss::attack4()
{
	_exCount++;
	if (_bossAni == ONE)
	{
		_img = ImageManager::GetInstance()->FindImage("bossHit");
		_y = 625;
		_motion = KEYANIMANAGER->findAnimation(_index, "bossLight");
		_motion->start();
		_bossAni = TWO;
	}
	if (_exCount > 50)
	{
		_attackRc = RectMakePivot(Vector2(_x, _y), Vector2(800, 900), Pivot::Center);
	}
	if (_bossAni == TWO)
	{
		if (!KEYANIMANAGER->findAnimation(_index, "bossLight")->isPlay())
		{
			_img = ImageManager::GetInstance()->FindImage("boss");
			_motion = KEYANIMANAGER->findAnimation(_index, "boss");
			_motion->start();
			_y = 500;
			EFFECTMANAGER->play("bossPullEffect", _pX + 135, _pY  + 90);
			_state = _idle;
			//_bossAni = ONE;
			_exCount = 0;
			_patternCheck = false;
			_attackDelay = 0;
			_attackRc = RectMakePivot(Vector2(-100, -100), Vector2(0, 0), Pivot::Center);
		}
	}
	RECT temp;
	if (IntersectRect(&temp, &_pRc.GetRect(), &_attackRc.GetRect()))
	{
		if (((getDistance(_pX, _pY, _x, _y)) < 500))
		{
			_isBossPush = true;
		}
	}
		if ((getDistance(_pX, _pY, _x, _y)) >= 1000)
		{
			_isBossPush = false;
		}

	

}

void boss::attack1_1()
{
	
	if (!_attack1.isAttack)
	{
		_attack1.xRandom = RND->getFromIntTo(-100, 100);
		_attack1.yRandom = RND->getFromIntTo(-100, 100);
		if (_pY > _attack1.y + _attack1.yRandom)
		{
			_attack1.y += _attack1.speed;
			_attack1.speed += 0.9f;
			_attack1.rc = RectMakePivot(Vector2(_attack1.x, _attack1.y), Vector2(50, 50), Pivot::Center);
		}
		else
		{
			_attack1.index = 2;
			_attack1.isAttack = true;
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
				_attack1.speed += 0.9f;
				_attack1.rc = RectMakePivot(Vector2(_attack1.x, _attack1.y), Vector2(50, 50), Pivot::Center);
			}
			else
			{
				_attack1.index = 0;
				_attack1.x = _pX + _attack1.xRandom;
				_attack1.speed = 8.0f;
				_attack1.isAttack = false;
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
	if (_attack2.index <= 0)
	{
		_attack2.index = 0;
	}

	_attack2.x = _x - 140;
	_attack2.y = _y;
	_attack2.width = 10;
	_attack2.height = 10;
	_attack2.rc = RectMakePivot(Vector2(_attack2.x, _attack2.y), Vector2(_attack2.width, _attack2.height), Pivot::LeftTop);


	if (!_attack2.isAttack)
	{
		_attack2.angle = 360 - getAngle((_leftTop.x + _rightTop.x) / 2, (_leftTop.y + _rightTop.y) / 2, (_leftBottom.x + _rightBottom.x) / 2, (_leftBottom.y + _rightBottom.y) / 2) * 180 / PI - 90;
		_leftBottom.x+=14.5;
		_rightBottom.x+=14.5;


		if (_leftBottom.x > 2000)
		{
			_attack2.isAttack = true;
		}
	}
	if (_attack2.isAttack)
	{
		_attack2.angle = 360 - getAngle((_leftTop.x + _rightTop.x) / 2, (_leftTop.y + _rightTop.y) / 2, (_leftBottom.x + _rightBottom.x) / 2, (_leftBottom.y + _rightBottom.y) / 2) * 180 / PI - 90;
		_leftBottom.x -= 14.5;
		_rightBottom.x -= 14.5;

		if (_leftBottom.x < 846)
		{
			_attack2.isAttack = false;
			_attack2.count++;
		}
		
	}
	if (_attack2.count > 2)
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
		}
	}

}

void boss::attack3_1()
{
	for (int i = 0; i < 13; ++i)
	{
		if (!_attack3Rc[i].rackFall)
		{
			setRock();
			_attack3Rc[i].rackFall = true;
			_isRockBottom = false;
		}
	}
	for (int i = 0; i < 13; ++i)
	{
		if (_attack3Rc[i].rackFall)
		{
			_attack3Rc[i].mY += 25;
			if (_attack3Rc[i].mY >= _attack3Rc[i].y)
			{
				_attackTimer++;
				if (_attackTimer < 100)
				{
					_isRockBottom = true;
				}
				else
				{
					_isRockBottom = false;
				}
				_cameraShake++;
				_attack3Rc[i].mY = _attack3Rc[i].y;
			}
			if (_cameraShake > 5 && _cameraShake <= 6 )
			{
				 CAMERAMANAGER->shakeCamera(5, 50);
			}
			_attack3Rc[i].rc = RectMakePivot(Vector2(_attack3Rc[i].x, _attack3Rc[i].mY), Vector2(_attack3Rc[i].width, _attack3Rc[i].width), Pivot::Center);
			_attack3Rc[i].attackRc = RectMakePivot(Vector2(_attack3Rc[i].x, _attack3Rc[i].mY), Vector2(100, 100), Pivot::Center);

		}
	}
}

void boss::attack3_2()
{

	for (int i = 0; i < 13; ++i)
	{ 
		if (!_attack3Rc2[i].rackFall)
		{
			_attack3Rc2[i].width = 150;
			_attack3Rc2[i].x = RND->getFromIntTo(600, 2500);
			_attack3Rc2[i].y = RND->getFromIntTo(600, 1200);
			_attack3Rc2[0].x = _pX;
			_attack3Rc2[0].y = _pY;
			_attack3Rc2[i].mX = 0 - _attack3Rc2[i].x;
			_attack3Rc2[i].mY = 0 - _attack3Rc2[i].y;
			_attack3Rc2[i].alpha = 0.5f;
			_attack3Rc2[i].rockAlpha = 1.0f;
			_attack3Rc2[i].rackFall = true;
			_isRockBottom = false;
			_attack3Rc2[i].scale = 0.5f;
			_attack3Rc2[i].rackCount = 0;
			_attack3Rc2[i].attackRc = RectMakePivot(Vector2(-100, -100), Vector2(_attack3Rc2[i].width, _attack3Rc2[i].width), Pivot::Center);
		}
		if (_attack3Rc2[i].rackFall)
		{
			_attack3Rc2[i].scale += 0.015f;
			_attack3Rc2[i].alpha + 0.1f;
			if (_attack3Rc2[i].scale >= 1.4f)
			{
				_attack3Rc2[i].scale = 1.4f;
			}
			if (_attack3Rc2[i].alpha >= 1.0f)
			{
				_attack3Rc2[i].alpha = 1.0f;
			}
		
			_attack3Rc2[i].mX = _attack3Rc2[i].x;


			_attack3Rc2[i].mY += 30;
			
			
			_attack3Rc2[i].rackCount++;
			if (_attack3Rc2[i].mY >= _attack3Rc2[i].y)
			{
				_attackTimer++;
				if (_attackTimer < 100)
				{
					_isRockBottom = true;
				}
				else
				{
					_isRockBottom = false;
				}
				_attack3Rc2[i].attackRc = RectMakePivot(Vector2(_attack3Rc2[i].x, _attack3Rc2[i].y), Vector2(_attack3Rc2[i].width, _attack3Rc2[i].width), Pivot::Center);
				CAMERAMANAGER->shakeCamera(3, 2);
				_attack3Rc2[i].mY = _attack3Rc2[i].y;
				if (_attack3Rc2[i].rackCount > 150)
				{
					_attack3Rc2[i].alpha -= 0.05f;
					_attack3Rc2[i].rockAlpha -= 0.5f;
					if (_attack3Rc2[i].alpha <= 0)
					{
						_attack3Rc2[i].alpha = 0;
					}
					if (_attack3Rc2[i].rockAlpha <= 0)
					{
						_attack3Rc2[i].rockAlpha = 0;
						_attack3.delay = 0;
						_state = _idle;
						_bossAni = ONE;
						_attackDelay = 0;
						_attack3Rc2[i].rackCount = 0;
						_patternCheck = false;
						_isRockBottom = false;
						_attack3Rc2[i].attackRc = RectMakePivot(Vector2(-100, -100), Vector2(_attack3Rc2[i].width, _attack3Rc2[i].width), Pivot::Center);

						_attack3Rc2[i].rackFall = false;
						
					}
				}

			}
		}
		_attack3Rc2[i].rc = RectMakePivot(Vector2(_attack3Rc2[i].mX, _attack3Rc2[i].mY), Vector2(_attack3Rc2[i].width, _attack3Rc2[i].width), Pivot::Center);
	}

}

void boss::attack3_3()
{
	if ((getDistance(_pX, _pY, _x, _y)) >= 400)
	{
		_isBossPull = true;
	}
	else
	{
		_isBossPull = false;
		_state = _idle;
		_bossAni = ONE;
		_patternCheck = false;
		_attackDelay = 0;
	}
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

void boss::setRock()
{
	for (int i = 0; i < 13; ++i)
	{
		_attack3Rc[i].alpha = 1;
		_attack3Rc[0].x = 960;
		_attack3Rc[0].y = 788;

		_attack3Rc[1].x = 1011;
		_attack3Rc[1].y = 891;

		_attack3Rc[2].x = 1084;
		_attack3Rc[2].y = 982;

		_attack3Rc[3].x = 1161;
		_attack3Rc[3].y = 1072;

		_attack3Rc[4].x = 1292;
		_attack3Rc[4].y = 1128;

		_attack3Rc[5].x = 1415;
		_attack3Rc[5].y = 1165;

		_attack3Rc[6].x = 1530;
		_attack3Rc[6].y = 1175;

		_attack3Rc[7].x = 1670;
		_attack3Rc[7].y = 1165;

		_attack3Rc[8].x = 1820;
		_attack3Rc[8].y = 1128;

		_attack3Rc[9].x = 1929;
		_attack3Rc[9].y = 1072;

		_attack3Rc[10].x = 2021;
		_attack3Rc[10].y = 978;

		_attack3Rc[11].x = 2104;
		_attack3Rc[11].y = 886;

		_attack3Rc[12].x = 2150;
		_attack3Rc[12].y = 788;

		_attack3Rc[i].width = 120;

		_attack3Rc[i].mY = 0;


		_attack3Rc[i].rc = RectMakePivot(Vector2(_attack3Rc[i].x, _attack3Rc[i].mY), Vector2(_attack3Rc[i].width, _attack3Rc[i].width), Pivot::Center);
	}
}

bool boss::playerCol()
{
	RECT temp;
	for (int i = 0; i < 13; i++)
	{
		if (IntersectRect(&temp, &_attack3Rc[i].attackRc.GetRect(), &_pRc.GetRect()) && _isRockBottom)
		{
			_attack3Rc[i].attackRc = RectMakePivot(Vector2(-100, -100), Vector2(0, 0), Pivot::Center);

				return true;
		}
		if (IntersectRect(&temp, &_attack3Rc2[i].attackRc.GetRect(), &_pRc.GetRect()) && _isRockBottom)
		{
			_attack3Rc2[i].attackRc = RectMakePivot(Vector2(-100, -100), Vector2(0, 0), Pivot::Center);
			return true;
		}
	}

	if (IntersectRect(&temp, &_attack1.rc.GetRect(), &_pRc.GetRect()) ||
		IntersectRect(&temp, &_attackRc.GetRect(), &_pRc.GetRect()) ||
		_isHandCol)
	{
		_attack1.rc = RectMakePivot(Vector2(-100, -100), Vector2(0, 0), Pivot::Center);
		_attackRc = RectMakePivot(Vector2(-100, -100), Vector2(0, 0), Pivot::Center);
		return true;
	}

	return false;
}

