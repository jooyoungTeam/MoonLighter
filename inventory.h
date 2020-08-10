#pragma once
#include "gameNode.h"
#include "item.h"

#define INVENSPACE 22					//인벤칸수(왼쪽)
#define GEARSPACE 6						//장비칸수(오른쪽)

struct tagInven
{
	FloatRect rc;
	item* item;
	int count;
};

class inventory : public gameNode
{
private:
	tagInven _inven[INVENSPACE];		//인벤
	Image* _mirror;						//거울이미지
	int _select;						//현재 인벤 번호
	bool _isOpen;						//인벤 열었나?

	int _frameCount;
	int _mirrorFrameX;
	bool _isActive;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void putItem();											//인벤에 아이템 넣기
	void draw();											//이미지 프레임 돌리기

public:
	bool getOpen() { return _isOpen; }						//인벤 열었다는 불 값 가져가기

public:
	void setOpen(BOOL open = FALSE) { _isOpen = open; }		//인벤 열었다는 불 값 설정하기
};