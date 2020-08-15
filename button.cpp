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

	for (int i = 0; i < BUTTON_END; i++)
	{
		if (_button[i].state == BUTTON_OFF) continue;

		if (i == _currentType)
		{
			D2DRenderer::GetInstance()->FillRectangle(_button[i].rc, D2D1::ColorF::Gray, 1);
		}
		else
		{
			D2DRenderer::GetInstance()->DrawRectangle(_button[i].rc, D2D1::ColorF::Black, 1);
		}
		D2DRenderer::GetInstance()->RenderText(_button[i].rc.left + 5, _button[i].rc.top + 5, _button[i].name, 15);
	}


}


void button::update()
{

	for (int i = 0; i < BUTTON_END; i++)
	{
		if (_button[i].state == BUTTON_OFF) continue;
		if (PtInRect(&_button[i].rc, _ptMouse))
		{
			if (i == BUTTON_EXIT)
				SCENEMANAGER->changeScene("≈∏¿Ã∆≤æ¿");

			_currentType = (BUTTONTYPE)i;
			break;
		}
	}

	if (_currentType == BUTTON_SAVE)
	{
		for (int i = 0; i < BUTTON_END; i++)
		{
			if (_button[i].state == BUTTON_TEMP)
				_button[i].state = BUTTON_OFF;
		}
		_button[BUTTON_SAVE_DUNGEON].state = BUTTON_TEMP;
		_button[BUTTON_SAVE_TOWN].state = BUTTON_TEMP;
		_button[BUTTON_SAVE_BOSS].state = BUTTON_TEMP;
		_button[BUTTON_SAVE_SHOP].state = BUTTON_TEMP;
		_button[BUTTON_SAVE_ENTERENCE].state = BUTTON_TEMP;
	}
	else if (_currentType == BUTTON_LOAD)
	{
		for (int i = 0; i < BUTTON_END; i++)
		{
			if (_button[i].state == BUTTON_TEMP)
				_button[i].state = BUTTON_OFF;
		}

		_button[BUTTON_LOAD_DUNGEON].state = BUTTON_TEMP;
		_button[BUTTON_LOAD_TOWN].state = BUTTON_TEMP;
		_button[BUTTON_LOAD_BOSS].state = BUTTON_TEMP;
		_button[BUTTON_LOAD_SHOP].state = BUTTON_TEMP;
		_button[BUTTON_LOAD_ENTERENCE].state = BUTTON_TEMP;
	}
	else if (_currentType == BUTTON_ERASE)
	{
		for (int i = 0; i < BUTTON_END; i++)
		{
			if (_button[i].state == BUTTON_TEMP)
				_button[i].state = BUTTON_OFF;
		}

		_button[BUTTON_ERASE_TERRAIN].state = BUTTON_TEMP;
		_button[BUTTON_ERASE_OBJECT].state = BUTTON_TEMP;
	}
	else if(_currentType == BUTTON_TERRAIN || _currentType == BUTTON_OBJECT)
	{
		for (int i = 0; i < BUTTON_END; i++)
		{
			if (_button[i].state == BUTTON_TEMP)
				_button[i].state = BUTTON_OFF;
		}
	}



}

void button::release()
{
}

