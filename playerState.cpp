#include "stdafx.h"
#include "playerState.h"
#include "player.h"
#include "arrow.h"

HRESULT playerIdleState::init()
{
	return S_OK;
}

//Idle 상태
void playerIdleState::update(player & player)
{
	player.setPlayerRc(player.getX(), player.getY(), player.getPlayerRcW(), player.getPlayerRcH());	//사실상 필요없음 일단 냅둠~
	player.setBedCount(player.getBedCount() + 1);
	//아이들 상태 오래 지속되면 빗자루질함
	if (player.getBedCount() >= 300)
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerBroom"), ImageManager::GetInstance()->FindImage("playerBroom"));
		player.setCurrentState(player.getBroomState());
		player.setBedCount(player.getBedCount() == 0);
	}

	//에너미한테 맞으면 히트상태로 넘어감
	if (player.getEnemyCol())
	{
		player.setCurrentState(player.getHitState());
	}

	if (!player.getTransform())
	{
		//걷기
		//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
		//위
		if (KEYMANAGER->isOnceKeyDown('W'))
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpWalk"), ImageManager::GetInstance()->FindImage("playerUpWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::UP);
		}
		//아래 
		if (KEYMANAGER->isOnceKeyDown('S'))
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::DOWN);
		}
		//왼쪽 
		if (KEYMANAGER->isOnceKeyDown('A'))
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftWalk"), ImageManager::GetInstance()->FindImage("playerLeftWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::LEFT);
		}
		//오른쪽 
		if (KEYMANAGER->isOnceKeyDown('D'))
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightWalk"), ImageManager::GetInstance()->FindImage("playerRightWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::RIGHT);
		}
		//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	}

	//플레이어 구르기
	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		if (player.getDirection() == DIRECTION::RIGHT)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightRoll"), ImageManager::GetInstance()->FindImage("playerRightRoll"));
			player.setCurrentState(player.getRollState());
		}
		if (player.getDirection() == DIRECTION::LEFT)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftRoll"), ImageManager::GetInstance()->FindImage("playerLeftRoll"));
			player.setCurrentState(player.getRollState());
		}
		if (player.getDirection() == DIRECTION::DOWN)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownRoll"), ImageManager::GetInstance()->FindImage("playerDownRoll"));
			player.setCurrentState(player.getRollState());
		}
		if (player.getDirection() == DIRECTION::UP)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpRoll"), ImageManager::GetInstance()->FindImage("playerUpRoll"));
			player.setCurrentState(player.getRollState());
		}
		player.setBedCount(player.getBedCount() == 0);
	}
	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ


	//플레이어 사망 <-- 임시
	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	if (KEYMANAGER->isOnceKeyDown('0'))
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDie"), ImageManager::GetInstance()->FindImage("playerDie"));
		player.setCurrentState(player.getDieState());
	}
	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ

	//플레이어 쉴드
	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	if (!player.getWeaponChange())
	{
		if (KEYMANAGER->isOnceKeyDown('K'))
		{
			if (player.getDirection() == DIRECTION::RIGHT)
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightShield"), ImageManager::GetInstance()->FindImage("playerRightShield"));
				player.setCurrentState(player.getShieldState());
			}
			if (player.getDirection() == DIRECTION::LEFT)
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftShield"), ImageManager::GetInstance()->FindImage("playerLeftShield"));
				player.setCurrentState(player.getShieldState());
			}
			if (player.getDirection() == DIRECTION::DOWN)
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownShield"), ImageManager::GetInstance()->FindImage("playerDownShield"));
				player.setCurrentState(player.getShieldState());
			}
			if (player.getDirection() == DIRECTION::UP)
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpShield"), ImageManager::GetInstance()->FindImage("playerUpShield"));
				player.setCurrentState(player.getShieldState());
			}
			player.setBedCount(player.getBedCount() == 0);
		}
	}
	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ

	//플레이어 수영 && 던전 in <-- 임시
	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ

	if (player.getTransform())
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownSwim"), ImageManager::GetInstance()->FindImage("playerDownSwim"));
		player.setCurrentState(player.getSwimState());
		player.setDirection(DIRECTION::DOWN);
	}


	if (KEYMANAGER->isOnceKeyDown(VK_DELETE))
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerTeleportIn"), ImageManager::GetInstance()->FindImage("playerTeleportIn"));
		player.setCurrentState(player.getTeleportInState());
	}
	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ

	//무기 변경
	if (player.getWeaponChange())
	{
		if (KEYMANAGER->isOnceKeyDown('Z'))
		{
			//화살로 변경
			player.setWeaponChange(false);
			player.setCurrentState(player.getBowState());
		}
	}

	//무기 변경
	if (!player.getWeaponChange())
	{
		if (KEYMANAGER->isOnceKeyDown('Z'))
		{
			//검으로 변경
			player.setWeaponChange(true);
			player.setCurrentState(player.getSwordState());
		}
	}

	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ

	//활
	if (player.getWeaponChange())
	{
		//활 충전 카운트
		if (player.getBowBool())
		{
			player.setBowChargeCount(player.getBowChargeCount() + 1);
		}
		if (!player.getBowBool())
		{
			player.setBowChargeCount(player.getBowChargeCount() == 0);
		}

		//활충전 알파값
		if (player.getBowChargeAlpha())
		{
			player.setBowAlphaCount(player.getBowAlphaCount() + 1);
		}

		if (!player.getBowChargeAlpha())
		{
			player.setBowAlphaCount(player.getBowAlphaCount() == 0);
		}

		//활 바로 쏠수도있고 꾹누르면 충전됨
		if (KEYMANAGER->isOnceKeyDown('J'))
		{
			player.setBowBool(true);
		}

		if (player.getBowChargeCount() >= 30)
		{
			player.setBowChargeAlpha(true);
			player.setBowChargeState(true);
			if (KEYMANAGER->isStayKeyDown('J'))
			{
				if (player.getDirection() == DIRECTION::UP)
				{
					player.setShadowY(player.getShadowY() - 0);
					//알파값효과 내기위해
					if (player.getBowAlphaCount() <= 10)
					{
						player.setPlayerMotion(KEYANIMANAGER->findAnimation("bowUpChargeWhite"), ImageManager::GetInstance()->FindImage("bowUpChargeWhite"));
					}
					if (player.getBowAlphaCount() >= 11)
					{
						player.setPlayerMotion(KEYANIMANAGER->findAnimation("bowUpCharge"), ImageManager::GetInstance()->FindImage("bowUpCharge"));
					}
				}
				if (player.getDirection() == DIRECTION::DOWN)
				{
					if (player.getBowAlphaCount() <= 10)
					{
						player.setPlayerMotion(KEYANIMANAGER->findAnimation("bowDownChargeWhite"), ImageManager::GetInstance()->FindImage("bowDownChargeWhite"));
					}
					if (player.getBowAlphaCount() >= 11)
					{
						player.setPlayerMotion(KEYANIMANAGER->findAnimation("bowDownCharge"), ImageManager::GetInstance()->FindImage("bowDownCharge"));
					}
				}
				if (player.getDirection() == DIRECTION::LEFT)
				{
					if (player.getBowAlphaCount() <= 10)
					{
						player.setPlayerMotion(KEYANIMANAGER->findAnimation("bowLeftChargeWhite"), ImageManager::GetInstance()->FindImage("bowLeftChargeWhite"));
					}
					if (player.getBowAlphaCount() >= 11)
					{
						player.setPlayerMotion(KEYANIMANAGER->findAnimation("bowLeftCharge"), ImageManager::GetInstance()->FindImage("bowLeftCharge"));
					}
				}
				if (player.getDirection() == DIRECTION::RIGHT)
				{
					if (player.getBowAlphaCount() <= 10)
					{
						player.setPlayerMotion(KEYANIMANAGER->findAnimation("bowRightChargeWhite"), ImageManager::GetInstance()->FindImage("bowRightChargeWhite"));
					}
					if (player.getBowAlphaCount() >= 11)
					{
						player.setPlayerMotion(KEYANIMANAGER->findAnimation("bowRightCharge"), ImageManager::GetInstance()->FindImage("bowRightCharge"));
					}
				}
				player.setBedCount(player.getBedCount() == 0);
			}
		}

		if (KEYMANAGER->isOnceKeyUp('J'))
		{
			if (player.getDirection() == DIRECTION::UP)
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpBow"), ImageManager::GetInstance()->FindImage("playerUpBow"));
				player.setCurrentState(player.getBowState());
			}
			if (player.getDirection() == DIRECTION::DOWN)
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownBow"), ImageManager::GetInstance()->FindImage("playerDownBow"));
				player.setCurrentState(player.getBowState());
			}
			if (player.getDirection() == DIRECTION::LEFT)
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftBow"), ImageManager::GetInstance()->FindImage("playerLeftBow"));
				player.setCurrentState(player.getBowState());
			}
			if (player.getDirection() == DIRECTION::RIGHT)
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightBow"), ImageManager::GetInstance()->FindImage("playerRightBow"));
				player.setCurrentState(player.getBowState());
			}
			player.setBedCount(player.getBedCount() == 0);
			player.setBowBool(false);
			player.setBowChargeAlpha(false);
		}
	}

	//검
	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	if (!player.getWeaponChange())
	{
		if (KEYMANAGER->isOnceKeyDown('J'))
		{
			player.setSwordAttack(true);
			player.setAttackRcbool(true);
			if (player.getDirection() == DIRECTION::UP)
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpSword1"), ImageManager::GetInstance()->FindImage("playerUpSword1"));
				player.setCurrentState(player.getSwordState());
				player.setAttackRc(player.getX(), player.getY() - 50, 50, 60);
			}

			if (player.getDirection() == DIRECTION::DOWN)
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownSword1"), ImageManager::GetInstance()->FindImage("playerDownSword1"));
				player.setCurrentState(player.getSwordState());
				player.setAttackRc(player.getX(), player.getY() + 50, 50, 60);
			}

			if (player.getDirection() == DIRECTION::LEFT)
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftSword1"), ImageManager::GetInstance()->FindImage("playerLeftSword1"));
				player.setCurrentState(player.getSwordState());
				player.setAttackRc(player.getX() - 50, player.getY(), 60, 50);
			}

			if (player.getDirection() == DIRECTION::RIGHT)
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightSword1"), ImageManager::GetInstance()->FindImage("playerRightSword1"));
				player.setCurrentState(player.getSwordState());
				player.setAttackRc(player.getX() + 50, player.getY(), 60, 50);
			}
			player.setBedCount(player.getBedCount() == 0);
		}
	}
	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ

	//플레이어 텔레포트
	if (KEYMANAGER->isOnceKeyDown('L'))
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerTeleport"), ImageManager::GetInstance()->FindImage("playerTeleport"));
		player.setCurrentState(player.getTeleportState());
		player.setBedCount(player.getBedCount() == 0);
	}

}

