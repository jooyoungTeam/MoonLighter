#include "stdafx.h"
#include "arrow.h"

arrow::arrow()
{
}

arrow::~arrow()
{
}

HRESULT arrow::init()
{
	return S_OK;
}

void arrow::release()
{
}

void arrow::update()
{
	arrowMove();
}

void arrow::render()
{
	for (int i= 0; i < _vArrow.size(); i++)
	{
		switch (_vArrow[i].arrowDirection)
		{
		case ARROWDIRECTION::UP:
			_vArrow[i].arrowImage->SetAngle(270);
			break;
		case ARROWDIRECTION::DOWN:
			_vArrow[i].arrowImage->SetAngle(90);
			break;
		case ARROWDIRECTION::LEFT:
			_vArrow[i].arrowImage->SetAngle(180);
			break;
		}
		_vArrow[i].arrowImage->FrameRender(Vector2(_vArrow[i].x, _vArrow[i].y), 0, 0);

		if (KEYMANAGER->isToggleKey('V'))
		{
			CAMERAMANAGER->rectangle(_vArrow[i].rc, D2D1::ColorF::Red, 1.0f);
		}
	}
}

void arrow::IsArrowShot(float x, float y, ARROWDIRECTION arrowDirection)
{
	tagArrow arrow;
	ZeroMemory(&arrow, sizeof(tagArrow));

	arrow.arrowImage = ImageManager::GetInstance()->FindImage("playerArrow");
	
	arrow.speed = 5.0f;
	arrow.x = arrow.shootX = x;
	arrow.y = arrow.shootY = y;

	arrow.arrowDirection = arrowDirection;

	arrow.rc = RectMakePivot(Vector2(arrow.x, arrow.y), Vector2(30, 30), Pivot::Center);
	_vArrow.push_back(arrow);
}

void arrow::arrowMove()
{
	for (_viArrow = _vArrow.begin(); _viArrow != _vArrow.end();)
	{
		_viArrow->angle = PI;

		switch (_viArrow->arrowDirection)
		{
		case ARROWDIRECTION::UP:
			_viArrow->x += cosf(_viArrow->angle / 2) * _viArrow->speed;
			_viArrow->y += -sinf(_viArrow->angle / 2) * _viArrow->speed;
			break;

		case ARROWDIRECTION::DOWN:
			_viArrow->x += cosf(_viArrow->angle * 1.5) * _viArrow->speed;
			_viArrow->y += -sinf(_viArrow->angle * 1.5) * _viArrow->speed;
			break;

		case ARROWDIRECTION::LEFT:
			_viArrow->x += cosf(_viArrow->angle) * _viArrow->speed;
			_viArrow->y += -sinf(_viArrow->angle) * _viArrow->speed;
			break;

		case ARROWDIRECTION::RIGHT:
			_viArrow->x += cosf(_viArrow->angle * 2) * _viArrow->speed;
			_viArrow->y += -sinf(_viArrow->angle * 2) * _viArrow->speed;
			break;
		}

		_viArrow->rc = RectMakePivot(Vector2(_viArrow->x, _viArrow->y), Vector2(30, 30), Pivot::Center);

		if ((300 < getDistance(_viArrow->x, _viArrow->y, _viArrow->shootX, _viArrow->shootY)))
		{
			_viArrow = _vArrow.erase(_viArrow);
		}
		else ++_viArrow;
	}
}

void arrow::playerRemoveArrow(int index)
{
	_vArrow.erase(_vArrow.begin() + index);
}
