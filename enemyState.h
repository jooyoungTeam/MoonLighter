#pragma once

class enemy;

enum ENEMYTYPE		//에너미 종류
{
	ENEMY_RED_SLIME,
	ENEMY_BLUE_SLIME,
	ENEMY_YELLOW_SLIME,
	ENEMY_GOLEM,
	ENEMY_POT,
	ENEMY_BOSS
};

enum GOLEMDIR		//골렘
{
	GOLEM_LEFT,
	GOLEM_RIGHT,
	GOLEM_TOP,
	GOLEM_BOTTOM
};

enum POTDIR			//팟
{
	POT_LEFT,
	POT_RIGHT,
	POT_TOP,
	POT_BOTTOM
};

enum BOSS_PATTERN		//보스
{
	HAND_FALL,			//손 떨어지는 공격	
	ARM_LONG,			//팔 늘어나는 공격
	ROCK_FALL,			//돌 떨어지는 공격
	PLAYER_PULL,		//플레이어 끌어당기는 공격
	EXPLOSION,			//폭발 공격
	BOSS_BULLET_FIRE,	//총알 많이 날라가는거
	BOSS_BULLET_PFIRE	//플레이어 따라가는거
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
	int _attackDelayCount;
public:
	enemyIdleState() { _attackDistance = 0; _attackDelayCount = 0; }
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