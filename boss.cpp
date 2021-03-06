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
	_saveRandom = -1;
	_bossAni = ONE;
	_maxHP = _curHP = 1000;
	_index = 0;
	_aniCount = 0;
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
	CAMERAMANAGER->zOrderAniRender(_img, _x, _y, _z, _motion, 2.5f);

	if (_state == _attack)
	{
		//CAMERAMANAGER->fillRectangle(_rc, D2D1::ColorF::Tomato, 0.7f);
		for (int i = 0; i < 17; ++i)
		{
			CAMERAMANAGER->zOrderRender(ImageManager::GetInstance()->FindImage("Boss_Rock0"), _attack3Rc[i].rc.left, _attack3Rc[i].rc.top, _attack3Rc[i].rc.bottom, _attack3Rc[i].alpha, 1.5f);
			CAMERAMANAGER->zOrderRender(ImageManager::GetInstance()->FindImage("Boss_Rock1"), _attack3Rc2[i].rc.left, _attack3Rc2[i].rc.top, _attack3Rc2[i].rc.bottom, _attack3Rc2[i].rockAlpha, 1.5f);

			if (_attack3Rc2[i].rockFall)
			{
				CAMERAMANAGER->render(ImageManager::GetInstance()->FindImage("shadow"), _attack3Rc2[i].x - 65, _attack3Rc2[i].y, _attack3Rc2[i].scale, _attack3Rc2[i].alpha);
			}
			//CAMERAMANAGER->fillRectangle(_attack3Rc2[i].attackRc, D2D1::ColorF::Tomato, 1.0f);
			CAMERAMANAGER->fillRectangle(_attack3Rc[i].rc, D2D1::ColorF::Tomato, 1.0f);
		}
		//CAMERAMANAGER->fillRectangle(_attackRc,  D2D1::ColorF::Tomato, 1.0f);
		//CAMERAMANAGER->fillRectangle(_attack1.attackRc, D2D1::ColorF::Tomato, 1.0f);
		CAMERAMANAGER->frameRender(_attack1.img, _attack1.x, _attack1.y, _attack1.index, 0);
		_attack1.img->SetScale(2.5f);
		CAMERAMANAGER->frameRender(_effectImage, _eX, _eY - 80, _index, 0);
		//CAMERAMANAGER->zOrderFrameRender(_effectImage, _eX, _eY - 80, _eY - 120, _index, 0, 1.0f, 1.0f);

		CAMERAMANAGER->zOrderFrameRender(_attack2.img, _attack2.x, _attack2.y, _leftBottom.y + 300, _attack2.index, 0, 2.5f, 1.0f);
		_attack2.img->SetAngle(_attack2.angle);
		//CAMERAMANAGER->fillRectangle(_attackRc, D2D1::ColorF::Tomato,0.4f);
		//CAMERAMANAGER->line(_leftTop, _rightTop, D2D1::ColorF::Black, 2.0f);
		//CAMERAMANAGER->line(_rightTop, _rightBottom, D2D1::ColorF::Black, 2.0f);
		//CAMERAMANAGER->line(_rightBottom, _leftBottom, D2D1::ColorF::Black, 2.0f);
		//CAMERAMANAGER->line(_leftBottom, _leftTop, D2D1::ColorF::Black, 2.0f);


	}
	EFFECTMANAGER->render();
}