//walk 상태
void playerWalkState::update(player & player)
{
	player.setPlayerRc(player.getX(), player.getY(), player.getPlayerRcW(), player.getPlayerRcH());

	//에너미한테 맞으면 히트상태로 넘어감
	if (player.getEnemyCol())
	{
		player.setCurrentState(player.getHitState());
	}

	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	//위

	int x = 0;
	int y = 0;

	if (player.getDirection() == DIRECTION::UP)
	{
		if (KEYMANAGER->isStayKeyDown('W'))
		{
			//만약 아래키 누르면 위쪽Idle 모습으로 변함
			if (KEYMANAGER->isOnceKeyDown('S'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpIdle"), ImageManager::GetInstance()->FindImage("playerUpIdle"));
			}
			//위쪽Idle 모습으로 멈추기
			else if (KEYMANAGER->isStayKeyDown('S'))
			{
				return;
			}
			//아래키를 떼면 위로 다시 움직임
			else if (KEYMANAGER->isOnceKeyUp('S'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpWalk"), ImageManager::GetInstance()->FindImage("playerUpWalk"));
				player.setCurrentState(player.getWalkState());
			}
			//만약 이동중 왼쪽키 누르면
			if (KEYMANAGER->isStayKeyDown('A'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpWalk"), ImageManager::GetInstance()->FindImage("playerUpWalk"));
				player.setCurrentState(player.getWalkState());
				player.setDirection(DIRECTION::LEFTTOP);
			}
			//만약 이동중 오른쪽키 누르면
			if (KEYMANAGER->isStayKeyDown('D'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpWalk"), ImageManager::GetInstance()->FindImage("playerUpWalk"));
				player.setCurrentState(player.getWalkState());
				player.setDirection(DIRECTION::RIGHTTOP);
			}
			//만약 이동중 구르기 누르면
			if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpRoll"), ImageManager::GetInstance()->FindImage("playerUpRoll"));
				player.setCurrentState(player.getRollState());
			}
			if (!player.getTileColTop())
			{
				y = -1;
			}
			else
			{
				y = 0;
			}
		}
	}

	//아래
	if (player.getDirection() == DIRECTION::DOWN)
	{
		if (KEYMANAGER->isStayKeyDown('S'))
		{
			//만약 위쪽키 누르면 아래 Idle 모습으로 변함
			if (KEYMANAGER->isOnceKeyDown('W'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownIdle"), ImageManager::GetInstance()->FindImage("playerDownIdle"));
			}
			//아래Idle 모습으로 멈추기
			else if (KEYMANAGER->isStayKeyDown('W'))
			{
				return;
			}
			//위쪽키를 떼면 아래로 다시 움직임
			else if (KEYMANAGER->isOnceKeyUp('W'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
				player.setCurrentState(player.getWalkState());
			}
			//만약 이동중 왼쪽키 누르면
			if (KEYMANAGER->isStayKeyDown('A'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
				player.setCurrentState(player.getWalkState());
				player.setDirection(DIRECTION::LEFTBOTTOM);
			}
			//만약 이동중 오른쪽키 누르면
			if (KEYMANAGER->isStayKeyDown('D'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
				player.setCurrentState(player.getWalkState());
				player.setDirection(DIRECTION::RIGHTBOTTOM);
			}

			//만약 이동중 구르기 누르면
			if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownRoll"), ImageManager::GetInstance()->FindImage("playerDownRoll"));
				player.setCurrentState(player.getRollState());
			}
			if (!player.getTileColBottom())
				y = 1;
			else
				y = 0;
		}
	}

	//왼쪽
	if (player.getDirection() == DIRECTION::LEFT)
	{
		if (KEYMANAGER->isStayKeyDown('A'))
		{
			//만약 오른쪽키 누르면 왼쪽 Idle 모습으로 변함
			if (KEYMANAGER->isOnceKeyDown('D'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftIdle"), ImageManager::GetInstance()->FindImage("playerLeftIdle"));
			}
			//왼쪽Idle 모습으로 멈추기
			else if (KEYMANAGER->isStayKeyDown('D'))
			{
				return;
			}
			//오른쪽키를 떼면 왼쪽으로 다시 움직임
			else if (KEYMANAGER->isOnceKeyUp('D'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftWalk"), ImageManager::GetInstance()->FindImage("playerLeftWalk"));
				player.setCurrentState(player.getWalkState());
			}
			//만약 이동중 위쪽키 누르면
			if (KEYMANAGER->isStayKeyDown('W'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpWalk"), ImageManager::GetInstance()->FindImage("playerUpWalk"));
				player.setCurrentState(player.getWalkState());
				player.setDirection(DIRECTION::LEFTTOP);
			}
			//만약 이동중 아래키 누르면
			if (KEYMANAGER->isStayKeyDown('S'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
				player.setCurrentState(player.getWalkState());
				player.setDirection(DIRECTION::LEFTBOTTOM);
			}

			//만약 이동중 구르기 누르면
			if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftRoll"), ImageManager::GetInstance()->FindImage("playerLeftRoll"));
				player.setCurrentState(player.getRollState());
			}
			if (!player.getTileColLeft())
				x = -1;
			else
				x = 0;
		}
	}

	//오른쪽
	if (player.getDirection() == DIRECTION::RIGHT)
	{
		if (KEYMANAGER->isStayKeyDown('D'))
		{
			//만약 왼쪽키 누르면 오른쪽 Idle 모습으로 변함
			if (KEYMANAGER->isOnceKeyDown('A'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightIdle"), ImageManager::GetInstance()->FindImage("playerRightIdle"));
			}
			//오른쪽Idle 모습으로 멈추기
			else if (KEYMANAGER->isStayKeyDown('A'))
			{
				return;
			}
			//왼쪽키를 떼면 오른쪽으로 다시 움직임
			else if (KEYMANAGER->isOnceKeyUp('A'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightWalk"), ImageManager::GetInstance()->FindImage("playerRightWalk"));
				player.setCurrentState(player.getWalkState());
			}

			//만약 이동중 왼쪽키 누르면
			if (KEYMANAGER->isStayKeyDown('W'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpWalk"), ImageManager::GetInstance()->FindImage("playerUpWalk"));
				player.setCurrentState(player.getWalkState());
				player.setDirection(DIRECTION::RIGHTTOP);
			}
			//만약 이동중 오른쪽키 누르면
			if (KEYMANAGER->isStayKeyDown('S'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
				player.setCurrentState(player.getWalkState());
				player.setDirection(DIRECTION::RIGHTBOTTOM);
			}

			//만약 이동중 구르기 누르면
			if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightRoll"), ImageManager::GetInstance()->FindImage("playerRightRoll"));
				player.setCurrentState(player.getRollState());
			}
			if (!player.getTileColRight())
				x = 1;
			else
				x = 0;
		}
	}

	//오른쪽위 이동
	if (player.getDirection() == DIRECTION::RIGHTTOP)
	{
		if (!player.getTileColRightTop())
		{
			x = 1;
			y = -1;
		}
		else
		{
			x = 0;
			y = 0;
		}
		//만약 이동중 구르기 누르면
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			if (KEYMANAGER->isStayKeyDown('D'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpRoll"), ImageManager::GetInstance()->FindImage("playerUpRoll"));
				player.setCurrentState(player.getRollState());
				player.setDirection(DIRECTION::RIGHTTOP);
			}
		}
	}

	//왼쪽위 이동
	if (player.getDirection() == DIRECTION::LEFTTOP)
	{
		if (!player.getTileColLeftTop())
		{
			x = -1;
			y = -1;
		}
		else
		{
			x = 0;
			y = 0;
		}
		//만약 이동중 구르기 누르면
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			if (KEYMANAGER->isStayKeyDown('A'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpRoll"), ImageManager::GetInstance()->FindImage("playerUpRoll"));
				player.setCurrentState(player.getRollState());
				player.setDirection(DIRECTION::LEFTTOP);
			}
		}
	}

	//왼쪽아래 이동
	if (player.getDirection() == DIRECTION::LEFTBOTTOM)
	{
		if (!player.getTileColLeftBottom())
		{
			x = -1;
			y = 1;
		}
		else
		{
			x = 0;
			y = 0;
		}
		//만약 이동중 구르기 누르면
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			if (KEYMANAGER->isStayKeyDown('A'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownRoll"), ImageManager::GetInstance()->FindImage("playerDownRoll"));
				player.setCurrentState(player.getRollState());
				player.setDirection(DIRECTION::LEFTBOTTOM);
			}
		}
	}

	//오른쪽아래 이동
	if (player.getDirection() == DIRECTION::RIGHTBOTTOM)
	{
		if (!player.getTileColRightBottom())
		{
			x = 1;
			y = 1;
		}
		else
		{
			x = 0;
			y = 0;
		}
		//만약 이동중 구르기 누르면
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			if (KEYMANAGER->isStayKeyDown('D'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownRoll"), ImageManager::GetInstance()->FindImage("playerDownRoll"));
				player.setCurrentState(player.getRollState());
				player.setDirection(DIRECTION::RIGHTBOTTOM);
			}
		}
	}

	Vector2 vec(x, y);
	Vector2 diagonal = Vector2::Normalize(&vec);
	if (Vector2::Length(&vec) > 1) // 대각선일 때
	{
		player.setShadowX(player.getShadowX() + (diagonal.x * MOVESPPED));
		//player.setX(player.getX() + (diagonal.x * MOVESPPED));
		player.setShadowY(player.getShadowY() + (diagonal.y * MOVESPPED));
		//player.setY(player.getY() + (diagonal.y * MOVESPPED));
	}
	else
	{
		//대각선 아닐때
		player.setShadowX(player.getShadowX() + (vec.x * MOVESPPED));
		//player.setX(player.getX() + (vec.x * MOVESPPED));
		player.setShadowY(player.getShadowY() + (vec.y * MOVESPPED));
		//player.setY(player.getY() + (vec.y * MOVESPPED));
	}

	//위쪽키 떼면
	if (KEYMANAGER->isOnceKeyUp('W'))
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpIdle"), ImageManager::GetInstance()->FindImage("playerUpIdle"));
		player.setCurrentState(player.getIdleState());

		//아래키를 누르면 다시 이동하게
		if (GetAsyncKeyState('S') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::DOWN);
		}
		//오른쪽키를 누르면 다시 이동하게
		else if (GetAsyncKeyState('D') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightWalk"), ImageManager::GetInstance()->FindImage("playerRightWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::RIGHT);
		}
		//왼쪽키를 누르면 다시 이동하게
		else if (GetAsyncKeyState('A') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftWalk"), ImageManager::GetInstance()->FindImage("playerLeftWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::LEFT);
		}
		player.setBedCount(player.getBedCount() == 0);
	}

	//아래키 떼면
	if (KEYMANAGER->isOnceKeyUp('S'))
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownIdle"), ImageManager::GetInstance()->FindImage("playerDownIdle"));
		player.setCurrentState(player.getIdleState());

		//위쪽키를 누르면 다시 이동하게
		if (GetAsyncKeyState('W') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpWalk"), ImageManager::GetInstance()->FindImage("playerUpWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::UP);
		}
		//오른쪽키를 누르면 다시 이동하게
		else if (GetAsyncKeyState('D') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightWalk"), ImageManager::GetInstance()->FindImage("playerRightWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::RIGHT);
		}
		//왼쪽키를 누르면 다시 이동하게
		else if (GetAsyncKeyState('A') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftWalk"), ImageManager::GetInstance()->FindImage("playerLeftWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::LEFT);
		}
		player.setBedCount(player.getBedCount() == 0);
	}

	//왼쪽키 떼면
	if (KEYMANAGER->isOnceKeyUp('A'))
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftIdle"), ImageManager::GetInstance()->FindImage("playerLeftIdle"));
		player.setCurrentState(player.getIdleState());

		//오른쪽키를 누르면 다시 이동하게
		if (GetAsyncKeyState('D') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightWalk"), ImageManager::GetInstance()->FindImage("playerRightWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::RIGHT);
		}
		//위쪽키를 누르면 다시 이동하게
		else if (GetAsyncKeyState('W') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpWalk"), ImageManager::GetInstance()->FindImage("playerUpWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::UP);
		}
		//아래를 누르면 다시 이동하게
		else if (GetAsyncKeyState('S') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::DOWN);
		}
		player.setBedCount(player.getBedCount() == 0);
	}

	//오른쪽키 떼면
	if (KEYMANAGER->isOnceKeyUp('D'))
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightIdle"), ImageManager::GetInstance()->FindImage("playerRightIdle"));
		player.setCurrentState(player.getIdleState());

		//왼쪽키를 누르면 다시 이동하게
		if (GetAsyncKeyState('A') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftWalk"), ImageManager::GetInstance()->FindImage("playerLeftWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::LEFT);
		}
		//위쪽키를 누르면 다시 이동하게
		else if (GetAsyncKeyState('W') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpWalk"), ImageManager::GetInstance()->FindImage("playerUpWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::UP);
		}
		//아래를 누르면 다시 이동하게
		else if (GetAsyncKeyState('S') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::DOWN);
		}
		player.setBedCount(player.getBedCount() == 0);
	}
	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ

	//플레이어 구르기
	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		if (player.getDirection() == DIRECTION::RIGHT)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightRoll"), ImageManager::GetInstance()->FindImage("playerRightRoll"));
			player.setCurrentState(player.getRollState());
		}
		if (player.getDirection() == DIRECTION::LEFT)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftRoll"), ImageManager::GetInstance()->FindImage("playerLeftRoll"));
			player.setCurrentState(player.getRollState());
		}
		if (player.getDirection() == DIRECTION::DOWN)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownRoll"), ImageManager::GetInstance()->FindImage("playerDownRoll"));
			player.setCurrentState(player.getRollState());
		}
		if (player.getDirection() == DIRECTION::UP)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpRoll"), ImageManager::GetInstance()->FindImage("playerUpRoll"));
			player.setCurrentState(player.getRollState());
		}
	}
	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ

	//플레이어 쉴드
	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	if (!player.getWeaponChange())
	{
		if (KEYMANAGER->isOnceKeyDown('K'))
		{
			if (player.getDirection() == DIRECTION::RIGHT)
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightShield"), ImageManager::GetInstance()->FindImage("playerRightShield"));
				player.setCurrentState(player.getShieldState());
			}
			if (player.getDirection() == DIRECTION::LEFT)
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftShield"), ImageManager::GetInstance()->FindImage("playerLeftShield"));
				player.setCurrentState(player.getShieldState());
			}
			if (player.getDirection() == DIRECTION::DOWN)
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownShield"), ImageManager::GetInstance()->FindImage("playerDownShield"));
				player.setCurrentState(player.getShieldState());
			}
			if (player.getDirection() == DIRECTION::UP)
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpShield"), ImageManager::GetInstance()->FindImage("playerUpShield"));
				player.setCurrentState(player.getShieldState());
			}
		}
	}
	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ

	//무기 변경
	if (player.getWeaponChange())
	{
		if (KEYMANAGER->isOnceKeyDown('Z'))
		{
			//화살로 변경
			player.setWeaponChange(false);
			player.setCurrentState(player.getBowState());
		}
	}

	//무기 변경
	if (!player.getWeaponChange())
	{
		if (KEYMANAGER->isOnceKeyDown('Z'))
		{
			//검으로 변경
			player.setWeaponChange(true);
			player.setCurrentState(player.getSwordState());
		}
	}

	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	//활
	if (player.getWeaponChange())
	{
		//활 충전 카운트
		if (player.getBowBool())
		{
			player.setBowChargeCount(player.getBowChargeCount() + 1);
		}
		if (!player.getBowBool())
		{
			player.setBowChargeCount(player.getBowChargeCount() == 0);
		}

		//활충전 알파값
		if (player.getBowChargeAlpha())
		{
			player.setBowAlphaCount(player.getBowAlphaCount() + 1);
		}

		if (!player.getBowChargeAlpha())
		{
			player.setBowAlphaCount(player.getBowAlphaCount() == 0);
		}

		//활 바로 쏠수도있고 꾹누르면 충전됨
		if (KEYMANAGER->isOnceKeyDown('J'))
		{
			player.setBowBool(true);
		}

		if (player.getBowChargeCount() >= 30)
		{
			player.setBowChargeAlpha(true);

			if (KEYMANAGER->isStayKeyDown('J'))
			{
				if (player.getDirection() == DIRECTION::UP)
				{
					//알파값효과 내기위해
					if (player.getBowAlphaCount() <= 10)
					{
						player.setPlayerMotion(KEYANIMANAGER->findAnimation("bowUpChargeWhite"), ImageManager::GetInstance()->FindImage("bowUpChargeWhite"));
					}
					if (player.getBowAlphaCount() >= 11)
					{
						player.setPlayerMotion(KEYANIMANAGER->findAnimation("bowUpCharge"), ImageManager::GetInstance()->FindImage("bowUpCharge"));
					}
				}
				if (player.getDirection() == DIRECTION::DOWN)
				{
					if (player.getBowAlphaCount() <= 10)
					{
						player.setPlayerMotion(KEYANIMANAGER->findAnimation("bowDownChargeWhite"), ImageManager::GetInstance()->FindImage("bowDownChargeWhite"));
					}
					if (player.getBowAlphaCount() >= 11)
					{
						player.setPlayerMotion(KEYANIMANAGER->findAnimation("bowDownCharge"), ImageManager::GetInstance()->FindImage("bowDownCharge"));
					}
				}
				if (player.getDirection() == DIRECTION::LEFT)
				{
					if (player.getBowAlphaCount() <= 10)
					{
						player.setPlayerMotion(KEYANIMANAGER->findAnimation("bowLeftChargeWhite"), ImageManager::GetInstance()->FindImage("bowLeftChargeWhite"));
					}
					if (player.getBowAlphaCount() >= 11)
					{
						player.setPlayerMotion(KEYANIMANAGER->findAnimation("bowLeftCharge"), ImageManager::GetInstance()->FindImage("bowLeftCharge"));
					}
				}
				if (player.getDirection() == DIRECTION::RIGHT)
				{
					if (player.getBowAlphaCount() <= 10)
					{
						player.setPlayerMotion(KEYANIMANAGER->findAnimation("bowRightChargeWhite"), ImageManager::GetInstance()->FindImage("bowRightChargeWhite"));
					}
					if (player.getBowAlphaCount() >= 11)
					{
						player.setPlayerMotion(KEYANIMANAGER->findAnimation("bowRightCharge"), ImageManager::GetInstance()->FindImage("bowRightCharge"));
					}
				}
				player.setBedCount(player.getBedCount() == 0);
			}
		}

		if (KEYMANAGER->isOnceKeyUp('J'))
		{
			if (player.getDirection() == DIRECTION::UP)
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpBow"), ImageManager::GetInstance()->FindImage("playerUpBow"));
				player.setCurrentState(player.getBowState());
			}
			if (player.getDirection() == DIRECTION::DOWN)
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownBow"), ImageManager::GetInstance()->FindImage("playerDownBow"));
				player.setCurrentState(player.getBowState());
			}
			if (player.getDirection() == DIRECTION::LEFT)
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftBow"), ImageManager::GetInstance()->FindImage("playerLeftBow"));
				player.setCurrentState(player.getBowState());
			}
			if (player.getDirection() == DIRECTION::RIGHT)
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightBow"), ImageManager::GetInstance()->FindImage("playerRightBow"));
				player.setCurrentState(player.getBowState());
			}
			player.setBedCount(player.getBedCount() == 0);
			player.setBowBool(false);
			player.setBowChargeAlpha(false);
		}
	}

	//검
	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	if (!player.getWeaponChange())
	{
		if (KEYMANAGER->isOnceKeyDown('J'))
		{
			player.setSwordAttack(true);

			if (player.getDirection() == DIRECTION::UP)
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpSword1"), ImageManager::GetInstance()->FindImage("playerUpSword1"));
				player.setCurrentState(player.getSwordState());
				player.setAttackRc(player.getX(), player.getY() - 50, 50, 60);
			}

			if (player.getDirection() == DIRECTION::DOWN)
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownSword1"), ImageManager::GetInstance()->FindImage("playerDownSword1"));
				player.setCurrentState(player.getSwordState());
				player.setAttackRc(player.getX(), player.getY() + 50, 50, 60);
			}

			if (player.getDirection() == DIRECTION::LEFT)
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftSword1"), ImageManager::GetInstance()->FindImage("playerLeftSword1"));
				player.setCurrentState(player.getSwordState());
				player.setAttackRc(player.getX() - 50, player.getY(), 60, 50);
			}

			if (player.getDirection() == DIRECTION::RIGHT)
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightSword1"), ImageManager::GetInstance()->FindImage("playerRightSword1"));
				player.setCurrentState(player.getSwordState());
				player.setAttackRc(player.getX() + 50, player.getY(), 60, 50);
			}
		}
	}
	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
}

