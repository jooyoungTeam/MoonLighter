#pragma once
#include "gameNode.h"
#include "aStar.h"
#include "item.h"

enum npcType			// NPC 종류 ENUM
{
	NPC_NOMAL,			// 일반 NPC
	NPC_HERO,			// 용사 NPC 
	NPC_RICH			// 부자 NPC 
};

enum npcActionState		// NPC 행동 ENUM
{
	NPC_ENTER,			// NPC 입장
	NPC_IDLE,			// NPC 가만히있는 상태
	NPC_WALK,			// 쇼핑하기전 배회?상태
	NPC_SHOPPING,		// 아이템 쇼핑 상태
	NPC_CHECKITEM,		// 아이템 확인 상태
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
	NPC_EMOTION_NULL,	// 없는상태
	NPC_CHOOSE,			// 고르는 상태
	NPC_TOO_EXPENSIVE,	// 너무 비쌈
	NPC_EXPENSIVE,		// 비쌈
	NPC_CHEAP,			// 저렴함
	NPC_TOO_CHEAP		// 너무 저렴함
};


class shopNPC : public gameNode
{
private:
	aStar*				_aStar;				// A*
	Image*				_itemImg;			// 들고있는 아이템
	Image*				_img;				// NPC의 이미지
	Image*				_emotionImg;		// 기분 이미지
	npcType				_npcType;			// NPC의 종류
	npcActionState		_npcActionState;	// NPC 행동 상태
	npcState			_npcState;			// NPC의 상태
	npcEmotionState     _npcEmotionState;	// NPC의 기분상태
	vector<POINT>		_vUnMove;			// 못가는 곳
	FloatRect			_rc;				// NPC 렉트

	POINT				_goToPoint;			// 가야 할곳
	POINT				_itemWayPoint[4];	// 아이템 고르는 좌표
	POINT				_counterPoint;		// 카운터 좌표
	POINT				_aroundPoint[3];	// 배회 좌표
	POINT				_eixtPoint;			// 출입문 좌표

	float				_centerX;			// 중점 x
	float				_centerY;			// 중점 y
	float				_thinkBoxX;			// 말풍선 x
	float				_thinkBoxY;			// 말풍선 y
	float				_angle;				// 각도
	float				_frameTimer;		// 프레임타이머
	float				_delayTimer;		// 딜레이타이머
	float				_emotionFrameTimer;	// 이모션 프레임타이머

	int					_indexX;			// 프레임인덱스X
	int					_indexY;			// 프레임인덱스Y
	int					_emotionIndexX;		// 이모션 프레임인덱스 X
	int					_rndChoiceItem;		// 아이템 고르는 난수
	int					_oldRndChoiceItem;  // 중복 방지 저장 수
	int					_rndChoicePt;		// 배회 난수
	int					_rightPrice;		// 물건의 적정가
	int					_settingPrice;		// 플레이어가 정한 가격
	int					_selectPrice;		// 고른 물건의 가격
	int					_checkItemCount;	// 아이템 확인한 수
	int					_idleCount;			// 배회 카운트

	bool				_checkItem[4];		// 아이템 확인 여부(똑같은 아이템 안보기)
	bool				_isAnotherPerson[4];// 다른사람이 자기가 고른 아이템을 보고있는지'
	bool				_isBuy;				// 구매했는지 확인
	bool				_isAway;			// 떠나는지 확인
	bool				_isCount;			// 계산중인지 확인	
	bool				_isExist;			// 아이템 있나?
public:
	shopNPC() {}
	~shopNPC() {}

public:
	HRESULT init(npcType type, vector<POINT> vUnMove);
	void	release();
	void	updadte();
	void	render();
	
	void	frameUpdate();					// 프레임 업데이트
	void	emotionFrameUpdate();			// 이모션 프레임 업데이트
	void	move();							// npc 이동
	void	comparePrice();					// 가격 비교
	void    wayPointSet();					// 가야되는곳 셋팅
	void	directionCheck();				// 방향 검사
	void	chooseItem();					// 아이템 뽑기
	void	choosePt();

public:
	//============================ Get ===========================
	npcActionState getNPCActionState() { return _npcActionState; }
	npcEmotionState getNPCEmotionState() { return _npcEmotionState; }
	FloatRect getNPCRect() { return _rc; }
	int  getSelectPrice() { return _selectPrice; }
	int  getRndItem() { return _rndChoiceItem; }
	int  getOldRndItem() { return _oldRndChoiceItem; }
	bool getIsBuy() { return _isBuy; }
	bool getIsAway() { return _isAway; }
	bool getIsCount() { return _isCount; }
public:
	//============================ Set ===========================
	void setSettingPrice(int price) { _settingPrice = price; }
	void setRightPrice(int price) { _rightPrice = price; }
	void setIsCount(bool arg) { _isCount = arg; }
	void setIsAnotherPerson(int index, bool arg) { _isAnotherPerson[index] = arg; }
};

