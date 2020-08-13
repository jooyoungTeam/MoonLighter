#include "stdafx.h"
#include "inventory.h"


//===========================================↓↓인벤에서 돌아다니기↓↓===========================================//
void inventory::moveInven()
{
	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		if (!_isSwap)
		{
			_select++;

			if (_select % 5 == 0 || _select > INVENSPACE - 1)
			{
				_isSwap = true;
				if (_state == INVEN_STATE::NOTE)
				{
					if (_select > INVENSPACE - 1) _select = 4;
					else _select = _select / 5 - 1;
				}

				if (_state == INVEN_STATE::SHOP)
				{
					if (_select / 10 == 0) _select = 0;
					else _select = 3;
				}
			}
		}
		else
		{
			if (_state == INVEN_STATE::NOTE)
			{
				_select++;

				if (_select == 0) _select = 5;
				else
				{
					_isSwap = false;
					if (_select >= 5) _select = 0;
					else _select *= 5;
				}
			}

			if (_state == INVEN_STATE::SHOP)
			{
				if (!_isSetPrice)
				{
					_select += 4;
					if (_select == 8)
					{
						_isSwap = false;
						_select = 0;
					}

					if (_select == 11)
					{
						_isSwap = false;
						_select = 15;
					}
				}

				else
				{
					_selectPrice++;;
					if (_selectPrice == 7) _selectPrice = 0;
				}
			}
		}
	}

	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		if (!_isSwap)
		{
			_select--;

			if (_select % 5 == 4 || _select < 0)
			{
				if (_state == INVEN_STATE::NOTE)
				{
					_isSwap = true;
					if (_select < 0) _select = 5;
					else _select = _select / 5 + 1;
				}

				if (_state == INVEN_STATE::SHOP)
				{
					if (_select < 0)
					{
						_isSwap = true;
						_select = 4;
					}

					if (_select == 14)
					{
						_isSwap = true;
						_select = 6;
					}
				}
			}
		}

		else
		{
			if (_state == INVEN_STATE::NOTE)
			{
				if (_select == 5) _select = 0;
				else if (_select <= 4)
				{
					_isSwap = false;
					if (_select == 4) _select = 21;
					else _select = _select * 5 + 4;
				}
			}

			if (_state == INVEN_STATE::SHOP)
			{
				if (!_isSetPrice)
				{
					_select -= 4;
					if (_select < 0)
					{
						_isSwap = false;
						if (_select == -4 || _select == -3) _select = 4;
						if (_select == -1 || _select == -2) _select = 19;
					}
				}

				else
				{
					_selectPrice--;
					if (_selectPrice == -1) _selectPrice = 6;
				}
			}
		}
	}

	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		if (!_isSwap)
		{
			if (_select < 5)
			{
				_select += 15;
				if (_select == 15) _select = 20;
				if (_select == 17) _select = 21;
			}

			else
			{
				_select -= 5;
				if (_select == 16) _select = 17;
			}
		}

		else
		{
			if (_state == INVEN_STATE::NOTE)
			{
				_select--;
				if (_select < 0) _select = 4;
			}

			if (_state == INVEN_STATE::SHOP)
			{
				if (!_isSetPrice)
				{
					_select--;
					if (_select < 0) _select = 3;
				}

				else
				{
					if (_select == 1)
					{
						_firstPrice[_selectPrice].price++;
						if (_firstPrice[_selectPrice].price > 9) _firstPrice[_selectPrice].price = 0;
					}

					else if (_select == 3)
					{
						_secondPrice[_selectPrice].price++;
						if (_secondPrice[_selectPrice].price > 9) _secondPrice[_selectPrice].price = 0;
					}

					else if (_select == 5)
					{
						_thirdPrice[_selectPrice].price++;
						if (_thirdPrice[_selectPrice].price > 9) _thirdPrice[_selectPrice].price = 0;
					}

					else if (_select == 7)
					{
						_fourthPrice[_selectPrice].price++;
						if (_fourthPrice[_selectPrice].price > 9) _fourthPrice[_selectPrice].price = 0;
					}
				}
			}
		}
	}

	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		if (!_isSwap)
		{
			if (_select < 20)
			{
				_select += 5;

				if (_select == 21 || _select == 22) _select -= 1;
				if (_select > 22) _select -= 20;
			}

			else
			{
				if (_select == 21) _select -= 19;
				else _select -= 20;
			}
		}

		else
		{
			if (_state == INVEN_STATE::NOTE)
			{
				_select++;
				if (_select > 4) _select = 0;
			}

			if (_state == INVEN_STATE::SHOP)
			{
				if (!_isSetPrice)
				{
					_select++;
					if (_select > 7) _select = 4;
				}

				else
				{
					if (_select == 1)
					{
						_firstPrice[_selectPrice].price--;
						if (_firstPrice[_selectPrice].price < 0) _firstPrice[_selectPrice].price = 9;
					}

					else if (_select == 3)
					{
						_secondPrice[_selectPrice].price--;
						if (_secondPrice[_selectPrice].price < 0) _secondPrice[_selectPrice].price = 9;
					}

					else if (_select == 5)
					{
						_thirdPrice[_selectPrice].price--;
						if (_thirdPrice[_selectPrice].price < 0) _thirdPrice[_selectPrice].price = 9;
					}

					else if (_select == 7)
					{
						_fourthPrice[_selectPrice].price--;
						if (_fourthPrice[_selectPrice].price < 0) _fourthPrice[_selectPrice].price = 9;
					}
				}
			}
		}
	}
}
//===========================================↑↑인벤에서 돌아다니기↑↑===========================================//


