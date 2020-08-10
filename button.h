#pragma once
#include "gameNode.h"

enum BUTTONTYPE
{
	BUTTON_TERRAIN,
	BUTTON_OBJECT,
	BUTTON_SAVE,
	BUTTON_LOAD,
	BUTTON_ERASE,
	BUTTON_COMPLETE,
	BUTTON_END
};


struct tagButton
{
	RECT	      rc;
	POINT         pos;
	BUTTONTYPE    type;
    wstring       name;
};


class button :	public gameNode
{
private:
	tagButton       _button[BUTTON_END];
	BUTTONTYPE      _currentType;
public:
	button() {}
	~button() {}
public:
	HRESULT init();
	void render();
	void update();
	void release();
public:
	void setButton();
public:
	BUTTONTYPE getType() { return _currentType; }
	void       setType(BUTTONTYPE type) { _currentType = type; }
};

