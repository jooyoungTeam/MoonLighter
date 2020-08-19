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

//인벤토리
struct tagInven						
{
	FloatRect rc;					//인벤 칸 렉트
	item* item;						//인벤에 담는 아이템 클래스
	wstring number;					//아이템 개수 표시 string
	int count;						//아이템 개수
	int price;						//아이템 가격(설정가)
	bool isFull;
};

//장비창
struct tagGear						
{
	FloatRect rc;					//장비 칸 렉트
	item* item;						//장비창에 담는 아이템 클래스
	wstring number;					//아이템 개수 표시 string
	int count;						//아이템 개수
};

//상점
struct tagShop						
{
	FloatRect rc;					//아이템 담는 렉트
	item* item;						//쇼케이스에 담는 아이템 클래스
	wstring countNum;				//아이템 개수 표시 string
	int count;						//아이템 개수
	int price;						//아이템 설정가
	int totalPrice;					//아이템의 전체 금액
	int originalPrice;				//아이템 원가 전체 금액
	bool isPeople;
};

//가격 설정 창
struct tagSetPrice					
{
	FloatRect rc;					//가격 변경 렉트
	int count;						//입력되는 숫자
};

//가격 저장용
struct tagSavePrice					
{
	int index;						//아이템 번호
	int price;						//설정한 가격
};

class player;
class UI;

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
	int _selectCount;					//가격 선택
	int _gold;							//소지금

	bool _isSelect;						//아이템 선택하는 불 값
	bool _isSale;						//아이템 판매하는 불 값(미러사용)
	bool _isSwap;						//배열 넘어가기
	bool _isSetPrice;					//가격 설정할 거니
	bool _isInven;						//인벤토리 열었니?

	vector<tagSavePrice> _vPrice;		//아이템 가격 저장할 벡터
	vector<ITEMTYPE> _vType;			//아이템 타입 저장할 벡터

	player* _player;
	UI* _ui;

public:
	inventory() {}
	~inventory() {}

	HRESULT init();
	void render();
	void update();
	void release();

	void moveInven();										//인벤에서 돌아다니기
	bool putItem(item* item);								//인벤에 아이템 넣기
	int fullInven();										//인벤 가득 찼는지 확인하기

	// 만드는데 필요한 아이템 인덱스(index), 개수(count), 금액(gold)
	void makePotion(int selectPotionIndex, int index, int count, int gold);		

	void selectItem();										//아이템 선택하기
	void moveItem();										//아이템 옮기기

	void renderInven();										//인벤 상태에 따른 렌더 조정
	void closeInven();										//인벤 닫으면
	void popInven();										//인벤 비우기
	void putType();

	void setCount(tagSetPrice p[PRICESPACE], wstring d);	//가격 설정하기
	void setPrice(tagSetPrice p[PRICESPACE], int s);		//가격 계산하기
	void savePrice(int select);								//가격 저장하기
	void loadPrice(tagSetPrice p[PRICESPACE], int s);		//가격 불러오기

	void useMirror();										//미러 사용하기
	void draw();											//이미지 프레임 돌리기

public:
	int getGold() { return _gold; }							//소지금 가져가기
	tagInven* getInven() { return _inven; }
	tagGear getPotion() { return _gear[4]; }				//장비칸 4번째(포션) 가져가기
	tagShop* getShowCase() { return _shop; }				//상점 배열 가져가기
	INVEN_STATE getState() { return _state; }				//어떤 인벤 열었는지 가져가기
	bool getIsInven() { return _isInven; }
	vector<ITEMTYPE> getVType() { return _vType; }

public:
	void setState(INVEN_STATE state) { _state = state; }	//어떤 인벤 열었는지 설정하기
	void setIsInven(bool arg) { _isInven = arg; }			//인벤 열지 말지 정하기
	void resetShowCase(int index)							//아이템 팔린 후 쇼케이스 리셋
	{ 
		_shop[index].count = 0;
		_shop[index].countNum = L"";
		_shop[index].item = NULL;
		_shop[index].originalPrice = 0;
		_shop[index].price = 0;
		_shop[index].totalPrice = 0;
	}					

	int countOfPotion()										//포션 개수 세는 함수
	{
		for (int i = 0; i < INVENSPACE; i++)
		{
			if (_inven[i].item == nullptr) continue;

			int count;

			if (_inven[i].item->getIndex() > 1000)
			{
				count++;
			}
			return count;
		}
	}

public:
	//플레이어 참조용
	void getPlayerMemoryAddressLink(player* player) { _player = player; }
	//UI 참조용
	void getUIMemoryAddressLink(UI* ui) { _ui = ui; }
};