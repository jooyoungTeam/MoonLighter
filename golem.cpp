#include "stdafx.h"
#include "golem.h"

golem::golem()
{
}

golem::~golem()
{
}

void golem::set()
{
	_golemDir = GOLEM_BOTTOM;
}



void golem::attack()
{
}

void golem::enemyMove()
{
	
	if (_x < _pX)
	{
		if (_y - 50 < _pX)
		{
			_golemDir = GOLEM_BOTTOM; 
		}
		else if (_y + 50 > _pX)
		{
			_golemDir = GOLEM_TOP;
		}
		else
		{
			_golemDir = GOLEM_RIGHT;
		}
	}
	if (_x >= _pX)
	{
		if (_y - 50 < _pX)
		{
			_golemDir = GOLEM_BOTTOM;
		}
		else if (_y + 50 > _pX)
		{
			_golemDir = GOLEM_TOP;
		}
		else
		{
			_golemDir = GOLEM_LEFT;
		}
	}

	switch (_golemDir)
	{
	case GOLEM_LEFT:
		_motion = KEYANIMANAGER->findAnimation(_index, "golemLeft");

		break;
	case GOLEM_RIGHT:
		_motion = KEYANIMANAGER->findAnimation(_index, "golemRight");

		break;
	case GOLEM_TOP:
		_motion = KEYANIMANAGER->findAnimation(_index, "golemUp");

		break;
	case GOLEM_BOTTOM:
		_motion = KEYANIMANAGER->findAnimation(_index, "golemDown");

		break;
	}
	


}
