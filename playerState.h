#pragma once

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

class player;

class playerIdleState;
class playerWalkState;
class playerRollState;
class playerDieState;
class playerShieldState;
class playerSwimState;
class playerbowState;
class playerSwordState;

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
	static playerSwimState* swim;
	static playerbowState* bow;
	static playerSwordState* sword;
};

class playerIdleState : public playerState
{
public:
	virtual void update(player& player) override;
};

class playerWalkState : public playerState
{
public:
	virtual void update(player& player) override;
};

class playerRollState : public playerState
{
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


class playerSwimState : public playerState
{
public:
	virtual void update(player& player) override;
};

class playerbowState : public playerState
{
public:
	virtual void update(player& player) override;
};

class playerSwordState : public playerState
{
public:
	virtual void update(player& player) override;
};