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
	//D2DRenderer::GetInstance()->DrawRectangle(_rc, D2DRenderer::DefaultBrush::Yellow, 1.f);
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
	//cout << "µé¾î¿È" << endl;

		switch (_golemDir)
		{
		case GOLEM_LEFT:
			_attackDelay = 0;
			_motion = KEYANIMANAGER->findAnimation(_index, "golemLeftAttack");
			_img = ImageManager::GetInstance()->FindImage("golemAttack");
			_motion->start();
			break;
		case GOLEM_RIGHT:
			_attackDelay = 0;
			_motion = KEYANIMANAGER->findAnimation(_index, "golemRightAttack");
			_img = ImageManager::GetInstance()->FindImage("golemAttack");
			_motion->start();
			break;
		case GOLEM_TOP:
			_attackDelay = 0;
			_motion = KEYANIMANAGER->findAnimation(_index, "golemUpAttack");
			_img = ImageManager::GetInstance()->FindImage("golemAttack");
			_motion->start();
			break;
		case GOLEM_BOTTOM:
			_attackDelay = 0;
			_motion = KEYANIMANAGER->findAnimation(_index, "golemDownAttack");
			_img = ImageManager::GetInstance()->FindImage("golemAttack");
			_motion->start();
			break;
		}
		_isAttack = true;
		_state = _attack;

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