//roll(구르기) 상태
void playerRollState::update(player & player)
{
	player.setPlayerRc(player.getX(), player.getY(), player.getPlayerRcW(), player.getPlayerRcH());
	//위로 구르기 
	if (player.getDirection() == DIRECTION::UP)
	{
		if (!player.getTileColTop())
			player.setShadowY(player.getShadowY() - 7);
	}
	//아래로 구르기
	if (player.getDirection() == DIRECTION::DOWN)
	{
		if (!player.getTileColBottom())
			player.setShadowY(player.getShadowY() + 7);
	}
	//왼쪽으로 구르기
	if (player.getDirection() == DIRECTION::LEFT)
	{
		if (!player.getTileColLeft())
			player.setShadowX(player.getShadowX() - 7);
	}
	//오른쪽으로 구르기
	if (player.getDirection() == DIRECTION::RIGHT)
	{
		if (!player.getTileColRight())
			player.setShadowX(player.getShadowX() + 7);
	}

	//오른쪽위 구르기
	if (player.getDirection() == DIRECTION::RIGHTTOP)
	{
		if (!player.getTileColRightTop())
		{
			player.setShadowY(player.getShadowY() - 7);
			player.setShadowX(player.getShadowX() + 5);
		}
	}

	//왼쪽위 구르기
	if (player.getDirection() == DIRECTION::LEFTTOP)
	{
		if (!player.getTileColLeftTop())
		{
			player.setShadowY(player.getShadowY() - 7);
			player.setShadowX(player.getShadowX() - 5);
		}
	}

	//왼쪽아래 구르기
	if (player.getDirection() == DIRECTION::LEFTBOTTOM)
	{
		if (!player.getTileColLeftBottom())
		{
			player.setShadowY(player.getShadowY() + 7);
			player.setShadowX(player.getShadowX() - 5);
		}
	}

	//오른쪽아래 구르기
	if (player.getDirection() == DIRECTION::RIGHTBOTTOM)
	{
		if (!player.getTileColRightBottom())
		{
			player.setShadowY(player.getShadowY() + 7);
			player.setShadowX(player.getShadowX() + 5);
		}
	}

	//애니메이션 재생이 끝나면 
	if (!KEYANIMANAGER->findAnimation("playerUpRoll")->isPlay()
		&& !KEYANIMANAGER->findAnimation("playerDownRoll")->isPlay()
		&& !KEYANIMANAGER->findAnimation("playerLeftRoll")->isPlay()
		&& !KEYANIMANAGER->findAnimation("playerRightRoll")->isPlay())
	{
		player.setPlayerRc(player.getX(), player.getY(), player.getPlayerRcW(), player.getPlayerRcH());
		//위쪽키를 누르면 다시 이동하게
		if (GetAsyncKeyState('W') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpWalk"), ImageManager::GetInstance()->FindImage("playerUpWalk"));
			player.setCurrentState(player.getWalkState());
		}
		//아래키를 누르면 다시 이동하게
		else if (GetAsyncKeyState('S') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
			player.setCurrentState(player.getWalkState());
		}
		//오른쪽키를 누르면 다시 이동하게
		else if (GetAsyncKeyState('D') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightWalk"), ImageManager::GetInstance()->FindImage("playerRightWalk"));
			player.setCurrentState(player.getWalkState());
		}
		//왼쪽키를 누르면 다시 이동하게
		else if (GetAsyncKeyState('A') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftWalk"), ImageManager::GetInstance()->FindImage("playerLeftWalk"));
			player.setCurrentState(player.getWalkState());
		}
		//아무키도 누르지 않고있으면 Idle 상태로 전환
		else
		{
			player.setPlayerRc(player.getX(), player.getY(), player.getPlayerRcW(), player.getPlayerRcH());
			if (player.getDirection() == DIRECTION::UP || KEYMANAGER->isOnceKeyUp('W'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpIdle"), ImageManager::GetInstance()->FindImage("playerUpIdle"));
				player.setCurrentState(player.getIdleState());
			}

			if (player.getDirection() == DIRECTION::DOWN || KEYMANAGER->isOnceKeyUp('S'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownIdle"), ImageManager::GetInstance()->FindImage("playerDownIdle"));
				player.setCurrentState(player.getIdleState());
			}

			if (player.getDirection() == DIRECTION::LEFT)
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftIdle"), ImageManager::GetInstance()->FindImage("playerLeftIdle"));
				player.setCurrentState(player.getIdleState());
			}

			if (player.getDirection() == DIRECTION::RIGHT)
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightIdle"), ImageManager::GetInstance()->FindImage("playerRightIdle"));
				player.setCurrentState(player.getIdleState());
			}
		}
	}
}

