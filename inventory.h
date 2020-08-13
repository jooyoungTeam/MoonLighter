#pragma once
#include "singletonBase.h"
#include "item.h"

#define INVENSPACE 22				//인벤칸수
#define GEARSPACE 6					//장비칸수
#define SHOPSPACE 8					//상점칸수
#define PRICESPACE 5				//가격설정

enum class INVEN_STATE
{
	TEMP, NOTE, SHOP				//인벤을 띄우지 않음, 수첩 인벤 띄움, 샵 인벤 띄움
};

enum class MIRROR_STATE
{
	STOP, STAY, ACTIVE				//미러가 멈춰있음, 미러에 머물러 있음, 미러를 사용함
};

struct tagInven						//인벤토리
{
	FloatRect rc;					//인벤 칸 렉트
	item* item;						//인벤에 담는 아이템 클래스
	wstring number;					//아이템 개수 표시 string
	int count;						//아이템 개수
	int price;						//아이템 가격(설정가)
};

struct tagGear						//장비창
{
	FloatRect rc;					//장비 칸 렉트
	item* item;						//장비창에 담는 아이템 클래스
	wstring number;					//아이템 개수 표시 string
	int count;						//아이템 개수
};

struct tagShop						//상점
{
	FloatRect rc;					//아이템 담는 렉트
	item* item;						//쇼케이스에 담는 아이템 클래스
	wstring countNum;				//아이템 개수 표시 string
	int count;						//아이템 개수
	int price;						//아이템 설정가
	int totalPrice;					//쇼케이스 전체 금액
};

struct tagSetPrice					//가격 설정 창
{
	FloatRect rc;					//가격 변경 렉트
	int price;						//입력되는 숫자
};

class player;
class UI;
class itemManager;

class inventory : public singletonBase<inventory>
{
private:
	INVEN_STATE _state;					//노트를 열었는지 상자를 열었는지
	MIRROR_STATE _mirror;				//미러 상태

	tagInven _inven[INVENSPACE];		//인벤
	tagInven _selectItem;				//선택한 아이템
	tagGear _gear[GEARSPACE];			//장비칸
	tagShop _shop[SHOPSPACE];			//상점칸
	tagSetPrice _firstPrice[PRICESPACE];//가격설정칸
	tagSetPrice _secondPrice[PRICESPACE];
	tagSetPrice _thirdPrice[PRICESPACE];
	tagSetPrice _fourthPrice[PRICESPACE];

	Image* _mirrorImg;					//거울이미지
	Image* _saleImg;					//판매이미지

	int _select;						//현재 인벤 번호
	int _selectNumber;					//선택한 칸 번호(인벤)
	int _selectGearNumber;				//선택한 칸 번호(장비칸)
	int _selectShopNumber;				//선택한 칸 번호(샵)
	int _frameCount;					//미러프레임용
	int _mirrorFrameX;					//미러 프레임X
	int _mirrorBallFrameX;				//미러 안 공 프레임X
	int _saleFrameX;					//판매 프레임X
	int _count;							//미러 딜레이
	int _selectPrice;					//가격 선택
	int _gold;							//소지금

	bool _isSelect;						//아이템 선택하는 불 값
	bool _isSale;						//아이템 판매하는 불 값
	bool _isSwap;						//배열 넘어가기
	bool _isInven;						//인벤토리 열었니?
	bool _isSetPrice;					//가격 설정할 거니

	player* _player;
	UI* _ui;
	itemManager* _itemMg;

public:
	inventory() {}
	~inventory() {}

	HRESULT init();
	void render();
	void update();
	void release();

	void moveInven();										//인벤에서 돌아다니기
	void putItem(item* item);								//인벤에 아이템 넣기
	void selectItem();										//아이템 선택하기
	void moveItem();										//아이템 옮기기
	void setPrice();										//가격 설정하기
	void closeInven();										//인벤 닫으면
	void useMirror();										//미러 사용하기
	void renderInven();										//인벤 상태에 따른 렌더 조정
	void draw();											//이미지 프레임 돌리기

public:
	int getGold() { return _gold; }							//소지금 가져가기
	tagGear getPotion() { return _gear[4]; }				//장비칸 4번째(포션) 가져가기
	tagShop* getShowCase() { return _shop; }				//상점 배열 가져가기
	INVEN_STATE getState() { return _state; }				//어떤 인벤 열었는지 가져가기
	bool getIsInven() { return _isInven; }

public:
	void setState(INVEN_STATE state) { _state = state; }	//어떤 인벤 열었는지 설정하기
	void setIsInven(bool arg) { _isInven = arg; }			//인벤 열지 말지 정하기

public:
	//플레이어 참조용
	void getPlayerMemoryAddressLink(player* player) { _player = player; }
	//UI 참조용
	void getUIMemoryAddressLink(UI* ui) { _ui = ui; }
};