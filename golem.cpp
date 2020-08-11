#include "stdafx.h"
#include "golem.h"

golem::golem()
{
}

golem::~golem()
{
}


void golem::render()
{
	_aStar->render();
	_img->aniRender(Vector2(_x, _y), _motion, 1.18f);
	_backBar->Render(Vector2(_bar.rc.left, _bar.rc.top));
	_middleBar->Render(Vector2(_bar.rc.left, _bar.rc.top));
	_middleBar->SetSize(Vector2(_saveHP, _backBar->GetHeight()));
	_frontBar->Render(Vector2(_bar.rc.left, _bar.rc.top));
	_frontBar->SetSize(Vector2(_bar.width, _backBar->GetHeight()));
	D2DRenderer::GetInstance()->DrawRectangle(_bar.rc, D2DRenderer::DefaultBrush::Yellow, 1.0f);
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
			_motion = KEYANIMANAGER->findAnimation(_index, "golemLeftAttack");
			_img = ImageManager::GetInstance()->FindImage("golemAttack");
			_motion->start();
			_attackRc = RectMakePivot(Vector2(_x - 70, _y + 20), Vector2(_width + 10, _height - 60), Pivot::Center);
			break;
		case GOLEM_RIGHT:
			_attackDelay = 0;
			_motion = KEYANIMANAGER->findAnimation(_index, "golemRightAttack");
			_img = ImageManager::GetInstance()->FindImage("golemAttack");
			_motion->start();
			_attackRc = RectMakePivot(Vector2(_x + 70, _y + 20), Vector2(_width + 10, _height - 60), Pivot::Center);
			break;
		case GOLEM_TOP:
			_attackDelay = 0;
			_motion = KEYANIMANAGER->findAnimation(_index, "golemUpAttack");
			_img = ImageManager::GetInstance()->FindImage("golemAttack");
			_motion->start();
			_attackRc = RectMakePivot(Vector2(_x, _y - 60), Vector2(_width - 30, _height - 30), Pivot::Center);
			break;
		case GOLEM_BOTTOM:
			_attackDelay = 0;
			_motion = KEYANIMANAGER->findAnimation(_index, "golemDownAttack");
			_img = ImageManager::GetInstance()->FindImage("golemAttack");
			_motion->start();
			_attackRc = RectMakePivot(Vector2(_x, _y + 80), Vector2(_width - 30, _height - 30), Pivot::Center);
			break;
		}
		_isAttack = true;
		_state = _attack;

		RECT temp;
		if (IntersectRect(&temp, &_pRc.GetRect(), &_attackRc.GetRect()))
		{
			_attackRc = RectMakePivot(Vector2(0,0), Vector2(0,0), Pivot::Center);
		}
	}
	
}

void golem::enemyMove()
{

	if ((_angle >= 315 && _angle < 360) || (_angle >= 0 && _angle < 45))
	{
		_golemDir = GOLEM_LEFT;
		_motion = KEYANIMANAGER->findAnimation(_index, "golemLeft");
		_img = ImageManager::GetInstance()->FindImage("golem");
		_motion->start();
	}
	else if (_angle >= 135 && _angle < 225)
	{
		_golemDir = GOLEM_RIGHT;
		_motion = KEYANIMANAGER->findAnimation(_index, "golemRight");
		_img = ImageManager::GetInstance()->FindImage("golem");
		_motion->start();
	}

	if (_angle >= 45 && _angle < 135)
	{
		_golemDir = GOLEM_BOTTOM;
		_motion = KEYANIMANAGER->findAnimation(_index, "golemDown");
		_img = ImageManager::GetInstance()->FindImage("golem");
		_motion->start();
	}
	else if (_angle >= 225 && _angle < 315)
	{
		_golemDir = GOLEM_TOP;
		_motion = KEYANIMANAGER->findAnimation(_index, "golemUp");
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
			_motion = KEYANIMANAGER->findAnimation(_index, "golemLeft");
			_img = ImageManager::GetInstance()->FindImage("golem");
			_motion->start();
			break;
		case GOLEM_RIGHT:
			_motion = KEYANIMANAGER->findAnimation(_index, "golemRight");
			_img = ImageManager::GetInstance()->FindImage("golem");
			_motion->start();
			break;
		case GOLEM_TOP:
			_motion = KEYANIMANAGER->findAnimation(_index, "golemUp");
			_img = ImageManager::GetInstance()->FindImage("golem");
			_motion->start();
			break;
		case GOLEM_BOTTOM:
			_motion = KEYANIMANAGER->findAnimation(_index, "golemDown");
			_img = ImageManager::GetInstance()->FindImage("golem");
			_motion->start();
			break;
		}
	}
}

void golem::dead()
{
	if (_onceAni)
	{
		_img = ImageManager::GetInstance()->FindImage("redSlimeDead");
		_motion = KEYANIMANAGER->findAnimation(_index, "redSlimeDead");
		_motion->start();
		_onceAni = false;
	}
	if (!KEYANIMANAGER->findAnimation(_index, "redSlimeDead")->isPlay())
	{
		_realDead = true;
	}
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
