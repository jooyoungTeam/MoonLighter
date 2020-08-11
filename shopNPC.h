#pragma once
#include "gameNode.h"

enum npcType			// NPC 종류 ENUM
{
	NPC_NOMAL,			// 일반 NPC - 아무거나 구매
	NPC_HERO,			// 용사 NPC - 장비류만 구매
	NPC_RICH			// 부자 NPC - 너무 비싸지 않는 이상 구매
};

enum npcActionState		// NPC 행동 ENUM
{
	NPC_IDLE,			// 쇼핑하기전 배회?상태
	NPC_SHOPPING,		// 아이템 쇼핑 상태
	NPC_BUY,			// 아이템 결제 상태
	NPC_AWAY			// 떠나는 상태
};

enum npcState			// NPC 상태 ENUM
{
	NPC_LEFT,			// 왼쪽 보는 상태
	NPC_UP,				// 위쪽 보는 상태
	NPC_RIGHT,			// 오른쪽 보는 상태
	NPC_DOWN			// 아래 보는 상태
};

enum npcEmotionState	// NPC 기분 NUM
{
	NPC_CHOOSE,			// 고르는 상태
	NPC_TOO_EXPENSIVE,	// 너무 비쌈
	NPC_EXPENSIVE,		// 비쌈
	NPC_CHEAP,			// 저렴함
	NPC_TOO_CHEAP		// 너무 저렴함
};


class shopNPC : public gameNode
{
private:
	Image*				_img;				// NPC의 이미지
	npcType				_npcType;			// NPC의 종류
	npcActionState		_npcActionState;
	npcState			_npcState;			// NPC의 상태
	npcEmotionState     _npcEmotionState;	// NPC의 기분상태

	float				_centerX;			// 중점 x
	float				_centerY;			// 중점 y
	float				_angle;				// 각도

	int					_rndChoiceItem;		// 아이템 고르는 난수
	int					_price;				// 고른 물건의 가격
	bool				_checkItem[4];		// 아이템 확인 여부

public:
	shopNPC() {}
	~shopNPC() {}

	HRESULT init();
	void	release();
	void	updadte();
	void	render();
	
	void	comparePrice();					// 가격 비교 함수

};

