#include "stdafx.h"
#include "item.h"

HRESULT item::init(ITEMBUNDLE bundle, float x, float y, float endX, float endY, int count)
{
	_bundle = bundle;
	_x = x;
	_y = y;
	_endX = endX;
	_endY = endY;

	_jumpPower = 3;
	_gravity = 0.2;

	_shake = 0;
	_isShake = false;
	_isDrop = true;

	setBundle(count);
	category();

	_rc = RectMakePivot(Vector2(_x, _y), Vector2(30, 30), Pivot::Center);

	return S_OK;
}

HRESULT item::init(ITEMTYPE type, float x, float y, float endX, float endY)
{
	_type = type;
	_x = x;
	_y = y;
	_endX = endX;
	_endY = endY;

	_jumpPower = 3;
	_gravity = 0.2;

	_shake = 0;
	_isShake = false;
	_isDrop = true;

	category();

	_rc = RectMakePivot(Vector2(_x, _y), Vector2(30, 30), Pivot::Center);

	return S_OK;
}

HRESULT item::init(ITEMTYPE type)
{
	_type = type;
	_shake = 0;
	_isShake = false;
	_isDrop = false;

	category();
	return S_OK;
}

HRESULT item::init(int itemIndex)
{
	switch (itemIndex)
	{
	case 1001:
		_type = ITEMTYPE::POTION_S;
		break;

	case 1002:
		_type = ITEMTYPE::POTION_M;
		break;

	case 1003:
		_type = ITEMTYPE::POTION_B;
		break;

	case 1004:
		_type = ITEMTYPE::POTION_L;
		break;
	}

	_shake = 0;
	_isShake = false;
	_isDrop = false;
	category();
	return S_OK;
}

void item::render()
{
	_img->Render(Vector2(_rc.left, _rc.top));
}

void item::cameraRender()
{
	CAMERAMANAGER->zOrderRender(_img, _rc.left, _rc.top, _rc.bottom,1.0f, 1.f);
}

void item::update()
{
	_rc = RectMakePivot(Vector2(_x, _y), Vector2(30, 30), Pivot::Center);
	pop();
}

void item::fieldUpdate()
{
	if (_y > _shakeMaxY)
	{
		_isShake = false;
		_shake = 0;
	}

	if (_y < _shakeMinY)
	{
		_isShake = true;
	}

	if (_isShake)
	{
		_shake += 0.01f;
	}
	else
	{
		_shake -= 0.01f;
	}

	_y += _shake;

	//_rc = RectMakePivot(Vector2(_x, _y), Vector2(30, 30), Pivot::Center);
}

void item::pop()
{
	if (_isDrop)
	{
		if (_endX > _x)
		{
			_x += 2;
		}

		if (_endX < _x)
		{
			_x -= 2;
		}
	}	

	if (_y >= _endY)
	{	
		_isDrop = false;
	}

	if (_isDrop)
	{
		_y -= _jumpPower;
		_jumpPower -= _gravity;
	}

	if (!_isDrop)
	{
		_jumpPower = 0;
		_gravity = 0;
	}
}

void item::follow(FloatRect rc)
{
	float distance = getDistance(_x, _y, rc.GetCenter().x, rc.GetCenter().y);
	float angle = getAngle(_x, _y, rc.GetCenter().x, rc.GetCenter().y);

	if (distance <= 150)
	{
		_x += cosf(angle) * 1;
		_y -= sinf(angle) * 1;
	}
}

void item::release()
{
	
}

