#include "stdafx.h"
#include "boss.h"

void boss::set()
{
	_isBossAttack = _isBossAttackEnd = 0; 
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

//	_rc = RectMakePivot(Vector2(_x, _y), Vector2(100, 100), Pivot::LeftTop);
	_attack2.img = ImageManager::GetInstance()->FindImage("bossLong");
	_attack2.hole = ImageManager::GetInstance()->FindImage("bossLong2");
}

void boss::render()
{
	//_img->aniRender(Vector2(_x, _y), _motion, 1.25f);

	CAMERAMANAGER->aniRender(_img, _x + 100, _y, _motion, 2.5f);
	
	CAMERAMANAGER->fillRectangle(_rc, D2D1::ColorF::Tomato, 0.7f);
	for (int i = 0; i < 13; ++i)
	{
		CAMERAMANAGER->zOrderRender(ImageManager::GetInstance()->FindImage("Boss_Rock0"), _attack3Rc[i].rc.left, _attack3Rc[i].rc.top, _attack3Rc[i].rc.bottom, _attack3Rc[i].alpha, 1.5f);
		//CAMERAMANAGER->render(ImageManager::GetInstance()->FindImage("Boss_Rock0"), _attack3Rc[i].rc.left, _attack3Rc[i].rc.top, 1.5f, 1.f);
		CAMERAMANAGER->zOrderRender(ImageManager::GetInstance()->FindImage("Boss_Rock1"), _attack3Rc2[i].rc.left, _attack3Rc2[i].rc.top, _attack3Rc2[i].rc.bottom, _attack3Rc2[i].alpha, 1.5f);
		if (_attack3Rc2[i].rackFall)
		{
			CAMERAMANAGER->render(ImageManager::GetInstance()->FindImage("shadow"), _attack3Rc2[i].x - 65, _attack3Rc2[i].y, _attack3Rc2[i].scale, _attack3Rc2[i].alpha);

		}
	}
	CAMERAMANAGER->frameRender(_attack1.img, _attack1.x, _attack1.y, _attack1.index, 0);
	_attack1.img->SetScale(2.5f);
//	CAMERAMANAGER->frameRender(_attack2.img, _attack2.x, _attack2.y, _attack2.index, 0);
	CAMERAMANAGER->zOrderFrameRender(_attack2.img, _attack2.x, _attack2.y, _leftBottom.y + 300, _attack2.index,0, 2.5f, 1.0f);
	_attack2.img->SetAngle(_attack2.angle);

	//CAMERAMANAGER->line(_leftTop, _rightTop, D2D1::ColorF::Black, 2.0f);
	//CAMERAMANAGER->line(_rightTop, _rightBottom, D2D1::ColorF::Black, 2.0f);
	//CAMERAMANAGER->line(_rightBottom, _leftBottom, D2D1::ColorF::Black, 2.0f);
	//CAMERAMANAGER->line(_leftBottom, _leftTop, D2D1::ColorF::Black, 2.0f);
	
	CAMERAMANAGER->fillRectangle(_bar.back, D2D1::ColorF::DimGray, _barAlpha);
	CAMERAMANAGER->fillRectangle(_bar.middle, D2D1::ColorF::LightSalmon, _barAlpha);
	CAMERAMANAGER->fillRectangle(_bar.front, D2D1::ColorF::Tomato, _barAlpha);

	//D2DRenderer::GetInstance()->FillRectangle(_attack2.rc, D2D1::ColorF::Black, 0.7f);
}

