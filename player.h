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
	int					_hitAlphaCount;						//��Ʈ ���� ī��Ʈ
	int					tileIndex[3];
	float			    _playerX, _playerY;					//�÷��̾� ����
	float				_playerRcW, _playerRcH;				//�÷��̾� RC ũ��
	float				_playerShadowX, _playerShadowY;		//�÷��̾� �׸��� ����
	float				_playerAttackX, _playerAttackY;		//�÷��̾� ������ġ
	float				_playerAttackW, _playerAttackH;		//�÷��̾� ���ݹ���
	float				_playerCurrentHp;					//�÷��̾� ü��
	float				_playerMaxHp;
	float				_SwordDamage;						//�÷��̾� �� ���ݷ�
	float				_hitAlpha;							//��Ʈ���ϸ� ���İ� ����
	bool				_swordAttack;						//�÷��̾� �� �����ϴ���
	bool				_swordAttackCombo;					//�÷��̾� �� �޺�����
	bool				_weaponChange;						//�÷��̾� ���� ����
	bool				_attackRcbool;						//�÷��̾� ���ݷ�Ʈ ���ֱ�
	bool				_bowBool;							//Ȱ ���� ��
	bool				_bowChargeAlpha;					//Ȱ ���� ����
	bool				_bowChargeState;					//Ȱ ������������.
	bool				_hitCondition;						//��Ʈ ��������
	bool				_enemyCol;							//���ʹ̿� �浹����
	bool				_colVoid;							//�浹 ȸ�ǻ���
	bool				_deadState;							//ĳ���� ��������
	bool				_tileColLeft;						//Ÿ�� �浹 ��������
	bool				_tileColRight;						//Ÿ�� �浹 ��������
	bool				_tileColTop;						//Ÿ�� �浹 ��������
	bool				_tileColBottom;						//Ÿ�� �浹 ��������
	bool				_tileColLeftTop;					//Ÿ�� �浹 ��������
	bool				_tileColRightTop;					//Ÿ�� �浹 ��������
	bool				_tileColLeftBottom;					//Ÿ�� �浹 ��������
	bool				_tileColRightBottom;				//Ÿ�� �浹 ��������

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



