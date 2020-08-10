#include "stdafx.h"
#include "item.h"

HRESULT item::init(ITEMTYPE type, float x, float y)
{
	ImageManager::GetInstance()->AddImage("slime_red", L"image/item/slime_jelly.png");
	ImageManager::GetInstance()->AddImage("slime_blue", L"image/item/slime_jelly_blue.png");
	ImageManager::GetInstance()->AddImage("slime_yellow", L"image/item/slime_jelly_yellow.png");

	_type = type;
	_x = x;
	_y = y;

	sort();

	_rc = RectMakePivot(Vector2(_x, _y), Vector2(50, 50), Pivot::Center);

	return S_OK;
}

void item::release()
{
}

void item::update()
{
}

void item::render()
{

}

void item::sort()
{
	if (_type == ITEMTYPE::SLIME_RED)
	{
		_img = ImageManager::GetInstance()->FindImage("slime_red");
		_itemIndex = 1001;
	}

	if (_type == ITEMTYPE::SLIME_BLUE)
	{
		_img = ImageManager::GetInstance()->FindImage("slime_blue");
		_itemIndex = 1002;
	}

	if (_type == ITEMTYPE::SLIME_YELLOW)
	{
		_img = ImageManager::GetInstance()->FindImage("slime_yellow");
		_itemIndex = 1003;
	}
}
