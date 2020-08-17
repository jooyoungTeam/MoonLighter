#pragma once
#include "gameNode.h"

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

enum class ITEMTYPE
{
	SLIME_RED, SLIME_BLUE, SLIME_YELLOW,
	//VINE, WOOD,
	CRYSTAL_ENERGY, REINFORCED_STEEL,
	BROKEN_SWORD, GOLEM_CORE,
	FABRIC, GOLEM_PIECES,
	GOLEMKING_CRYSTAL, GOLEMKING_RECORD,
	POTION_S
};

enum class ITEMBUNDLE
{
	SLIME_RED,
	SLIME_BLUE,
	SLIME_YELLOW,
	GOLEM_KNIGHT,
	GOLEM_POT,
	GOLEM_KING
};

class item : public gameNode
{
private:
	ITEMTYPE _type;
	ITEMBUNDLE _bundle;
	FloatRect _rc;
	Image* _img;
	float _x, _y;
	float _shakeMaxY;
	float _shakeMinY;
	float _shake;
	float _endX, _endY;
	float _jumpPower;
	float _gravity;
	int _itemIndex;
	int _limitCount;
	int _price;
	int _count;

	bool _isShake;
	bool _isDrop;
public:
	item() {}
	~item() {}

	HRESULT init(ITEMBUNDLE bundle, float x, float y, float endX, float endY);
	HRESULT init(ITEMTYPE type);
	void render();			// 인벤토리용 랜더
	void cameraRender();    // 필드용 랜더
	void update();			// 인벤토리용 업데이트
	void fieldUpdate();		// 필드용 업데이트
	void move();
	void release();
	
	void category();			//아이템 종류에 따른 정보 정리
	void setBundle();


public:
	ITEMTYPE getType() { return _type; }					//아이템 타입 가져가기
	FloatRect getRc() { return _rc; }						//아이템 렉트 가져가기
	Image* getImg() { return _img; }						//아이템 이미지 가져가기
	int getIndex() { return _itemIndex; }					//아이템 인덱스 번호 가져가기
	int getLimit() { return _limitCount; }					//아이템 개수 한계치 가져가기
	int getPrice() { return _price; }						//아이템 가격 가져가기

public:
	// ================== NPC =================
	void setItemPos(float x, float y) { _x = x; _y = y; }	// NPC 머리위에 아이템 띄우기 위해 위치 재조정 Setter
	void setShakeY(float y) { _shakeMaxY = y + 5; _shakeMinY = y; }
	// ================== 아이템매니저 =================
	void setItemType(ITEMTYPE type) { _type = type; }
};

