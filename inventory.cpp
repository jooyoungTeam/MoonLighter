#include "stdafx.h"
#include "inventory.h"

HRESULT inventory::init()
{
	_mirrorImg = ImageManager::GetInstance()->AddImage("bagMirror", L"image/UI/bagMirror.png");
	ImageManager::GetInstance()->AddFrameImage("mirror_stay", L"image/UI/mirror_stay.png", 11, 1);
	ImageManager::GetInstance()->AddFrameImage("mirror_active", L"image/UI/mirror_active.png", 14, 1);
	ImageManager::GetInstance()->AddImage("inven", L"image/UI/note.png");
	ImageManager::GetInstance()->AddImage("invenSpace", L"image/UI/invenSpace.png");
	ImageManager::GetInstance()->AddImage("select", L"image/UI/invenslot.png");
	ImageManager::GetInstance()->AddImage("pendant", L"image/UI/pendant.png");

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

	//장비창 속성
	_gear[0].kind = GEAR_KIND::WEAPON1;
	_gear[5].kind = GEAR_KIND::WEAPON2;
	_gear[1].kind = GEAR_KIND::HELMET;
	_gear[2].kind = GEAR_KIND::TOP;
	_gear[3].kind = GEAR_KIND::SHOES;
	_gear[4].kind = GEAR_KIND::POTION;

	//인벤 상태
	_state = INVEN_STATE::NOTE;
	//미러 상태
	_mirror = MIRROR_STATE::STOP;

	_select = 0;
	_isOpen = false;
	_isSwap = false;
	_isSelect = false;

	return S_OK;
}

void inventory::release()
{
}

void inventory::update()
{
	_frameCount++;
	draw();

	if (_isSelect && !_isSwap) _selectItem.rc = RectMakePivot(Vector2(_inven[_select].rc.left - 5, _inven[_select].rc.top - 60), Vector2(60, 60), Pivot::LeftTop);
	if (_isSelect && _isSwap && _state == INVEN_STATE::NOTE) _selectItem.rc = RectMakePivot(Vector2(_gear[_select].rc.left - 5, _gear[_select].rc.top - 60), Vector2(60, 60), Pivot::LeftTop);

	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
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
			}
		}
		else
		{
			if (_state == INVEN_STATE::NOTE)
			{
				if (_select == 0) _select = 5;
				else
				{
					_isSwap = false;
					if (_select >= 5) _select = 0;
					else _select *= 5;
				}
			}
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		if (!_isSwap)
		{
			_select--;

			if (_select % 5 == 4 || _select < 0)
			{
				_isSwap = true;
				if (_select < 0) _select = 5;
				else _select = _select / 5 + 1;
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
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_UP))
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
				_select -= 1;
				if (_select < 0) _select = 4;
			}
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		if (!_isSwap)
		{
			if (_select < 20)
			{
				_select += 5;

				if (_select == 21) _select = 20;
				if (_select == 22) _select = 21;
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
				_select += 1;
				if (_select > 4) _select = 0;
			}
		}
	}

	moveItem();
	useMirror();
	equipGear();
}

