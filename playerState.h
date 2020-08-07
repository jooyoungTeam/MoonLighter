#pragma once

class player;

class playerIdleState;

class playerState
{
public:

	virtual ~playerState() {}
	virtual void update(player& player) {}

public:
	static playerIdleState* idle;
};

class playerIdleState : public playerState
{
public:
	virtual void update(player& player) override;
};