//die 상태
void playerDieState::update(player & player)
{
	player.setPlayerRc(player.getX(), player.getY(), player.getPlayerRcW(), player.getPlayerRcH());
	//아무키도 안누르면 Idle 상태로 전환
	if (KEYMANAGER->isOnceKeyUp('0'))
	{
		if (KEYMANAGER->getKeyUp() == NULL)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpIdle"), ImageManager::GetInstance()->FindImage("playerUpIdle"));
			player.setCurrentState(player.getIdleState());
		}
		//아래키를 누르면 다시 이동
		else if (GetAsyncKeyState('S') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::DOWN);
		}
	}
}

//shield 상태
void playerShieldState::update(player & player)
{
	player.setPlayerRc(player.getX(), player.getY(), player.getPlayerRcW(), player.getPlayerRcH());
	//플레이어 쉴드
	if (KEYMANAGER->isStayKeyDown('K'));
	{
		if (player.getDirection() == DIRECTION::RIGHT)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightShield"), ImageManager::GetInstance()->FindImage("playerRightShield"));
			if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightRoll"), ImageManager::GetInstance()->FindImage("playerRightRoll"));
				player.setCurrentState(player.getRollState());
			}
			if (KEYMANAGER->isStayKeyDown('D'))
			{
				player.setShadowX(player.getShadowX() + 1);
				player.setX(player.getX() + 1);
			}
			if (KEYMANAGER->isStayKeyDown('A'))
			{
				player.setShadowX(player.getShadowX() - 1);
				player.setX(player.getX() - 1);
			}
			if (KEYMANAGER->isStayKeyDown('S'))
			{
				player.setShadowY(player.getShadowY() + 1);
				player.setY(player.getY() + 1);
			}
			if (KEYMANAGER->isStayKeyDown('W'))
			{
				player.setShadowY(player.getShadowY() - 1);
				player.setY(player.getY() - 1);
			}
		}
		if (player.getDirection() == DIRECTION::LEFT)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftShield"), ImageManager::GetInstance()->FindImage("playerLeftShield"));
			if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftRoll"), ImageManager::GetInstance()->FindImage("playerLeftRoll"));
				player.setCurrentState(player.getRollState());
			}
			if (KEYMANAGER->isStayKeyDown('D'))
			{
				player.setShadowX(player.getShadowX() + 1);
				player.setX(player.getX() + 1);
			}
			if (KEYMANAGER->isStayKeyDown('A'))
			{
				player.setShadowX(player.getShadowX() - 1);
				player.setX(player.getX() - 1);
			}
			if (KEYMANAGER->isStayKeyDown('S'))
			{
				player.setShadowY(player.getShadowY() + 1);
				player.setY(player.getY() + 1);
			}
			if (KEYMANAGER->isStayKeyDown('W'))
			{
				player.setShadowY(player.getShadowY() - 1);
				player.setY(player.getY() - 1);
			}
		}
		if (player.getDirection() == DIRECTION::DOWN)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownShield"), ImageManager::GetInstance()->FindImage("playerDownShield"));
			if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownRoll"), ImageManager::GetInstance()->FindImage("playerDownRoll"));
				player.setCurrentState(player.getRollState());
			}
			if (KEYMANAGER->isStayKeyDown('D'))
			{
				player.setShadowX(player.getShadowX() + 1);
				player.setX(player.getX() + 1);
			}
			if (KEYMANAGER->isStayKeyDown('A'))
			{
				player.setShadowX(player.getShadowX() - 1);
				player.setX(player.getX() - 1);
			}
			if (KEYMANAGER->isStayKeyDown('S'))
			{
				player.setShadowY(player.getShadowY() + 1);
				player.setY(player.getY() + 1);
			}
			if (KEYMANAGER->isStayKeyDown('W'))
			{
				player.setShadowY(player.getShadowY() - 1);
				player.setY(player.getY() - 1);
			}
		}
		if (player.getDirection() == DIRECTION::UP)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpShield"), ImageManager::GetInstance()->FindImage("playerUpShield"));
			if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpRoll"), ImageManager::GetInstance()->FindImage("playerUpRoll"));
				player.setCurrentState(player.getRollState());
			}
			if (KEYMANAGER->isStayKeyDown('D'))
			{
				player.setShadowX(player.getShadowX() + 1);
				player.setX(player.getX() + 1);
			}
			if (KEYMANAGER->isStayKeyDown('A'))
			{
				player.setShadowX(player.getShadowX() - 1);
				player.setX(player.getX() - 1);
			}
			if (KEYMANAGER->isStayKeyDown('S'))
			{
				player.setShadowY(player.getShadowY() + 1);
				player.setY(player.getY() + 1);
			}
			if (KEYMANAGER->isStayKeyDown('W'))
			{
				player.setShadowY(player.getShadowY() - 1);
				player.setY(player.getY() - 1);
			}
		}
	}

	//쉴드키 떼면
	if (KEYMANAGER->isOnceKeyUp('K'))
	{
		if (KEYMANAGER->getKeyUp() == NULL || KEYMANAGER->isOnceKeyUp('W') || KEYMANAGER->isOnceKeyUp('S') || KEYMANAGER->isOnceKeyUp('A') || KEYMANAGER->isOnceKeyUp('D'))
		{
			if (player.getDirection() == DIRECTION::RIGHT)
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightIdle"), ImageManager::GetInstance()->FindImage("playerRightIdle"));
				player.setCurrentState(player.getIdleState());
			}
			if (player.getDirection() == DIRECTION::LEFT)
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftIdle"), ImageManager::GetInstance()->FindImage("playerLeftIdle"));
				player.setCurrentState(player.getIdleState());
			}
			if (player.getDirection() == DIRECTION::DOWN)
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownIdle"), ImageManager::GetInstance()->FindImage("playerDownIdle"));
				player.setCurrentState(player.getIdleState());
			}
			if (player.getDirection() == DIRECTION::UP)
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpIdle"), ImageManager::GetInstance()->FindImage("playerUpIdle"));
				player.setCurrentState(player.getIdleState());
			}
		}
		//오른쪽키를 누르면 다시 이동하게
		else if (GetAsyncKeyState('D') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightWalk"), ImageManager::GetInstance()->FindImage("playerRightWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::RIGHT);
		}
		//왼쪽키를 누르면 다시 이동하게
		else if (GetAsyncKeyState('A') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftWalk"), ImageManager::GetInstance()->FindImage("playerLeftWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::LEFT);
		}
		//위쪽키를 누르면 다시 이동하게
		else if (GetAsyncKeyState('W') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpWalk"), ImageManager::GetInstance()->FindImage("playerUpWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::UP);
		}
		//아래키를 누르면 다시 이동하게
		else if (GetAsyncKeyState('S') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::DOWN);
		}
	}
}

