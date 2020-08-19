#pragma once
#include "gameNode.h"
#include "playerState.h"

class enemyManager;

enum class DIRECTION
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	LEFTTOP,
	RIGHTTOP,
	LEFTBOTTOM,
	RIGHTBOTTOM,
};

class player : public gameNode
{
private:
	FloatRect			_playerRc;							//플레이어 렉트
	FloatRect			_playerAttackRc;					//플레이어 공격렉트
	FloatRect			_playerShadowRc;					//플레이어 그림자렉트
	Image*				_playerImg;							//플레이어 이미지
	Image*				_playerShadowImg;					//플레이어 그림자 이미지
	playerState*		_CurrentState;						//현재 클래스 상태
	animation*			_playerMotion;						//플레이어 애니메이션
	DIRECTION			_playerDirection;					//플레이어 방향
	arrow*				_arrow;
	enemyManager*		_enemyLink;							//에너미 상호참조용
	int					_index;								//플레이어 인덱스 0
	int					_arrowCount;						//화살한발만 쏘게
	int					_bedCount;							//아이들상태 오래되면 침대상태로
	int					_bowChargeCount;					//활 충전 카운트
	int					_bowAlphaCount;						//활 충전 알파 카운트
	int					_hitAlphaCount;						//히트 알파 카운트
	int					tileIndex[3];
	float			    _playerX, _playerY;					//플레이어 중점
	float				_playerRcW, _playerRcH;				//플레이어 RC 크기
	float				_playerShadowX, _playerShadowY;		//플레이어 그림자 중점
	float				_playerAttackX, _playerAttackY;		//플레이어 공격위치
	float				_playerAttackW, _playerAttackH;		//플레이어 공격범위
	float				_playerCurrentHp;					//플레이어 체력
	float				_playerMaxHp;
	float				_SwordDamage;						//플레이어 검 공격력
	float				_hitAlpha;							//히트당하면 알파값 조정
	bool				_swordAttack;						//플레이어 검 공격하는중
	bool				_swordAttackCombo;					//플레이어 검 콤보공격
	bool				_weaponChange;						//플레이어 무기 변경
	bool				_attackRcbool;						//플레이어 공격렉트 꺼주기
	bool				_bowBool;							//활 충전 값
	bool				_bowChargeAlpha;					//활 충전 알파
	bool				_bowChargeState;					//활 충전상태인지.
	bool				_hitCondition;						//히트 상태인지
	bool				_enemyCol;							//에너미와 충돌상태
	bool				_colVoid;							//충돌 회피상태
	bool				_deadState;							//캐릭터 죽은상태
	bool				_tileColLeft;						//타일 충돌 상태인지
	bool				_tileColRight;						//타일 충돌 상태인지
	bool				_tileColTop;						//타일 충돌 상태인지
	bool				_tileColBottom;						//타일 충돌 상태인지
	bool				_tileColLeftTop;					//타일 충돌 상태인지
	bool				_tileColRightTop;					//타일 충돌 상태인지
	bool				_tileColLeftBottom;					//타일 충돌 상태인지
	bool				_tileColRightBottom;				//타일 충돌 상태인지

	//플레이어 상태 정의
	playerState*	    _idle;
	playerState*	    _walk;
	playerState*	    _roll;
	playerState*	    _die;
	playerState*	    _shield;
	playerState*		_idleSwim;
	playerState*	    _swim;
	playerState*	    _bow;
	playerState*	    _sword;
	playerState*		_hit;
	playerState*	    _broom;
	playerState*		_bed;
	playerState*		_teleport;
	playerState*		_teleportIn;
	playerState*		_teleportOut;

public:
	virtual HRESULT init(float x, float y);
	void render();
	void update();
	void release();

public:
	void animationLoad();
	bool tileSceneChange(DWORD * attribute, tagTile * tile, RECT rcCol);
	void tileCollision(DWORD* attribute, tagTile* tile, int tileSizeX);
	void arrowShoot();
	void playerHp();

public:
	int getIndex() { return _index; }
	int getBedCount() { return _bedCount; }
	int getBowChargeCount() { return _bowChargeCount; }
	int getBowAlphaCount() { return _bowAlphaCount; }
	int getHitAlphaCount() { return _hitAlphaCount; }
	int*  getColTileIdx() { return tileIndex; }

	float getX() { return _playerX; }
	float getY() { return _playerY; }
	float getShadowX() { return _playerShadowX; }
	float getShadowY() { return _playerShadowY; }
	float getplayerCurrentHp() { return _playerCurrentHp; }
	float getPlayerMaxHp() { return _playerMaxHp; }
	float getSwordDamage() { return _SwordDamage; }
	float getPlayerRcW() { return _playerRcW; }
	float getPlayerRcH() { return  _playerRcH; }
	float getHitAlpha() { return _hitAlpha; }

