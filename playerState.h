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
class playerTeleportState;
class playerTeleportInState;
class playerTeleportOutState;

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
	static playerTeleportState* teleport;
	static playerTeleportInState* teleportIn;
	static playerTeleportOutState* teleportOut;
};

class playerIdleState : public playerState
{
private:
	bool	_transForm;
	bool   _alphaChange;
public:
	HRESULT init();
	virtual void update(player& player) override;
};

class playerWalkState : public playerState
{
private:
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

class playerTeleportState : public playerState
{
public:
	virtual void update(player& player) override;
};

class playerTeleportInState : public playerState
{
public:
	virtual void update(player& player) override;
};

class playerTeleportOutState : public playerState
{
public:
	virtual void update(player& player) override;
};