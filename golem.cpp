#include "stdafx.h"
#include "golem.h"


void golem::render()
{
	_aStar->render();
	CAMERAMANAGER->render(_shadow, _shadowRc.left, _shadowRc.top, 0.4f);
	CAMERAMANAGER->zOrderAniRender(_img, _x, _y, _z, _motion, 1.5f);
	CAMERAMANAGER->fillRectangle(_bar.back, D2D1::ColorF::DimGray, _barAlpha);
	CAMERAMANAGER->fillRectangle(_bar.middle, D2D1::ColorF::LightSalmon, _barAlpha);
	CAMERAMANAGER->fillRectangle(_bar.front, D2D1::ColorF::Tomato, _barAlpha);
	CAMERAMANAGER->fillRectangle(_attackRc, D2D1::ColorF::Tomato, 1.0f);
	D2DRenderer::GetInstance()->FillRectangle(_bar.back, D2D1::ColorF::DimGray, _barAlpha);
	D2DRenderer::GetInstance()->FillRectangle(_bar.middle, D2D1::ColorF::LightSalmon, _barAlpha);
	D2DRenderer::GetInstance()->FillRectangle(_bar.front, D2D1::ColorF::Tomato, _barAlpha);
}

void golem::set()
{
	_golemDir = GOLEM_BOTTOM;
	_oldDir = GOLEM_BOTTOM;
	_angle = 0;
	_count = 0;
}



void golem::attack()
{
	
	if (!_isAttack)
	{
		switch (_golemDir)
		{
		case GOLEM_LEFT:
			_attackDelay = 0;
			_motion->stop();
			_motion = KEYANIMANAGER->findAnimation( "golemLeftAttack");
			_img = ImageManager::GetInstance()->FindImage("golemAttack");
			_motion->start();
			_attackRc = RectMakePivot(Vector2(_x - 70, _y + 20), Vector2(_width + 10, _height - 60), Pivot::Center);
			break;
		case GOLEM_RIGHT:
			_attackDelay = 0;
			_motion->stop();
			_motion = KEYANIMANAGER->findAnimation( "golemRightAttack");
			_img = ImageManager::GetInstance()->FindImage("golemAttack");
			_motion->start();
			_attackRc = RectMakePivot(Vector2(_x + 70, _y + 20), Vector2(_width + 10, _height - 60), Pivot::Center);
			break;
		case GOLEM_TOP:
			_attackDelay = 0;
			_motion->stop();
			_motion = KEYANIMANAGER->findAnimation( "golemUpAttack");
			_img = ImageManager::GetInstance()->FindImage("golemAttack");
			_motion->start();
			_attackRc = RectMakePivot(Vector2(_x, _y - 60), Vector2(_width - 30, _height - 30), Pivot::Center);
			break;
		case GOLEM_BOTTOM:
			_attackDelay = 0;
			_motion->stop();
			_motion = KEYANIMANAGER->findAnimation( "golemDownAttack");
			_img = ImageManager::GetInstance()->FindImage("golemAttack");
			_motion->start();
			_attackRc = RectMakePivot(Vector2(_x, _y + 80), Vector2(_width - 30, _height - 30), Pivot::Center);
			break;
		}
		_isAttack = true;
		_state = _attack;

		RECT temp;
		/*if (IntersectRect(&temp, &_pRc.GetRect(), &_attackRc.GetRect()))
		{
			_attackRc = RectMakePivot(Vector2(0,0), Vector2(0,0), Pivot::Center);
		}*/
	}
	
}

