#include "stdafx.h"
#include "enemyState.h"
#include "enemy.h"

void enemyIdleState::update(enemy & enemy, ENEMYTYPE enemyType)
{
	//cout << "¾ÆÀÌµé" << endl;
	enemy.setIsPlayerHit(false);
	enemy.setAttackDelay(enemy.getAttackDelay() + 1);
	if (enemyType == ENEMY_GOLEM)
	{
		enemy.directionCheck();
	}

	if (enemyType != ENEMY_POT && !enemy.getIsHit())
	{
		enemy.move();
	}
	if (enemyType != ENEMY_POT && enemy.getIsHit())
	{
		enemy.hitMove();
	}
	if (enemyType == ENEMY_GOLEM)
	{
		_attackDistance = 100;
		_attackDelayCount = 100;
	}
	if (enemyType == ENEMY_RED_SLIME)
	{
		_attackDistance = 200;
		_attackDelayCount = 200;
	}
	if (enemyType == ENEMY_BLUE_SLIME)
	{
		_attackDistance = 400;
		_attackDelayCount = 50;
	}
	if (enemyType == ENEMY_YELLOW_SLIME)
	{
		_attackDistance = 400;
		_attackDelayCount = 50;
	}
	if (enemyType == ENEMY_BOSS)
	{
		enemy.setY(500);
		_attackDistance = 5000;
		_attackDelayCount = 100;
	}

	if (enemy.getAttackDelay() > _attackDelayCount)
	{
		if (getDistance(enemy.getPX(), enemy.getPY(), enemy.getX(), enemy.getY()) < _attackDistance)
		{
			enemy.setState(enemy.getAttack());
			enemy.setAttackAngle(getAngle(enemy.getX(), enemy.getY(), enemy.getPX(), enemy.getPY()));
		}
	}
}

void enemyMoveState::update(enemy & enemy, ENEMYTYPE enemyType)
{
}

void enemyAttackState::update(enemy & enemy, ENEMYTYPE enemyType)
{
	//cout << "¾îÅÃ" << endl;
	enemy.attack();
	enemy.setAttackDelay(0);
	//enemy.setAttackRect(RectMakePivot(Vector2(enemy.getX(), enemy.getY()), Vector2(enemy.getWidth(), enemy.getHeight()), Pivot::Center));

	if (enemyType == ENEMY_GOLEM)
	{
		if (!enemy.getAni()->isPlay())
		{
			enemy.enemyMove();
			enemy.setState(enemy.getIdle());
			enemy.setIsAttack(false);
		}
	}
}

void enemyHitState::update(enemy & enemy, ENEMYTYPE enemyType)
{
	//cout << "Èý" << endl;
	enemy.enemyHit();
}

void enemyDeadState::update(enemy & enemy, ENEMYTYPE enemyType)
{
	//cout << "Á×À½" << endl;
	enemy.dead();
}
