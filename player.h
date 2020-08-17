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
	FloatRect			_playerRc;							//�÷��̾� ��Ʈ
	FloatRect			_playerAttackRc;					//�÷��̾� ���ݷ�Ʈ
	FloatRect			_playerShadowRc;					//�÷��̾� �׸��ڷ�Ʈ
	Image*				_playerImg;							//�÷��̾� �̹���
	Image*				_playerShadowImg;					//�÷��̾� �׸��� �̹���
	playerState*		_CurrentState;						//���� Ŭ���� ����
	animation*			_playerMotion;						//�÷��̾� �ִϸ��̼�
	DIRECTION			_playerDirection;					//�÷��̾� ����
	arrow*				_arrow;
	enemyManager*		_enemyLink;							//���ʹ� ��ȣ������
	int					_index;								//�÷��̾� �ε��� 0
	int					_arrowCount;						//ȭ���ѹ߸� ���
	int					_bedCount;							//���̵���� �����Ǹ� ħ����·�
	int					_bowChargeCount;					//Ȱ ���� ī��Ʈ
	int					_bowAlphaCount;						//Ȱ ���� ���� ī��Ʈ
	float			    _playerX, _playerY;					//�÷��̾� ����
	float				_playerRcW, _playerRcH;				//�÷��̾� RC ũ��
	float				_playerShadowX, _playerShadowY;		//�÷��̾� �׸��� ����
	float				_playerAttackX, _playerAttackY;		//�÷��̾� ������ġ
	float				_playerAttackW, _playerAttackH;		//�÷��̾� ���ݹ���
	float				_playerCurrentHp;					//�÷��̾� ü��
	float				_SwordDamage;						//�÷��̾� �� ���ݷ�
	bool				_swordAttack;						//�÷��̾� �� �����ϴ���
	bool				_swordAttackCombo;					//�÷��̾� �� �޺�����
	bool				_weaponChange;						//�÷��̾� ���� ����
	bool				_attackRcbool;						//�÷��̾� ���ݷ�Ʈ ���ֱ�
	bool				_bowBool;							//Ȱ ���� ��
	bool				_bowChargeAlpha;					//Ȱ ���� ����
	bool				_bowChargeState;					//Ȱ ������������.

	//�÷��̾� ���� ����
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



