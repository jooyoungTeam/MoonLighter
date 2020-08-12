#pragma once
#include "singletonBase.h"
#include "item.h"

#define INVENSPACE 22					//인벤칸수(왼쪽)
#define GEARSPACE 6						//장비칸수(오른쪽)
#define SHOPSPACE 4						//상점칸수

enum class INVEN_STATE
{
	NOTE, SHOP
};

enum class MIRROR_STATE
{
	STOP, STAY, ACTIVE
};

struct tagInven
{
	FloatRect rc;
	item* item;
	int count;
	wstring number;
};

struct tagGear
{
	Image* img;
	FloatRect rc;
	item* item;
	int count;
	wstring number;
};

struct tagShop
{
	FloatRect rc;
	item* item;
	int count;
	int price;
	wstring countNum;
	wstring priceNum;
};

class player;
class UI;

class inventory : public singletonBase<inventory>
{
private:
	INVEN_STATE _state;					//노트를 열었는지 상자를 열었는지

	tagInven _inven[INVENSPACE];		//인벤
	tagInven _selectItem;				//선택한 아이템
	Image* _mirrorImg;					//거울이미지
	Image* _saleImg;					//판매이미지
	int _select;						//현재 인벤 번호
	int _selectNumber;					//선택했을 때의 인벤 번호
	int _count;							//미러 딜레이
	bool _isSelect;						//아이템 선택하는 불 값
	bool _isSale;						//아이템 판매하는 불 값

	tagGear _gear[GEARSPACE];			//장비칸
	tagShop _shop[SHOPSPACE];			//상점칸
	bool _isSwap;						//넘어가기

	MIRROR_STATE _mirror;				//미러 상태
	int _frameCount;					//미러프레임용
	int _mirrorFrameX;					//미러 프레임X
	int _mirrorBallFrameX;				//미러 안 공 프레임X
	int _saleFrameX;					//판매 프레임X

	int _gold;							//소지금

	player* _player;
	UI* _ui;

public:
	inventory() {}
	~inventory() {}

	HRESULT init();
	void render();
	void update();
	void release();

	void putItem(item* item);								//인벤에 아이템 넣기
	void moveItem();										//인벤에서 아이템 옮기기
	void useMirror();										//미러 사용하기
	void draw();											//이미지 프레임 돌리기

public:
	int getGold() { return _gold; }							//소지금 가져가기
	tagGear getPotion() { return _gear[4]; }				//장비칸 4번째(포션) 가져가기
	INVEN_STATE getState() { return _state; }				//어떤 인벤 열었는지 가져가기

public:
	void setSale(BOOL sale = FALSE) { _isSale = sale; }		//판매하는 불 값 설정하기
	void setState(INVEN_STATE state) { _state = state; }	//어떤 인벤 열었는지 설정하기

public:
	//플레이어 참조용
	void getPlayerMemoryAddressLink(player* player) { _player = player; }
	//UI 참조용
	void getUIMemoryAddressLink(UI* ui) { _ui = ui; }
	
	tagShop* getShowCase() { return _shop; }
};