void boss::attack()
{
	if (_isPlayerHit)
	{
		_hitTimer++;
		if (_hitTimer > 60)
		{
			_isPlayerHit = false;
			_hitTimer = 0;
		}
	}
	_playerCol = playerCol();
	if (!_patternCheck)
	{
		_index = 0;
		_attackTimer = 0;
		_patternRandom = RND->getFromIntTo(0, 7);

		//	�������� ���� �޴µ� 
		//	���� �ߴ� �����̸� ����. �ٽ� �޾ƿͶ�
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
			_index = 0;
		}
		if (_patternRandom == 4)
		{
			if (abs(getDistance(_pX, _pY, _x, _y)) >= 550)
			{
				attack();
				return;
			}
			_bossPattern = EXPLOSION;
			_index = 0;
		}
		if (_patternRandom == 5)
		{
			_bossPattern = BOSS_BULLET_FIRE;
		}
		if (_patternRandom == 6)
		{
			_bossPattern = BOSS_BULLET_PFIRE;
		}
		//���� ������ �������� ����
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
		SOUNDMANAGER->play("��������", 1.0f);
		_y = 625;
		_img = ImageManager::GetInstance()->FindImage("bossHit");
		_motion->stop();
		_motion = KEYANIMANAGER->findAnimation("bossHit");
		_motion->start();
		_bossAni = TWO;
	}
	if (_bossAni == TWO)
	{
		if (!_motion->isPlay())
		{
			_y = 650;
			_img = ImageManager::GetInstance()->FindImage("bossDead");
			_motion->stop();
			_motion = KEYANIMANAGER->findAnimation("bossDead");
			_motion->start();
			_bossAni = THREE;
		}
	}
	if (_bossAni == THREE)
	{
		if (!_motion->isPlay())
		{
			_realDead = true;
			_bossAni = FOUR;
		}
	}
	
}

void boss::enemyHit()
{
	if (_bossAni == ONE)
	{
		_img = ImageManager::GetInstance()->FindImage("BossUp");
		_motion->stop();
		_motion = KEYANIMANAGER->findAnimation("BossDown");
		_motion->start();
		_bossAni = TWO;
	}
	if (_bossAni == TWO)
	{
		if (!_motion->isPlay())
		{
			_img = ImageManager::GetInstance()->FindImage("BossUp");
			_motion->stop();
			_motion = KEYANIMANAGER->findAnimation("BossUp");
			_motion->start();
			_bossAni = THREE;
		}
	}
	if (_bossAni == THREE)
	{
		if (!_motion->isPlay())
		{
			_motion->stop();
			_motion = KEYANIMANAGER->findAnimation("boss");
			_img = ImageManager::GetInstance()->FindImage("boss");
			_motion->start();
			_state = _attack;
			_isHit = false;
			_bossAni = ONE;
		}
	}
}

