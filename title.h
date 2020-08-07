#pragma once
#include "gameNode.h"

#define MENUNUM 3

enum class SELECT
{
	MOVE, STOP, STAY
};

struct tagMenu
{
	FloatRect rc;
	wstring name;
};

class title :public gameNode
{
private:
	Image* _titleFront;
	Image* _titleBack;
	Image* _menuBox;
	Image* _logo;

	tagMenu _menu[MENUNUM];
	SELECT _menuSelect;
	Image* _selectImg;
	int _select;
	int _selectX;
	int _count;

	int _frameCount;
	int _frameX;

public:
	title() {}
	~title() {}
public:
	HRESULT init();
	void update();
	void render();
	void release();

	void draw();
};

