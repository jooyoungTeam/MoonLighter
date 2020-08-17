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
	ITEMTYPE _type;						//아이템 타입
	ITEMBUNDLE _bundle;					//에너미에 따른 묶음
	FloatRect _rc;						//아이템 렉트
	Image* _img;						//아이템 이미지
	float _x, _y;						//아이템 렉트 x, y 좌표
	float _shakeMaxY;					//상점 아이템 둥실둥실 최대 y좌표
	float _shakeMinY;					//상점 아이템 둥실둥실 최소 y좌표
	float _shake;						//둥실둥실 정도
	float _endX, _endY;					//아이템 최초 드랍시 목표 x, y 좌표
	float _jumpPower;					//아이템 드랍시 점프파워
	float _gravity;						//드랍시 중력값
	int _itemIndex;						//아이템 고유번호
	int _limitCount;					//아이템 들고 있을 수 있는 최대 개수
	int _price;							//아이템 원가
	int _count;							//아이템 랜덤으로 골라내는 숫자

	bool _isShake;						//둥실둥실
	bool _isDrop;						//아이템 드랍
public:
	item() {}
	~item() {}

	HRESULT init(ITEMBUNDLE bundle, float x, float y, float endX, float endY);
	HRESULT init(ITEMTYPE type);
	void render();				//인벤토리용 랜더
	void cameraRender();	    //필드용 랜더
	void update();				//인벤토리용 업데이트
	void fieldUpdate();			//필드용 업데이트
	void move();				//아이템 드랍시 움직임
	void follow(FloatRect rc);	//플레이어 쫓아다닐 함수
	void release();
	
	void category();			//아이템 종류에 따른 정보 정리
	void setBundle();			//에너미 종류에 따른 아이템 묶기


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
};