//===========================================↓↓아이템 인벤에 넣기↓↓===========================================//
void inventory::putItem(item* item)
{
	for (int i = 0; i < INVENSPACE; i++)
	{
		if (_inven[i].item == nullptr && i < 20)
		{
			_inven[i].item = item;
			_inven[i].count++;
			break;
		}

		if (_inven[i].item != nullptr)
		{
			if (_inven[i].item->getIndex() == item->getIndex())
			{
				if (_inven[i].count >= _inven[i].item->getLimit())
				{
					continue;
				}

				_inven[i].count++;
				break;
			}

			if (_inven[i].item->getIndex() != item->getIndex())
			{
				continue;
			}
		}
	}
}
//===========================================↑↑아이템 인벤에 넣기↑↑===========================================//


//===========================================↓↓가격 설정하기↓↓===========================================//
void inventory::setPrice()
{
	for (int i = 0; i < PRICESPACE; i++)
	{
		_firstPrice[i].rc = RectMakePivot(Vector2(_shop[1].rc.GetCenter().x + i * 20 - 40, _shop[1].rc.GetCenter().y), Vector2(20, 30), Pivot::Center);
		_shop[1].totalPrice = _firstPrice[0].price * 10000 + _firstPrice[1].price * 1000 + _firstPrice[2].price * 100 + _firstPrice[3].price * 10 + _firstPrice[4].price;

		_secondPrice[i].rc = RectMakePivot(Vector2(_shop[3].rc.GetCenter().x + i * 20 - 40, _shop[3].rc.GetCenter().y), Vector2(20, 30), Pivot::Center);
		_shop[3].totalPrice = _secondPrice[0].price * 10000 + _secondPrice[1].price * 1000 + _secondPrice[2].price * 100 + _secondPrice[3].price * 10 + _secondPrice[4].price;

		_thirdPrice[i].rc = RectMakePivot(Vector2(_shop[5].rc.GetCenter().x + i * 20 - 40, _shop[5].rc.GetCenter().y), Vector2(20, 30), Pivot::Center);
		_shop[5].totalPrice = _thirdPrice[0].price * 10000 + _thirdPrice[1].price * 1000 + _thirdPrice[2].price * 100 + _thirdPrice[3].price * 10 + _thirdPrice[4].price;

		_fourthPrice[i].rc = RectMakePivot(Vector2(_shop[7].rc.GetCenter().x + i * 20 - 40, _shop[7].rc.GetCenter().y), Vector2(20, 30), Pivot::Center);
		_shop[7].totalPrice = _fourthPrice[0].price * 10000 + _fourthPrice[1].price * 1000 + _fourthPrice[2].price * 100 + _fourthPrice[3].price * 10 + _fourthPrice[4].price;
	}
}
//===========================================↑↑가격 설정하기↑↑===========================================//