//idleSwim 상태
void playerIdleSwimState::update(player & player)
{
	player.setPlayerRc(player.getX(), player.getY(), player.getPlayerRcW(), player.getPlayerRcH());
	//위
	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpSwim"), ImageManager::GetInstance()->FindImage("playerUpSwim"));
		player.setCurrentState(player.getSwimState());
		player.setDirection(DIRECTION::UP);
	}

	//아래
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownSwim"), ImageManager::GetInstance()->FindImage("playerDownSwim"));
		player.setCurrentState(player.getSwimState());
		player.setDirection(DIRECTION::DOWN);
	}

	//왼쪽
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftSwim"), ImageManager::GetInstance()->FindImage("playerLeftSwim"));
		player.setCurrentState(player.getSwimState());
		player.setDirection(DIRECTION::LEFT);
	}

	//오른쪽
	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightSwim"), ImageManager::GetInstance()->FindImage("playerRightSwim"));
		player.setCurrentState(player.getSwimState());
		player.setDirection(DIRECTION::RIGHT);
	}
}


//swim 상태
void playerSwimState::update(player & player)
{
	player.setPlayerRc(player.getX(), player.getY(), player.getPlayerRcW(), player.getPlayerRcH());
	//위 
	if (player.getDirection() == DIRECTION::UP)
	{
		if (KEYMANAGER->isStayKeyDown('W'))
		{
			//만약 아래쪽키 누르면 위쪽 idleSwim 모습으로 변함
			if (KEYMANAGER->isOnceKeyDown('S'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpIdleSwim"), ImageManager::GetInstance()->FindImage("playerUpIdleSwim"));
			}
			//위쪽 idleSwim 모습으로 멈추기
			else if (KEYMANAGER->isStayKeyDown('S'))
			{
				player.setShadowY(player.getShadowY() - 0);
				player.setY(player.getY() - 0);
				return;
			}
			//키 떼면 다시 이동
			else if (KEYMANAGER->isOnceKeyUp('S'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpSwim"), ImageManager::GetInstance()->FindImage("playerUpSwim"));
				player.setCurrentState(player.getSwimState());
			}
			player.setShadowY(player.getShadowY() - 3);
			player.setY(player.getY() - 3);
		}
	}

	//위쪽키 떼면
	if (KEYMANAGER->isOnceKeyUp('W'))
	{
		//아무키도 안누르면 Idle 상태로 전환
		if (KEYMANAGER->getKeyUp() == NULL)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpIdleSwim"), ImageManager::GetInstance()->FindImage("playerUpIdleSwim"));
			player.setCurrentState(player.getIdleSwimState());
		}
		//아래키를 누르면 다시 이동
		else if (GetAsyncKeyState('S') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownSwim"), ImageManager::GetInstance()->FindImage("playerDownSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirection(DIRECTION::DOWN);
		}
		//왼쪽키를 누르면 다시 이동
		else if (GetAsyncKeyState('A') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftSwim"), ImageManager::GetInstance()->FindImage("playerLeftSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirection(DIRECTION::LEFT);
		}
		//오른쪽키를 누르면 다시 이동
		else if (GetAsyncKeyState('D') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightSwim"), ImageManager::GetInstance()->FindImage("playerRightSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirection(DIRECTION::RIGHT);
		}
		player.setBedCount(player.getBedCount() == 0);
	}

	//아래
	if (player.getDirection() == DIRECTION::DOWN)
	{
		if (KEYMANAGER->isStayKeyDown('S'))
		{
			//만약 위쪽키 누르면 아래 idleSwim 모습으로 변함
			if (KEYMANAGER->isOnceKeyDown('W'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownIdleSwim"), ImageManager::GetInstance()->FindImage("playerDownIdleSwim"));
			}
			//아래 idleSwim 모습으로 멈추기
			else if (KEYMANAGER->isStayKeyDown('W'))
			{
				player.setShadowY(player.getShadowY() + 0);
				player.setY(player.getY() + 0);
				return;
			}
			//키 떼면 다시 이동
			else if (KEYMANAGER->isOnceKeyUp('W'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownSwim"), ImageManager::GetInstance()->FindImage("playerDownSwim"));
				player.setCurrentState(player.getSwimState());
			}
			player.setShadowY(player.getShadowY() + 3);
			player.setY(player.getY() + 3);
		}
	}

	//아래쪽키 떼면
	if (KEYMANAGER->isOnceKeyUp('S'))
	{
		//아무키도 안누르면 Idle 상태로 전환
		if (KEYMANAGER->getKeyUp() == NULL)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownIdleSwim"), ImageManager::GetInstance()->FindImage("playerDownIdleSwim"));
			player.setCurrentState(player.getIdleSwimState());
		}
		//위쪽키를 누르면 다시 이동
		else if (GetAsyncKeyState('W') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpSwim"), ImageManager::GetInstance()->FindImage("playerUpSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirection(DIRECTION::UP);
		}
		//왼쪽키를 누르면 다시 이동
		else if (GetAsyncKeyState('A') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftSwim"), ImageManager::GetInstance()->FindImage("playerLeftSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirection(DIRECTION::LEFT);
		}
		//오른쪽키를 누르면 다시 이동
		else if (GetAsyncKeyState('D') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightSwim"), ImageManager::GetInstance()->FindImage("playerRightSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirection(DIRECTION::RIGHT);
		}
		player.setBedCount(player.getBedCount() == 0);
	}

	//왼쪽
	if (player.getDirection() == DIRECTION::LEFT)
	{
		if (KEYMANAGER->isStayKeyDown('A'))
		{
			//만약 오른쪽키 누르면 왼쪽 idleSwim 모습으로 변함
			if (KEYMANAGER->isOnceKeyDown('D'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftIdleSwim"), ImageManager::GetInstance()->FindImage("playerLeftIdleSwim"));
			}
			//왼쪽 idleSwim 모습으로 멈추기
			else if (KEYMANAGER->isStayKeyDown('D'))
			{
				player.setShadowX(player.getShadowX() - 0);
				player.setX(player.getX() - 0);
				return;
			}
			//키 떼면 다시 이동
			else if (KEYMANAGER->isOnceKeyUp('D'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftSwim"), ImageManager::GetInstance()->FindImage("playerLeftSwim"));
				player.setCurrentState(player.getSwimState());
			}
			player.setShadowX(player.getShadowX() - 3);
			player.setX(player.getX() - 3);
		}
	}

	//왼쪽키 떼면
	if (KEYMANAGER->isOnceKeyUp('A'))
	{
		//아무키도 안누르면 Idle 상태로 전환
		if (KEYMANAGER->getKeyUp() == NULL)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftIdleSwim"), ImageManager::GetInstance()->FindImage("playerLeftIdleSwim"));
			player.setCurrentState(player.getIdleSwimState());
		}
		//오른쪽키를 누르면 다시 이동
		else if (GetAsyncKeyState('D') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightSwim"), ImageManager::GetInstance()->FindImage("playerRightSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirection(DIRECTION::RIGHT);
		}
		//위쪽키를 누르면 다시 이동
		else if (GetAsyncKeyState('W') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpSwim"), ImageManager::GetInstance()->FindImage("playerUpSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirection(DIRECTION::UP);
		}
		//아래키를 누르면 다시 이동
		else if (GetAsyncKeyState('S') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownSwim"), ImageManager::GetInstance()->FindImage("playerDownSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirection(DIRECTION::DOWN);
		}
		player.setBedCount(player.getBedCount() == 0);
	}

	//오른쪽
	if (player.getDirection() == DIRECTION::RIGHT)
	{
		if (KEYMANAGER->isStayKeyDown('D'))
		{
			//만약 왼쪽키 누르면 오른쪽 idleSwim 모습으로 변함
			if (KEYMANAGER->isOnceKeyDown('A'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightIdleSwim"), ImageManager::GetInstance()->FindImage("playerRightIdleSwim"));
			}
			//오른쪽 idleSwim 모습으로 멈추기
			else if (KEYMANAGER->isStayKeyDown('A'))
			{
				player.setShadowX(player.getShadowX() + 0);
				player.setX(player.getX() + 0);
				return;
			}
			//키 떼면 다시 이동
			else if (KEYMANAGER->isOnceKeyUp('A'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightSwim"), ImageManager::GetInstance()->FindImage("playerRightSwim"));
				player.setCurrentState(player.getSwimState());
			}
			player.setShadowX(player.getShadowX() + 3);
			player.setX(player.getX() + 3);
		}
	}

	//오른쪽키 떼면
	if (KEYMANAGER->isOnceKeyUp('D'))
	{
		//아무키도 안누르면 Idle 상태로 전환
		if (KEYMANAGER->getKeyUp() == NULL)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightIdleSwim"), ImageManager::GetInstance()->FindImage("playerRightIdleSwim"));
			player.setCurrentState(player.getIdleSwimState());
		}
		//왼쪽키를 누르면 다시 이동
		else if (GetAsyncKeyState('A') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftSwim"), ImageManager::GetInstance()->FindImage("playerLeftSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirection(DIRECTION::LEFT);
		}
		//위쪽키를 누르면 다시 이동
		else if (GetAsyncKeyState('W') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpSwim"), ImageManager::GetInstance()->FindImage("playerUpSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirection(DIRECTION::UP);
		}
		//아래키를 누르면 다시 이동
		else if (GetAsyncKeyState('S') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownSwim"), ImageManager::GetInstance()->FindImage("playerDownSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirection(DIRECTION::DOWN);
		}
		player.setBedCount(player.getBedCount() == 0);
	}
}

//bow 상태
void playerbowState::update(player & player)
{
	//에너미한테 맞으면 히트상태로 넘어감
	if (player.getEnemyCol())
	{
		player.setCurrentState(player.getHitState());
	}

	player.setPlayerRc(player.getX(), player.getY(), player.getPlayerRcW(), player.getPlayerRcH());
	//만약 애니메이션 재생 끝나면
	if (!KEYANIMANAGER->findAnimation("playerUpBow")->isPlay() && !KEYANIMANAGER->findAnimation("playerDownBow")->isPlay()
		&& !KEYANIMANAGER->findAnimation("playerLeftBow")->isPlay() && !KEYANIMANAGER->findAnimation("playerRightBow")->isPlay())
	{
		//아무키도 누르지않으면 아이들 상태로 전환
		if (KEYMANAGER->getKeyUp() == NULL || KEYMANAGER->isOnceKeyUp('W') || KEYMANAGER->isOnceKeyUp('S') || KEYMANAGER->isOnceKeyUp('A') || KEYMANAGER->isOnceKeyUp('D'))
		{
			if (player.getDirection() == DIRECTION::UP)
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpIdle"), ImageManager::GetInstance()->FindImage("playerUpIdle"));
				player.setCurrentState(player.getIdleState());
				player.setDirection(DIRECTION::UP);
			}

			if (player.getDirection() == DIRECTION::DOWN)
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownIdle"), ImageManager::GetInstance()->FindImage("playerDownIdle"));
				player.setCurrentState(player.getIdleState());
				player.setDirection(DIRECTION::DOWN);
			}

			if (player.getDirection() == DIRECTION::LEFT)
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftIdle"), ImageManager::GetInstance()->FindImage("playerLeftIdle"));
				player.setCurrentState(player.getIdleState());
				player.setDirection(DIRECTION::LEFT);
			}

			if (player.getDirection() == DIRECTION::RIGHT)
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightIdle"), ImageManager::GetInstance()->FindImage("playerRightIdle"));
				player.setCurrentState(player.getIdleState());
				player.setDirection(DIRECTION::RIGHT);
			}
		}

		//오른쪽키를 누르면 다시 이동하게
		else if (GetAsyncKeyState('D') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightWalk"), ImageManager::GetInstance()->FindImage("playerRightWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::RIGHT);
		}
		//왼쪽키를 누르면 다시 이동하게
		else if (GetAsyncKeyState('A') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftWalk"), ImageManager::GetInstance()->FindImage("playerLeftWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::LEFT);
		}
		//위쪽키를 누르면 다시 이동하게
		else if (GetAsyncKeyState('W') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpWalk"), ImageManager::GetInstance()->FindImage("playerUpWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::UP);
		}
		//아래키를 누르면 다시 이동하게
		else if (GetAsyncKeyState('S') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::DOWN);
		}
	}
}