void golem::enemyMove()
{

	if ((_angle >= 315 && _angle < 360) || (_angle >= 0 && _angle < 45))
	{
		_golemDir = GOLEM_LEFT;
		_motion->stop();
		_motion = KEYANIMANAGER->findAnimation( "golemLeft");
		_img = ImageManager::GetInstance()->FindImage("golem");
		_motion->start();
	}
	else if (_angle >= 135 && _angle < 225)
	{
		_golemDir = GOLEM_RIGHT;
		_motion->stop();
		_motion = KEYANIMANAGER->findAnimation( "golemRight");
		_img = ImageManager::GetInstance()->FindImage("golem");
		_motion->start();
	}

	if (_angle >= 45 && _angle < 135)
	{
		_golemDir = GOLEM_BOTTOM;
		_motion->stop();
		_motion = KEYANIMANAGER->findAnimation( "golemDown");
		_img = ImageManager::GetInstance()->FindImage("golem");
		_motion->start();
	}
	else if (_angle >= 225 && _angle < 315)
	{
		_golemDir = GOLEM_TOP;
		_motion->stop();
		_motion = KEYANIMANAGER->findAnimation( "golemUp");
		_img = ImageManager::GetInstance()->FindImage("golem");
		_motion->start();
	}



}

void golem::direcitonChange()
{
	if (_oldDir != _golemDir)
	{
		_oldDir = _golemDir;

		switch (_golemDir)
		{
		case GOLEM_LEFT:
			_motion->stop();
			_motion = KEYANIMANAGER->findAnimation( "golemLeft");
			_img = ImageManager::GetInstance()->FindImage("golem");
			_motion->start();
			break;
		case GOLEM_RIGHT:
			_motion->stop();
			_motion = KEYANIMANAGER->findAnimation( "golemRight");
			_img = ImageManager::GetInstance()->FindImage("golem");
			_motion->start();
			break;
		case GOLEM_TOP:
			_motion->stop();
			_motion = KEYANIMANAGER->findAnimation( "golemUp");
			_img = ImageManager::GetInstance()->FindImage("golem");
			_motion->start();
			break;
		case GOLEM_BOTTOM:
			_motion->stop();
			_motion = KEYANIMANAGER->findAnimation( "golemDown");
			_img = ImageManager::GetInstance()->FindImage("golem");
			_motion->start();
			break;
		}
	}
}

void golem::dead()
{
	_golemCount++;
	if (_onceAni)
	{
		_img = ImageManager::GetInstance()->FindImage("golemRed");
		//_motion = KEYANIMANAGER->findAnimation( "golemRed");
		_onceAni = false;
	}
	hitMove();
	if (_golemCount > 20)
	{
		_realDead = true; 
		_golemCount = 0;
	}
	
}

void golem::enemyHit()
{
	if (_state == _idle)
	{
		_img = ImageManager::GetInstance()->FindImage("golemRed");
		_hitCount++;
		if (_hitCount > 10 && _hitCount <= 20)
		{
			_img = ImageManager::GetInstance()->FindImage("golemWhite");
		}
		if (_hitCount > 20 && _hitCount <= 30)
		{
			_isHit = false;
			_img = ImageManager::GetInstance()->FindImage("golem");
		}

	}
	if (_state == _attack)
	{
		_img = ImageManager::GetInstance()->FindImage("golemAttackRed");
		_hitCount++;
		if (_hitCount > 5 && _hitCount <= 10)
		{
			_img = ImageManager::GetInstance()->FindImage("golemAttackWhite");
		}
		if (_hitCount > 10 && _hitCount <= 15)
		{
			_img = ImageManager::GetInstance()->FindImage("golemAttackRed");
			_isHit = false;
			_img = ImageManager::GetInstance()->FindImage("golemAttack");
		}

	}

}

void golem::setShadow()
{
	_shadowX = _x - 10;
	_shadowY = _y + _width / 2;
	_shadowRc = RectMakePivot(Vector2(_shadowX, _shadowY), Vector2(_width - 10, 20.f), Pivot::Center);

}

void golem::directionCheck()
{
	if ((_angle >= 315 && _angle < 360) || (_angle >= 0 && _angle < 45))
	{
		_golemDir = GOLEM_LEFT;
	}
	else if (_angle >= 135 && _angle < 225)
	{
		_golemDir = GOLEM_RIGHT;
	}
	if (_angle >= 45 && _angle < 135)
	{
		_golemDir = GOLEM_BOTTOM;
	}
	else if (_angle >= 225 && _angle < 315)
	{
		_golemDir = GOLEM_TOP;
	}
	direcitonChange();
}
