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
	_golemDir = GOLEM_TOP;
	_angle = 0;
	_count = 0;
}



void golem::attack()
{
}

void golem::enemyMove()
{
	_count++;
	cout << _golemDir << endl;

	if (_golemDir == GOLEM_TOP || _golemDir == GOLEM_BOTTOM)
	{
		if ((_angle >= 315 && _angle < 360) || (_angle >= 0 && _angle < 45))
		{
			_golemDir = GOLEM_LEFT;
			_motion = KEYANIMANAGER->findAnimation(_index, "golemLeft");
			_motion->start();
		}
		else if (_angle >= 135 && _angle < 225)
		{
			_golemDir = GOLEM_RIGHT;
			_motion = KEYANIMANAGER->findAnimation(_index, "golemRight");
			_motion->start();
		}
	}
	else if (_golemDir == GOLEM_RIGHT || _golemDir == GOLEM_LEFT)
	{
		if (_angle >= 45 && _angle < 135)
		{
			_golemDir = GOLEM_BOTTOM;
			_motion = KEYANIMANAGER->findAnimation(_index, "golemDown");
			_motion->start();
		}
		else if (_angle >= 225 && _angle < 315)
		{
			_golemDir = GOLEM_TOP;
			_motion = KEYANIMANAGER->findAnimation(_index, "golemUp");
			_motion->start();
		}
	}
		

}
