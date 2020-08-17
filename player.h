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
	float			    _playerX, _playerY;					//플레이어 중점
	float				_playerRcW, _playerRcH;				//플레이어 RC 크기
	float				_playerShadowX, _playerShadowY;		//플레이어 그림자 중점
	float				_playerAttackX, _playerAttackY;		//플레이어 공격위치
	float				_playerAttackW, _playerAttackH;		//플레이어 공격범위
	float				_playerCurrentHp;					//플레이어 체력
	float				_SwordDamage;						//플레이어 검 공격력
	bool				_swordAttack;						//플레이어 검 공격하는중
	bool				_swordAttackCombo;					//플레이어 검 콤보공격
	bool				_weaponChange;						//플레이어 무기 변경
	bool				_attackRcbool;						//플레이어 공격렉트 꺼주기
	bool				_bowBool;							//활 충전 값
	bool				_bowChargeAlpha;					//활 충전 알파
	bool				_bowChargeState;					//활 충전상태인지.

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
	void tileCollision(DWORD* attribute, tagTile* tile);
	void arrowShoot();

public:
	int getIndex() { return _index; }
	int getBedCount() { return _bedCount; }
	int getBowChargeCount() { return _bowChargeCount; }
	int getBowAlphaCount() { return _bowAlphaCount; }
	float getX() { return _playerX; }
	float getY() { return _playerY; }
	float getShadowX() { return _playerShadowX; }
	float getShadowY() { return _playerShadowY; }
	float getplayerCurrentHp() { return _playerCurrentHp; }
	float getSwordDamage() { return _SwordDamage; }
	bool getSwordAttack() { return _swordAttack; }
	bool getSwordAttackCombo() { return _swordAttackCombo; }
	bool getWeaponChange() { return _weaponChange; }
	bool getAttackRcbool() { return _attackRcbool; }
	bool getBowBool() { return _bowBool; }
	bool getBowChargeAlpha() { return _bowChargeAlpha; }
	bool getBowChargeState() { return _bowChargeState; }

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
	void setX(float playerX) { _playerX = playerX; }
	void setY(float playerY) { _playerY = playerY; }
	void setShadowX(float shadowX) { _playerShadowX = shadowX; }
	void setShadowY(float shadowY) { _playerShadowY = shadowY; }
	void setPlayerCurrentHp(float playerCurrentHp) { _playerCurrentHp = playerCurrentHp; }
	void setSwordAttack(bool swordAttack) { _swordAttack = swordAttack; }
	void setSwrodAttackCombo(bool swordAttackCombo) { _swordAttackCombo = swordAttackCombo; }
	void setWeaponChange(bool weaponChange) { _weaponChange = weaponChange; }
	void setAttackRcbool(bool attackrcbool) { _attackRcbool = attackrcbool; }
	void setBowBool(bool bowBool) { _bowBool = bowBool; }
	void setBowChargeAlpha(bool bowChargeAlpha) { _bowChargeAlpha = bowChargeAlpha; }
	void setBowChargeState(bool bowChargeState) { _bowChargeState = bowChargeState; }
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
	playerState* getBroomState()		{ return _broom; }
	playerState* getBedState()			{ return _bed; }
	playerState* getTeleportState()		{ return _teleport; }
	playerState* getTeleportInState()	{ return _teleportIn; }
	playerState* getTeleportOutState()	{ return _teleportOut; }
};



