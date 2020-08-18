#include "stdafx.h"
#include "inventory.h"
#include "player.h"

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
					if (_select % 5 == 0) _select = _select / 5 - 1;
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
					if (_select > 7)
					{
						_isSwap = false;
						if (_select == 8) _select = 0;
						if (_select == 9) _select = 5;
						if (_select == 10) _select = 10;
						if (_select == 11) _select = 15;
					}

				}

				else
				{
					_selectCount++;
					if (_selectCount == 5) _selectCount = 0;
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
					_isSwap = true;
					if (_select < 0) _select = 4;
					else  if (_select < 19) _select = _select % 5 + _select / 5 + 1;
					else _select = 7;
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
						if (_select == -4) _select = 4;
						if (_select == -3) _select = 9;
						if (_select == -2) _select = 14;
						if (_select == -1) _select = 19;
					}
				}

				else
				{
					_selectCount--;
					if (_selectCount == -1) _selectCount = 4;
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

				else if (_isSetPrice && _shop[_select - 1].item != nullptr)
				{
					if (_select == 1) setCount(_firstPrice, L"up");
					if (_select == 3) setCount(_secondPrice, L"up");
					if (_select == 5) setCount(_thirdPrice, L"up");
					if (_select == 7) setCount(_fourthPrice, L"up");
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

				else if (_isSetPrice && _shop[_select - 1].item != nullptr)
				{
					if (_select == 1) setCount(_firstPrice, L"down");
					if (_select == 3) setCount(_secondPrice, L"down");
					if (_select == 5) setCount(_thirdPrice, L"down");
					if (_select == 7) setCount(_fourthPrice, L"down");
				}
			}
		}
	}
}
//===========================================↑↑인벤에서 돌아다니기↑↑===========================================//


//===========================================↓↓아이템 인벤에 넣기↓↓===========================================//
bool inventory::putItem(item* item)
{
	int invenFullNum = fullInven();
	if (invenFullNum >= 19)
	{
		return false;
	}
	else
	{
		for (int i = 0; i < INVENSPACE; i++)
		{
			if (_inven[i].isFull) continue;

			if (_inven[i].item != nullptr)
			{
				if (_inven[i].item->getIndex() == item->getIndex())
				{
					_inven[i].count++;
					return true;
				}
				else
					continue;
			}

			if (_inven[i].item == nullptr && i < 20)
			{
				_inven[i].item = item;
				_inven[i].count++;
				return true;
			}
		}
	}
	return false;
}
//===========================================↑↑아이템 인벤에 넣기↑↑===========================================//


