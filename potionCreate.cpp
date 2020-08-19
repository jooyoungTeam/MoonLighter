#include "stdafx.h"
#include "potionCreate.h"

HRESULT potionCreate::init()
{
	ImageManager::GetInstance()->AddImage("potion_shop_bg", L"Image/potionShop/potion_shop_background.png");
	ImageManager::GetInstance()->AddImage("alphaBlack", L"Image/UI/alphaBlack.png");
	_select = ImageManager::GetInstance()->AddImage("select_potion", L"Image/potionShop/select_potion.png");

	ImageManager::GetInstance()->AddImage("potion_size", L"Image/potionShop/potion_size.png");
	ImageManager::GetInstance()->AddImage("potion_size_left", L"Image/potionShop/size_select_left.png");
	ImageManager::GetInstance()->AddImage("potion_size_right", L"Image/potionShop/size_select_right.png");
	ImageManager::GetInstance()->AddImage("potion_check_yes", L"Image/potionShop/potion_check_yes.png");
	ImageManager::GetInstance()->AddImage("potion_check_no", L"Image/potionShop/potion_check_no.png");

	_selectIndex = 0;
	_state = POTION_INIT;

	_selectPt = _pt[0] = Vector2(585, 259);
	_pt[1] = Vector2(695, 259);
	_pt[2] = Vector2(806, 259);
	_pt[3] = Vector2(916, 259);

	_isSizeLeft = true;
	_isSizeRight = true;
	_isPotionCheck = true;
	_isActive = false;

	potionSet();
	
	return S_OK;
}

void potionCreate::update()
{
	_selectPt = _pt[_selectIndex];
	indexSet();

	switch (_state)
	{
	case POTION_INIT:
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
		break;
	case POTION_SIZE:
		if (KEYMANAGER->isOnceKeyDown('A'))
		{
			if(_isSizeLeft)
				_makeCount--;
			// 포션 개수 마이너스
		}
		if (KEYMANAGER->isOnceKeyDown('D'))
		{
			if (_isSizeRight)
				_makeCount++;
			// 포션 개수 플러스	
		}
		break;
	case POTION_CHECK:
		if (KEYMANAGER->isOnceKeyDown('A'))
		{
			if (_isPotionCheck)
			{
				_isPotionCheck = false;
			}
			else
			{
				_isPotionCheck = true;
			}
		}
		if (KEYMANAGER->isOnceKeyDown('D'))
		{
			if (_isPotionCheck)
			{
				_isPotionCheck = false;
			}
			else
			{
				_isPotionCheck = true;
			}
		}
		break;

	}

	if (KEYMANAGER->isOnceKeyDown('J'))
	{
		switch (_state)
		{
		case POTION_INIT:
			_state = POTION_SIZE;
			break;
		case POTION_SIZE:
			_state = POTION_CHECK;
			break;
		case POTION_CHECK:
			if (_isPotionCheck)
			{
				INVENTORY->makePotion(1001, 101, 1, 0);
				// 포션 만들기 함수
				_isActive = false;
			}
			else
			{
				_state = POTION_SIZE;
			}
			break;
		}
	}

	if (KEYMANAGER->isOnceKeyDown('K'))
	{
		switch (_state)
		{
		case POTION_INIT:
			_isActive = false;
			break;
		case POTION_SIZE:
			_state = POTION_INIT;
			break;
		case POTION_CHECK:
			_state = POTION_SIZE;
			break;
		}
	}

}

void potionCreate::render()
{
	ImageManager::GetInstance()->FindImage("alphaBlack")->Render(Vector2(0, 0));
	ImageManager::GetInstance()->FindImage("potion_shop_bg")->Render(Vector2(0,0));
	_select->Render(_selectPt);
	
	switch (_state)
	{
	case POTION_INIT:
		break;
	case POTION_SIZE:
		ImageManager::GetInstance()->FindImage("alphaBlack")->Render(Vector2(0, 0));
		ImageManager::GetInstance()->FindImage("potion_size")->Render(Vector2(550, 300));

		if (_isSizeLeft)
		{
			ImageManager::GetInstance()->FindImage("potion_size_left")->Render(Vector2(601, WINSIZEY / 2 + 24));
		}
		if (_isSizeRight)
		{
			ImageManager::GetInstance()->FindImage("potion_size_right")->Render(Vector2(733, WINSIZEY / 2 + 24));
		}
		break;
	case POTION_CHECK:
		ImageManager::GetInstance()->FindImage("alphaBlack")->Render(Vector2(0, 0));
		ImageManager::GetInstance()->FindImage("alphaBlack")->Render(Vector2(0, 0));
		if (_isPotionCheck)
		{
			ImageManager::GetInstance()->FindImage("potion_check_yes")->Render(Vector2(450, 50));
		}
		else
		{
			ImageManager::GetInstance()->FindImage("potion_check_no")->Render(Vector2(450, 50));
		}
		break;
	}
}

void potionCreate::release()
{
	
}

void potionCreate::indexSet()
{
	switch (_selectIndex)
	{
	case 0:
		_selectPotion = _potion[0];
		break;

	case 1:
		_selectPotion = _potion[1];
		break;

	case 2:
		_selectPotion = _potion[2];
		break;

	case 3:
		_selectPotion = _potion[3];
		break;
	}

}

void potionCreate::potionSet()
{
	_potion[0].index = 1001;
	_potion[0].price = 100;
	_potion[0].img = ImageManager::GetInstance()->FindImage("potion_S");
	_potion[0].name = L"포션(소)";
	_potion[0].discription = L"체력을 40 회복한다. 한두 개 정도는 항상 휴대하는 게 좋다.";

	_potion[1].index = 1002;
	_potion[1].price = 500;
	_potion[1].img = ImageManager::GetInstance()->FindImage("potion_S");
	_potion[1].name = L"포션(중)";
	_potion[1].discription = L"체력을 60 회복한다. 제값을 톡톡히 하는 제품이다. ";

	_potion[2].index = 1003;
	_potion[2].price = 1000;
	_potion[2].img = ImageManager::GetInstance()->FindImage("potion_S");
	_potion[2].name = L"포션(대)";
	_potion[2].discription = L"체력을 80 회복한다. 그 괴물과 맞닥뜨렸을 때 하나 가지고 있었다면 좋았겠지만...";

	_potion[3].index = 1004;
	_potion[3].price = 2000;
	_potion[3].img = ImageManager::GetInstance()->FindImage("potion_S");
	_potion[3].name = L"포션(특대)";
	_potion[3].discription = L"체력을 100 회복한다. 마녀가 드디어 스스로의 능력을 뛰어넘는 물건을 만들어 냈다.";
}

void potionCreate::reset()
{
	_state = POTION_INIT;
	_selectIndex = 0;
	_isSizeLeft = false;
	_isSizeRight = true;
	_isPotionCheck = true;
	_isActive = false;
}

void potionCreate::isSizeUpdate()
{
	if (_makeCount == 1)
	{
		_isSizeLeft = false;
	}
	else
	{
		_isSizeLeft = true;
	}
}
