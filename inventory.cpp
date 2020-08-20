#include "stdafx.h"
#include "inventory.h"
#include "UI.h"
#include "player.h"

HRESULT inventory::init()
{
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
		_gear[i].number = _gear[i].count;
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
		_shop[i].totalPrice = 0;
		_shop[i].countNum = to_wstring(_shop[i].count);
		_shop[i].isPeople = false;
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
	_selectCount = 4;

	_isSwap = false;
	_isSale = false;
	_isSelect = false;
	_isInven = false;
	_isSetPrice = false;

	return S_OK;
}

void inventory::render()
{
	//인벤
	ImageManager::GetInstance()->FindImage("inven")->Render(Vector2(WINSIZEX / 2 - 600, WINSIZEY / 2 - 350));

	//인벤 상태에 따른 렌더
	renderInven();

	//펜던트
	ImageManager::GetInstance()->FindImage("pendant")->Render(Vector2(459, 565));

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

	//내가 선택한 아이템
	if (_selectItem.item != nullptr)
	{
		//D2DRenderer::GetInstance()->DrawRectangle(_selectItem.rc, D2DRenderer::DefaultBrush::Black, 2.f);
		ImageManager::GetInstance()->FindImage("inven_select")->Render(Vector2(_selectItem.rc.left, _selectItem.rc.top));
		_selectItem.item->getImg()->Render(Vector2(_selectItem.rc.GetCenter().x - _selectItem.item->getImg()->GetWidth() / 2, _selectItem.rc.GetCenter().y - _selectItem.item->getImg()->GetHeight() / 2));
		D2DRenderer::GetInstance()->RenderText(_selectItem.rc.right - _selectItem.number.length() * 20, _selectItem.rc.bottom - 20, to_wstring(_selectItem.count), 20, D2DRenderer::DefaultBrush::Black);
	}

	//선택테두리
	if (!_isSwap)
	{
		ImageManager::GetInstance()->FindImage("select")->Render(Vector2(_inven[_select].rc.left - 7, _inven[_select].rc.top - 7));
	}
	
	//아이템 이름 띄우기
	if (_inven[_select].item != nullptr && !_isSwap)
	{
		ImageManager::GetInstance()->FindImage("item_tag")->Render(Vector2(WINSIZEX / 2 - 350, 750));
		wstring name;
		name = _inven[_select].item->getName();
		D2DRenderer::GetInstance()->RenderText(WINSIZEX / 2 - name.length() * 13, 760, name, 30);
	}

	if (fullInven() >= 19)
	D2DRenderer::GetInstance()->RenderText(WINSIZEX / 2 - 50, WINSIZEY / 2, L"아이템 창이 가득 찼습니다.", 40, D2DRenderer::DefaultBrush::Red);
}

void inventory::update()
{
	_frameCount++;
	draw();

	if (_isSelect && !_isSwap) _selectItem.rc = RectMakePivot(Vector2(_inven[_select].rc.left - 5, _inven[_select].rc.top - 70), Vector2(60, 60), Pivot::LeftTop);
	if (_isSelect && _isSwap && _state == INVEN_STATE::NOTE) _selectItem.rc = RectMakePivot(Vector2(_gear[_select].rc.left - 5, _gear[_select].rc.top - 70), Vector2(60, 60), Pivot::LeftTop);
	if (_isSelect && _isSwap && _state == INVEN_STATE::SHOP) _selectItem.rc = RectMakePivot(Vector2(_shop[_select].rc.left - 5, _shop[_select].rc.top - 70), Vector2(60, 60), Pivot::LeftTop);

	if (_state == INVEN_STATE::SHOP)
	{
		setPrice(_firstPrice, 0);	//가격 정하기
		setPrice(_secondPrice, 2);
		setPrice(_thirdPrice, 4);
		setPrice(_fourthPrice, 6);
	}

	moveInven();					//인벤에서 돌아다니기
	selectItem();					//아이템 선택하기
	moveItem();						//아이템 인벤에서 옮기기
	useMirror();					//미러상태
}

void inventory::release()
{
}