void inventory::render()
{
	//노트
	ImageManager::GetInstance()->FindImage("inven")->Render(Vector2(WINSIZEX / 2 - 600, WINSIZEY / 2 - 350));

	//인벤토리 관련 렌더
	for (int i = 0; i < INVENSPACE; i++)
	{
		//D2DRenderer::GetInstance()->DrawRectangle(_inven[i].rc, D2DRenderer::DefaultBrush::Green, 1.f);
		ImageManager::GetInstance()->FindImage("invenSpace")->SetSize(Vector2(65, 65));
		if (i <= 20) ImageManager::GetInstance()->FindImage("invenSpace")->Render(Vector2(_inven[i].rc.left - 5, _inven[i].rc.top - 5));

		if (_inven[i].item != nullptr)
		{
			_inven[i].item->getImg()->Render(Vector2(_inven[i].rc.GetCenter().x - _inven[i].item->getImg()->GetWidth() / 2, _inven[i].rc.GetCenter().y - _inven[i].item->getImg()->GetHeight() / 2));
			D2DRenderer::GetInstance()->RenderText(_inven[i].rc.right - _inven[i].number.length() * 20, _inven[i].rc.bottom - 20, to_wstring(_inven[i].count), 20, D2DRenderer::DefaultBrush::Black);
		}

		if (i == _select && !_isSwap) ImageManager::GetInstance()->FindImage("select")->Render(Vector2(_inven[i].rc.left - 7, _inven[i].rc.top - 7));
	}

	ImageManager::GetInstance()->FindImage("pendant")->Render(Vector2(459, 565));

	//장비창 관련 렌더
	if (_state == INVEN_STATE::NOTE)
	{
		for (int i = 0; i < GEARSPACE; i++)
		{
			//D2DRenderer::GetInstance()->DrawRectangle(_gear[i].rc, D2DRenderer::DefaultBrush::Green, 1.f);
			ImageManager::GetInstance()->FindImage("invenSpace")->SetSize(Vector2(65, 65));
			ImageManager::GetInstance()->FindImage("invenSpace")->Render(Vector2(_gear[i].rc.left - 5, _gear[i].rc.top - 5));
			if (i == _select && _isSwap) ImageManager::GetInstance()->FindImage("select")->Render(Vector2(_gear[i].rc.left - 7, _gear[i].rc.top - 7));
		}
	}

	//내가 선택한 아이템 창
	if (_selectItem.item != nullptr)
	{
		D2DRenderer::GetInstance()->DrawRectangle(_selectItem.rc, D2DRenderer::DefaultBrush::Black, 2.f);
		_selectItem.item->getImg()->Render(Vector2(_selectItem.rc.GetCenter().x - _selectItem.item->getImg()->GetWidth() / 2, _selectItem.rc.GetCenter().y - _selectItem.item->getImg()->GetHeight() / 2));
		D2DRenderer::GetInstance()->RenderText(_selectItem.rc.right - _selectItem.number.length() * 20, _selectItem.rc.bottom - 20, to_wstring(_selectItem.count), 20, D2DRenderer::DefaultBrush::Black);
	}

	//미러
	if(_mirror == MIRROR_STATE::STOP) _mirrorImg->Render(Vector2(_inven[20].rc.left - 130, _inven[20].rc.top - 65));
	else _mirrorImg->FrameRender(Vector2(_inven[20].rc.left - 5, _inven[20].rc.top + 70), _mirrorFrameX, 0);
}

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
				if (_inven[i].item->getIndex() < 300 &&
					_inven[i].count >= 10)
				{
					continue;
				}

				if (((_inven[i].item->getIndex() > 300 && _inven[i].item->getIndex() < 400) || _inven[i].item->getIndex() > 1000) &&
					_inven[i].count >= 5)
				{
					continue;
				}

				if ((_inven[i].item->getIndex() > 900 && _inven[i].item->getIndex() < 1000) &&
					_inven[i].count >= 1)
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

