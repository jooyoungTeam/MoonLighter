#include "stdafx.h"
#include "inventory.h"
#include "UI.h"
#include "player.h"
#include "itemManager.h"

HRESULT inventory::init()
{
	ImageManager::GetInstance()->AddImage("bagMirror", L"image/UI/bagMirror.png");
	ImageManager::GetInstance()->AddFrameImage("mirror_stay", L"image/UI/mirror_stay.png", 11, 1);
	ImageManager::GetInstance()->AddFrameImage("mirror_active", L"image/UI/mirror_active.png", 14, 1);
	ImageManager::GetInstance()->AddImage("inven", L"Image/UI/inventory.png");
	ImageManager::GetInstance()->AddImage("invenSpace", L"image/UI/invenSpace.png");
	ImageManager::GetInstance()->AddImage("select", L"image/UI/invenslot.png");
	ImageManager::GetInstance()->AddImage("pendant", L"image/UI/pendant.png");
	ImageManager::GetInstance()->AddImage("empty_weapon", L"image/UI/empty_sword.png");
	ImageManager::GetInstance()->AddImage("empty_helmet", L"image/UI/empty_helmet.png");
	ImageManager::GetInstance()->AddImage("empty_top", L"image/UI/empty_top.png");
	ImageManager::GetInstance()->AddImage("empty_shoes", L"image/UI/empty_shoes.png");
	ImageManager::GetInstance()->AddImage("inven_weapon_1", L"Image/UI/Inven_weapon_1.png");
	ImageManager::GetInstance()->AddImage("inven_weapon_2", L"Image/UI/Inven_weapon_2.png");
	ImageManager::GetInstance()->AddImage("empty_potion", L"Image/UI/empty_potion.png");
	ImageManager::GetInstance()->AddImage("inven_select", L"Image/UI/inven_select.png");
	ImageManager::GetInstance()->AddFrameImage("mirror_ball", L"Image/UI/mirror_empty.png", 10, 1);
	ImageManager::GetInstance()->AddFrameImage("mirror_sale", L"Image/UI/inven_sale.png", 29, 1);
	ImageManager::GetInstance()->AddFrameImage("inven_sale", L"Image/UI/mirror_sale.png", 8, 1);
	ImageManager::GetInstance()->AddImage("showcase", L"Image/UI/showcase.png");

	//인벤창
	for (int i = 0; i < INVENSPACE; i++)
	{
		_inven[i].rc = FloatRect(Vector2(310 + i * 82, 205), Vector2(60, 60), Pivot::LeftTop);

		if (i > 4)
		{
			_inven[i].rc = FloatRect(Vector2(310 + i * 82 - 410, 300), Vector2(60, 60), Pivot::LeftTop);
		}

		if (i > 9)
		{
			_inven[i].rc = FloatRect(Vector2(310 + i * 82 - 820, 390), Vector2(60, 60), Pivot::LeftTop);
		}

		if (i > 14)
		{
			_inven[i].rc = FloatRect(Vector2(310 + i * 82 - 1230, 480), Vector2(60, 60), Pivot::LeftTop);
		}

		if (i == 20)
		{
			_inven[i].rc = FloatRect(Vector2(310 + i * 82 - 1640, 610), Vector2(60, 60), Pivot::LeftTop);
		}

		if (i == 21)
		{
			_inven[i].rc = FloatRect(Vector2(484, 585), Vector2(60, 60), Pivot::LeftTop);
		}

		/*if (i == 22)
		{
			_inven[i].rc = FloatRect(Vector2(615, 585), Vector2(60, 60), Pivot::LeftTop);
		}*/

		_inven[i].item = nullptr;
		_inven[i].count = 0;
		_inven[i].number = _inven[i].count;
	}
	
	//장비창
	for (int i = 0; i < GEARSPACE; i++)
	{
		if (i == 0)
		{
			_gear[i].rc = RectMakePivot(Vector2(920, 205), Vector2(60, 60), Pivot::LeftTop);
		}

		if (i >= 1)
		{
			_gear[i].rc = RectMakePivot(Vector2(820, 335 + i * 80 - 115), Vector2(60, 60), Pivot::LeftTop);
		}

		if (i > 4)
		{
			_gear[i].rc = RectMakePivot(Vector2(1120, 205), Vector2(60, 60), Pivot::LeftTop);
		}

		_gear[i].item = nullptr;
	}

	//쇼케이스
	for (int i = 0; i < SHOPSPACE; i++)
	{
		if (i % 2 == 0)
		{
			if (i < 4)
			_shop[i].rc = RectMakePivot(Vector2(950, 217 + i * 142), Vector2(60, 60), Pivot::Center);
			if (i >= 4)
			_shop[i].rc = RectMakePivot(Vector2(1252, 434 + i * 142 - 785), Vector2(60, 60), Pivot::Center);
		}

		else
		{
			if (i < 4)
			_shop[i].rc = RectMakePivot(Vector2(950, 175 + i * 142), Vector2(180, 60), Pivot::Center);
			if (i >= 4)
			_shop[i].rc = RectMakePivot(Vector2(1252, 392 + i * 142 - 785), Vector2(180, 60), Pivot::Center);
		}	
	}

	_mirrorImg = ImageManager::GetInstance()->FindImage("bagMirror");
	_saleImg = ImageManager::GetInstance()->FindImage("mirror_ball");

	//인벤 상태
	_state = INVEN_STATE::TEMP;
	//미러 상태
	_mirror = MIRROR_STATE::STOP;

	_mirrorFrameX = 0;
	_mirrorBallFrameX = 0;
	_saleFrameX = 0;

	_gold = 0;
	_select = 0;
	_isSwap = false;
	_isSale = false;
	_isSelect = false;

	return S_OK;
}

