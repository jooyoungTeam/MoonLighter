#include "stdafx.h"
#include "enemyState.h"
#include "enemy.h"

void enemyIdleState::update(enemy & enemy, ENEMYTYPE enemyType)
{
	if (getDistance(enemy.getPX(),  enemy.getPX(), enemy.getX(), enemy.getY()) < 100)
	{
		if (enemyType == ENEMY_RED_SLIME)
		{
			enemy.setState(enemy.getAttack());
		}
	}
	
}

void enemyMoveState::update(enemy & enemy, ENEMYTYPE enemyType)
{
}

void enemyAttackState::update(enemy & enemy, ENEMYTYPE enemyType)
{
	cout << "µé¾î¿È" << endl;
	if (getDistance(enemy.getPX(), enemy.getPX(), enemy.getX(), enemy.getY()) >= 100)
	{
		if (enemyType == ENEMY_RED_SLIME)
		{
			enemy.setState(enemy.getIdle());
		}
	}
}

void enemyHitState::update(enemy & enemy, ENEMYTYPE enemyType)
{
}

void enemyDeadState::update(enemy & enemy, ENEMYTYPE enemyType)
{
}