void inventory::moveItem()
{
	if (!_isSelect && KEYMANAGER->isOnceKeyDown('J'))
	{
		_isSelect = true;
		_selectItem.count++;
		_selectNumber = _select;

		if (_inven[_select].item != nullptr && !_isSwap)
		{
			_selectItem.rc = RectMakePivot(Vector2(_inven[_select].rc.left - 5, _inven[_select].rc.top - 60), Vector2(60, 60), Pivot::LeftTop);
			_selectItem.item = _inven[_select].item;
			_inven[_select].count--;

			//인벤 카운트가 0 이하가 되면 비워버린다
			if (_inven[_select].count <= 0) _inven[_select].item = nullptr;
		}

		else if (_gear[_select].item != nullptr && _isSwap && _state == INVEN_STATE::NOTE)
		{
			_selectItem.rc = RectMakePivot(Vector2(_gear[_select].rc.left - 5, _gear[_select].rc.top - 60), Vector2(60, 60), Pivot::LeftTop);
			_selectItem.item = _gear[_select].item;
			_gear[_select].count--;

			//장비창 카운트가 0 이하가 되면 비워버린다
			if (_gear[_select].count <= 0) _gear[_select].item = nullptr;
		}
	}

	if (_isSelect && KEYMANAGER->isOnceKeyDown('J'))
	{
		//선택한 인벤이 비어있으면
		if (_inven[_select].item == nullptr)
		{
			_inven[_select].item = _selectItem.item;
			_inven[_select].count = _selectItem.count;
			_selectItem.count = 0;
			_selectItem.item = nullptr;
			_isSelect = false;
		}

		//비어있지 않으면
		else
		{
			//선택한 인벤의 아이템 인덱스가 들고 있는 아이템 인덱스와 같지 않으면
			if (_inven[_select].item->getIndex() != _selectItem.item->getIndex())
			{
				return;
			}

			//인덱스가 같으면
			else if (_inven[_select].item->getIndex() == _selectItem.item->getIndex())
			{
				//선택했을 때 인벤 칸에서 변화가 없으면
				if (_selectNumber == _select)
				{
					_selectItem.count++;
					_inven[_select].count--;
					if (_inven[_select].count <= 0) _inven[_select].item = nullptr;

					if (_selectItem.item->getIndex() < 300 &&
						_selectItem.count > 10)
					{
						_inven[_select].item = _selectItem.item;
						_inven[_select].count = _selectItem.count;
						_selectItem.item = nullptr;
						_isSelect = false;
					}

					if (((_selectItem.item->getIndex() > 300 && _selectItem.item->getIndex() < 400) || _selectItem.item->getIndex() > 1000) &&
						_selectItem.count > 5)
					{
						_inven[_select].item = _selectItem.item;
						_inven[_select].count = _selectItem.count;
						_selectItem.item = nullptr;
						_isSelect = false;
					}

					if ((_selectItem.item->getIndex() > 900 && _selectItem.item->getIndex() < 1000) &&
						_selectItem.count > 1)
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
					_inven[_select].count++;
					_selectItem.count--;

					if (_selectItem.count <= 0)
					{
						_selectItem.item = nullptr;
						_isSelect = false;
					}

					if (_inven[_select].item->getIndex() < 300 &&
						_inven[_select].count >= 10)
					{
						return;
					}

					if (((_inven[_select].item->getIndex() > 300 && _inven[_select].item->getIndex() < 400) || _inven[_select].item->getIndex() > 1000) &&
						_inven[_select].count >= 5)
					{
						return;
					}

					if ((_inven[_select].item->getIndex() > 900 && _inven[_select].item->getIndex() < 1000) &&
						_inven[_select].count >= 1)
					{
						return;
					}
				}
			}
		}
	}
}

void inventory::equipGear()
{

}

void inventory::useMirror()
{
	if (_select == 20)
	{
		//미러 칸에 머무르고 있으면
		_count++;
		if (_count == 10 && _mirror != MIRROR_STATE::STAY)
		{
			_mirror = MIRROR_STATE::STAY;
			_mirrorFrameX = 0;
			_mirrorImg = ImageManager::GetInstance()->FindImage("mirror_stay");
		}

		//미러를 활성화 시킨다면
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			_mirror = MIRROR_STATE::ACTIVE;
			_mirrorFrameX = 0;
			_mirrorImg = ImageManager::GetInstance()->FindImage("mirror_active");
		}
	}

	else
	{
		_mirror = MIRROR_STATE::STOP;
		_count = 0;
		_mirrorFrameX = 0;
		_mirrorImg = ImageManager::GetInstance()->FindImage("bagMirror");
	}
}

void inventory::draw()
{
	//미러 프레임 돌아간다~
	if (_frameCount % 5 == 0)
	{
		_mirrorFrameX++;

		if (_mirrorImg != nullptr && _mirrorFrameX > _mirrorImg->GetMaxFrameX() - 1)
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
		_frameCount = 0;
	}	
}
