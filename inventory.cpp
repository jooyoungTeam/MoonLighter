#include "stdafx.h"
#include "inventory.h"

HRESULT inventory::init()
{
	_mirror = ImageManager::GetInstance()->AddImage("bagMirror", L"image/UI/bagMirror.png");
	ImageManager::GetInstance()->AddFrameImage("mirror_stay", L"image/UI/mirror_stay.png", 11, 1);
	ImageManager::GetInstance()->AddFrameImage("mirror_active", L"image/UI/mirror_active.png", 14, 1);
	ImageManager::GetInstance()->AddImage("inven", L"image/UI/note.png");
	ImageManager::GetInstance()->AddImage("invenSpace", L"image/UI/invenSpace.png");
	ImageManager::GetInstance()->AddImage("select", L"image/UI/invenslot.png");
	ImageManager::GetInstance()->AddImage("pendant", L"image/UI/pendant.png");

	//렉트 위치 잡기
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
	}
	
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
	}

	_state = INVEN_STATE::NOTE;

	_select = 0;
	_isOpen = false;
	_isActive = false;
	_isSwap = false;

	return S_OK;
}

void inventory::release()
{
}

void inventory::update()
{
	if (_isOpen)
	{
		_frameCount++;
		draw();

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

		if (_select == 20)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
			{
				_isActive = true;
				_mirrorFrameX = 0;
				_mirror = ImageManager::GetInstance()->FindImage("mirror_active");
			}

			if (!_isActive)
			{
				_mirror = ImageManager::GetInstance()->FindImage("mirror_stay");
			}
		}

		else
		{
			_mirrorFrameX = 0;
			_mirror = ImageManager::GetInstance()->FindImage("bagMirror");
		}

		cout << _select << endl;
	}	
}

void inventory::render()
{
	if (_isOpen)
	{
		ImageManager::GetInstance()->FindImage("inven")->Render(Vector2(WINSIZEX / 2 - 600, WINSIZEY / 2 - 350));

		for (int i = 0; i < INVENSPACE; i++)
		{
			//D2DRenderer::GetInstance()->DrawRectangle(_inven[i].rc, D2DRenderer::DefaultBrush::Green, 1.f);
			ImageManager::GetInstance()->FindImage("invenSpace")->SetSize(Vector2(65, 65));

			if (i <= 20) ImageManager::GetInstance()->FindImage("invenSpace")->Render(Vector2(_inven[i].rc.left - 5, _inven[i].rc.top - 5));
			if (i == _select && !_isSwap) ImageManager::GetInstance()->FindImage("select")->Render(Vector2(_inven[i].rc.left - 7, _inven[i].rc.top - 7));
		}

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

		ImageManager::GetInstance()->FindImage("pendant")->Render(Vector2(459, 565));

		if(_select == 20) _mirror->FrameRender(Vector2(_inven[20].rc.left - 5, _inven[20].rc.top + 70), _mirrorFrameX, 0);
		else _mirror->Render(Vector2(_inven[20].rc.left - 130, _inven[20].rc.top - 65));
	}
}

void inventory::putItem()
{
}

void inventory::equipGear()
{
}

void inventory::draw()
{
	if (_frameCount % 5 == 0)
	{
		_mirrorFrameX++;

		if (_mirror != nullptr && _mirrorFrameX > _mirror->GetMaxFrameX() - 1)
		{
			if (_isActive)
			{
				_isActive = false;
				_mirrorFrameX = 0;
			}

			if (_select == 20 && !_isActive)
			{
				_mirrorFrameX = 3;
			}
		}
		_frameCount = 0;
	}	
}