//===========================================↓↓인벤 가득 찼는지 확인↓↓===========================================//
int inventory::fullInven()
{
	int invenFullNum = 0;

	for (int i = 0; i < 20; i++)
	{
		if (_inven[i].item == nullptr) return 0;

		if (_inven[i].count >= _inven[i].item->getLimit())
		{
			_inven[i].isFull = true;
			invenFullNum++;
		}

		else
		{
			_inven[i].isFull = false;
		}
	}
	return invenFullNum;
}
//===========================================↑↑인벤 가득 찼는지 확인↑↑===========================================//


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
		}
		//ImageManager::GetInstance()->FindImage("empty_weapon")->Render(Vector2(_gear[0].rc.GetCenter().x - 26, _gear[0].rc.GetCenter().y - 25));
		//ImageManager::GetInstance()->FindImage("empty_weapon")->Render(Vector2(_gear[5].rc.GetCenter().x - 26, _gear[5].rc.GetCenter().y - 25));
		ImageManager::GetInstance()->FindImage("empty_helmet")->Render(Vector2(_gear[1].rc.GetCenter().x - 26, _gear[1].rc.GetCenter().y - 25));
		ImageManager::GetInstance()->FindImage("empty_top")->Render(Vector2(_gear[2].rc.GetCenter().x - 26, _gear[2].rc.GetCenter().y - 25));
		ImageManager::GetInstance()->FindImage("empty_shoes")->Render(Vector2(_gear[3].rc.GetCenter().x - 26, _gear[3].rc.GetCenter().y - 25));
		if (_gear[4].item == nullptr) ImageManager::GetInstance()->FindImage("empty_potion")->Render(Vector2(_gear[4].rc.GetCenter().x - 26, _gear[4].rc.GetCenter().y - 25));

		ImageManager::GetInstance()->FindImage("inven_sword")->Render(Vector2(_gear[0].rc.GetCenter().x - 30, _gear[0].rc.GetCenter().y - 30));
		ImageManager::GetInstance()->FindImage("inven_bow")->Render(Vector2(_gear[5].rc.GetCenter().x - 30, _gear[5].rc.GetCenter().y - 30));

		//장비 변경
		if (!_player->getWeaponChange())
		{
			ImageManager::GetInstance()->FindImage("inven_weapon_1")->Render(Vector2(960, 205));
		}

		if (_player->getWeaponChange())
		{
			ImageManager::GetInstance()->FindImage("inven_weapon_2")->Render(Vector2(960, 205));
		}

		if (_isSwap) ImageManager::GetInstance()->FindImage("select")->Render(Vector2(_gear[_select].rc.left - 7, _gear[_select].rc.top - 7));
	}

	//쇼케이스
	if (_state == INVEN_STATE::SHOP)
	{
		ImageManager::GetInstance()->FindImage("showcase")->Render(Vector2(800, 160));

		for (int i = 0; i < SHOPSPACE; i++)
		{
			//D2DRenderer::GetInstance()->DrawRectangle(_shop[i].rc, D2DRenderer::DefaultBrush::White, 1.f);

			//아이템이 들어가면 이미지 띄우기
			if (_shop[i].item != nullptr)
			{
				_shop[i].item->getImg()->Render(Vector2(_shop[i].rc.GetCenter().x - _shop[i].item->getImg()->GetWidth() / 2, _shop[i].rc.GetCenter().y - _shop[i].item->getImg()->GetHeight() / 2));
				D2DRenderer::GetInstance()->RenderText(_shop[i].rc.right - _shop[i].countNum.length() * 20, _shop[i].rc.bottom - 20, to_wstring(_shop[i].count), 20, D2DRenderer::DefaultBrush::White);
			}

			//가격 적어두기
			if (i % 2 != 0)
				D2DRenderer::GetInstance()->RenderText(_shop[i].rc.GetCenter().x - 5, _shop[i].rc.GetCenter().y + 40, to_wstring(_shop[i - 1].totalPrice), 20, D2DRenderer::DefaultBrush::White);

			//선택 커서 띄어두기
			if (i == _select && _isSwap)
			{
				if (i % 2 == 0)
				{
					ImageManager::GetInstance()->FindImage("select")->Render(Vector2(_shop[i].rc.left - 5, _shop[i].rc.top - 5));
				}

				else
				{
					ImageManager::GetInstance()->FindImage("selectShowcase")->Render(Vector2(_shop[i].rc.left - 39, _shop[i].rc.top - 12));
				}
			}
		}

		//가격설정칸 활성상태에 따른 렌더 변화
		for (int i = 0; i < PRICESPACE; i++)
		{
			D2DRenderer::GetInstance()->RenderText(_firstPrice[i].rc.GetCenter().x - 4, _firstPrice[i].rc.GetCenter().y, to_wstring(_firstPrice[i].count), 10, D2DRenderer::DefaultBrush::Black);
			D2DRenderer::GetInstance()->RenderText(_secondPrice[i].rc.GetCenter().x - 4, _secondPrice[i].rc.GetCenter().y, to_wstring(_secondPrice[i].count), 10, D2DRenderer::DefaultBrush::Black);
			D2DRenderer::GetInstance()->RenderText(_thirdPrice[i].rc.GetCenter().x - 4, _thirdPrice[i].rc.GetCenter().y, to_wstring(_thirdPrice[i].count), 10, D2DRenderer::DefaultBrush::Black);
			D2DRenderer::GetInstance()->RenderText(_fourthPrice[i].rc.GetCenter().x - 4, _fourthPrice[i].rc.GetCenter().y, to_wstring(_fourthPrice[i].count), 10, D2DRenderer::DefaultBrush::Black);

			if (_isSwap)
			{
				if (i == _selectCount && _isSetPrice)
				{
					if (_select == 1)
					{
						//D2DRenderer::GetInstance()->DrawRectangle(_firstPrice[i].rc, D2DRenderer::DefaultBrush::Green, 1.f);
						ImageManager::GetInstance()->FindImage("price_cursor")->Render(Vector2(_firstPrice[i].rc.left + 2, _firstPrice[i].rc.top));
					}

					if (_select == 3)
					{
						//D2DRenderer::GetInstance()->DrawRectangle(_secondPrice[i].rc, D2DRenderer::DefaultBrush::Green, 1.f);
						ImageManager::GetInstance()->FindImage("price_cursor")->Render(Vector2(_secondPrice[i].rc.left + 2, _secondPrice[i].rc.top));
					}

					if (_select == 5)
					{
						//D2DRenderer::GetInstance()->DrawRectangle(_thirdPrice[i].rc, D2DRenderer::DefaultBrush::Green, 1.f);
						ImageManager::GetInstance()->FindImage("price_cursor")->Render(Vector2(_thirdPrice[i].rc.left + 2, _thirdPrice[i].rc.top));
					}

					if (_select == 7)
					{
						//D2DRenderer::GetInstance()->DrawRectangle(_fourthPrice[i].rc, D2DRenderer::DefaultBrush::Green, 1.f);
						ImageManager::GetInstance()->FindImage("price_cursor")->Render(Vector2(_fourthPrice[i].rc.left + 2, _fourthPrice[i].rc.top));
					}
				}				
			}
		}
	}
}
//===========================================↑↑인벤 상태에 따른 렌더↑↑===========================================//