void boss::attack()
{
	cout << _attack3.delay << endl;
	if (!_patternCheck)
	{
		_patternRandom = RND->getFromIntTo(0,2);
		if (_patternRandom == 0)
		{
			_bossPattern = ATTACK1;
		}
		if (_patternRandom == 1)
		{
			_bossPattern = ATTACK2;
		}
		_patternCheck = true;
	}
	if (_bossPattern == ATTACK1)
	{
		attack1();
	}
	if (_bossPattern == ATTACK2)
	{
		if (!_patternCheck2)
		{
			_patternRandom2 = RND->getFromIntTo(0, 2);
			if (_patternRandom2 == 0)
			{
				_bossPattern3 = PATTERN1;
			}
			if (_patternRandom2 == 1)
			{
				_bossPattern3 = PATTERN2;
			}
			_patternCheck2 = true;
		}
		if (!_attack3.isBottom)
		{

			attack3();
		}
		else
		{
			attack2();
			attack2Angle();
		}
	}
	//if (_bossPattern == ATTACK3)
	//{

	//}
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
		//cout << _isBossAttackEnd << endl;
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
			cout << "dddd" << endl;
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
			//cout << "emdmd" << endl;
			_motion = KEYANIMANAGER->findAnimation(_index, "boss");
			_img = ImageManager::GetInstance()->FindImage("boss");
			_motion->start();
			_isBossAttackEnd = false;
			_state = _idle;
			_isHit = false;
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
			_motion = KEYANIMANAGER->findAnimation(_index, "boss");
			_img = ImageManager::GetInstance()->FindImage("boss");
			_motion->start();
			_state = _idle;
			_patternCheck2 = false;
			_patternCheck = false;
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
			//_attack2.count = 0;
		}
	}
	if (_isBossAttack && _onceAni)
	{
		_attack2.aniDelayCount++;
		attack2_1();
		if (_attack2.count > 3)
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
			_attack1.isBottom = true;
		}
	}
	if (_attack1.isBottom)
	{
		//cout << "dd" << endl;
		for (int i = 0; i < 13; i++)
		{
				_attack3Rc[i].alpha -= 0.05f;
			_attack2.count = 0;

			if (_attack3Rc[i].alpha <= 0)
			{
				//cout << "dddd" << endl;
				setRock();
				_attack1.isBottom = false;
				_state = _idle;
				_attackDelay = 0;
				_patternCheck2 = false;
				_patternCheck = false; 
				_isBossAttackEnd = false;
				_isAttack = false;
				_attack3.isBottom = false;
				_cameraShake = 0;
			}
		}
	}
	
}

void boss::attack3()
{
	if (!_isAttack)
	{
		_img = ImageManager::GetInstance()->FindImage("bossHandFly");
		_motion = KEYANIMANAGER->findAnimation(_index, "bossAttack11");
		_motion->start();
		_isAttack = true;
		_onceAni = false;
		_isBossAttackEnd = true;
	}
	if (!KEYANIMANAGER->findAnimation(_index, "bossAttack11")->isPlay() && _isBossAttackEnd)
	{
		_motion = KEYANIMANAGER->findAnimation(_index, "bossAttack22");
		_motion->start();
		_onceAni = true;
		_isBossAttackEnd = false;
	}
	if (_onceAni)
	{
		if (!KEYANIMANAGER->findAnimation(_index, "bossAttack22")->isPlay())
		{
			//cout << "ต้0" << endl;
			_img = ImageManager::GetInstance()->FindImage("boss");
			_motion = KEYANIMANAGER->findAnimation(_index, "boss");
			_motion->start();
			_onceAni = false;
			_attackDelay = 0;
		}
	}
	if (!_onceAni && !_isBossAttackEnd && _isAttack)
	{
		if (_bossPattern3 == PATTERN1)
		{
			attack3_1(); 
			_attack3.delay++;
			if (_attack3.delay > 300)
			{
				_isAttack = false;
				_attack3.delay = 0;
				_attack3.isBottom = true;
			}
		}
		if (_bossPattern3 == PATTERN2)
		{
			attack3_2();
			//_attack3.delay++;

			//if (_attack3.delay > 120)
			//{
				/*_isAttack = false;
				_attack3.delay = 0;
				_state = _idle;
				_attackDelay = 0;
				_patternCheck2 = false;
				_patternCheck = false;
				for (int i = 0; i < 13; ++i)
				{
					_attack3Rc2[i].rackFall = false;
				}*/
			//}
		
		}

	}
}

