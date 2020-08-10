#include "stdafx.h"
#include "button.h"

HRESULT button::init()
{
	setButton();
	_currentType = BUTTON_TERRAIN;
	return S_OK;
}

void button::render()
{
	if (_currentType == BUTTON_OBJECT)
	{
		for (int i = 0; i < BUTTON_END; i++)
		{
			if (_button[i].type == _currentType)
			{
				D2DRenderer::GetInstance()->FillRectangle(_button[i].rc, D2D1::ColorF::Gray, 1);
			}
			else
			{
				D2DRenderer::GetInstance()->DrawRectangle(_button[i].rc, D2D1::ColorF::Black, 1);
			}
			D2DRenderer::GetInstance()->RenderText(_button[i].pos.x - 35, _button[i].pos.y - 10, _button[i].name, 15);
		}
	}
	else
	{
		for (int i = 0; i < BUTTON_END; i++)
		{
			if (_button[i].type == _currentType)
			{
				D2DRenderer::GetInstance()->FillRectangle(_button[i].rc, D2D1::ColorF::Gray, 1);
			}
			else
			{
				D2DRenderer::GetInstance()->DrawRectangle(_button[i].rc, D2D1::ColorF::Black, 1);
			}
			D2DRenderer::GetInstance()->RenderText(_button[i].pos.x - 35, _button[i].pos.y - 10, _button[i].name, 15);
		}
	}


}


void button::update()
{

	for (int i = 0; i < BUTTON_END; i++)
	{
		if (PtInRect(&_button[i].rc, _ptMouse))
		{
			_currentType = _button[i].type;
			break;
		}
	}

	

}

void button::release()
{
}

void button::setButton()
{
	for (int i = 0; i < BUTTON_END; i++)
	{
		if (i == 5)
		{
			_button[i].pos.x = WINSIZEX / 2 + 530;
			_button[i].pos.y = 150;
		}
		else
		{
			_button[i].pos.x = WINSIZEX / 2 + 330 + i * 100;
			_button[i].pos.y = 100;
		}
		_button[i].type = (BUTTONTYPE)i;
		_button[i].rc = RectMakeCenter(_button[i].pos.x, _button[i].pos.y, 80, 30);
	}


	_button[0].name = L"  TERRAIN";
	_button[1].name = L"   OBJECT";
	_button[2].name = L"    SAVE";
	_button[3].name = L"    LOAD";
	_button[4].name = L"   ERASE";
	_button[5].name = L"COMPLETE";
}
