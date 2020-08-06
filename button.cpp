#include "stdafx.h"
#include "button.h"

HRESULT button::init()
{
	setButton();

	return S_OK;
}

void button::render()
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

		wstring str;
		str.assign(_button[i].name.begin(), _button[i].name.end());
		D2DRenderer::GetInstance()->RenderText(_button[i].pos.x - 35, _button[i].pos.y - 10, str, 15);
	}
}


void button::update()
{
	for (int i = 0; i < BUTTON_END; i++)
	{
		if (PtInRect(&_button[i].rc, _ptMouse))
		{
			_currentType = _button[i].type;
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
		_button[i].type = (BUTTONTYPE)i;
		_button[i].pos.x = WINSIZEX / 2 + 100 + i * 100;
		_button[i].pos.y = WINSIZEY / 2 + 300;
		_button[i].rc = RectMakeCenter(_button[i].pos.x, _button[i].pos.y, 80, 30);
	}
	_button[0].name = "  TERRAIN";
	_button[1].name = "   OBJECT";
	_button[2].name = "    SAVE";
	_button[3].name = "    LOAD";
	_button[4].name = "   ERASE";
	_button[5].name = "COMPLETE";
}