	bool getSwordAttack() { return _swordAttack; }
	bool getSwordAttackCombo() { return _swordAttackCombo; }
	bool getWeaponChange() { return _weaponChange; }
	bool getAttackRcbool() { return _attackRcbool; }
	bool getBowBool() { return _bowBool; }
	bool getBowChargeAlpha() { return _bowChargeAlpha; }
	bool getBowChargeState() { return _bowChargeState; }
	bool getHitCondition() { return _hitCondition; }
	bool getEnemyCol() { return _enemyCol; }
	bool getColVoid() { return _colVoid; }
	bool getDeadState() { return _deadState; }
	bool getTileColLeft() { return _tileColLeft; }
	bool getTileColTop() { return _tileColTop; }
	bool getTileColRight() { return _tileColRight; }
	bool getTileColBottom() { return _tileColBottom; }
	bool getTileColLeftTop() { return _tileColLeftTop; }
	bool getTileColRightTop() { return _tileColRightTop; }
	bool getTileColLeftBottom() { return _tileColLeftBottom; }
	bool getTileColRightBottom() { return _tileColRightBottom; }

	FloatRect getPlayerRc() { return _playerRc; }
	FloatRect getPlayerAttackRc() { return _playerAttackRc; }
	Image* getImage() { return _playerImg; }
	animation* getPlayerMotion() { return _playerMotion; }
	playerState* getCurrectState() { return _CurrentState; }
	DIRECTION getDirection() { return _playerDirection; }
	arrow* getArrow() { return _arrow; }

	void setBedCount(int bedCount) { _bedCount = bedCount; }
	void setBowChargeCount(int bowChargeCount) { _bowChargeCount = bowChargeCount; }
	void setBowAlphaCount(int bowAlphaCount) { _bowAlphaCount = bowAlphaCount; }
	void setHitAlphaCount(int hitAlphaCount) { _hitAlphaCount = hitAlphaCount; }
	void setX(float playerX) { _playerX = playerX; }
	void setY(float playerY) { _playerY = playerY; }
	void setShadowX(float shadowX) { _playerShadowX = shadowX; }
	void setShadowY(float shadowY) { _playerShadowY = shadowY; }
	void setPlayerCurrentHp(float playerCurrentHp) { _playerCurrentHp = playerCurrentHp; }
	void setPlayerMaxHp(float playerMaxHp) { _playerMaxHp = playerMaxHp; }
	void setHitAlpha(float hitAlpha) { _hitAlpha = hitAlpha; }
	void setPlayerRcW(float playerRcW) { _playerRcW = playerRcW; }
	void setPlayerRcH(float playerRcH) { _playerRcH = playerRcH; }
	void setSwordAttack(bool swordAttack) { _swordAttack = swordAttack; }
	void setSwrodAttackCombo(bool swordAttackCombo) { _swordAttackCombo = swordAttackCombo; }
	void setWeaponChange(bool weaponChange) { _weaponChange = weaponChange; }
	void setAttackRcbool(bool attackrcbool) { _attackRcbool = attackrcbool; }
	void setBowBool(bool bowBool) { _bowBool = bowBool; }
	void setBowChargeAlpha(bool bowChargeAlpha) { _bowChargeAlpha = bowChargeAlpha; }
	void setBowChargeState(bool bowChargeState) { _bowChargeState = bowChargeState; }
	void setHitCondition(bool hitCondition) { _hitCondition = hitCondition; }
	void setEnemyCol(bool enemyCol) { _enemyCol = enemyCol; }
	void setColVoid(bool colVoid) { _colVoid = colVoid; }
	void setDeadState(bool deadState) { _deadState = deadState;}
	void setPlayerMotion(animation* playerMotion, Image* img) { _playerMotion->stop(); _playerImg = img; _playerMotion = playerMotion; _playerMotion->start(); }
	void setCurrentState(playerState* state) { _CurrentState = state; }
	void setDirection(DIRECTION playerDirection) { _playerDirection = playerDirection; }
	void setAttackRc(float playerAttackX, float playerAttackY, float playerAttackW, float playerAttackH)
	{
		_playerAttackX = playerAttackX, _playerAttackY = playerAttackY, _playerAttackW = playerAttackW, _playerAttackH = playerAttackH;
	}
	void setPlayerRc(float playerRcX, float playerRcY, float playerRcW, float playerRcH)
	{
		_playerX = playerRcX, _playerY = playerRcY, _playerRcW = playerRcW, _playerRcH = playerRcH;
	}
	void setEnemyLink(enemyManager* enemyLink) { _enemyLink = enemyLink; }
	void setPlayerPos(float x, float y) { _playerShadowX = x, _playerShadowY = y; }

public:
	playerState* getIdleState()			{ return _idle; }
	playerState* getWalkState()			{ return _walk; }
	playerState* getRollState()			{ return _roll; }
	playerState* getDieState()			{ return _die; }
	playerState* getShieldState()		{ return _shield; }
	playerState* getIdleSwimState()		{ return _idleSwim; }
	playerState* getSwimState()			{ return _swim; }
	playerState* getBowState()			{ return _bow; }
	playerState* getSwordState()		{ return _sword; }
	playerState* getHitState()			{ return _hit; }
	playerState* getBroomState()		{ return _broom; }
	playerState* getBedState()			{ return _bed; }
	playerState* getTeleportState()		{ return _teleport; }
	playerState* getTeleportInState()	{ return _teleportIn; }
	playerState* getTeleportOutState()	{ return _teleportOut; }
};



