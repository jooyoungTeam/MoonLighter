#include "stdafx.h"
#include "item.h"

HRESULT item::init(ITEMTYPE type, float x, float y)
{
	ImageManager::GetInstance()->AddImage("slime_red", L"Image/Item/slime_jelly.png");
	ImageManager::GetInstance()->AddImage("slime_blue", L"Image/Item/slime_jelly_blue.png");
	ImageManager::GetInstance()->AddImage("slime_yellow", L"Image/Item/slime_jelly_yellow.png");
	ImageManager::GetInstance()->AddImage("fabric", L"Image/Item/fabric.png");
	ImageManager::GetInstance()->AddImage("vine", L"Image/Item/Vine.png");
	ImageManager::GetInstance()->AddImage("wood", L"Image/Item/Treated_Wood.png");
	ImageManager::GetInstance()->AddImage("golem_pieces", L"Image/Item/golem_pieces.png");
	ImageManager::GetInstance()->AddImage("golem_core", L"Image/Item/Golem_Core.png");
	ImageManager::GetInstance()->AddImage("broken_sword", L"Image/Item/Broken_Sword.png");
	ImageManager::GetInstance()->AddImage("crystal_energy", L"Image/Item/Crystal_Energy.png");
	ImageManager::GetInstance()->AddImage("reinforced_steel", L"Image/Item/Reinforced_Steel_G.png");
	ImageManager::GetInstance()->AddImage("golemKing_Energy", L"Image/Item/Energy_Crystal.png");
	ImageManager::GetInstance()->AddImage("golemKing_record", L"Image/Item/Golem_King_design.png");
	ImageManager::GetInstance()->AddImage("potion_S", L"Image/Item/Potion_S.png");

	_type = type;
	_x = x;
	_y = y;

	sort();

	_rc = RectMakePivot(Vector2(_x, _y), Vector2(30, 30), Pivot::Center);

	return S_OK;
}

void item::release()
{
}

void item::update()
{
	_rc = RectMakePivot(Vector2(_x, _y), Vector2(30, 30), Pivot::Center);
}

void item::render()
{
	_img->Render(Vector2(_rc.left, _rc.top));
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
			_price = 6;
			break;

		//ǳ���� ����(�Ķ�)
		case ITEMTYPE::SLIME_BLUE:
			_img = ImageManager::GetInstance()->FindImage("slime_blue");
			_itemIndex = 102;
			_limitCount = 10;
			_price = 6;
			break;

		//ǳ���� ����(���)
		case ITEMTYPE::SLIME_YELLOW:
			_img = ImageManager::GetInstance()->FindImage("slime_yellow");
			_itemIndex = 103;
			_limitCount = 10;
			_price = 6;
			break;

		//õ
		case ITEMTYPE::FABRIC:
			_img = ImageManager::GetInstance()->FindImage("fabric");
			_itemIndex = 201;
			_limitCount = 10;
			_price = 300;
			break;

		//����
		case ITEMTYPE::VINE:
			_img = ImageManager::GetInstance()->FindImage("vine");
			_itemIndex = 202;
			_limitCount = 10;
			_price = 2;
			break;

		//�Ѹ�
		case ITEMTYPE::WOOD:
			_img = ImageManager::GetInstance()->FindImage("wood");
			_itemIndex = 203;
			_limitCount = 5;
			_price = 5;
			break;

		//�ֹ� ����
		case ITEMTYPE::GOLEM_PIECES:
			_img = ImageManager::GetInstance()->FindImage("golem_pieces");
			_itemIndex = 204;
			_limitCount = 10;
			_limitCount = 5;
			_price = 150;
			break;

		//�η��� ��
		case ITEMTYPE::BROKEN_SWORD:
			_img = ImageManager::GetInstance()->FindImage("broken_sword");
			_itemIndex = 301;
			_limitCount = 5;
			_price = 180;
			break;

		//����ȭ�� ������
		case ITEMTYPE::CRYSTAL_ENERGY:
			_img = ImageManager::GetInstance()->FindImage("crystal_energy");
			_itemIndex = 302;
			_limitCount = 5;
			_price = 100;
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
			_price = 120;
			break;

		//�񷽿��� ������
		case ITEMTYPE::GOLEMKING_CRYSTAL:
			_img = ImageManager::GetInstance()->FindImage("golemKing_Energy");
			_itemIndex = 901;
			_limitCount = 1;
			_price = 300;
			break;

		//�񷽿��� ���
		case ITEMTYPE::GOLEMKING_RECORD:
			_img = ImageManager::GetInstance()->FindImage("golemKing_record");
			_itemIndex = 902;
			_limitCount = 1;
			_price = 300;
			break;

		//����(��)
		case ITEMTYPE::POTION_S:
			_img = ImageManager::GetInstance()->FindImage("potion_S");
			_itemIndex = 1001;
			_limitCount = 5;
			_price = 150;
			break;
	}
}
