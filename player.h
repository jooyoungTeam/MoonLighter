#pragma once
#include "gameNode.h"
#include "playerState.h"

enum class DIRECTION
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
};

class player : public gameNode
{
private:
	FloatRect			_playerRc;							//�÷��̾� ��Ʈ
	Image*				_playerImg;							//�÷��̾� �̹���
	playerState*		_CurrentState;						//���� Ŭ���� ����
	animation*			_playerMotion;						//�÷��̾� �ִϸ��̼�
	DIRECTION			_playerDirection;					//�÷��̾� ����

	int					_index;								//�÷��̾� �ε��� 0
	float			    _playerX, _playerY;					//�÷��̾� ����
	float				_playerShadowX, _playerShadowY;		//�÷��̾� �׸��� ����

	bool				_swordAttack;						//�÷��̾� �� �����ϴ���
	bool				_swordAttackCombo;					//�÷��̾� �� �޺�����
	bool				_weaponChange;						//�÷��̾� ���� ����

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

public:
	virtual HRESULT init();
	void render();
	void update();
	void release();

public:
	void animationLoad();
	void tileCollision();

public:
	int getIndex() { return _index; }
	float getX() { return _playerX; }
	float getY() { return _playerY; }
	float getShadowX() { return _playerShadowX; }
	float getShadowY() { return _playerShadowY; }
	bool getSwordAttack() { return _swordAttack; }
	bool getSwordAttackCombo() { return _swordAttackCombo; }
	bool getWeaponChange() { return _weaponChange; }

	FloatRect getPlayerRc() { return _playerRc; }
	Image* getImage() { return _playerImg; }
	animation* getPlayerMotion() { return _playerMotion; }
	playerState* getCurrectState() { return _CurrentState; }
	DIRECTION getDirection() { return _playerDirection; }

	void setX(float playerX) { _playerX = playerX; }
	void setY(float playerY) { _playerY = playerY; }
	void setShadowX(float shadowX) { _playerShadowX = shadowX; }
	void setShadowY(float shadowY) { _playerShadowY = shadowY; }
	void setSwordAttack(bool swordAttack) { _swordAttack = swordAttack; }
	void setSwrodAttackCombo(bool swordAttackCombo) { _swordAttackCombo = swordAttackCombo; }
	void setWeaponChange(bool weaponChange) { _weaponChange = weaponChange; }
	void setPlayerMotion(animation* playerMotion, Image* img) { _playerMotion = playerMotion, _playerImg = img; _playerMotion->start(); }
	void setCurrentState(playerState* state) { _CurrentState = state; }
	void setDirection(DIRECTION playerDirection) { _playerDirection = playerDirection; }

public:
	playerState* getIdleState()		{ return _idle; }
	playerState* getWalkState()		{ return _walk; }
	playerState* getRollState()		{ return _roll; }
	playerState* getDieState()		{ return _die; }
	playerState* getShieldState()	{ return _shield; }
	playerState* getIdleSwimState() { return _idleSwim; }
	playerState* getSwimState()		{ return _swim; }
	playerState* getBowState()		{ return _bow; }
	playerState* getSwordState()	{ return _sword; }

};



