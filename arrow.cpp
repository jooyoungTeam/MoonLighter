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
	for (_viArrow = _vArrow.begin(); _viArrow != _vArrow.end();)
	{
		_viArrow->arrowImage->FrameRender(Vector2(_viArrow->x, _viArrow->y), 3, 1);
	}
}

void arrow::IsArrowShot(float x, float y, const char* imageName)
{
	tagArrow arrow;
	ZeroMemory(&arrow, sizeof(tagArrow));
	arrow.arrowImage = ImageManager::GetInstance()->FindImage(imageName);
	
	arrow.speed = 5.0f;
	arrow.x = arrow.shootX = x;
	arrow.y = arrow.shootY = y;

	arrow.rc = RectMakePivot(Vector2(arrow.x, arrow.y), Vector2(30, 30), Pivot::Center);
	_vArrow.push_back(arrow);
}

void arrow::arrowMove()
{
	for (_viArrow = _vArrow.begin(); _viArrow != _vArrow.end();)
	{
		_viArrow->x += cosf(_viArrow->angle) * _viArrow->speed;
		_viArrow->y += -sinf(_viArrow->angle) * _viArrow->speed;
	}

	_viArrow->rc = RectMakePivot(Vector2(_viArrow->x, _viArrow->y), Vector2(30, 30), Pivot::Center);

	if ((500 < getDistance(_viArrow->x, _viArrow->y, _viArrow->shootX, _viArrow->shootY)))
	{
		_viArrow = _vArrow.erase(_viArrow);
	}
	else ++_viArrow;
}

void arrow::playerRemoveArrow(int index)
{
	_vArrow.erase(_vArrow.begin() + index);
}
