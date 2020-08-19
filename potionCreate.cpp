#include "stdafx.h"
#include "potionCreate.h"

HRESULT potionCreate::init()
{
	ImageManager::GetInstance()->AddImage("potion_shop_bg", L"Image/potionShop/potion_shop_background.png");
	ImageManager::GetInstance()->AddImage("alphaBlack", L"Image/UI/alphaBlack.png");
	_selectPotion = ImageManager::GetInstance()->AddImage("select_potion", L"Image/potionShop/select_potion.png");

	_selectIndex = 0;


	_selectPt = _pt[0] = Vector2(585, 259);
	_pt[1] = Vector2(695, 259);
	_pt[2] = Vector2(806, 259);
	_pt[3] = Vector2(916, 259);

	return S_OK;
}

void potionCreate::update()
{
	_selectPt = _pt[_selectIndex];
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		_selectIndex--;
		if (_selectIndex == -1)
			_selectIndex = 3;
	}

	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		_selectIndex++;
		if (_selectIndex == 4)
			_selectIndex = 0;
	}

}

void potionCreate::render()
{
	ImageManager::GetInstance()->FindImage("alphaBlack")->Render(Vector2(0, 0));
	ImageManager::GetInstance()->FindImage("potion_shop_bg")->Render(Vector2(0,0));
	_selectPotion->Render(_selectPt);
}

void potionCreate::release()
{

}
