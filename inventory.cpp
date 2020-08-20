#include "stdafx.h"
#include "inventory.h"
#include "UI.h"
#include "player.h"

HRESULT inventory::init()
{
	//�κ�â
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
	
	//���â
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

	//�����̽�
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

	//�κ� ����
	_state = INVEN_STATE::TEMP;
	//�̷� ����
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
	//�κ�
	ImageManager::GetInstance()->FindImage("inven")->Render(Vector2(WINSIZEX / 2 - 600, WINSIZEY / 2 - 350));

	//�κ� ���¿� ���� ����
	renderInven();

	//���Ʈ
	ImageManager::GetInstance()->FindImage("pendant")->Render(Vector2(459, 565));

	//�̷�
	if (_mirror == MIRROR_STATE::STOP) _mirrorImg->Render(Vector2(_inven[20].rc.left - 130, _inven[20].rc.top - 65));
	else _mirrorImg->FrameRender(Vector2(_inven[20].rc.left - 5, _inven[20].rc.top + 70), _mirrorFrameX, 0);

	//�������� �Ȱڴٸ�
	if (_isSale)
	{	
		if (_isSelect)
		{
			//�κ����� �ȱ�
			_saleImg->FrameRender(Vector2(_inven[20].rc.GetCenter().x - 5, _inven[20].rc.GetCenter().y), _mirrorBallFrameX, 0);
			ImageManager::GetInstance()->FindImage("inven_sale")->FrameRender(Vector2(_selectItem.rc.GetCenter().x, _selectItem.rc.GetCenter().y), _saleFrameX, 0);
		}

		else
		{
			//�̷� ��
			_saleImg->FrameRender(Vector2(_inven[_select].rc.GetCenter().x - 3, _inven[_select].rc.GetCenter().y - 3), _mirrorBallFrameX, 0);
		}
	}

	//���� ������ ������
	if (_selectItem.item != nullptr)
	{
		//D2DRenderer::GetInstance()->DrawRectangle(_selectItem.rc, D2DRenderer::DefaultBrush::Black, 2.f);
		ImageManager::GetInstance()->FindImage("inven_select")->Render(Vector2(_selectItem.rc.left, _selectItem.rc.top));
		_selectItem.item->getImg()->Render(Vector2(_selectItem.rc.GetCenter().x - _selectItem.item->getImg()->GetWidth() / 2, _selectItem.rc.GetCenter().y - _selectItem.item->getImg()->GetHeight() / 2));
		D2DRenderer::GetInstance()->RenderText(_selectItem.rc.right - _selectItem.number.length() * 20, _selectItem.rc.bottom - 20, to_wstring(_selectItem.count), 20, D2DRenderer::DefaultBrush::Black);
	}

	//�����׵θ�
	if (!_isSwap)
	{
		ImageManager::GetInstance()->FindImage("select")->Render(Vector2(_inven[_select].rc.left - 7, _inven[_select].rc.top - 7));
	}
	
	//������ �̸� ����
	if (_inven[_select].item != nullptr && !_isSwap)
	{
		ImageManager::GetInstance()->FindImage("item_tag")->Render(Vector2(WINSIZEX / 2 - 350, 750));
		wstring name;
		name = _inven[_select].item->getName();
		D2DRenderer::GetInstance()->RenderText(WINSIZEX / 2 - name.length() * 13, 760, name, 30);
	}

	if (fullInven() >= 19)
	D2DRenderer::GetInstance()->RenderText(WINSIZEX / 2 - 50, WINSIZEY / 2, L"������ â�� ���� á���ϴ�.", 40, D2DRenderer::DefaultBrush::Red);
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
		setPrice(_firstPrice, 0);	//���� ���ϱ�
		setPrice(_secondPrice, 2);
		setPrice(_thirdPrice, 4);
		setPrice(_fourthPrice, 6);
	}

	moveInven();					//�κ����� ���ƴٴϱ�
	selectItem();					//������ �����ϱ�
	moveItem();						//������ �κ����� �ű��
	useMirror();					//�̷�����
}

void inventory::release()
{
}

