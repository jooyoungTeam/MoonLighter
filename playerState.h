#pragma once
#include "arrow.h"
#define MOVESPPED 5
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

class player;

class playerIdleState;
class playerWalkState;
class playerRollState;
class playerDieState;
class playerShieldState;
class playerIdleSwimState;
class playerSwimState;
class playerbowState;
class playerSwordState;
class playerbroomState;
class playerBedState;

class playerState
{

public:
	virtual ~playerState() {}
	virtual void update(player& player) {}

public:
	static playerIdleState* idle;
	static playerWalkState* walk;
	static playerRollState* roll;
	static playerDieState* die;
	static playerShieldState* shield;
	static playerIdleSwimState* idleSwim;
	static playerSwimState* swim;
	static playerbowState* bow;
	static playerSwordState* sword;
	static playerbroomState* broom;
	static playerBedState* bed;
};

class playerIdleState : public playerState
{
private:
	bool _transForm;
	int _idleCount;				//���̵���� �����Ǹ�
public:
	HRESULT init();
	virtual void update(player& player) override;
};

class playerWalkState : public playerState
{
private:
	bool _rollCount;
	int _rollCount2;
public:
	virtual void update(player& player) override;
};

class playerRollState : public playerState
{
private:

public:
	virtual void update(player& player) override;
};

class playerDieState : public playerState
{
public:
	virtual void update(player& player) override;
};

class playerShieldState : public playerState
{
public:
	virtual void update(player& player) override;
};

class playerIdleSwimState : public playerState
{
public:
	virtual void update(player& player) override;
};

class playerSwimState : public playerState
{
public:
	virtual void update(player& player) override;
};

class playerbowState : public playerState
{
private:
	arrow* _arrow;
public:
	virtual HRESULT init();
	virtual void render();
	virtual void release();
	virtual void update(player& player) override;
};

class playerSwordState : public playerState
{
public:
	virtual void update(player& player) override;
};

class playerBroomState : public playerState
{
public:
	virtual void update(player& player) override;
};

class playerBedState : public playerState
{
public:
	virtual void update(player& player) override;
};