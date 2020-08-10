#pragma once
#include "gameNode.h"
#include "item.h"

#define INVENSPACE 22					//인벤칸수(왼쪽)
#define GEARSPACE 6						//장비칸수(오른쪽)

enum class INVEN_STATE
{
	NOTE, BOX
};

enum class GEAR_KIND
{
	WEAPON1, WEAPON2, HELMET, TOP, SHOES, POTION
};

struct tagInven
{
	FloatRect rc;
	item* item;
	int count;
};

struct tagGear
{
	GEAR_KIND kind;
	FloatRect rc;
	item* item;
};

class inventory : public gameNode
{
private:
	INVEN_STATE _state;

	tagInven _inven[INVENSPACE];		//인벤
	Image* _mirror;						//거울이미지
	int _select;						//현재 인벤 번호
	bool _isOpen;						//인벤 열었나?

	tagGear _gear[GEARSPACE];			//장비칸
	bool _isSwap;						//넘어가기

	int _frameCount;					//미러프레임용
	int _mirrorFrameX;					//미러프레임X
	bool _isActive;						//미러 쓰나?

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void putItem();											//인벤에 아이템 넣기
	void equipGear();										//장비 입기
	void draw();											//이미지 프레임 돌리기

public:
	bool getOpen() { return _isOpen; }						//인벤 열었다는 불 값 가져가기
	INVEN_STATE getState() { return _state; }				//어떤 인벤 열었는지 가져가기

public:
	void setOpen(BOOL open = FALSE) { _isOpen = open; }		//인벤 열었다는 불 값 설정하기
	void setState(INVEN_STATE state) { _state = state; }	//어떤 인벤 열었는지 설정하기
};