//===========================================�������� �����ϱ���===========================================//
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

			//�̷��� �����ߴٸ�
			if (_select == 20 && _selectItem.item == nullptr)
			{
				_isSelect = true;
				_isSale = true;
				_mirrorBallFrameX = 0;
				_saleImg = ImageManager::GetInstance()->FindImage("mirror_ball");
				_selectItem.rc = RectMakePivot(Vector2(_inven[_select].rc.left - 5, _inven[_select].rc.top - 70), Vector2(60, 60), Pivot::LeftTop);
			}

			//������ �κ�â�� ������� �ʴٸ�
			if (_inven[_select].item != nullptr)
			{
				_isSelect = true;
				_selectItem.rc = RectMakePivot(Vector2(_inven[_select].rc.left - 5, _inven[_select].rc.top - 70), Vector2(60, 60), Pivot::LeftTop);
				_selectItem.item = _inven[_select].item;
				_selectItem.price = _inven[_select].price;
				_selectItem.count++;
				_inven[_select].count--;	

				//�κ� ī��Ʈ�� 0 ���ϰ� �Ǹ� ���������
				if (_inven[_select].count <= 0)
				{
					_inven[_select].isFull = false;
					_inven[_select].item = nullptr;
				}
			}
		}

		else
		{
			//������ ���â�� ������� �ʴٸ�
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

				//���â ī��Ʈ�� 0 ���ϰ� �Ǹ� ���������
				if (_gear[_select].count <= 0) _gear[_select].item = nullptr;
			}

			if (_state == INVEN_STATE::SHOP)
			{
				_selectNumber = -1;
				_selectGearNumber = -1;
				_selectShopNumber = _select;

				//������ �����̽��� ������� �ʴٸ�
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
						
						//�����̽��� ��� �Ǹ� ���� �ʱ�ȭ
						for (int i = 0; i < PRICESPACE; i++)
						{
							if (_select == 0) _firstPrice[i].count = 0;
							if (_select == 2) _secondPrice[i].count = 0;
							if (_select == 4) _thirdPrice[i].count = 0;
							if (_select == 6) _fourthPrice[i].count = 0;
						}						
					}
				}

				//����ִٸ�
				else
				{
					//���߿����� ���ݼ���ĭ�̸�
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
//===========================================�������� �����ϱ���===========================================//


//===========================================�������� �κ����� �ű����===========================================//
void inventory::moveItem()
{
	if (_isSelect && KEYMANAGER->isOnceKeyDown('J'))
	{
		if (!_isSwap)
		{
			if (_select == 21) return;

			//������ �κ��� ���������
			if (_inven[_select].item == nullptr)
			{
				if (_selectItem.item != nullptr)
				{
					//�κ����� �������� ������ �Ǹ��ϰڴٸ�
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

			//������� ������
			else
			{
				//�κ����� �������� ������ �Ǹ��ϰڴٸ�
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

				//������ �κ��� ������ �ε����� ��� �ִ� ������ �ε����� ���� ������
				if (_inven[_select].item->getIndex() != _selectItem.item->getIndex())
				{
					//�������� ������ �Դ� �κ� â�� ����ִٸ�
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

					//�������� ������ �Դ� �����̽� â�� ����ִٸ�
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

							//����� �ε��� ���� ������ �ε����� ������ ���ݵ� ����
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

				//�ε����� ������
				else if (_inven[_select].item->getIndex() == _selectItem.item->getIndex())
				{
					//�������� ���� �κ� ĭ���� ��ȭ�� ������
					if (_selectNumber == _select)
					{
						_selectItem.count++;
						_inven[_select].count--;

						//�κ� ī��Ʈ�� 0�� �Ǹ� �����
						if (_inven[_select].count <= 0)
						{
							_inven[_select].count = 0;
							_inven[_select].item = nullptr;
						}

						//���� ī��Ʈ�� �ִ��� �� �κ����� �� �����Դٴ� ���̴ϱ�
						//�� ���������� �ϸ� �ٽ� �������ƶ�
						if (_selectItem.count > _selectItem.item->getLimit())
						{
							_inven[_select].item = _selectItem.item;
							_inven[_select].count = _selectItem.count;
							_selectItem.item = nullptr;
							_selectItem.count = 0;
							_isSelect = false;
						}						
					}

					//��ȭ�� ������
					else
					{
						//�κ� ī��Ʈ�� �Ѱ�ġ�� ������
						if (_inven[_select].count + _selectItem.count > _inven[_select].item->getLimit())
						{
							_selectItem.count = (_inven[_select].count + _selectItem.count) - _inven[_select].item->getLimit();
							_inven[_select].count = _inven[_select].item->getLimit();
						}

						//���� �ʴ´ٸ�
						else
						{
							_inven[_select].count = _inven[_select].count + _selectItem.count;
							_selectItem.count = 0;
						}

						//���� ������ ī��Ʈ�� 0 ���ϰ� �Ǹ� �����
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

			//���â�� �ű��
			if (_state == INVEN_STATE::NOTE)
			{
				//����ĭ
				if (_select == 4)
				{
					//�����̸�
					if (_selectItem.item->getIndex() > 1000)
					{
						//���ĭ�� ���������
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

						//������� ������
						else
						{
							//���â���� �״�� �������� ì��� �ִ� ����
							if (_selectGearNumber == _select)
							{
								_selectItem.count++;
								_gear[_select].count--;

								//���â�� �ִ� �������� ��� ����ٸ�
								if (_gear[_select].count <= 0) _gear[_select].item = nullptr;

								//���â�� �ִ� ������ �� ì�ܼ� ���� �� �������� �ٽ� ��������
								if (_selectItem.count > _selectItem.item->getLimit())
								{
									_gear[_select].item = _selectItem.item;
									_gear[_select].count = _selectItem.count;
								}
							}

							//�κ����� ������ �������̶��
							else
							{
								_selectItem.count--;
								_gear[_select].count++;

								//������ �Ѱ�ġ�� ������
								if (_gear[_select].count + _selectItem.count > _gear[_select].item->getLimit())
								{
									_selectItem.count = (_gear[_select].count + _selectItem.count) - _gear[_select].item->getLimit();
									_gear[_select].count = _gear[_select].item->getLimit();
								}

								//�� �������ٸ�
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

			//�����̽��� �ű��
			if (_state == INVEN_STATE::SHOP)
			{
				//�����̽��� ���������
				if (_shop[_select].item == nullptr)
				{
					//������ ��ġ
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

						//�����߾��� ������ ���� �ҷ�����
						for (int i = 0; i < _vPrice.size(); ++i)
						{
							if (_vPrice.size() < 0) continue;

							//����� �ε��� ���� ������ �ε����� ������ ���ݵ� ����
							if (_select == 0) loadPrice(_firstPrice, _select);
							if (_select == 2) loadPrice(_secondPrice, _select);
							if (_select == 4) loadPrice(_thirdPrice, _select);
							if (_select == 6) loadPrice(_fourthPrice, _select);
						}
					}	

					//���� �����ϴ� â�̸�
					if (_select % 2 != 0)
					{
						//�������� ��� �Դٸ�
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

							//�����߾��� ������ ���� �ҷ�����
							for (int i = 0; i < _vPrice.size(); ++i)
							{
								if (_vPrice.size() < 0) continue;

								//����� �ε��� ���� ������ �ε����� ������ ���ݵ� ����
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
						
						//���� �����ϴ� ���̸�
						if (_isSetPrice)
						{
							//�����̽��� �������� ������ ���� ����
							if (_shop[_select - 1].item != nullptr) savePrice(_select - 1);
																			
							_isSetPrice = false;
						}						
					}
					_isSelect = false;
				}

				//������� ������
				else
				{
					//������ �ε����� ������
					if (_shop[_select].item->getIndex() == _selectItem.item->getIndex())
					{
						//�����̽����� �״�� �������� ì��� �ִ� ����
						if (_selectShopNumber == _select)
						{
							_selectItem.count++;
							_shop[_select].count--;

							//�����̽��� �ִ� �������� ��� ����ٸ�
							if (_shop[_select].count <= 0)
							{
								_shop[_select].count = 0;
								_shop[_select].item = nullptr;

								//�����̽� �������� �� ĭ�̸� ī��Ʈ �ʱ�ȭ
								for (int i = 0; i < PRICESPACE; i++)
								{
									if (_select == 0) _firstPrice[i].count = 0;
									if (_select == 2) _secondPrice[i].count = 0;
									if (_select == 4) _thirdPrice[i].count = 0;
									if (_select == 6) _fourthPrice[i].count = 0;
								}								
							}

							//�����̽� �������� �� �������� �ٽ� ��������
							if (_selectItem.count > _selectItem.item->getLimit())
							{
								_shop[_select].item = _selectItem.item;
								_shop[_select].count = _selectItem.count;
							}
						}

						//�ڸ� �̵��� �־���
						else
						{
							//������ �Ѱ�ġ�� ������
							if (_shop[_select].count + _selectItem.count > _shop[_select].item->getLimit())
							{
								_selectItem.count = (_shop[_select].count + _selectItem.count) - _shop[_select].item->getLimit();
								_shop[_select].count = _shop[_select].item->getLimit();
							}

							//���� �ʴ´ٸ�
							else
							{
								_shop[_select].count = _shop[_select].count + _selectItem.count;
								_selectItem.count = 0;
							}

							//�� �������ٸ�
							if (_selectItem.count <= 0)
							{
								_selectItem.item = nullptr;
								_isSelect = false;
							}
						}
					}					

					//������ �ε����� �ٸ���
					else
					{
						//�κ����� ������
						if (_selectNumber >= 0 && _inven[_selectNumber].item == nullptr)
						{
							_inven[_selectNumber].item = _shop[_select].item;
							_inven[_selectNumber].count = _shop[_select].count;
							_inven[_selectNumber].price = _shop[_select].price;
							_shop[_select].item = _selectItem.item;
							_shop[_select].count = _selectItem.count;
							_shop[_select].price = _selectItem.price;

							//�����̽��� ��� �Ǹ� ���� �ʱ�ȭ
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

						//�����̽����� ������
						if (_selectShopNumber >= 0 && _shop[_selectShopNumber].item == nullptr)
						{
							_shop[_selectShopNumber].item = _shop[_select].item;
							_shop[_selectShopNumber].count = _shop[_select].count;
							_shop[_selectShopNumber].price = _shop[_select].price;
							_shop[_select].item = _selectItem.item;
							_shop[_select].count = _selectItem.count;
							_shop[_select].price = _selectItem.price;

							//�����̽��� ��� �Ǹ� ���� �ʱ�ȭ
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

							//����� �ε��� ���� ������ �ε����� ������ ���ݵ� ����
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
//===========================================�������� �κ����� �ű����===========================================//


//===========================================������� �������===========================================//
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
//===========================================������� �������===========================================//