//===========================================↓↓인벤 닫기↓↓===========================================//
void inventory::closeInven()
{
	if (_isSelect)
	{
		//인벤에서 아이템을 선택하고 있는 상태였다면
		if (_selectNumber >= 0)
		{
			if (_inven[_selectNumber].item == nullptr)
			{
				_inven[_selectNumber].item = _selectItem.item;
				_inven[_selectNumber].count = _selectItem.count;
				_inven[_selectNumber].price = _selectItem.price;
				_selectItem.item = nullptr;
			}

			else
			{
				_inven[_selectNumber].count += _selectItem.count;
				_selectItem.item = nullptr;
			}
		}

		//장비창에서 아이템을 선택하고 있는 상태였다면
		if (_selectGearNumber >= 0)
		{
			if (_gear[_selectGearNumber].item == nullptr)
			{
				_gear[_selectGearNumber].item = _selectItem.item;
				_gear[_selectGearNumber].count = _selectItem.count;
				_selectItem.item = nullptr;
			}

			else
			{
				_gear[_selectGearNumber].count += _selectItem.count;
				_selectItem.item = nullptr;
			}
		}

		//쇼케이스에서 아이템을 선택하고 있는 상태였다면
		if (_selectShopNumber >= 0)
		{
			if (_shop[_selectShopNumber].item == nullptr)
			{
				_shop[_selectShopNumber].item = _selectItem.item;
				_shop[_selectShopNumber].count = _selectItem.count;
				_shop[_selectShopNumber].price = _selectItem.price;
				_selectItem.item = nullptr;
			}

			else
			{
				_shop[_selectShopNumber].count += _selectItem.count;
				_selectItem.item = nullptr;
			}
		}
	}

	_isSelect = false;
	_isSale = false;
	_isSwap = false;
	_state = INVEN_STATE::TEMP;
	_mirror = MIRROR_STATE::STOP;
	_select = 0;
}
//===========================================↑↑인벤 닫기↑↑===========================================//


//===========================================↓↓미러 사용하기↓↓===========================================//
void inventory::useMirror()
{
	if (_select == 20)
	{
		//미러 칸에 머무르고 있으면
		_count++;
		if (_count == 15 && _mirror != MIRROR_STATE::ACTIVE)
		{
			_mirror = MIRROR_STATE::STAY;
			_mirrorFrameX = 0;
			_mirrorImg = ImageManager::GetInstance()->FindImage("mirror_stay");
		}
	}

	else if (_select != 20 && _mirror != MIRROR_STATE::ACTIVE)
	{
		_mirror = MIRROR_STATE::STOP;
		_count = 0;
		_mirrorFrameX = 0;
		_mirrorImg = ImageManager::GetInstance()->FindImage("bagMirror");
	}
}
//===========================================↑↑미러 사용하기↑↑===========================================//


