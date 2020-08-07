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

class enemyIdleState;
class enemyMoveState;
class enemyAttackState;
class enemyHitState;
class enemyDeadState;

class enemyState
{
public:
	virtual ~enemyState() {}
	virtual void update(enemy& enemy, ENEMYTYPE enemyType) = 0;

	static enemyIdleState enemyIdle;
	static enemyMoveState enemyMove;
	static enemyAttackState enemyAttack;
	static enemyHitState enemyHit;
	static enemyDeadState enemyDead;
};

class enemyIdleState : public enemyState
{
public:
	virtual void update(enemy& enemy, ENEMYTYPE enemyType) override;
};

class enemyMoveState : public enemyState
{
public:
	virtual void update(enemy& enemy, ENEMYTYPE enemyType) override;
};

class enemyAttackState : public enemyState
{
public:
	virtual void update(enemy& enemy, ENEMYTYPE enemyType) override;
};

class enemyHitState : public enemyState
{
public:
	virtual void update(enemy& enemy, ENEMYTYPE enemyType) override;
};

class enemyDeadState : public enemyState
{
public:
	virtual void update(enemy& enemy, ENEMYTYPE enemyType) override;
};