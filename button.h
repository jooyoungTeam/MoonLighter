#pragma once
#include "gameNode.h"


enum BUTTONTYPE
{
	BUTTON_TERRAIN,
	BUTTON_OBJECT,
	BUTTON_COLLISION,
	BUTTON_SELECTSIZE,
	BUTTON_AUTO,

	BUTTON_SAVE,
	BUTTON_SAVE_DUNGEON,
	BUTTON_SAVE_TOWN,
	BUTTON_SAVE_BOSS,
	BUTTON_SAVE_SHOP,
	BUTTON_SAVE_ENTERENCE,
	BUTTON_SAVE_TEST,

	BUTTON_LOAD,
	BUTTON_LOAD_DUNGEON,
	BUTTON_LOAD_TOWN,
	BUTTON_LOAD_BOSS,
	BUTTON_LOAD_SHOP,
	BUTTON_LOAD_ENTERENCE,
	BUTTON_LOAD_TEST,

	BUTTON_ERASE,
	BUTTON_ERASE_TERRAIN,
	BUTTON_ERASE_OBJECT,

	BUTTON_EXIT,
	BUTTON_END

};

enum BUTTONSTATE
{
	BUTTON_ALWAYS,  // 항상 켜있음
	BUTTON_TEMP,    // 껐다가 켰다가하는 버튼
	BUTTON_OFF,		// 꺼진 상태
};


struct tagButton
{
	RECT	      rc;
	wstring       name;
	BUTTONSTATE   state;
};


class button : public gameNode
{
private:
	tagButton         _button[BUTTON_END];
	BUTTONTYPE        _currentType;

	int _saveCount;
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

