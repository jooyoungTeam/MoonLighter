#pragma once

class enemy;

enum ENEMYTYPE		//¿¡³Ê¹Ì Á¾·ù
{
	ENEMY_RED_SLIME,
	ENEMY_BLUE_SLIME,
	ENEMY_YELLOW_SLIME,
	ENEMY_GOLEM,
	ENEMY_POT,
	ENEMY_BOSS
};

enum GOLEMDIR		//°ñ·½
{
	GOLEM_LEFT,
	GOLEM_RIGHT,
	GOLEM_TOP,
	GOLEM_BOTTOM
};

enum POTDIR			//ÆÌ
{
	POT_LEFT,
	POT_RIGHT,
	POT_TOP,
	POT_BOTTOM
};

class enemyIdleState;
class enemyMoveState;
class enemyAttackState;
class enemyHitState;
class enemyDeadState;

class enemyState
{
	GOLEMDIR _golemDir;

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
private:
	int _attackDistance;
public:
	enemyIdleState() { _attackDistance = 0; }
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