void inventory::render()
{
	//인벤
	ImageManager::GetInstance()->FindImage("inven")->Render(Vector2(WINSIZEX / 2 - 600, WINSIZEY / 2 - 350));

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

	//펜던트
	ImageManager::GetInstance()->FindImage("pendant")->Render(Vector2(459, 565));

	//장비창
	if (_state == INVEN_STATE::NOTE)
	{
		//장비 변경
		//플레이어 불값false
		ImageManager::GetInstance()->FindImage("inven_weapon_1")->Render(Vector2(960, 205));
		//플레이어 불값true
		//ImageManager::GetInstance()->FindImage("inven_weapon_2")->Render(Vector2(960, 205));

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
	}

	//쇼케이스
	if (_state == INVEN_STATE::SHOP)
	{
		ImageManager::GetInstance()->FindImage("showcase")->Render(Vector2(800, 160));

		for (int i = 0; i < SHOPSPACE; i++)
		{
			D2DRenderer::GetInstance()->DrawRectangle(_shop[i].rc, D2DRenderer::DefaultBrush::Green, 1.f);

			if (_shop[i].item != nullptr)
			{
				_shop[i].item->getImg()->Render(Vector2(_shop[i].rc.GetCenter().x - _shop[i].item->getImg()->GetWidth() / 2, _shop[i].rc.GetCenter().y - _shop[i].item->getImg()->GetHeight() / 2));
				D2DRenderer::GetInstance()->RenderText(_shop[i].rc.right - _shop[i].countNum.length() * 20, _shop[i].rc.bottom - 20, to_wstring(_shop[i].count), 20, D2DRenderer::DefaultBrush::White);
			}		

			if (i == _select && _isSwap)
			{
				if (i % 2 == 0)
				{
					ImageManager::GetInstance()->FindImage("select")->Render(Vector2(_shop[i].rc.left - 5, _shop[i].rc.top - 5));
				}

				else
				{
					//ImageManager::GetInstance()->FindImage("select")->Render(Vector2(_shop[i].rc.GetCenter().x - 35, _shop[i].rc.GetCenter().y - 35));
				}
			}
		}		
	}

	//선택테두리
	if (!_isSwap) ImageManager::GetInstance()->FindImage("select")->Render(Vector2(_inven[_select].rc.left - 7, _inven[_select].rc.top - 7));

	//미러
	if (_mirror == MIRROR_STATE::STOP) _mirrorImg->Render(Vector2(_inven[20].rc.left - 130, _inven[20].rc.top - 65));
	else _mirrorImg->FrameRender(Vector2(_inven[20].rc.left - 5, _inven[20].rc.top + 70), _mirrorFrameX, 0);

	//아이템을 팔겠다면
	if (_isSale)
	{	
		if (_isSelect)
		{
			//인벤에서 팔기
			_saleImg->FrameRender(Vector2(_inven[20].rc.GetCenter().x - 5, _inven[20].rc.GetCenter().y), _mirrorBallFrameX, 0);
			ImageManager::GetInstance()->FindImage("inven_sale")->FrameRender(Vector2(_selectItem.rc.GetCenter().x, _selectItem.rc.GetCenter().y), _saleFrameX, 0);
		}

		else
		{
			//미러 안
			_saleImg->FrameRender(Vector2(_inven[_select].rc.GetCenter().x - 3, _inven[_select].rc.GetCenter().y - 3), _mirrorBallFrameX, 0);
		}
	}

	for (int i = 0; i < PRICESPACE; i++)
	{
		if(_isSetPrice)
		D2DRenderer::GetInstance()->DrawRectangle(_price[i].rc, D2DRenderer::DefaultBrush::Green, 1.f);
	}

	//내가 선택한 아이템
	if (_selectItem.item != nullptr)
	{
		//D2DRenderer::GetInstance()->DrawRectangle(_selectItem.rc, D2DRenderer::DefaultBrush::Black, 2.f);
		ImageManager::GetInstance()->FindImage("inven_select")->Render(Vector2(_selectItem.rc.left, _selectItem.rc.top));
		_selectItem.item->getImg()->Render(Vector2(_selectItem.rc.GetCenter().x - _selectItem.item->getImg()->GetWidth() / 2, _selectItem.rc.GetCenter().y - _selectItem.item->getImg()->GetHeight() / 2));
		D2DRenderer::GetInstance()->RenderText(_selectItem.rc.right - _selectItem.number.length() * 20, _selectItem.rc.bottom - 20, to_wstring(_selectItem.count), 20, D2DRenderer::DefaultBrush::Black);
	}
}

