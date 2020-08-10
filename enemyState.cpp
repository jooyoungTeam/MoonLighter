#include "stdafx.h"
#include "enemyState.h"
#include "enemy.h"

void enemyIdleState::update(enemy & enemy, ENEMYTYPE enemyType)
{
	enemy.setAttackDelay(enemy.getAttackDelay() + 1);
	enemy.enemyMove();
	//cout << " µé¿È" << endl;
	if (enemy.getAttackDelay() > 80)
	{
	if (enemyType == ENEMY_GOLEM)
	{
		if (getDistance(enemy.getPX(), enemy.getPY(), enemy.getX(), enemy.getY()) < 100)
		{
			switch (enemy.getGolDriection())
			{
			case GOLEM_LEFT:
				enemy.setMotion(ImageManager::GetInstance()->FindImage("golemAttack"), KEYANIMANAGER->findAnimation(enemy.getIndex(), "golemLeftAttack"));
				break;
			case GOLEM_RIGHT:
				enemy.setMotion(ImageManager::GetInstance()->FindImage("golemAttack"), KEYANIMANAGER->findAnimation(enemy.getIndex(), "golemRightAttack"));
				break;
			case GOLEM_TOP:
				enemy.setMotion(ImageManager::GetInstance()->FindImage("golemAttack"), KEYANIMANAGER->findAnimation(enemy.getIndex(), "golemUpAttack"));
				break;
			case GOLEM_BOTTOM:
				enemy.setMotion(ImageManager::GetInstance()->FindImage("golemAttack"), KEYANIMANAGER->findAnimation(enemy.getIndex(), "golemDownAttack"));
				break;
			}
			//enemy.setIsAttack(true);
			enemy.setState(enemy.getAttack());

		}

	}

	}
}

void enemyMoveState::update(enemy & enemy, ENEMYTYPE enemyType)
{
}


void enemyAttackState::update(enemy & enemy, ENEMYTYPE enemyType)
{
	//enemy.setIsAttack(true);
	//cout << enemy.getIsAttack() << endl;
	
	if (enemyType == ENEMY_GOLEM)
	{
		if (!KEYANIMANAGER->findAnimation(enemy.getIndex(), "golemLeftAttack")->isPlay() && !KEYANIMANAGER->findAnimation(enemy.getIndex(), "golemRightAttack")->isPlay() &&
			!KEYANIMANAGER->findAnimation(enemy.getIndex(), "golemUpAttack")->isPlay() && !KEYANIMANAGER->findAnimation(enemy.getIndex(), "golemDownAttack")->isPlay())
		{
			switch (enemy.getGolDriection())
			{
			case GOLEM_LEFT:
				enemy.setMotion(ImageManager::GetInstance()->FindImage("golem"), KEYANIMANAGER->findAnimation(enemy.getIndex(), "golemLeft"));
				break;
			case GOLEM_RIGHT:
				enemy.setMotion(ImageManager::GetInstance()->FindImage("golem"), KEYANIMANAGER->findAnimation(enemy.getIndex(), "golemRight"));
				break;
			case GOLEM_TOP:
				enemy.setMotion(ImageManager::GetInstance()->FindImage("golem"), KEYANIMANAGER->findAnimation(enemy.getIndex(), "golemUp"));
				break;
			case GOLEM_BOTTOM:
				enemy.setMotion(ImageManager::GetInstance()->FindImage("golem"), KEYANIMANAGER->findAnimation(enemy.getIndex(), "golemDown"));
				break;
			}
			enemy.setAttackDelay(0);
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