//===========================================↓↓가격 설정하기↓↓===========================================//
void inventory::setCount(tagSetPrice price[PRICESPACE], wstring direction)
{
	if (direction == L"up")
	{
		price[_selectCount].count++;
		if (price[_selectCount].count > 9) price[_selectCount].count = 0;
	}

	if (direction == L"down")
	{
		price[_selectCount].count--;
		if (price[_selectCount].count < 0) price[_selectCount].count = 9;
	}
}
//===========================================↑↑가격 설정하기↑↑===========================================//


//===========================================↓↓가격 계산하기↓↓===========================================//
void inventory::setPrice(tagSetPrice setPrice[PRICESPACE], int select)
{
	for (int i = 0; i < PRICESPACE; i++)
	{
		setPrice[i].rc = RectMakePivot(Vector2(_shop[select + 1].rc.GetCenter().x + i * 20 - 40, _shop[select + 1].rc.GetCenter().y), Vector2(20, 30), Pivot::Center);
	}

	_shop[select].price = setPrice[0].count * 10000 + setPrice[1].count * 1000 + setPrice[2].count * 100 + setPrice[3].count * 10 + setPrice[4].count;
	_shop[select].totalPrice = _shop[select].count * _shop[select].price;

	if (_shop[select].item == nullptr) return;
	_shop[select].originalPrice = _shop[select].count * _shop[select].item->getPrice();
}
//===========================================↑↑가격 계산하기↑↑===========================================//


//===========================================↓↓가격 저장하기↓↓===========================================//
void inventory::savePrice(int select)
{
	if (_vPrice.size() < 0) return;

	//쇼케이스에 있는 아이템 인덱스 정보가 있으면 먼저 지우고
	for (int i = 0; i < _vPrice.size(); i++)
	{
		if (_vPrice[i].index == _shop[select].item->getIndex())
			_vPrice.erase(_vPrice.begin() + i);
	}

	//새롭게 인덱스 정보와 가격 정보를 벡터에 담는다
	tagSavePrice save;
	save.index = _shop[select].item->getIndex();
	save.price = _shop[select].price;

	_vPrice.push_back(save);
}
//===========================================↑↑가격 저장하기↑↑===========================================//


//===========================================↓↓가격 불러오기↓↓===========================================//
void inventory::loadPrice(tagSetPrice setPrice[PRICESPACE], int select)
{
	for (int i = 0; i < _vPrice.size(); ++i)
	{
		if (_shop[select].item == nullptr) return;

		//인덱스가 같은 가격만 불러오기
		if (_vPrice[i].index == _shop[select].item->getIndex())
		{
			setPrice[0].count = _vPrice[i].price / 10000;
			setPrice[1].count = (_vPrice[i].price - (setPrice[0].count * 10000)) / 1000;
			setPrice[2].count = (_vPrice[i].price - (setPrice[0].count * 10000 + setPrice[1].count * 1000)) / 100;
			setPrice[3].count = (_vPrice[i].price - (setPrice[0].count * 10000 + setPrice[1].count * 1000 + setPrice[2].count * 100)) / 10;
			setPrice[4].count = (_vPrice[i].price - (setPrice[0].count * 10000 + setPrice[1].count * 1000 + setPrice[2].count * 100 + setPrice[3].count * 10));
		}
	}
}
//===========================================↑↑가격 불러오기↑↑===========================================//


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

	_isSwap = false;
	_isSale = false;
	_isSelect = false;
	_isSetPrice = false;
	_state = INVEN_STATE::TEMP;
	_mirror = MIRROR_STATE::STOP;
	_select = 0;
}
//===========================================↑↑인벤 닫기↑↑===========================================//


//===========================================↓↓인벤 비우기↓↓===========================================//
void inventory::popInven()
{
	for (int i = 0; i < INVENSPACE; i++)
	{
		if (_inven[i].item == nullptr) continue;

		SAFE_DELETE(_inven[i].item);
		_inven[i].item = nullptr;
	}
}
//===========================================↑↑인벤 비우기↑↑===========================================//

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
//===========================================↑↑프레임 돌리기↑↑===========================================//