void inventory::update()
{
	_frameCount++;
	draw();

	if (_isSelect && !_isSwap) _selectItem.rc = RectMakePivot(Vector2(_inven[_select].rc.left - 5, _inven[_select].rc.top - 70), Vector2(60, 60), Pivot::LeftTop);
	if (_isSelect && _isSwap && _state == INVEN_STATE::NOTE) _selectItem.rc = RectMakePivot(Vector2(_gear[_select].rc.left - 5, _gear[_select].rc.top - 70), Vector2(60, 60), Pivot::LeftTop);
	if (_isSelect && _isSwap && _state == INVEN_STATE::SHOP) _selectItem.rc = RectMakePivot(Vector2(_shop[_select].rc.left - 5, _shop[_select].rc.top - 70), Vector2(60, 60), Pivot::LeftTop);

	//움직임
	//if(!_isSetPrice)
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
					_select -= 4;
					if (_select < 0)
					{
						_isSwap = false;
						if (_select == -4 || _select == -3) _select = 4;
						if (_select == -1 || _select == -2) _select = 19;
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
				_select--;
				if (_state == INVEN_STATE::NOTE)
				{
					if (_select < 0) _select = 4;
				}

				if (_state == INVEN_STATE::SHOP)
				{
					if (_select < 0) _select = 3;
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
				_select++;
				if (_state == INVEN_STATE::NOTE)
				{
					if (_select > 4) _select = 0;
				}

				if (_state == INVEN_STATE::SHOP)
				{
					if (_select > 7) _select = 4;
				}
			}
		}
	}

	if (_isSetPrice)
	{
		for (int i = 0; i < PRICESPACE; i++)
		{
			_price[i].rc = RectMakePivot(Vector2(_shop[_select].rc.GetCenter().x + i * 20 - 60, _shop[_select].rc.GetCenter().y), Vector2(20, 30), Pivot::Center);
		}
	}

	selectInvenItem();
	moveInvenItem();
	useMirror();	
}

void inventory::release()
{
}

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