//sword 상태
void playerSwordState::update(player & player)
{
	//에너미한테 맞으면 히트상태로 넘어감
	if (player.getEnemyCol())
	{
		player.setCurrentState(player.getHitState());
	}

	player.setPlayerRc(player.getX(), player.getY(), player.getPlayerRcW(), player.getPlayerRcH());
	//1타 공격
	if (!player.getSwordAttackCombo())
	{
		if (KEYMANAGER->isOnceKeyDown('J'))
		{
			player.setSwrodAttackCombo(true);
		}
	}

	//공격중
	if (player.getSwordAttack())
	{
		if (player.getPlayerMotion() == KEYANIMANAGER->findAnimation("playerUpSword1")
			|| player.getPlayerMotion() == KEYANIMANAGER->findAnimation("playerDownSword1")
			|| player.getPlayerMotion() == KEYANIMANAGER->findAnimation("playerLeftSword1")
			|| player.getPlayerMotion() == KEYANIMANAGER->findAnimation("playerRightSword1"))
		{
			//애니메이션 재생 끝나면
			if (!KEYANIMANAGER->findAnimation("playerUpSword1")->isPlay() && !KEYANIMANAGER->findAnimation("playerDownSword1")->isPlay()
				&& !KEYANIMANAGER->findAnimation("playerLeftSword1")->isPlay() && !KEYANIMANAGER->findAnimation("playerRightSword1")->isPlay())
			{
				player.setAttackRcbool(false);
				player.setAttackRc(player.getX(), player.getY(), 0, 0);
				//키누르면 2타로 넘어감
				if (player.getSwordAttackCombo())
				{
					player.setSwordAttack(true);
					if (player.getDirection() == DIRECTION::UP)
					{
						player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpSword2"), ImageManager::GetInstance()->FindImage("playerUpSword2"));
						player.setAttackRc(player.getX(), player.getY() - 50, 50, 60);
					}
					if (player.getDirection() == DIRECTION::DOWN)
					{
						player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownSword2"), ImageManager::GetInstance()->FindImage("playerDownSword2"));
						player.setAttackRc(player.getX(), player.getY() + 50, 50, 60);
					}
					if (player.getDirection() == DIRECTION::LEFT)
					{
						player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftSword2"), ImageManager::GetInstance()->FindImage("playerLeftSword2"));
						player.setAttackRc(player.getX() - 50, player.getY(), 60, 50);
					}
					if (player.getDirection() == DIRECTION::RIGHT)
					{
						player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightSword2"), ImageManager::GetInstance()->FindImage("playerRightSword2"));
						player.setAttackRc(player.getX() + 50, player.getY(), 60, 50);
					}
					player.setSwrodAttackCombo(false);
				}
			}
		}
	}

	//만약 애니메이션 재생 끝나면
	if (!KEYANIMANAGER->findAnimation("playerUpSword1")->isPlay() && !KEYANIMANAGER->findAnimation("playerDownSword1")->isPlay()
		&& !KEYANIMANAGER->findAnimation("playerLeftSword1")->isPlay() && !KEYANIMANAGER->findAnimation("playerRightSword1")->isPlay()
		&& !KEYANIMANAGER->findAnimation("playerUpSword2")->isPlay() && !KEYANIMANAGER->findAnimation("playerDownSword2")->isPlay()
		&& !KEYANIMANAGER->findAnimation("playerLeftSword2")->isPlay() && !KEYANIMANAGER->findAnimation("playerRightSword2")->isPlay())
	{
		player.setSwrodAttackCombo(false);
		player.setAttackRcbool(false);
		player.setAttackRc(player.getX(), player.getY(), 0, 0);

		//아무키도 누르지않으면 아이들 상태로 전환
		if (KEYMANAGER->getKeyUp() == NULL || KEYMANAGER->isOnceKeyUp('W') || KEYMANAGER->isOnceKeyUp('S') || KEYMANAGER->isOnceKeyUp('A') || KEYMANAGER->isOnceKeyUp('D'))
		{
			if (player.getDirection() == DIRECTION::UP)
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpIdle"), ImageManager::GetInstance()->FindImage("playerUpIdle"));
				player.setCurrentState(player.getIdleState());
				player.setDirection(DIRECTION::UP);
			}

			if (player.getDirection() == DIRECTION::DOWN)
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownIdle"), ImageManager::GetInstance()->FindImage("playerDownIdle"));
				player.setCurrentState(player.getIdleState());
				player.setDirection(DIRECTION::DOWN);
			}

			if (player.getDirection() == DIRECTION::LEFT)
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftIdle"), ImageManager::GetInstance()->FindImage("playerLeftIdle"));
				player.setCurrentState(player.getIdleState());
				player.setDirection(DIRECTION::LEFT);
			}

			if (player.getDirection() == DIRECTION::RIGHT)
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightIdle"), ImageManager::GetInstance()->FindImage("playerRightIdle"));
				player.setCurrentState(player.getIdleState());
				player.setDirection(DIRECTION::RIGHT);
			}
		}

		//오른쪽키를 누르면 다시 이동하게
		else if (GetAsyncKeyState('D') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightWalk"), ImageManager::GetInstance()->FindImage("playerRightWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::RIGHT);
		}
		//왼쪽키를 누르면 다시 이동하게
		else if (GetAsyncKeyState('A') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftWalk"), ImageManager::GetInstance()->FindImage("playerLeftWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::LEFT);
		}
		//위쪽키를 누르면 다시 이동하게
		else if (GetAsyncKeyState('W') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpWalk"), ImageManager::GetInstance()->FindImage("playerUpWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::UP);
		}
		//아래키를 누르면 다시 이동하게
		else if (GetAsyncKeyState('S') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::DOWN);
		}
	}
}