//===========================================↓↓인벤 상태에 따른 렌더↓↓===========================================//
void inventory::renderInven()
{
	//인벤토리
	for (int i = 0; i < INVENSPACE; i++)
	{
		//D2DRenderer::GetInstance()->DrawRectangle(_inven[i].rc, D2DRenderer::DefaultBrush::Green, 1.f);
		if (i <= 20) ImageManager::GetInstance()->FindImage("invenSpace")->Render(Vector2(_inven[i].rc.left - 5, _inven[i].rc.top - 5));

		if (_inven[i].item != nullptr)
		{
			_inven[i].item->getImg()->Render(Vector2(_inven[i].rc.GetCenter().x - _inven[i].item->getImg()->GetWidth() / 2, _inven[i].rc.GetCenter().y - _inven[i].item->getImg()->GetHeight() / 2));
			D2DRenderer::GetInstance()->RenderText(_inven[i].rc.right - _inven[i].number.length() * 20, _inven[i].rc.bottom - 20, to_wstring(_inven[i].count), 20, D2DRenderer::DefaultBrush::Black);
		}
	}

	//장비창
	if (_state == INVEN_STATE::NOTE)
	{
		for (int i = 0; i < GEARSPACE; i++)
		{
			//D2DRenderer::GetInstance()->DrawRectangle(_gear[i].rc, D2DRenderer::DefaultBrush::Green, 1.f);
			ImageManager::GetInstance()->FindImage("invenSpace")->Render(Vector2(_gear[i].rc.left - 5, _gear[i].rc.top - 5));

			if (_gear[i].item != nullptr)
			{
				_gear[i].item->getImg()->Render(Vector2(_gear[i].rc.GetCenter().x - _gear[i].item->getImg()->GetWidth() / 2, _gear[i].rc.GetCenter().y - _gear[i].item->getImg()->GetHeight() / 2));
				D2DRenderer::GetInstance()->RenderText(_gear[i].rc.right - _gear[i].number.length() * 20, _gear[i].rc.bottom - 20, to_wstring(_gear[i].count), 20, D2DRenderer::DefaultBrush::Black);
			}

			if (i == _select && _isSwap) ImageManager::GetInstance()->FindImage("select")->Render(Vector2(_gear[i].rc.left - 7, _gear[i].rc.top - 7));
		}

		ImageManager::GetInstance()->FindImage("empty_weapon")->Render(Vector2(_gear[0].rc.GetCenter().x - 26, _gear[0].rc.GetCenter().y - 25));
		ImageManager::GetInstance()->FindImage("empty_weapon")->Render(Vector2(_gear[5].rc.GetCenter().x - 26, _gear[5].rc.GetCenter().y - 25));
		ImageManager::GetInstance()->FindImage("empty_helmet")->Render(Vector2(_gear[1].rc.GetCenter().x - 26, _gear[1].rc.GetCenter().y - 25));
		ImageManager::GetInstance()->FindImage("empty_top")->Render(Vector2(_gear[2].rc.GetCenter().x - 26, _gear[2].rc.GetCenter().y - 25));
		ImageManager::GetInstance()->FindImage("empty_shoes")->Render(Vector2(_gear[3].rc.GetCenter().x - 26, _gear[3].rc.GetCenter().y - 25));
		if (_gear[4].item == nullptr) ImageManager::GetInstance()->FindImage("empty_potion")->Render(Vector2(_gear[4].rc.GetCenter().x - 26, _gear[4].rc.GetCenter().y - 25));

		//장비 변경
		if (!_player->getWeaponChange()) ImageManager::GetInstance()->FindImage("inven_weapon_1")->Render(Vector2(960, 205));
		if (_player->getWeaponChange())ImageManager::GetInstance()->FindImage("inven_weapon_2")->Render(Vector2(960, 205));
	}

	//쇼케이스
	if (_state == INVEN_STATE::SHOP)
	{
		ImageManager::GetInstance()->FindImage("showcase")->Render(Vector2(800, 160));

		for (int i = 0; i < SHOPSPACE; i++)
		{
			//D2DRenderer::GetInstance()->DrawRectangle(_shop[i].rc, D2DRenderer::DefaultBrush::Green, 1.f);

			//아이템이 들어가면 이미지 띄우기
			if (_shop[i].item != nullptr)
			{
				_shop[i].item->getImg()->Render(Vector2(_shop[i].rc.GetCenter().x - _shop[i].item->getImg()->GetWidth() / 2, _shop[i].rc.GetCenter().y - _shop[i].item->getImg()->GetHeight() / 2));
				D2DRenderer::GetInstance()->RenderText(_shop[i].rc.right - _shop[i].countNum.length() * 20, _shop[i].rc.bottom - 20, to_wstring(_shop[i].count), 20, D2DRenderer::DefaultBrush::White);
			}

			//가격 적어두기
			if (i % 2 != 0)
			D2DRenderer::GetInstance()->RenderText(_shop[i].rc.GetCenter().x, _shop[i].rc.GetCenter().y + 45, to_wstring(_shop[i].totalPrice), 20, D2DRenderer::DefaultBrush::White);

			//선택 커서 띄어두기
			if (i == _select && _isSwap && !_isSetPrice)
			{
				if (i % 2 == 0)
				{
					ImageManager::GetInstance()->FindImage("select")->Render(Vector2(_shop[i].rc.left - 5, _shop[i].rc.top - 5));
				}

				else
				{
					ImageManager::GetInstance()->FindImage("select")->Render(Vector2(_shop[i].rc.GetCenter().x - 35, _shop[i].rc.GetCenter().y - 35));
				}
			}
		}

		//가격설정칸 활성상태에 따른 렌더 변화
		for (int i = 0; i < PRICESPACE; i++)
		{
			float line;
			if (i == _selectPrice) line = 2.f;
			else line = 1.f;

			//if (_isSetPrice) 
			D2DRenderer::GetInstance()->DrawRectangle(_firstPrice[i].rc, D2DRenderer::DefaultBrush::Green, line);
			D2DRenderer::GetInstance()->RenderText(_firstPrice[i].rc.GetCenter().x, _firstPrice[i].rc.GetCenter().y, to_wstring(_firstPrice[i].price), 10, D2DRenderer::DefaultBrush::Black);

			D2DRenderer::GetInstance()->DrawRectangle(_secondPrice[i].rc, D2DRenderer::DefaultBrush::Green, line);
			D2DRenderer::GetInstance()->RenderText(_secondPrice[i].rc.GetCenter().x, _secondPrice[i].rc.GetCenter().y, to_wstring(_secondPrice[i].price), 10, D2DRenderer::DefaultBrush::Black);

			D2DRenderer::GetInstance()->DrawRectangle(_thirdPrice[i].rc, D2DRenderer::DefaultBrush::Green, line);
			D2DRenderer::GetInstance()->RenderText(_thirdPrice[i].rc.GetCenter().x, _thirdPrice[i].rc.GetCenter().y, to_wstring(_thirdPrice[i].price), 10, D2DRenderer::DefaultBrush::Black);

			D2DRenderer::GetInstance()->DrawRectangle(_fourthPrice[i].rc, D2DRenderer::DefaultBrush::Green, line);
			D2DRenderer::GetInstance()->RenderText(_fourthPrice[i].rc.GetCenter().x, _fourthPrice[i].rc.GetCenter().y, to_wstring(_fourthPrice[i].price), 10, D2DRenderer::DefaultBrush::Black);
		}
	}
}
//===========================================↑↑인벤 상태에 따른 렌더↑↑===========================================//


//===========================================↓↓프레임 돌리기↓↓===========================================//
void inventory::draw()
{

	if (_frameCount % 5 == 0)
	{
		//미러 프레임 돌아간다~
		_mirrorFrameX++;
		if (_mirrorImg != nullptr && _mirrorFrameX >= _mirrorImg->GetMaxFrameX())
		{
			if (_mirror == MIRROR_STATE::ACTIVE)
			{
				_mirror = MIRROR_STATE::STAY;
				_mirrorImg = ImageManager::GetInstance()->FindImage("mirror_stay");
				_mirrorFrameX = 0;
			}

			if (_mirror == MIRROR_STATE::STAY)
			{
				_mirrorFrameX = 3;
			}
		}

		if (_isSale)
		{
			//미러 안 공
			_mirrorBallFrameX++;
			if (_mirrorBallFrameX >= _saleImg->GetMaxFrameX())
			{
				_mirrorBallFrameX = 0;
				if (!_isSelect) _isSale = false;
			}

			//아이템 파는 select공
			_saleFrameX++;
			if (_saleFrameX >= ImageManager::GetInstance()->FindImage("inven_sale")->GetMaxFrameX())
			{
				_saleFrameX = 0;
			}
		}

		_frameCount = 0;
	}
}