//===========================================↓↓아이템 선택하기↓↓===========================================//
void inventory::selectInvenItem()
{
	if (!_isSelect && KEYMANAGER->isOnceKeyDown('J'))
	{
		_selectItem.count = 0;

		if (!_isSwap)
		{
			_selectNumber = _select;
			_selectGearNumber = -1;
			_selectShopNumber = -1;

			if (_select == 21) return;

			//미러를 선택했다면
			if (_select == 20 && _selectItem.item == nullptr)
			{
				_isSelect = true;
				_isSale = true;
				_mirrorBallFrameX = 0;
				_saleImg = ImageManager::GetInstance()->FindImage("mirror_ball");
				_selectItem.rc = RectMakePivot(Vector2(_inven[_select].rc.left - 5, _inven[_select].rc.top - 70), Vector2(60, 60), Pivot::LeftTop);
			}

			//선택한 인벤창이 비어있지 않다면
			if (_inven[_select].item != nullptr)
			{
				_isSelect = true;
				_selectItem.rc = RectMakePivot(Vector2(_inven[_select].rc.left - 5, _inven[_select].rc.top - 70), Vector2(60, 60), Pivot::LeftTop);
				_selectItem.item = _inven[_select].item;
				_selectItem.count++;
				_inven[_select].count--;	

				//인벤 카운트가 0 이하가 되면 비워버린다
				if (_inven[_select].count <= 0)
				{
					_inven[_select].item = nullptr;
				}
			}
		}

		else
		{
			//선택한 장비창이 비어있지 않다면
			if (_gear[_select].item != nullptr && _state == INVEN_STATE::NOTE)
			{
				_selectNumber = -1;
				_selectGearNumber = _select;
				_selectShopNumber = -1;

				_isSelect = true;
				_selectItem.rc = RectMakePivot(Vector2(_gear[_select].rc.left - 5, _gear[_select].rc.top - 70), Vector2(60, 60), Pivot::LeftTop);
				_selectItem.item = _gear[_select].item;
				_selectItem.count++;
				_gear[_select].count--;

				//장비창 카운트가 0 이하가 되면 비워버린다
				if (_gear[_select].count <= 0) _gear[_select].item = nullptr;
			}

			if (_state == INVEN_STATE::SHOP)
			{
				//선택한 쇼케이스가 비어있지 않다면
				if (_shop[_select].item != nullptr)
				{
					_selectNumber = -1;
					_selectGearNumber = -1;
					_selectShopNumber = _select;

					_isSelect = true;
					_selectItem.rc = RectMakePivot(Vector2(_shop[_select].rc.left - 5, _shop[_select].rc.top - 70), Vector2(60, 60), Pivot::LeftTop);
					_selectItem.item = _shop[_select].item;
					_selectItem.count++;
					_shop[_select].count--;

					if (_shop[_select].count <= 0)
					{
						_shop[_select].item = nullptr;
					}
				}

				//비어있다면
				else
				{
					//그중에서도 가격설정칸이면
					if (_select % 2 != 0 && !_isSetPrice)
					{
						if (_selectItem.item != nullptr) return;
						_isSelect = true;
						_isSetPrice = true;
					}
				}				
			}			
		}		
	}
}
//===========================================↑↑아이템 선택하기↑↑===========================================//