void item::category()
{
	//Index ¹øÈ£ 100´ë ½½¶óÀÓ(10°³ ¹­À½, ¹°¾à Àç·á)
	//Index ¹øÈ£ 200´ë Àç·á (10°³ ¹­À½, ´ëÀåÀåÀÌ Àç·á)
	//Index ¹øÈ£ 300´ë Àç·á (5°³ ¹­À½, ´ëÀåÀåÀÌ Àç·á)
	//Index ¹øÈ£ 900´ë º¸½º ¾ÆÀÌÅÛ (1°³ ¹­À½)
	//Index ¹øÈ£ 1000´ë ¹°¾à (5°³ ¹­À½, ¼Òºñ ¾ÆÀÌÅÛ)


	switch (_type)
	{
	case ITEMTYPE::SLIME_RED:
		_img = ImageManager::GetInstance()->FindImage("slime_red");
		_name = L"Ç³ºÎÇÑ Á©¸®(»¡°­)";
		_itemIndex = 101;
		_limitCount = 10;
		_price = 600;
		break;

	case ITEMTYPE::SLIME_BLUE:
		_img = ImageManager::GetInstance()->FindImage("slime_blue");
		_name = L"Ç³ºÎÇÑ Á©¸®(ÆÄ¶û)";
		_itemIndex = 102;
		_limitCount = 10;
		_price = 600;
		break;

	case ITEMTYPE::SLIME_YELLOW:
		_img = ImageManager::GetInstance()->FindImage("slime_yellow");
		_name = L"Ç³ºÎÇÑ Á©¸®(³ë¶û)";
		_itemIndex = 103;
		_limitCount = 10;
		_price = 600;
		break;

	case ITEMTYPE::FABRIC:
		_img = ImageManager::GetInstance()->FindImage("fabric");
		_name = L"Ãµ";
		_itemIndex = 201;
		_limitCount = 10;
		_price = 3000;
		break;

		//case ITEMTYPE::VINE:
		//	_img = ImageManager::GetInstance()->FindImage("vine");
		//	_name = L"µ¢±¼";
		//	_itemIndex = 202;
		//	_limitCount = 10;
		//	_price = 200;
		//	break;

		//case ITEMTYPE::WOOD:
		//	_img = ImageManager::GetInstance()->FindImage("wood");
		//	_name = L"»Ñ¸®";
		//	_itemIndex = 203;
		//	_limitCount = 5;
		//	_price = 500;
		//	break;

	case ITEMTYPE::GOLEM_PIECES:
		_img = ImageManager::GetInstance()->FindImage("golem_pieces");
		_name = L"ÁÖ¹° ÀÜÇØ";
		_itemIndex = 204;
		_limitCount = 10;
		_limitCount = 5;
		_price = 1500;
		break;

	case ITEMTYPE::BROKEN_SWORD:
		_img = ImageManager::GetInstance()->FindImage("broken_sword");
		_name = L"ºÎ·¯Áø °Ë";
		_itemIndex = 301;
		_limitCount = 5;
		_price = 1800;
		break;

	case ITEMTYPE::CRYSTAL_ENERGY:
		_img = ImageManager::GetInstance()->FindImage("crystal_energy");
		_name = L"¼öÁ¤È­µÈ ¿¡³ÊÁö";
		_itemIndex = 302;
		_limitCount = 5;
		_price = 1000;
		break;

	case ITEMTYPE::REINFORCED_STEEL:
		_img = ImageManager::GetInstance()->FindImage("reinforced_steel");
		_name = L"´ÜÁ¶µÈ °­Ã¶";
		_itemIndex = 303;
		_limitCount = 5;
		_price = 300;
		break;

	case ITEMTYPE::GOLEM_CORE:
		_img = ImageManager::GetInstance()->FindImage("golem_core");
		_name = L"°ñ·½ ÄÚ¾î";
		_itemIndex = 304;
		_limitCount = 5;
		_price = 1200;
		break;

	case ITEMTYPE::GOLEMKING_CRYSTAL:
		_img = ImageManager::GetInstance()->FindImage("golemKing_Energy");
		_name = L"°ñ·½¿ÕÀÇ ¿¡³ÊÁö";
		_itemIndex = 901;
		_limitCount = 5;
		_price = 3000;
		break;

	case ITEMTYPE::GOLEMKING_RECORD:
		_img = ImageManager::GetInstance()->FindImage("golemKing_record");
		_name = L"°ñ·½¿ÕÀÇ ±â·Ï";
		_itemIndex = 902;
		_limitCount = 1;
		_price = 3000;
		break;

	case ITEMTYPE::POTION_S:
		_img = ImageManager::GetInstance()->FindImage("potion_S");
		_name = L"Æ÷¼Ç(¼Ò)";
		_itemIndex = 1001;
		_limitCount = 5;
		_price = 1500;
		_fillHp = 40;
		break;

	case ITEMTYPE::POTION_M:
		_img = ImageManager::GetInstance()->FindImage("potion_M");
		_name = L"Æ÷¼Ç(Áß)";
		_itemIndex = 1002;
		_limitCount = 5;
		_price = 2000;
		_fillHp = 60;
		break;

	case ITEMTYPE::POTION_B:
		_img = ImageManager::GetInstance()->FindImage("potion_B");
		_name = L"Æ÷¼Ç(´ë)";
		_itemIndex = 1003;
		_limitCount = 5;
		_price = 2500;
		_fillHp = 80;
		break;

	case ITEMTYPE::POTION_L:
		_img = ImageManager::GetInstance()->FindImage("potion_L");
		_name = L"Æ÷¼Ç(Æ¯´ë)";
		_itemIndex = 1004;
		_limitCount = 5;
		_price = 3000;
		_fillHp = 100;
		break;
	}
	
}

void item::setBundle(int count)
{
	switch (_bundle)
	{
	case ITEMBUNDLE::SLIME_RED:
		if (count < 6) _type = ITEMTYPE::SLIME_RED;
		break;

	case ITEMBUNDLE::SLIME_BLUE:
		if (count < 6) _type = ITEMTYPE::SLIME_BLUE;
		break;

	case ITEMBUNDLE::SLIME_YELLOW:
		if (count < 6) _type = ITEMTYPE::SLIME_YELLOW;
		break;

	case ITEMBUNDLE::GOLEM_KNIGHT:
		if (count >= 0 && count < 2) _type = ITEMTYPE::GOLEM_PIECES;
		if (count >= 2 && count < 3) _type = ITEMTYPE::FABRIC;
		if (count >= 3 && count < 4) _type = ITEMTYPE::BROKEN_SWORD;
		if (count >= 4 && count < 6) _type = ITEMTYPE::GOLEM_CORE;
		break;

	case ITEMBUNDLE::GOLEM_POT:
		if (count >= 0 && count < 2) _type = ITEMTYPE::CRYSTAL_ENERGY;
		if (count >= 2 && count < 4) _type = ITEMTYPE::REINFORCED_STEEL;
		if (count >= 4 && count < 6) _type = ITEMTYPE::GOLEM_CORE;
		break;

	case ITEMBUNDLE::GOLEM_KING:
		if (count >= 0 && count < 4) _type = ITEMTYPE::GOLEMKING_CRYSTAL;
		if (count >= 4 && count < 5) _type = ITEMTYPE::GOLEMKING_RECORD;
		if (count >= 5 && count < 8) _type = ITEMTYPE::FABRIC;
		if (count >= 8 && count < 10) _type = ITEMTYPE::SLIME_RED;
		break;
	}
}
