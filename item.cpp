#include "stdafx.h"
#include "item.h"

HRESULT item::init(ITEMTYPE type, float x, float y)
{
	_type = type;
	_x = x;
	_y = y;
	_shake = 0;
	_isShake = false;

	sort();

	_rc = RectMakePivot(Vector2(_x, _y), Vector2(30, 30), Pivot::Center);

	return S_OK;
}

HRESULT item::init(ITEMTYPE type)
{
	_type = type;
	_shake = 0;
	_isShake = false;

	sort();
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

void item::release()
{
}

void item::sort()
{
	//Index ��ȣ 100�� ������(10�� ����, ���� ���)
	//Index ��ȣ 200�� ��� (10�� ����, �������� ���)
	//Index ��ȣ 300�� ��� (5�� ����, �������� ���)
	//Index ��ȣ 900�� ���� ������ (1�� ����)
	//Index ��ȣ 1000�� ���� (5�� ����, �Һ� ������)

	switch (_type)
	{
		//ǳ���� ����(����)
		case ITEMTYPE::SLIME_RED:
			_img = ImageManager::GetInstance()->FindImage("slime_red");
			_itemIndex = 101;
			_limitCount = 10;
			_price = 600;
			break;

		//ǳ���� ����(�Ķ�)
		case ITEMTYPE::SLIME_BLUE:
			_img = ImageManager::GetInstance()->FindImage("slime_blue");
			_itemIndex = 102;
			_limitCount = 10;
			_price = 600;
			break;

		//ǳ���� ����(���)
		case ITEMTYPE::SLIME_YELLOW:
			_img = ImageManager::GetInstance()->FindImage("slime_yellow");
			_itemIndex = 103;
			_limitCount = 10;
			_price = 600;
			break;

		//õ
		case ITEMTYPE::FABRIC:
			_img = ImageManager::GetInstance()->FindImage("fabric");
			_itemIndex = 201;
			_limitCount = 10;
			_price = 3000;
			break;

		//����
		case ITEMTYPE::VINE:
			_img = ImageManager::GetInstance()->FindImage("vine");
			_itemIndex = 202;
			_limitCount = 10;
			_price = 200;
			break;

		//�Ѹ�
		case ITEMTYPE::WOOD:
			_img = ImageManager::GetInstance()->FindImage("wood");
			_itemIndex = 203;
			_limitCount = 5;
			_price = 500;
			break;

		//�ֹ� ����
		case ITEMTYPE::GOLEM_PIECES:
			_img = ImageManager::GetInstance()->FindImage("golem_pieces");
			_itemIndex = 204;
			_limitCount = 10;
			_limitCount = 5;
			_price = 1500;
			break;

		//�η��� ��
		case ITEMTYPE::BROKEN_SWORD:
			_img = ImageManager::GetInstance()->FindImage("broken_sword");
			_itemIndex = 301;
			_limitCount = 5;
			_price = 1800;
			break;

		//����ȭ�� ������
		case ITEMTYPE::CRYSTAL_ENERGY:
			_img = ImageManager::GetInstance()->FindImage("crystal_energy");
			_itemIndex = 302;
			_limitCount = 5;
			_price = 1000;
			break;

		//������ ��ö
		case ITEMTYPE::REINFORCED_STEEL:
			_img = ImageManager::GetInstance()->FindImage("reinforced_steel");
			_itemIndex = 303;
			_limitCount = 5;
			_price = 300;
			break;

		//�� �ھ�
		case ITEMTYPE::GOLEM_CORE:
			_img = ImageManager::GetInstance()->FindImage("golem_core");
			_itemIndex = 304;
			_limitCount = 5;
			_price = 1200;
			break;

		//�񷽿��� ������
		case ITEMTYPE::GOLEMKING_CRYSTAL:
			_img = ImageManager::GetInstance()->FindImage("golemKing_Energy");
			_itemIndex = 901;
			_limitCount = 1;
			_price = 3000;
			break;

		//�񷽿��� ���
		case ITEMTYPE::GOLEMKING_RECORD:
			_img = ImageManager::GetInstance()->FindImage("golemKing_record");
			_itemIndex = 902;
			_limitCount = 1;
			_price = 3000;
			break;

		//����(��)
		case ITEMTYPE::POTION_S:
			_img = ImageManager::GetInstance()->FindImage("potion_S");
			_itemIndex = 1001;
			_limitCount = 5;
			_price = 1500;
			break;
	}
}