void boss::attack1()
{
	if (_bossAni == ONE)
	{
		_motion->stop();
		_img = ImageManager::GetInstance()->FindImage("bossAttack");
		_motion = KEYANIMANAGER->findAnimation("bossAttack");
		_motion->start();
		_bossAni = TWO;
	}
	if (_bossAni == TWO)
	{
		if (!_motion->isPlay())
		{
			_motion->stop();
			_img = ImageManager::GetInstance()->FindImage("bossAttackIdle");
			_motion = KEYANIMANAGER->findAnimation("bossAttackIdle");
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
		_motion->stop();
		_img = ImageManager::GetInstance()->FindImage("bossHandCome");
		_motion = KEYANIMANAGER->findAnimation("bossHandCome");
		_motion->start();
		_bossAni = FIVE;
	}
	if (_bossAni == FIVE)
	{
		if (!_motion->isPlay())
		{
			_motion->stop();
			_motion = KEYANIMANAGER->findAnimation("boss");
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
		_motion->stop();
		_img = ImageManager::GetInstance()->FindImage("bossHandFly");
		_motion = KEYANIMANAGER->findAnimation("bossHandFly1");
		_motion->start();
		_bossAni = TWO;
	}
	if (_bossAni == TWO)
	{
		if (!_motion->isPlay())
		{
			_motion->stop();
			_img = ImageManager::GetInstance()->FindImage("bossHandFly");
			_motion = KEYANIMANAGER->findAnimation("bossHandFly2");
			_motion->start();
			_bossAni = THREE;
			SOUNDMANAGER->play("�ջ���", 1.0f);
		}

	}
	if (_bossAni == THREE)
	{
		attack2_1();
		if (_attack2.count > 2)
		{
			_motion->stop();
			_img = ImageManager::GetInstance()->FindImage("bossHandFly");
			_motion = KEYANIMANAGER->findAnimation("bossHandFly3");
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
		if (!_motion->isPlay())
		{
			_motion->stop();
			_motion = KEYANIMANAGER->findAnimation("boss");
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
		_motion->stop();
		_img = ImageManager::GetInstance()->FindImage("bossHandFly");
		_motion = KEYANIMANAGER->findAnimation("bossAttack11");
		_motion->start();
		_bossAni = TWO;
	}
	if (_bossAni == TWO)
	{
		if (!_motion->isPlay())
		{
			if (_bossPattern == ROCK_FALL || _bossPattern == ARM_LONG)
			{
				SOUNDMANAGER->play("��������2", 1.0f);
			}
			_motion->stop();
			_motion = KEYANIMANAGER->findAnimation("bossAttack22");
			_motion->start();
			_onceAni = true;
			_bossAni = THREE;
		}

	}
	if (_bossAni == THREE)
	{
		if (!_motion->isPlay())
		{
			_motion->stop();
			_img = ImageManager::GetInstance()->FindImage("boss");
			_motion = KEYANIMANAGER->findAnimation("boss");
			_motion->start();
			_attackDelay = 0;
			_bossAni = FOUR;
			if (_bossPattern == PLAYER_PULL)
			{
				SOUNDMANAGER->play("������", 1.0f);
			}

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
		SOUNDMANAGER->play("����", 1.0f);
		_img = ImageManager::GetInstance()->FindImage("bossHit");
		_y = 625;
		_motion->stop();
		_motion = KEYANIMANAGER->findAnimation("bossLight");
		_motion->start();
		_bossAni = TWO;
		_index = 0;
	}
	if (_exCount > 50)
	{
		if (!_isPlayerHit)
		{
			_attackRc = RectMakePivot(Vector2(_x, _y), Vector2(800, 900), Pivot::Center);
		}
	}
	if (_bossAni == TWO)
	{
		if (!_motion->isPlay())
		{
			_img = ImageManager::GetInstance()->FindImage("boss");
			_motion->stop();
			_motion = KEYANIMANAGER->findAnimation("boss");
			_motion->start();
			_y = 500;
			//EFFECTMANAGER->play("bossPullEffect", _pX + 135, _pY  + 90);
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
		if (((getDistance(_pX, _pY, _x, _y)) < 600))
		{
			_isBossPush = true;
		}
	}
	if ((getDistance(_pX, _pY, _x, _y)) >= 600)
	{
		_eX = -100;
		_eY = -100;
		_isBossPush = false;
	}

		else if ((getDistance(_pX, _pY, _x, _y)) >= 600)
		{
			effect();
		}
	

}

void boss::attack5()
{

}

void boss::attack1_1()
{

	if (!_attack1.isAttack)
	{
		_attack1.xRandom = RND->getFromIntTo(-50, 50);
		_attack1.yRandom = RND->getFromIntTo(-50, 50);
		if (!_onceSound)
		{
			SOUNDMANAGER->play("�ն�����", 1.0f);
			_onceSound = true;
			_attack1.x = _pX + _attack1.xRandom;
		}
		if (_pY > _attack1.y + _attack1.yRandom)
		{
			SOUNDMANAGER->play("bossFallHand", 1.0f);
			_attack1.y += _attack1.speed;
			_attack1.speed += 0.9f;
			_attack1.rc = RectMakePivot(Vector2(_attack1.x, _attack1.y), Vector2(50, 50), Pivot::Center);
		}
		else
		{
			CAMERAMANAGER->shakeCamera(5, 20);
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
				_attack1.rc = RectMakePivot(Vector2(-100, -100), Vector2(50, 50), Pivot::Center);
			}
			else
			{
				_attack1.index = 0;
				_attack1.x = _pX + _attack1.xRandom;
				_attack1.speed = 8.0f;
				_attack1.isAttack = false;
				_attack1.count++;
				_onceSound = false;
				_attack1.delay = 0;

			}
		}
	}
}

void boss::attack2_1()
{
	_attack2.delay = 0;
	_attack2.aniDelayCount++;
	if (_attack2.aniDelayCount > 4)
	{
		_attack2.index--;
		_attack2.aniDelayCount = 0;
	}
	if (_attack2.index <= 0)
	{
		_attack2.index = 0;

		attack2Angle();

	}

	_attack2.x = _x - 140;
	_attack2.y = _y;
	_attack2.width = 10;
	_attack2.height = 10;
	_attack2.rc = RectMakePivot(Vector2(_attack2.x, _attack2.y), Vector2(_attack2.width, _attack2.height), Pivot::LeftTop);


	if (!_attack2.isAttack)
	{
		_attack2.angle = 360 - getAngle((_leftTop.x + _rightTop.x) / 2, (_leftTop.y + _rightTop.y) / 2, (_leftBottom.x + _rightBottom.x) / 2, (_leftBottom.y + _rightBottom.y) / 2) * 180 / PI - 90;
		_leftBottom.x += 25.f;
		_rightBottom.x += 25.f;


		if (_leftBottom.x > 3000)
		{
			_attack2.isAttack = true;
		}
	}
	if (_attack2.isAttack)
	{
		_attack2.angle = 360 - getAngle((_leftTop.x + _rightTop.x) / 2, (_leftTop.y + _rightTop.y) / 2, (_leftBottom.x + _rightBottom.x) / 2, (_leftBottom.y + _rightBottom.y) / 2) * 180 / PI - 90;
		_leftBottom.x -= 25.f;
		_rightBottom.x -= 25.f;

		if (_leftBottom.x < 300)
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
	//cout << _isRockBottom << endl;
	for (int i = 0; i < 17; ++i)
	{
		if (!_attack3Rc[i].rockFall)
		{
			setRock();
			_attack3Rc[i].rockFall = true;
			_isRockBottom = false;
		}
	}
	for (int i = 0; i < 17; ++i)
	{
		if (_attack3Rc[i].rockFall)
		{
			_attack3Rc[i].mY += 25;
			if (_attack3Rc[i].mY >= _attack3Rc[i].y)
			{
				_attackTimer++;
				if (_attackTimer < 130)
				{
					//cout << "��" << endl;
					_isRockBottom = true;
				}
				else
				{
					_attack3Rc[i].attackRc = RectMakePivot(Vector2(-100, -100), Vector2(100, 100), Pivot::Center);
					_isRockBottom = false;
				}
				_cameraShake++;
				_attack3Rc[i].mY = _attack3Rc[i].y;
			}
			if (_cameraShake > 5 && _cameraShake <= 6)
			{
				CAMERAMANAGER->shakeCamera(5, 50);
			}
			_attack3Rc[i].rc = RectMakePivot(Vector2(_attack3Rc[i].x, _attack3Rc[i].mY), Vector2(_attack3Rc[i].width, _attack3Rc[i].width), Pivot::Center);
			if (!_isPlayerHit)
			{
				_attack3Rc[i].attackRc = RectMakePivot(Vector2(_attack3Rc[i].x, _attack3Rc[i].mY), Vector2(100, 100), Pivot::Center);
			}

		}
	}
}

void boss::attack3_2()
{
	for (int i = 0; i < 13; ++i)
	{
		if (!_attack3Rc2[i].rockFall)
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
			_attack3Rc2[i].rockFall = true;
			_isRockBottom = false;
			_attack3Rc2[i].scale = 0.5f;
			_attack3Rc2[i].rockCount = 0;
			_attack3Rc2[i].attackRc = RectMakePivot(Vector2(-100, -100), Vector2(_attack3Rc2[i].width, _attack3Rc2[i].width), Pivot::Center);
		}
		if (_attack3Rc2[i].rockFall)
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


			_attack3Rc2[i].rockCount++;
			if (!_isPlayerHit)
			{
				_attack3Rc2[i].attackRc = RectMakePivot(Vector2(_attack3Rc2[i].x, _attack3Rc2[i].y), Vector2(_attack3Rc2[i].width, _attack3Rc2[i].width), Pivot::Center);
			}
			if (_attack3Rc2[i].mY >= _attack3Rc2[i].y)
			{
				_attackTimer++;
				if (_attackTimer < 100)
				{
					if (_attack3Rc[0].mY >= _attack3Rc[0].y)
					{
						_isRockBottom = true;

					}
				}
				else
				{
					_attack3Rc2[i].attackRc = RectMakePivot(Vector2(-100, -100), Vector2(_attack3Rc2[i].width, _attack3Rc2[i].width), Pivot::Center);
					_isRockBottom = false;
				}

				CAMERAMANAGER->shakeCamera(3, 2);
				_attack3Rc2[i].mY = _attack3Rc2[i].y;
				if (_attack3Rc2[i].rockCount > 150)
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
						_attack3Rc2[i].rockCount = 0;
						_patternCheck = false;
						_isRockBottom = false;
						_attack3Rc2[i].attackRc = RectMakePivot(Vector2(-100, -100), Vector2(_attack3Rc2[i].width, _attack3Rc2[i].width), Pivot::Center);

						_attack3Rc2[i].rockFall = false;

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
		effect();
		SOUNDMANAGER->play("pull", 1.0f);
		_isBossPull = true;
	}
	else
	{
		_eX = -100;
		_eY = -100;
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

	if ((angle1 > angle3 && angle2 < angle4 && _pY > _leftTop.y && _pY < _leftBottom.y) && !_isPlayerHit)
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
	for (int i = 0; i < 17; ++i)
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

		_attack3Rc[13].x = 900;
		_attack3Rc[13].y = 680;

		_attack3Rc[14].x = 2200;
		_attack3Rc[14].y = 680;

		_attack3Rc[15].x = 890;
		_attack3Rc[15].y = 600;

		_attack3Rc[16].x = 2210;
		_attack3Rc[16].y = 600;
		_attack3Rc[i].width = 160;

		_attack3Rc[i].mY = 0;

		_attack3Rc[i].rc = RectMakePivot(Vector2(_attack3Rc[i].x, _attack3Rc[i].mY), Vector2(_attack3Rc[i].width, _attack3Rc[i].width), Pivot::Center);
	}
}

bool boss::playerCol()
{
	RECT temp;
	for (int i = 0; i < 17; i++)
	{
		if (IntersectRect(&temp, &_attack3Rc[i].attackRc.GetRect(), &_pRc.GetRect()) && _isRockBottom && (abs(_attack3Rc[i].mY - _attack3Rc[i].y) < 100))
		{
			_isPlayerHit = true;
			_attack3Rc[i].attackRc = RectMakePivot(Vector2(-100, -100), Vector2(0, 0), Pivot::Center);
			//cout << "�� 1�̶� ����" << endl;
			return true;
		}
		if (IntersectRect(&temp, &_attack3Rc2[i].attackRc.GetRect(), &_pRc.GetRect()) && _isRockBottom)
		{
			_isPlayerHit = true;
			_attack3Rc2[i].attackRc = RectMakePivot(Vector2(-100, -100), Vector2(0, 0), Pivot::Center);
			//cout << "�� 2�̶� ����" << endl;
			return true;
		}
	}

	if (IntersectRect(&temp, &_attack1.rc.GetRect(), &_pRc.GetRect()) ||
		IntersectRect(&temp, &_attackRc.GetRect(), &_pRc.GetRect()) ||
		_isHandCol)
	{
		_isPlayerHit = true;
		//cout << "���̶� ����" << endl;
		_attack1.rc = RectMakePivot(Vector2(-100, -100), Vector2(0, 0), Pivot::Center);
		_attackRc = RectMakePivot(Vector2(-100, -100), Vector2(0, 0), Pivot::Center);
		return true;
	}

	return false;
}

bool boss::playerStop(RECT& rc)
{
	for (int i = 0; i < 17; i++)
	{
		if (isCollisionReaction(_attack3Rc[i].rc.GetRect(), rc))
		{
			return true;
		}
	}

	return false;
}

void boss::effect()
{
	if (_bossPattern == PLAYER_PULL)
	{
		_effectImage = ImageManager::GetInstance()->FindImage("bossTornadoEffect");
		_aniCount++;
		_eX = _pX;
		_eY = _pY;
		if (_aniCount > 2)
		{
			_index++;
			_aniCount = 0;
			if (_index >= 15)
			{
				_index = 15;
			}

		}
	}
	if (_bossPattern == EXPLOSION)
	{
		_effectImage = ImageManager::GetInstance()->FindImage("bossPullEffect");
		_aniCount++;
		_eX = _pX;
		_eY = _pY;
		if (_aniCount > 4)
		{
			_index++;
			_aniCount = 0;
			if (_index >= 11)
			{
				_index = 0;
			}

		}
	}

}
