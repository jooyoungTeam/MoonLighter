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

HRESULT item::init(ITEMTYPE type)
{
	_type = type;
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
	CAMERAMANAGER->render(_img, _rc.left, _rc.top, 1.f);
}

void item::update()
{
	_rc = RectMakePivot(Vector2(_x, _y), Vector2(30, 30), Pivot::Center);
	move();
}

void item::fieldUpdate()
{
	//cout << _shake << endl;
	if (_y > _shakeMaxY)
	{
		_isShake = false;
		_shake = 0;
	}

	if (_y < _shakeMinY)
	{
		_isShake = true;
		//_shake = 0;
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

	_rc = RectMakePivot(Vector2(_x, _y), Vector2(30, 30), Pivot::Center);
}

void item::move()
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

	if (distance <= 100)
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
		//Ç³ºÎÇÑ Á©¸®(»¡°­)
		case ITEMTYPE::SLIME_RED:
			_img = ImageManager::GetInstance()->FindImage("slime_red");
			_itemIndex = 101;
			_limitCount = 10;
			_price = 600;
			break;

		//Ç³ºÎÇÑ Á©¸®(ÆÄ¶û)
		case ITEMTYPE::SLIME_BLUE:
			_img = ImageManager::GetInstance()->FindImage("slime_blue");
			_itemIndex = 102;
			_limitCount = 10;
			_price = 600;
			break;

		//Ç³ºÎÇÑ Á©¸®(³ë¶û)
		case ITEMTYPE::SLIME_YELLOW:
			_img = ImageManager::GetInstance()->FindImage("slime_yellow");
			_itemIndex = 103;
			_limitCount = 10;
			_price = 600;
			break;

		//Ãµ
		case ITEMTYPE::FABRIC:
			_img = ImageManager::GetInstance()->FindImage("fabric");
			_itemIndex = 201;
			_limitCount = 10;
			_price = 3000;
			break;

		////µ¢±¼
		//case ITEMTYPE::VINE:
		//	_img = ImageManager::GetInstance()->FindImage("vine");
		//	_itemIndex = 202;
		//	_limitCount = 10;
		//	_price = 200;
		//	break;

		////»Ñ¸®
		//case ITEMTYPE::WOOD:
		//	_img = ImageManager::GetInstance()->FindImage("wood");
		//	_itemIndex = 203;
		//	_limitCount = 5;
		//	_price = 500;
		//	break;

		//ÁÖ¹° ÀÜÇØ
		case ITEMTYPE::GOLEM_PIECES:
			_img = ImageManager::GetInstance()->FindImage("golem_pieces");
			_itemIndex = 204;
			_limitCount = 10;
			_limitCount = 5;
			_price = 1500;
			break;

		//ºÎ·¯Áø °Ë
		case ITEMTYPE::BROKEN_SWORD:
			_img = ImageManager::GetInstance()->FindImage("broken_sword");
			_itemIndex = 301;
			_limitCount = 5;
			_price = 1800;
			break;

		//¼öÁ¤È­µÈ ¿¡³ÊÁö
		case ITEMTYPE::CRYSTAL_ENERGY:
			_img = ImageManager::GetInstance()->FindImage("crystal_energy");
			_itemIndex = 302;
			_limitCount = 5;
			_price = 1000;
			break;

		//´ÜÁ¶µÈ °­Ã¶
		case ITEMTYPE::REINFORCED_STEEL:
			_img = ImageManager::GetInstance()->FindImage("reinforced_steel");
			_itemIndex = 303;
			_limitCount = 5;
			_price = 300;
			break;

		//°ñ·½ ÄÚ¾î
		case ITEMTYPE::GOLEM_CORE:
			_img = ImageManager::GetInstance()->FindImage("golem_core");
			_itemIndex = 304;
			_limitCount = 5;
			_price = 1200;
			break;

		//°ñ·½¿ÕÀÇ ¿¡³ÊÁö
		case ITEMTYPE::GOLEMKING_CRYSTAL:
			_img = ImageManager::GetInstance()->FindImage("golemKing_Energy");
			_itemIndex = 901;
			_limitCount = 1;
			_price = 3000;
			break;

		//°ñ·½¿ÕÀÇ ±â·Ï
		case ITEMTYPE::GOLEMKING_RECORD:
			_img = ImageManager::GetInstance()->FindImage("golemKing_record");
			_itemIndex = 902;
			_limitCount = 1;
			_price = 3000;
			break;

		//Æ÷¼Ç(¼Ò)
		case ITEMTYPE::POTION_S:
			_img = ImageManager::GetInstance()->FindImage("potion_S");
			_itemIndex = 1001;
			_limitCount = 5;
			_price = 1500;
			break;

		default:

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
		if (count >= 2 && count < 3) _type = ITEMTYPE::REINFORCED_STEEL;
		if (count >= 3 && count < 6) _type = ITEMTYPE::GOLEM_CORE;
		break;

	case ITEMBUNDLE::GOLEM_KING:
		if (count >= 0 && count < 2) _type = ITEMTYPE::GOLEMKING_CRYSTAL;
		if (count >= 2 && count < 3) _type = ITEMTYPE::GOLEMKING_RECORD;
		if (count >= 3 && count < 4) _type = ITEMTYPE::FABRIC;
		if (count >= 4 && count < 6) _type = ITEMTYPE::SLIME_RED;
		break;
	}
}