//===========================================↓↓아이템 선택하기↓↓===========================================//
void inventory::selectItem()
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
				_selectItem.price = _inven[_select].price;
				_selectItem.count++;
				_inven[_select].count--;	

				//인벤 카운트가 0 이하가 되면 비워버린다
				if (_inven[_select].count <= 0)
				{
					_inven[_select].isFull = false;
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
				_selectNumber = -1;
				_selectGearNumber = -1;
				_selectShopNumber = _select;

				//선택한 쇼케이스가 비어있지 않다면
				if (_shop[_select].item != nullptr)
				{
					_isSelect = true;
					_selectItem.rc = RectMakePivot(Vector2(_shop[_select].rc.left - 5, _shop[_select].rc.top - 70), Vector2(60, 60), Pivot::LeftTop);
					_selectItem.item = _shop[_select].item;
					_selectItem.price = _shop[_select].price;
					_selectItem.count++;
					_shop[_select].count--;

					if (_shop[_select].count <= 0)
					{
						_shop[_select].item = nullptr;
						
						//쇼케이스가 비게 되면 가격 초기화
						for (int i = 0; i < PRICESPACE; i++)
						{
							if (_select == 0) _firstPrice[i].count = 0;
							if (_select == 2) _secondPrice[i].count = 0;
							if (_select == 4) _thirdPrice[i].count = 0;
							if (_select == 6) _fourthPrice[i].count = 0;
						}						
					}
				}

				//비어있다면
				else
				{
					//그중에서도 가격설정칸이면
					if (_select % 2 != 0 && !_isSetPrice)
					{
						if (_selectItem.item != nullptr) return;
						_selectCount = 4;
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
void inventory::moveItem()
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
						_selectItem.count = 0;
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
						_selectItem.item = nullptr;
						_selectItem.count = 0;
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
					_inven[_select].count = 0;
					_inven[_select].isFull = false;
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
						_selectItem.count = 0;
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

						for (int i = 0; i < _vPrice.size(); ++i)
						{
							if (_vPrice.size() < 0) continue;

							//저장된 인덱스 값과 아이템 인덱스가 같으면 가격도 같게
							if (_selectShopNumber == 0) loadPrice(_firstPrice, _selectShopNumber);
							if (_selectShopNumber == 2) loadPrice(_secondPrice, _selectShopNumber);
							if (_selectShopNumber == 4) loadPrice(_thirdPrice, _selectShopNumber);
							if (_selectShopNumber == 6) loadPrice(_fourthPrice, _selectShopNumber);
						}

						_selectItem.item = nullptr;
						_selectItem.count = 0;
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
							_selectItem.count = 0;
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
							_selectItem.count = 0;
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
					//아이템 배치
					if (_select % 2 == 0 && !_isSetPrice)
					{
						if (_shop[_select].item != nullptr) delete(_shop[_select].item);

						item* select;
						select = new item;
						select->init(_selectItem.item->getType());
						_shop[_select].item = select;
						_shop[_select].count = _selectItem.count;
						_selectItem.item = nullptr;
						_selectItem.count = 0;

						//설정했었던 아이템 가격 불러오기
						for (int i = 0; i < _vPrice.size(); ++i)
						{
							if (_vPrice.size() < 0) continue;

							//저장된 인덱스 값과 아이템 인덱스가 같으면 가격도 같게
							if (_select == 0) loadPrice(_firstPrice, _select);
							if (_select == 2) loadPrice(_secondPrice, _select);
							if (_select == 4) loadPrice(_thirdPrice, _select);
							if (_select == 6) loadPrice(_fourthPrice, _select);
						}
					}	

					//가격 설정하는 창이면
					if (_select % 2 != 0)
					{
						//아이템을 들고 왔다면
						if (_selectItem.item != nullptr)
						{
							if (_selectNumber >= 0)
							{
								if (_inven[_selectNumber].item == nullptr) _inven[_selectNumber].item = _selectItem.item;
								_inven[_selectNumber].count += _selectItem.count;
							}

							if (_selectShopNumber >= 0)
							{
								if (_shop[_selectShopNumber].item == nullptr) _shop[_selectShopNumber].item = _selectItem.item;
								_shop[_selectShopNumber].count += _selectItem.count;
							}
							_selectItem.item = nullptr;
							_selectItem.count = 0;
							_isSelect = false;

							//설정했었던 아이템 가격 불러오기
							for (int i = 0; i < _vPrice.size(); ++i)
							{
								if (_vPrice.size() < 0) continue;

								//저장된 인덱스 값과 아이템 인덱스가 같으면 가격도 같게
								if (_select == 0) loadPrice(_firstPrice, _select);
								if (_select == 2) loadPrice(_secondPrice, _select);
								if (_select == 4) loadPrice(_thirdPrice, _select);
								if (_select == 6) loadPrice(_fourthPrice, _select);

								if (_selectShopNumber == 0) loadPrice(_firstPrice, _selectShopNumber);
								if (_selectShopNumber == 2) loadPrice(_secondPrice, _selectShopNumber);
								if (_selectShopNumber == 4) loadPrice(_thirdPrice, _selectShopNumber);
								if (_selectShopNumber == 6) loadPrice(_fourthPrice, _selectShopNumber);

								_selectItem.item = nullptr;
								_selectItem.count = 0;
								_isSelect = false;
							}
						}		
						
						//가격 설정하던 중이면
						if (_isSetPrice)
						{
							//쇼케이스에 아이템이 있으면 가격 저장
							if (_shop[_select - 1].item != nullptr) savePrice(_select - 1);
																			
							_isSetPrice = false;
						}						
					}
					_isSelect = false;
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

								//쇼케이스 아이템이 빈 칸이면 카운트 초기화
								for (int i = 0; i < PRICESPACE; i++)
								{
									if (_select == 0) _firstPrice[i].count = 0;
									if (_select == 2) _secondPrice[i].count = 0;
									if (_select == 4) _thirdPrice[i].count = 0;
									if (_select == 6) _fourthPrice[i].count = 0;
								}								
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

							//쇼케이스가 비게 되면 가격 초기화
							for (int i = 0; i < PRICESPACE; i++)
							{
								if (_select == 0) _firstPrice[i].count = 0;
								if (_select == 2) _secondPrice[i].count = 0;
								if (_select == 4) _thirdPrice[i].count = 0;
								if (_select == 6) _fourthPrice[i].count = 0;
							}

							_selectItem.item = nullptr;
							_selectItem.count = 0;
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

							//쇼케이스가 비게 되면 가격 초기화
							for (int i = 0; i < PRICESPACE; i++)
							{
								if (_select == 0) _firstPrice[i].count = 0;
								if (_select == 2) _secondPrice[i].count = 0;
								if (_select == 4) _thirdPrice[i].count = 0;
								if (_select == 6) _fourthPrice[i].count = 0;
							}

							_selectItem.item = nullptr;
							_selectItem.count = 0;
							_isSelect = false;
						}		

						for (int i = 0; i < _vPrice.size(); ++i)
						{
							if (_vPrice.size() < 0) continue;

							//저장된 인덱스 값과 아이템 인덱스가 같으면 가격도 같게
							if (_selectShopNumber == 0) loadPrice(_firstPrice, _selectShopNumber);
							if (_selectShopNumber == 2) loadPrice(_secondPrice, _selectShopNumber);
							if (_selectShopNumber == 4) loadPrice(_thirdPrice, _selectShopNumber);
							if (_selectShopNumber == 6) loadPrice(_fourthPrice, _selectShopNumber);

							if (_select == 0) loadPrice(_firstPrice, _select);
							if (_select == 2) loadPrice(_secondPrice, _select);
							if (_select == 4) loadPrice(_thirdPrice, _select);
							if (_select == 6) loadPrice(_fourthPrice, _select);
						}
						
					}
				}
			}
		}
	}
}
//===========================================↑↑아이템 인벤에서 옮기기↑↑===========================================//