void button::setButton()
{
	_button[BUTTON_TERRAIN].rc = RectMakeCenter(WINSIZEX / 2 + 330, 100, 80, 30);
	_button[BUTTON_TERRAIN].name = L"  TERRAIN";
	_button[BUTTON_TERRAIN].state = BUTTON_ALWAYS;

	_button[BUTTON_OBJECT].rc = RectMakeCenter(WINSIZEX / 2 + 430, 100, 80, 30);
	_button[BUTTON_OBJECT].name = L"   OBJECT";
	_button[BUTTON_OBJECT].state = BUTTON_ALWAYS;

	_button[BUTTON_COLLISION].rc = RectMakeCenter(WINSIZEX / 2 + 430, 50, 80, 30);
	_button[BUTTON_COLLISION].name = L"COLLISION";
	_button[BUTTON_COLLISION].state = BUTTON_ALWAYS;

	_button[BUTTON_SAVE].rc = RectMakeCenter(WINSIZEX / 2 + 530, 100, 80, 30);
	_button[BUTTON_SAVE].name = L"    SAVE";
	_button[BUTTON_SAVE].state = BUTTON_ALWAYS;

	_button[BUTTON_SAVE_DUNGEON].rc = RectMakeCenter(WINSIZEX / 2 + 330, 150, 80, 30);
	_button[BUTTON_SAVE_DUNGEON].name = L"DUNGEON";
	_button[BUTTON_SAVE_DUNGEON].state = BUTTON_OFF;
	_button[BUTTON_SAVE_TOWN].rc = RectMakeCenter(WINSIZEX / 2 + 430, 150, 80, 30);
	_button[BUTTON_SAVE_TOWN].name = L"   TOWN";
	_button[BUTTON_SAVE_TOWN].state = BUTTON_OFF;
	_button[BUTTON_SAVE_BOSS].rc = RectMakeCenter(WINSIZEX / 2 + 530, 150, 80, 30);
	_button[BUTTON_SAVE_BOSS].name = L"   BOSS";
	_button[BUTTON_SAVE_BOSS].state = BUTTON_OFF;
	_button[BUTTON_SAVE_SHOP].rc = RectMakeCenter(WINSIZEX / 2 + 630, 150, 80, 30);
	_button[BUTTON_SAVE_SHOP].name = L"   SHOP";
	_button[BUTTON_SAVE_SHOP].state = BUTTON_OFF;
	_button[BUTTON_SAVE_ENTERENCE].rc = RectMakeCenter(WINSIZEX / 2 + 730, 150, 90, 30);
	_button[BUTTON_SAVE_ENTERENCE].name = L"ENTERENCE";
	_button[BUTTON_SAVE_ENTERENCE].state = BUTTON_OFF;


	_button[BUTTON_LOAD].rc = RectMakeCenter(WINSIZEX / 2 + 630, 100, 80, 30);
	_button[BUTTON_LOAD].name = L"    LOAD";
	_button[BUTTON_LOAD].state = BUTTON_ALWAYS;

	_button[BUTTON_LOAD_DUNGEON].rc = RectMakeCenter(WINSIZEX / 2 + 330, 150, 80, 30);
	_button[BUTTON_LOAD_DUNGEON].name = L"DUNGEON";
	_button[BUTTON_LOAD_DUNGEON].state = BUTTON_OFF;
	_button[BUTTON_LOAD_TOWN].rc = RectMakeCenter(WINSIZEX / 2 + 430, 150, 80, 30);
	_button[BUTTON_LOAD_TOWN].name = L"   TOWN";
	_button[BUTTON_LOAD_TOWN].state = BUTTON_OFF;
	_button[BUTTON_LOAD_BOSS].rc = RectMakeCenter(WINSIZEX / 2 + 530, 150, 80, 30);
	_button[BUTTON_LOAD_BOSS].name = L"   BOSS";
	_button[BUTTON_LOAD_BOSS].state = BUTTON_OFF;
	_button[BUTTON_LOAD_SHOP].rc = RectMakeCenter(WINSIZEX / 2 + 630, 150, 80, 30);
	_button[BUTTON_LOAD_SHOP].name = L"   SHOP";
	_button[BUTTON_LOAD_SHOP].state = BUTTON_OFF;
	_button[BUTTON_LOAD_ENTERENCE].rc = RectMakeCenter(WINSIZEX / 2 + 730, 150, 90, 30);
	_button[BUTTON_LOAD_ENTERENCE].name = L"ENTERENCE";
	_button[BUTTON_LOAD_ENTERENCE].state = BUTTON_OFF;


	_button[BUTTON_ERASE].rc = RectMakeCenter(WINSIZEX / 2 + 730, 100, 80, 30);
	_button[BUTTON_ERASE].name = L"   ERASE";
	_button[BUTTON_ERASE].state = BUTTON_ALWAYS;

	_button[BUTTON_ERASE_TERRAIN].rc = RectMakeCenter(WINSIZEX / 2 + 630, 150, 80, 30);
	_button[BUTTON_ERASE_TERRAIN].name = L"TERRAIN";
	_button[BUTTON_ERASE_TERRAIN].state = BUTTON_OFF;
	_button[BUTTON_ERASE_OBJECT].rc = RectMakeCenter(WINSIZEX / 2 + 730, 150, 80, 30);
	_button[BUTTON_ERASE_OBJECT].name = L"OBJECT";
	_button[BUTTON_ERASE_OBJECT].state = BUTTON_OFF;


	_button[BUTTON_EXIT].rc = RectMakeCenter(WINSIZEX / 2 + 530, 50, 50, 30);
	_button[BUTTON_EXIT].name = L"  EXIT";
	_button[BUTTON_EXIT].state = BUTTON_ALWAYS;

}
