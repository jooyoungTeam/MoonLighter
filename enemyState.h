#pragma once

class enemy;

enum ENEMYTYPE
{
	ENEMY_RED_SLIME,
	ENEMY_BLUE_SLIME,
	ENEMY_YELLOW_SLIME,
	ENEMY_GOLEM,
	ENEMY_POT,
	ENEMY_BOSS
};


class enemyState
{
public:
	virtual ~enemyState() {}
	virtual void update(enemy& _enemy, RECT rc, ENEMYTYPE enemyType) = 0;
};

class enemyIdleState : public enemyState
{
public:
	virtual void update(enemy& _enemy, RECT rc, ENEMYTYPE enemyType) override;
};

class enemyMoveState : public enemyState
{
public:
	virtual void update(enemy& _enemy, RECT rc, ENEMYTYPE enemyType) override;
};

class enemyHitState : public enemyState
{
public:
	virtual void update(enemy& _enemy, RECT rc, ENEMYTYPE enemyType) override;
};

class enemyDeadState : public enemyState
{
public:
	virtual void update(enemy& _enemy, RECT rc, ENEMYTYPE enemyType) override;
};