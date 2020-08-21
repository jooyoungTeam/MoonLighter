#include "stdafx.h"
#include "display.h"

HRESULT display::init(int index, Vector2 mPos, item * mIt, int mPrice, int mCount, bool mIsActive)
{
	_index = index;
	_pos = mPos;

	_maxY = mPos.y + 10;
	_minY = mPos.y - 10;

	int tempX = _pos.x;
	if (_pos.y == 870)
	{
		_rc = RectMakePivot(Vector2(tempX, 830), Vector2(50, 50), Pivot::Center);
	}
	else
	{
		_rc = RectMakePivot(Vector2(tempX, 1000), Vector2(50, 50), Pivot::Center);
	}
	_it = mIt;
	_settingPrice = mPrice;
	_count = mCount;
	_isActive = mIsActive;

	_direction = false;

	return S_OK;
}

void display::update()
{
	_count = INVENTORY->getShowCase()[_index * 2].count;
	_it = INVENTORY->getShowCase()[_index * 2].item;
	_settingPrice = INVENTORY->getShowCase()[_index * 2].totalPrice;
	_rightPrice = INVENTORY->getShowCase()[_index * 2].originalPrice;
	_isPeople = INVENTORY->getShowCase()[_index * 2].isPeople;

	itemMove();

	if (_it != NULL)
	{
		_it->setItemPos(_pos.x, _pos.y);
		_isActive = true;
		_it->setShakeY(_pos.y);
	}
	else
	{
		_isActive = false;
	}
}

void display::render()
{
	if (_it != NULL)
		_it->cameraRender();

	if (KEYMANAGER->isToggleKey('V'))
	{
		CAMERAMANAGER->rectangle(_rc, D2D1::ColorF::Black, 1.f, 2.f);
	}
}

void display::release()
{
}

void display::itemMove()
{
	if (_pos.y < _minY)
	{
		_direction = true;
	}
	else if (_pos.y > _maxY)
	{
		_direction = false;
	}

	if (_direction)
	{
		_pos.y += 0.2f;
	}
	else
	{
		_pos.y -= 0.2f;
	}
}