//빗자루질 
void playerBroomState::update(player & player)
{
	player.setPlayerRc(player.getX(), player.getY(), player.getPlayerRcW(), player.getPlayerRcH());
	//위
	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpWalk"), ImageManager::GetInstance()->FindImage("playerUpWalk"));
		player.setCurrentState(player.getWalkState());
	}
	//아래 
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
		player.setCurrentState(player.getWalkState());
	}
	//왼쪽 
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftWalk"), ImageManager::GetInstance()->FindImage("playerLeftWalk"));
		player.setCurrentState(player.getWalkState());
	}
	//오른쪽 
	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightWalk"), ImageManager::GetInstance()->FindImage("playerRightWalk"));
		player.setCurrentState(player.getWalkState());
	}
}

//침대 상태
void playerBedState::update(player & player)
{
	player.setPlayerRc(player.getX(), player.getY(), player.getPlayerRcW(), player.getPlayerRcH());
	//애니메이션이 끝나고 진행
	if (!KEYANIMANAGER->findAnimation("playerBed")->isPlay())
	{
		player.setShadowX(player.getShadowX() + 11);
		player.setShadowY(player.getShadowY() + 50);
		player.setX(player.getShadowX());
		player.setY(player.getShadowY() - 50);

		player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownIdle"), ImageManager::GetInstance()->FindImage("playerDownIdle"));
		player.setCurrentState(player.getIdleState());
	}
}