void boss::attack4()
{


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
		_attack2.angle = 360 - getAngle((_leftTop.x + _rightTop.x) / 2, (_leftTop.y + _rightTop.y) / 2, (_leftBottom.x + _rightBottom.x) / 2, (_leftBottom.y + _rightBottom.y) / 2) * 180 / PI - 90;
		//_attack2.angle--;
		_leftBottom.x+=14.5;
		_rightBottom.x+=14.5;
		//_leftTop.x+=0.5;
		//_rightTop.x+=0.5;

		if (_leftBottom.x > 2000)
		{
			_attack2.isBottom = true;
		}
		/*if (_attack2.angle <= -60.f)
		{
			_attack2.isBottom = true;
		}*/
	}
	if (_attack2.isBottom)
	{
		_attack2.angle = 360 - getAngle((_leftTop.x + _rightTop.x) / 2, (_leftTop.y + _rightTop.y) / 2, (_leftBottom.x + _rightBottom.x) / 2, (_leftBottom.y + _rightBottom.y) / 2) * 180 / PI - 90;
		//_attack2.angle++;
		_leftBottom.x -= 14.5;
		_rightBottom.x -= 14.5;
		//_leftTop.x -= 0.5;
		//_rightTop.x-=0.5;
		
		/*if (_attack2.angle >= 40.f)
		{
			_attack2.isBottom = false;
			_attack2.count++;
		}*/

		if (_leftBottom.x < 846)
		{
			
			_attack2.isBottom = false;
			_attack2.count++;
		}
		
	}
	if (_attack2.count > 3)
	{
		//cout << "dd" << endl;
		_attack2.aniDelayCount++;
		if (_attack2.aniDelayCount > 4)
		{
			_attack2.index++;
			_attack2.aniDelayCount = 0;
		}
		if (_attack2.index >= 5)
		{
			_attack2.index = 5;
			_isBossAttackEnd = true;
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
		}
	}
	for (int i = 0; i < 13; ++i)
	{
		if (_attack3Rc[i].rackFall)
		{
			_attack3Rc[i].mY += 25;
			if (_attack3Rc[i].mY >= _attack3Rc[i].y)
			{
				_cameraShake++;
				_attack3Rc[i].mY = _attack3Rc[i].y;
			}
			if (_cameraShake > 5 && _cameraShake <= 6 )
			{
				//cout << "dd" << endl;
				 CAMERAMANAGER->shakeCamera(5, 50);
			}
			if (!_cameraShake)
			{
			//	cout << "ee" << endl;
			}
			_attack3Rc[i].rc = RectMakePivot(Vector2(_attack3Rc[i].x, _attack3Rc[i].mY), Vector2(_attack3Rc[i].width, _attack3Rc[i].width), Pivot::Center);

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
			_attack3Rc2[i].mX = 0 - _attack3Rc2[i].x;
			_attack3Rc2[i].mY = 0 - _attack3Rc2[i].y;
			_attack3Rc2[i].alpha = 1;
			_attack3Rc2[i].rackFall = true;
			_attack3Rc2[i].scale = 0.5f;
			_attack3Rc2[i].attackCount++;
			_attack3Rc2[i].rackCount = 0;

			//_attack3Rc2[i].rc = RectMakePivot(Vector2(_attack3Rc2[i].mX, _attack3Rc2[i].mY), Vector2(_attack3Rc[i].width, _attack3Rc[i].width), Pivot::Center);
		}
		if (_attack3Rc2[i].rackFall)
		{
			if (getDistance(_attack3Rc[i].mX, _attack3Rc[i].mY, _attack3Rc[i].x, _attack3Rc[i].y) < 200)
			{
				_attack3Rc2[i].scale += 0.015f;
				if (_attack3Rc2[i].scale >= 1.4f)
				{
					_attack3Rc2[i].scale = 1.4f;
				}
			}
			_attack3Rc2[i].mX = _attack3Rc2[i].x;

			if (_attack3Rc2[i].attackCount < 4)
			{

				_attack3Rc2[i].mY += 30;
			}
			
			_attack3Rc2[i].rackCount++;
			//cout << _attack3Rc2[i].rackCount << endl;
			if (_attack3Rc2[i].mY >= _attack3Rc2[i].y)
			{
				CAMERAMANAGER->shakeCamera(3, 2);
				_attack3Rc2[i].mY = _attack3Rc2[i].y;
				if (_attack3Rc2[i].rackCount > 100)
				{
					_attack3Rc2[i].alpha -= 0.05f;
					if (_attack3Rc2[i].alpha <= 0)
					{
						_attack3Rc2[i].alpha = 0;
						_isAttack = false;
						_attack3.delay = 0;
						_state = _idle;
						_attackDelay = 0;
						_patternCheck2 = false;
						_patternCheck = false;

						_attack3Rc2[i].rackFall = false;
						
					}
				}

			}
		}
		_attack3Rc2[i].rc = RectMakePivot(Vector2(_attack3Rc2[i].mX, _attack3Rc2[i].mY), Vector2(_attack3Rc2[i].width, _attack3Rc2[i].width), Pivot::Center);
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
