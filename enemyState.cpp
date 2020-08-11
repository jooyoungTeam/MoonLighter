#include "stdafx.h"
#include "enemyState.h"
#include "enemy.h"

void enemyIdleState::update(enemy & enemy, ENEMYTYPE enemyType)
{
	enemy.setAttackDelay(enemy.getAttackDelay() + 1);
	enemy.directionCheck();

	if (enemy.getAttackDelay() > 100)
	{
		if (enemyType == ENEMY_GOLEM)
		{
			_attackDistance = 50;
		}
		if (enemyType == ENEMY_RED_SLIME)
		{
			_attackDistance = 50;
		}
		if (enemyType == ENEMY_BLUE_SLIME)
		{
			_attackDistance = 50;

		}
		if (enemyType == ENEMY_YELLOW_SLIME)
		{
			_attackDistance = 50;

		}

		if (getDistance(enemy.getPX(), enemy.getPY(), enemy.getX(), enemy.getY()) < _attackDistance)
		{
			enemy.attack();
		}

	}
}

void enemyMoveState::update(enemy & enemy, ENEMYTYPE enemyType)
{
}

void enemyAttackState::update(enemy & enemy, ENEMYTYPE enemyType)
{
	enemy.setAttackDelay(0);

	if (!KEYANIMANAGER->findAnimation(enemy.getIndex(), "golemLeftAttack")->isPlay() && !KEYANIMANAGER->findAnimation(enemy.getIndex(), "golemRightAttack")->isPlay() &&
		!KEYANIMANAGER->findAnimation(enemy.getIndex(), "golemUpAttack")->isPlay() && !KEYANIMANAGER->findAnimation(enemy.getIndex(), "golemDownAttack")->isPlay())
	{
		enemy.enemyMove();
		enemy.setState(enemy.getIdle());
		enemy.setIsAttack(false);
	}
	
	
}

void enemyHitState::update(enemy & enemy, ENEMYTYPE enemyType)
{
}

void enemyDeadState::update(enemy & enemy, ENEMYTYPE enemyType)
{
}