//===========================================↓↓포션 만들기↓↓===========================================//
void inventory::makePotion(int selectPotionIndex, int makeCount, int itemIndex, int itemTotlaCount, int totalGold)
{
	int maxCount = 0;
	bool isEnd = false;

	if (_gold >= totalGold) _gold -= totalGold;
	else return;

	for (int i = 0; i < INVENSPACE; i++)
	{
		if (_inven[i].item->getIndex() == itemIndex)
		{
			if (_inven[i].count >= itemTotlaCount)
			{
				_inven[i].count -= itemTotlaCount;

				isEnd = true;
				break;
			}				

			if (_inven[i].count < itemTotlaCount)
			{
				maxCount += _inven[i].count;

				if (maxCount >= itemTotlaCount)
				{
					maxCount -= itemTotlaCount;
					_inven[i].count = maxCount;

					isEnd = true;
				}				
			}
		}
	}

	for (int i = 0; i < INVENSPACE; i++)
	{
		if (_inven[i].count <= 0)
		{
			_inven[i].isFull = false;
			_inven[i].item = nullptr;
		}
	}


	if (isEnd)
	{
		for (int i = 0; i < makeCount; ++i)
		{
			if (fullInven() >= 19)
				break;

			item* temp = new item;
			temp->init(selectPotionIndex);

			putItem(temp);
		}
	}
}
//===========================================↑↑포션 만들기↑↑===========================================//