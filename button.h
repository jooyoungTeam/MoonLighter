#pragma once
#include "gameNode.h"

typedef void(*CALLBACK_FUNCTION)(void);

enum BUTTONTYPE
{
	BUTTON_TERRAIN,
	BUTTON_OBJECT,
	BUTTON_COLLISION,
	BUTTON_SAVE,
	BUTTON_SAVE_DUNGEON,
	BUTTON_SAVE_TOWN,
	BUTTON_LOAD,
	BUTTON_LOAD_DUNGEON,
	BUTTON_LOAD_TOWN,

	BUTTON_ERASE,
	BUTTON_ERASE_TERRAIN,
	BUTTON_ERASE_OBJECT,

	BUTTON_EXIT,
	BUTTON_END

};

enum BUTTONSTATE
{
	BUTTON_ALWAYS,  // �׻� ������
	BUTTON_TEMP,    // ���ٰ� �״ٰ��ϴ� ��ư
	BUTTON_OFF,		// ���� ����
};


struct tagButton
{
	RECT	      rc;
    wstring       name;
	BUTTONSTATE   state;
};


class button :	public gameNode
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