//텔레포트 상태
void playerTeleportState::update(player & player)
{
	player.setPlayerRc(player.getX(), player.getY(), player.getPlayerRcW(), player.getPlayerRcH());
	//애니메이션 끝나고 진행
	if (!KEYANIMANAGER->findAnimation("playerTeleport")->isPlay())
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerTeleportOut"), ImageManager::GetInstance()->FindImage("playerTeleportOut"));
		player.setCurrentState(player.getTeleportOutState());
	}
}

//텔레포트(던전) 들어가기 상태
void playerTeleportInState::update(player & player)
{
	player.setPlayerRc(player.getX(), player.getY(), player.getPlayerRcW(), player.getPlayerRcH());
	//애니메이션 끝나고 진행
	if (!KEYANIMANAGER->findAnimation("playerTeleportIn")->isPlay())
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownIdle"), ImageManager::GetInstance()->FindImage("playerDownIdle"));
		player.setCurrentState(player.getIdleState());
	}
}

//텔레포트(탈출) 상태
void playerTeleportOutState::update(player & player)
{
	player.setPlayerRc(player.getX(), player.getY(), player.getPlayerRcW(), player.getPlayerRcH());
	//애니메이션 끝나고 진행
	if (!KEYANIMANAGER->findAnimation("playerTeleportOut")->isPlay())
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownIdle"), ImageManager::GetInstance()->FindImage("playerDownIdle"));
		player.setCurrentState(player.getIdleState());
	}
}

//플레이어 Hit 상태
void playerHitState::update(player & player)
{
	//플레이어 알파값 true
	player.setHitCondition(true);
	player.setHitAlphaCount(player.getHitAlphaCount() + 1);
	//Count가 20이 넘어가면 다시 알파값 false 줘서 원래대로
	if (player.getHitAlphaCount() >= 20)
	{
		player.setHitCondition(false);
		player.setEnemyCol(false);
		player.setHitAlphaCount(player.getHitAlphaCount() == 0);
	}

	if (player.getHitCondition())
	{
		player.setHitAlpha(player.getHitAlpha() + 0.02f);
	}
	if (!player.getHitCondition())
	{
		player.setHitAlpha(player.getHitAlpha() == 1.0f);
		player.setCurrentState(player.getWalkState());
	}
}