//===========================================↓↓아이템 인벤에서 옮기기↓↓===========================================//
void inventory::moveInvenItem()
{
	if (_isSelect && KEYMANAGER->isOnceKeyDown('J'))
	{
		if (!_isSwap)
		{
			if (_select == 21) return;

			//선택한 인벤이 비어있으면
			if (_inven[_select].item == nullptr)
			{
				if (_selectItem.item != nullptr)
				{
					//인벤에서 아이템을 가져와 판매하겠다면
					if (_select == 20 && _selectNumber != 20)
					{
						_mirror = MIRROR_STATE::ACTIVE;
						_mirrorFrameX = 0;
						_mirrorImg = ImageManager::GetInstance()->FindImage("mirror_active");
						_gold += _selectItem.item->getPrice() * _selectItem.count;
						_inven[_select].item = nullptr;
						_selectItem.item = nullptr;
						_isSelect = false;
					}

					else
					{
						if (_inven[_select].item != nullptr) delete(_inven[_select].item);

						item* select;
						select = new item;
						select->init(_selectItem.item->getType());

						_inven[_select].item = select;
						_inven[_select].count = _selectItem.count;
						_selectItem.count = 0;
						_selectItem.item = nullptr;
						_isSelect = false;
					}
				}

				else
				{
					_isSelect = false;
					_isSale = false;
				}
			}

			//비어있지 않으면
			else
			{
				//인벤에서 아이템을 선택해 판매하겠다면
				if (_isSale)
				{
					_mirrorBallFrameX = 0;
					_saleImg = ImageManager::GetInstance()->FindImage("mirror_sale");
					_gold += _inven[_select].item->getPrice() * _inven[_select].count;
					_inven[_select].item = nullptr;
					_isSelect = false;
					return;
				}

				//선택한 인벤의 아이템 인덱스가 들고 있는 아이템 인덱스와 같지 않으면
				if (_inven[_select].item->getIndex() != _selectItem.item->getIndex())
				{
					//아이템을 가지고 왔던 인벤 창이 비어있다면
					if (_selectNumber >= 0 && _inven[_selectNumber].item == nullptr)
					{
						_inven[_selectNumber].item = _inven[_select].item;
						_inven[_selectNumber].count = _inven[_select].count;
						_inven[_selectNumber].price = _inven[_select].price;
						_inven[_select].item = _selectItem.item;
						_inven[_select].count = _selectItem.count;
						_inven[_select].price = _selectItem.price;
						_selectItem.item = nullptr;
						_isSelect = false;
					}

					//아이템을 가지고 왔던 쇼케이스 창이 비어있다면
					if (_selectShopNumber >= 0 && _shop[_selectShopNumber].item == nullptr)
					{
						_shop[_selectShopNumber].item = _inven[_select].item;
						_shop[_selectShopNumber].count = _inven[_select].count;
						_shop[_selectShopNumber].price = _inven[_select].price;
						_inven[_select].item = _selectItem.item;
						_inven[_select].count = _selectItem.count;
						_inven[_select].price = _selectItem.price;
						_selectItem.item = nullptr;
						_isSelect = false;
					}
				}

				//인덱스가 같으면
				else if (_inven[_select].item->getIndex() == _selectItem.item->getIndex())
				{
					//선택했을 때의 인벤 칸에서 변화가 없으면
					if (_selectNumber == _select)
					{
						_selectItem.count++;
						_inven[_select].count--;

						//인벤 카운트가 0이 되면 비워라
						if (_inven[_select].count <= 0)
						{
							_inven[_select].count = 0;
							_inven[_select].item = nullptr;
						}

						//선택 카운트가 최대라는 건 인벤에서 다 가져왔다는 뜻이니까
						//더 가져오려고 하면 다시 돌려놓아라
						if (_selectItem.count > _selectItem.item->getLimit())
						{
							_inven[_select].item = _selectItem.item;
							_inven[_select].count = _selectItem.count;
							_selectItem.item = nullptr;
							_isSelect = false;
						}						
					}

					//변화가 있으면
					else
					{
						//인벤 카운트가 한계치를 넘으면
						if (_inven[_select].count + _selectItem.count > _inven[_select].item->getLimit())
						{
							_selectItem.count = (_inven[_select].count + _selectItem.count) - _inven[_select].item->getLimit();
							_inven[_select].count = _inven[_select].item->getLimit();
						}

						//넘지 않는다면
						else
						{
							_inven[_select].count = _inven[_select].count + _selectItem.count;
							_selectItem.count = 0;
						}

						//선택 아이템 카운트가 0 이하가 되면 비워라
						if (_selectItem.count <= 0)
						{
							_selectItem.item = nullptr;
							_isSelect = false;
						}
					}
				}
			}
		}

		if (_isSwap)
		{
			if (_isSale) return;

			//장비창에 옮기기
			if (_state == INVEN_STATE::NOTE)
			{
				//포션칸
				if (_select == 4)
				{
					//포션이면
					if (_selectItem.item->getIndex() > 1000)
					{
						//장비칸이 비어있으면
						if (_gear[_select].item == nullptr)
						{
							if (_gear[_select].item != nullptr) delete(_gear[_select].item);

							item* select;
							select = new item;
							select->init(_selectItem.item->getType());

							_gear[_select].item = select;
							_gear[_select].count = _selectItem.count;
							_selectItem.item = nullptr;
							_isSelect = false;
						}

						//비어있지 않으면
						else
						{
							//장비창에서 그대로 아이템을 챙기고 있는 상태
							if (_selectGearNumber == _select)
							{
								_selectItem.count++;
								_gear[_select].count--;

								//장비창에 있는 아이템을 모두 들었다면
								if (_gear[_select].count <= 0) _gear[_select].item = nullptr;

								//장비창에 있는 포션을 다 챙겨서 내가 다 들어버리면 다시 돌려놓기
								if (_selectItem.count > _selectItem.item->getLimit())
								{
									_gear[_select].item = _selectItem.item;
									_gear[_select].count = _selectItem.count;
								}
							}

							//인벤에서 가져온 아이템이라면
							else
							{
								_selectItem.count--;
								_gear[_select].count++;

								//아이템 한계치를 넘으면
								if (_gear[_select].count + _selectItem.count > _gear[_select].item->getLimit())
								{
									_selectItem.count = (_gear[_select].count + _selectItem.count) - _gear[_select].item->getLimit();
									_gear[_select].count = _gear[_select].item->getLimit();
								}

								//다 내려놨다면
								if (_selectItem.count <= 0)
								{
									_selectItem.count = 0;
									_selectItem.item = nullptr;
									_isSelect = false;
								}
							}
						}
					}
				}
			}

			//쇼케이스에 옮기기
			if (_state == INVEN_STATE::SHOP)
			{
				//쇼케이스가 비어있으면
				if (_shop[_select].item == nullptr)
				{
					//아이템 가격 설정
					if (_select % 2 != 0 && _isSetPrice)
					{
						if (_selectItem.item != nullptr) return;
						_isSelect = false;
						_isSetPrice = false;
					}

					//아이템 배치
					if (_select % 2 == 0)
					{
						if (_shop[_select].item != nullptr) delete(_shop[_select].item);

						item* select;
						select = new item;
						select->init(_selectItem.item->getType());

						_shop[_select].item = select;
						_shop[_select].count = _selectItem.count;
						_selectItem.item = nullptr;
						_isSelect = false;
					}								
				}

				//비어있지 않으면
				else
				{
					//아이템 인덱스가 같으면
					if (_shop[_select].item->getIndex() == _selectItem.item->getIndex())
					{
						//쇼케이스에서 그대로 아이템을 챙기고 있는 상태
						if (_selectShopNumber == _select)
						{
							_selectItem.count++;
							_shop[_select].count--;

							//쇼케이스에 있는 아이템을 모두 들었다면
							if (_shop[_select].count <= 0)
							{
								_shop[_select].count = 0;
								_shop[_select].item = nullptr;
							}

							//쇼케이스 아이템을 다 들어버리면 다시 돌려놓기
							if (_selectItem.count > _selectItem.item->getLimit())
							{
								_shop[_select].item = _selectItem.item;
								_shop[_select].count = _selectItem.count;
							}
						}

						//자리 이동이 있었음
						else
						{
							//아이템 한계치를 넘으면
							if (_shop[_select].count + _selectItem.count > _shop[_select].item->getLimit())
							{
								_selectItem.count = (_shop[_select].count + _selectItem.count) - _shop[_select].item->getLimit();
								_shop[_select].count = _shop[_select].item->getLimit();
							}

							//넘지 않는다면
							else
							{
								_shop[_select].count = _shop[_select].count + _selectItem.count;
								_selectItem.count = 0;
							}

							//다 내려놨다면
							if (_selectItem.count <= 0)
							{
								_selectItem.item = nullptr;
								_isSelect = false;
							}
						}
					}					

					//아이템 인덱스가 다르면
					else
					{
						//인벤에서 가져옴
						if (_selectNumber >= 0 && _inven[_selectNumber].item == nullptr)
						{
							_inven[_selectNumber].item = _shop[_select].item;
							_inven[_selectNumber].count = _shop[_select].count;
							_inven[_selectNumber].price = _shop[_select].price;
							_shop[_select].item = _selectItem.item;
							_shop[_select].count = _selectItem.count;
							_shop[_select].price = _selectItem.price;
							_selectItem.item = nullptr;
							_isSelect = false;
						}

						//쇼케이스에서 가져옴
						if (_selectShopNumber >= 0 && _shop[_selectShopNumber].item == nullptr)
						{
							_shop[_selectShopNumber].item = _shop[_select].item;
							_shop[_selectShopNumber].count = _shop[_select].count;
							_shop[_selectShopNumber].price = _shop[_select].price;
							_shop[_select].item = _selectItem.item;
							_shop[_select].count = _selectItem.count;
							_shop[_select].price = _selectItem.price;
							_selectItem.item = nullptr;
							_isSelect = false;
						}
					}
				}
			}
		}
	}
}
//===========================================↑↑아이템 인벤에서 옮기기↑↑===========================================//


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
				if(!_isSelect) _isSale = false;				
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
