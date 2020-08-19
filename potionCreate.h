#pragma once
#include "gameNode.h"

struct tagPotionInfo
{
	Image img;
	wstring name;
	wstring discription;
	int price;

};

case ITEMTYPE::POTION_S:
	_img = ImageManager::GetInstance()->FindImage("potion_S");
	_name = L"포션(소)";
	_itemIndex = 1001;
	_limitCount = 5;
	_price = 1500;
	_fillHp = 40;
	break;

case ITEMTYPE::POTION_M:
	_img = ImageManager::GetInstance()->FindImage("potion_M");
	_name = L"포션(중)";
	_itemIndex = 1002;
	_limitCount = 5;
	_price = 2000;
	_fillHp = 60;
	break;

case ITEMTYPE::POTION_B:
	_img = ImageManager::GetInstance()->FindImage("potion_B");
	_name = L"포션(대)";
	_itemIndex = 1003;
	_limitCount = 5;
	_price = 2500;
	_fillHp = 80;
	break;

case ITEMTYPE::POTION_L:
	_img = ImageManager::GetInstance()->FindImage("potion_L");
	_name = L"포션(특대)";
	_itemIndex = 1004;
	_limitCount = 5;
	_price = 3000;
	_fillHp = 100;
	break;
class potionCreate : public gameNode
{
private:
	Image* _selectPotion;

	Vector2 _selectPt;
	Vector2 _pt[4];

	int _selectIndex;

public:
	potionCreate() {}
	~potionCreate() {}


public:
	HRESULT init();
	void update();
	void render();
	void release();

public:


};


