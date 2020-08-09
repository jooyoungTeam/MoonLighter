#include "stdafx.h"
#include "playerState.h"
#include "player.h"

HRESULT playerIdleState::init()
{
	_transForm = false;

	return S_OK;
}

//Idle 상태
void playerIdleState::update(player & player)
{
	cout << _transForm << endl;
	if (!_transForm)
	{
		//위 걷기
		if (KEYMANAGER->isOnceKeyDown('W'))
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpWalk"), ImageManager::GetInstance()->FindImage("playerUpWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirectionY(false);
		}

		//아래 걷기
		if (KEYMANAGER->isOnceKeyDown('S'))
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirectionY(true);
		}

		//왼쪽 걷기
		if (KEYMANAGER->isOnceKeyDown('A'))
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftWalk"), ImageManager::GetInstance()->FindImage("playerLeftWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirectionX(false);
		}

		//오른쪽 걷기
		if (KEYMANAGER->isOnceKeyDown('D'))
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightWalk"), ImageManager::GetInstance()->FindImage("playerRightWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirectionX(true);
		}
	}
	
	//플레이어 구르기
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		if (player.getDirectionX())
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightRoll"), ImageManager::GetInstance()->FindImage("playerRightRoll"));
			player.setCurrentState(player.getRollState());
		}
		if (!player.getDirectionX())
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftRoll"), ImageManager::GetInstance()->FindImage("playerLeftRoll"));
			player.setCurrentState(player.getRollState());
		}
		if (player.getDirectionY())
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownRoll"), ImageManager::GetInstance()->FindImage("playerDownRoll"));
			player.setCurrentState(player.getRollState());
		}
		if (!player.getDirectionY())
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpRoll"), ImageManager::GetInstance()->FindImage("playerUpRoll"));
			player.setCurrentState(player.getRollState());
		}
	}

	//플레이어 사망 <-- 임시
	if (KEYMANAGER->isOnceKeyDown('I'))
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDie"), ImageManager::GetInstance()->FindImage("playerDie"));
		player.setCurrentState(player.getDieState());
	}

	//플레이어 쉴드
	if (KEYMANAGER->isOnceKeyDown('K'))
	{
		if (player.getDirectionX())
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightShield"), ImageManager::GetInstance()->FindImage("playerRightShield"));
			player.setCurrentState(player.getShieldState());
		}
		if (!player.getDirectionX())
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftShield"), ImageManager::GetInstance()->FindImage("playerLeftShield"));
			player.setCurrentState(player.getShieldState());
		}
		if (player.getDirectionY())
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownShield"), ImageManager::GetInstance()->FindImage("playerDownShield"));
			player.setCurrentState(player.getShieldState());
		}
		if (!player.getDirectionY())
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpShield"), ImageManager::GetInstance()->FindImage("playerUpShield"));
			player.setCurrentState(player.getShieldState());
		}
	}
	
	//플레이어 수영 <-- 임시
	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	if (KEYMANAGER->isOnceKeyDown('O'))
	{
		_transForm = true;
	}

	if (_transForm)
	{
		if (KEYMANAGER->isOnceKeyDown('W'))
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpSwim"), ImageManager::GetInstance()->FindImage("playerUpSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirectionY(false);
		}

		if (KEYMANAGER->isOnceKeyDown('S'))
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownSwim"), ImageManager::GetInstance()->FindImage("playerDownSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirectionY(true);
		}

		if (KEYMANAGER->isOnceKeyDown('A'))
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftSwim"), ImageManager::GetInstance()->FindImage("playerLeftSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirectionX(false);
		}

		if (KEYMANAGER->isOnceKeyDown('D'))
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightSwim"), ImageManager::GetInstance()->FindImage("playerRightSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirectionX(true);
		}
	}
	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
}

//walk 상태
void playerWalkState::update(player & player)
{
	//위
	if (!player.getDirectionY())
	{
		if (KEYMANAGER->isStayKeyDown('W'))
		{
			//만약 아래키 누르면 위쪽Idle 모습으로 변함
			if (KEYMANAGER->isOnceKeyDown('S'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpIdle"), ImageManager::GetInstance()->FindImage("playerUpIdle"));
			}
			//위쪽Idle 모습으로 멈추기
			else if (KEYMANAGER->isStayKeyDown('S'))
			{
				player.setY(player.getY() - 0);
				return;
			}
			//아래키를 떼면 위로 다시 움직임
			else if (KEYMANAGER->isOnceKeyUp('S'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpWalk"), ImageManager::GetInstance()->FindImage("playerUpWalk"));
				player.setCurrentState(player.getWalkState());
			}
			//만약 이동중 왼쪽키 누르면
			if (KEYMANAGER->isOnceKeyDown('A'))
			{
				player.setDirectionX(false);
			}
			//만약 이동중 오른쪽키 누르면
			if (KEYMANAGER->isOnceKeyDown('D'))
			{
				player.setDirectionX(true);
			}
			//만약 이동중 구르기 누르면
			if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpRoll"), ImageManager::GetInstance()->FindImage("playerUpRoll"));
			}
			player.setY(player.getY() - 5);
		}
	}

	//위쪽키 떼면
	if (KEYMANAGER->isOnceKeyUp('W'))
	{
		//아무키도 누른상태가 아니면 Idle 상태로 
		if (KEYMANAGER->getKeyUp() == NULL)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpIdle"), ImageManager::GetInstance()->FindImage("playerUpIdle"));
			player.setCurrentState(player.getIdleState());
		}
		//아래키를 누르면 다시 이동하게
		else if (GetAsyncKeyState('S') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirectionY(true);
		}
	}

	//아래
	if (player.getDirectionY())
	{
		if (KEYMANAGER->isStayKeyDown('S'))
		{
			//만약 위쪽키 누르면 아래 Idle 모습으로 변함
			if (KEYMANAGER->isOnceKeyDown('W'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownIdle"), ImageManager::GetInstance()->FindImage("playerDownIdle"));
			}
			//아래Idle 모습으로 멈추기
			else if (KEYMANAGER->isStayKeyDown('W'))
			{
				player.setY(player.getY() + 0);
				return;
			}
			//위쪽키를 떼면 아래로 다시 움직임
			else if (KEYMANAGER->isOnceKeyUp('W'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
				player.setCurrentState(player.getWalkState());
			}
			//만약 이동중 왼쪽키 누르면
			if (KEYMANAGER->isOnceKeyDown('A'))
			{
				player.setDirectionX(false);
			}
			//만약 이동중 오른쪽키 누르면
			if (KEYMANAGER->isOnceKeyDown('D'))
			{
				player.setDirectionX(true);
			}

			//만약 이동중 구르기 누르면
			if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownRoll"), ImageManager::GetInstance()->FindImage("playerDownRoll"));
			}
			player.setY(player.getY() + 5);
		}
	}

	//아래키 떼면
	if (KEYMANAGER->isOnceKeyUp('S'))
	{
		//아무키도 누른상태가 아니면 Idle 상태로 
		if (KEYMANAGER->getKeyUp() == NULL)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownIdle"), ImageManager::GetInstance()->FindImage("playerDownIdle"));
			player.setCurrentState(player.getIdleState());
		}
		//위쪽키를 누르면 다시 이동하게
		else if (GetAsyncKeyState('W') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpWalk"), ImageManager::GetInstance()->FindImage("playerUpWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirectionY(true);
		}
	}

	//왼쪽
	if (!player.getDirectionX())
	{
		if (KEYMANAGER->isStayKeyDown('A'))
		{
			//만약 오른쪽키 누르면 왼쪽 Idle 모습으로 변함
			if (KEYMANAGER->isOnceKeyDown('D'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftIdle"), ImageManager::GetInstance()->FindImage("playerLeftIdle"));
			}
			//왼쪽Idle 모습으로 멈추기
			else if (KEYMANAGER->isStayKeyDown('D'))
			{
				player.setX(player.getX() - 0);
				return;
			}
			//오른쪽키를 떼면 왼쪽으로 다시 움직임
			else if (KEYMANAGER->isOnceKeyUp('D'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftWalk"), ImageManager::GetInstance()->FindImage("playerLeftWalk"));
				player.setCurrentState(player.getWalkState());
			}
			//만약 이동중 위쪽키 누르면
			if (KEYMANAGER->isOnceKeyDown('W'))
			{
				player.setDirectionY(false);
			}
			//만약 이동중 아래쪽키 누르면
			if (KEYMANAGER->isOnceKeyDown('S'))
			{
				player.setDirectionY(true);
			}
			//만약 이동중 구르기 누르면
			if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftRoll"), ImageManager::GetInstance()->FindImage("playerLeftRoll"));
			}
			player.setX(player.getX() - 5);
		}
	}

	//왼쪽키 떼면
	if (KEYMANAGER->isOnceKeyUp('A'))
	{
		//아무키도 누른상태가 아니면 Idle 상태로 
		if (KEYMANAGER->getKeyUp() == NULL)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftIdle"), ImageManager::GetInstance()->FindImage("playerLeftIdle"));
			player.setCurrentState(player.getIdleState());
		}
		//오른쪽키를 누르면 다시 이동하게
		else if (GetAsyncKeyState('D') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightWalk"), ImageManager::GetInstance()->FindImage("playerRightWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirectionX(true);
		}
	}

	//오른쪽
	if (player.getDirectionX())
	{
		if (KEYMANAGER->isStayKeyDown('D'))
		{
			//만약 왼쪽키 누르면 오른쪽 Idle 모습으로 변함
			if (KEYMANAGER->isOnceKeyDown('A'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightIdle"), ImageManager::GetInstance()->FindImage("playerRightIdle"));
			}
			//오른쪽Idle 모습으로 멈추기
			else if (KEYMANAGER->isStayKeyDown('A'))
			{
				player.setX(player.getX() + 0);
				return;
			}
			//왼쪽키를 떼면 오른쪽으로 다시 움직임
			else if (KEYMANAGER->isOnceKeyUp('A'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightWalk"), ImageManager::GetInstance()->FindImage("playerRightWalk"));
				player.setCurrentState(player.getWalkState());
			}
			//만약 이동중 위쪽키 누르면
			if (KEYMANAGER->isOnceKeyDown('W'))
			{
				player.setDirectionY(false);
			}
			//만약 이동중 아래쪽키 누르면
			if (KEYMANAGER->isOnceKeyDown('S'))
			{
				player.setDirectionY(true);
			}
			//만약 이동중 구르기 누르면
			if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightRoll"), ImageManager::GetInstance()->FindImage("playerRightRoll"));
			}
			player.setX(player.getX() + 5);
		}
	}

	//오른쪽키 떼면
	if (KEYMANAGER->isOnceKeyUp('D'))
	{
		//아무키도 누른상태가 아니면 Idle 상태로 
		if (KEYMANAGER->getKeyUp() == NULL)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightIdle"), ImageManager::GetInstance()->FindImage("playerRightIdle"));
			player.setCurrentState(player.getIdleState());
		}
		//왼쪽키를 누르면 다시 이동하게
		else if (GetAsyncKeyState('A') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftWalk"), ImageManager::GetInstance()->FindImage("playerLeftWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirectionX(false);
		}
	}

	//플레이어 구르기
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		if (player.getDirectionX())
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightRoll"), ImageManager::GetInstance()->FindImage("playerRightRoll"));
			player.setCurrentState(player.getRollState());
		}
		if (!player.getDirectionX())
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftRoll"), ImageManager::GetInstance()->FindImage("playerLeftRoll"));
			player.setCurrentState(player.getRollState());
		}
		if (player.getDirectionY())
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownRoll"), ImageManager::GetInstance()->FindImage("playerDownRoll"));
			player.setCurrentState(player.getRollState());
		}
		if (!player.getDirectionY())
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpRoll"), ImageManager::GetInstance()->FindImage("playerUpRoll"));
			player.setCurrentState(player.getRollState());
		}
	}

	//플레이어 쉴드
	if (KEYMANAGER->isOnceKeyDown('K'))
	{
		if (player.getDirectionX())
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightShield"), ImageManager::GetInstance()->FindImage("playerRightShield"));
			player.setCurrentState(player.getShieldState());
		}
		if (!player.getDirectionX())
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftShield"), ImageManager::GetInstance()->FindImage("playerLeftShield"));
			player.setCurrentState(player.getShieldState());
		}
		if (player.getDirectionY())
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownShield"), ImageManager::GetInstance()->FindImage("playerDownShield"));
			player.setCurrentState(player.getShieldState());
		}
		if (!player.getDirectionY())
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpShield"), ImageManager::GetInstance()->FindImage("playerUpShield"));
			player.setCurrentState(player.getShieldState());
		}
	}
}

//roll(구르기) 상태
void playerRollState::update(player & player)
{
	//위로 구르기 
	if(player.getPlayerMotion() == KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpRoll"))
	{
		player.setY(player.getY() - 10);
	}
	//아래로 구르기
	if (player.getPlayerMotion() == KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownRoll"))
	{
		player.setY(player.getY() + 10);
	}
	//왼쪽으로 구르기
	if (player.getPlayerMotion() == KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftRoll"))
	{
		player.setX(player.getX() - 10);
	}
	//오른쪽으로 구르기
	if (player.getPlayerMotion() == KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightRoll"))
	{
		player.setX(player.getX() + 10);
	}

	//키 떼면
	if (KEYMANAGER->isOnceKeyUp(VK_SPACE))
	{
		//아무키도 누르지 않고있으면 Idle 상태로 전환
		if (KEYMANAGER->getKeyUp() == NULL)
		{
			if (!player.getDirectionY())
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpIdle"), ImageManager::GetInstance()->FindImage("playerUpIdle"));
				player.setCurrentState(player.getIdleState());
			}

			if (player.getDirectionY())
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownIdle"), ImageManager::GetInstance()->FindImage("playerDownIdle"));
				player.setCurrentState(player.getIdleState());
			}

			if (!player.getDirectionX())
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftIdle"), ImageManager::GetInstance()->FindImage("playerLeftIdle"));
				player.setCurrentState(player.getIdleState());
			}

			if (player.getDirectionX())
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightIdle"), ImageManager::GetInstance()->FindImage("playerRightIdle"));
				player.setCurrentState(player.getIdleState());
			}
		}
	}
}

//die 상태
void playerDieState::update(player & player)
{

}

//shield 상태
void playerShieldState::update(player & player)
{
	//플레이어 쉴드
	if (KEYMANAGER->isStayKeyDown('K'))
	{
		if (player.getDirectionX())
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightShield"), ImageManager::GetInstance()->FindImage("playerRightShield"));
		}
		if (!player.getDirectionX())
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftShield"), ImageManager::GetInstance()->FindImage("playerLeftShield"));
		}
		if (player.getDirectionY())
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownShield"), ImageManager::GetInstance()->FindImage("playerDownShield"));
		}
		if (!player.getDirectionY())
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpShield"), ImageManager::GetInstance()->FindImage("playerUpShield"));
		}
	}

	//쉴드키 떼면
	if (KEYMANAGER->isOnceKeyUp('K'))
	{
		if (KEYMANAGER->getKeyUp() == NULL)
		{
			if (player.getDirectionX())
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightIdle"), ImageManager::GetInstance()->FindImage("playerRightIdle"));
				player.setCurrentState(player.getIdleState());
			} 
			if (!player.getDirectionX())
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftIdle"), ImageManager::GetInstance()->FindImage("playerLeftIdle"));
				player.setCurrentState(player.getIdleState());
			}
			if (player.getDirectionY())
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownIdle"), ImageManager::GetInstance()->FindImage("playerDownIdle"));
				player.setCurrentState(player.getIdleState());
			}
			if (!player.getDirectionY())
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpIdle"), ImageManager::GetInstance()->FindImage("playerUpIdle"));
				player.setCurrentState(player.getIdleState());
			}
		}
		//오른쪽키를 누르면 다시 이동하게
		else if (GetAsyncKeyState('D') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightWalk"), ImageManager::GetInstance()->FindImage("playerRightWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirectionX(true);
		}
		//왼쪽키를 누르면 다시 이동하게
		else if (GetAsyncKeyState('A') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftWalk"), ImageManager::GetInstance()->FindImage("playerLeftWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirectionX(true);
		}
		//위쪽키를 누르면 다시 이동하게
		else if (GetAsyncKeyState('W') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpWalk"), ImageManager::GetInstance()->FindImage("playerUpWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirectionX(true);
		}
		//아래키를 누르면 다시 이동하게
		else if (GetAsyncKeyState('S') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirectionX(true);
		}
	}	
}

//idleSwim 상태
void playerIdleSwimState::update(player & player)
{

}


//swim 상태
void playerSwimState::update(player & player)
{
	//위 
	if (!player.getDirectionY())
	{
		if (KEYMANAGER->isStayKeyDown('W'))
		{
			//만약 아래쪽키 누르면 위쪽 idleSwim 모습으로 변함
			if (KEYMANAGER->isOnceKeyDown('S'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpIdleSwim"), ImageManager::GetInstance()->FindImage("playerUpIdleSwim"));
			}
			//위쪽 idleSwim 모습으로 멈추기
			else if (KEYMANAGER->isStayKeyDown('S'))
			{
				player.setY(player.getY() - 0);
				return;
			}
			//키 떼면 다시 이동
			else if (KEYMANAGER->isOnceKeyUp('S'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpSwim"), ImageManager::GetInstance()->FindImage("playerUpSwim"));
				player.setCurrentState(player.getSwimState());
			}
			player.setY(player.getY() - 3);
		}
	}

	//위쪽키 떼면
	if (KEYMANAGER->isOnceKeyUp('W'))
	{
		//아무키도 안누르면 Idle 상태로 전환
		if (KEYMANAGER->getKeyUp() == NULL)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpIdleSwim"), ImageManager::GetInstance()->FindImage("playerUpIdleSwim"));
			//player.setCurrentState(player.getIdleSwimState());
		}
		//아래키를 누르면 다시 이동
		else if (GetAsyncKeyState('S') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownSwim"), ImageManager::GetInstance()->FindImage("playerDownSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirectionY(true);
		}
	}

	//아래
	if (player.getDirectionY())
	{
		if (KEYMANAGER->isStayKeyDown('S'))
		{
			//만약 위쪽키 누르면 아래 idleSwim 모습으로 변함
			if (KEYMANAGER->isOnceKeyDown('W'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownIdleSwim"), ImageManager::GetInstance()->FindImage("playerDownIdleSwim"));
			}
			//아래 idleSwim 모습으로 멈추기
			else if (KEYMANAGER->isStayKeyDown('W'))
			{
				player.setY(player.getY() + 0);
				return;
			}
			//키 떼면 다시 이동
			else if (KEYMANAGER->isOnceKeyUp('W'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownSwim"), ImageManager::GetInstance()->FindImage("playerDownSwim"));
				player.setCurrentState(player.getSwimState());
			}
			player.setY(player.getY() + 3);
		}
	}

	//아래쪽키 떼면
	if (KEYMANAGER->isOnceKeyUp('S'))
	{
		//아무키도 안누르면 Idle 상태로 전환
		if (KEYMANAGER->getKeyUp() == NULL)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownIdleSwim"), ImageManager::GetInstance()->FindImage("playerDownIdleSwim"));
			//player.setCurrentState(player.getIdleSwimState());
		}
		//위쪽키를 누르면 다시 이동
		else if (GetAsyncKeyState('W') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpSwim"), ImageManager::GetInstance()->FindImage("playerUpSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirectionY(false);
		}
	}

	//왼쪽
	if (!player.getDirectionX())
	{
		if (KEYMANAGER->isStayKeyDown('A'))
		{
			//만약 오른쪽키 누르면 왼쪽 idleSwim 모습으로 변함
			if (KEYMANAGER->isOnceKeyDown('D'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftIdleSwim"), ImageManager::GetInstance()->FindImage("playerLeftIdleSwim"));
			}
			//왼쪽 idleSwim 모습으로 멈추기
			else if (KEYMANAGER->isStayKeyDown('D'))
			{
				player.setX(player.getX() - 0);
				return;
			}
			//키 떼면 다시 이동
			else if (KEYMANAGER->isOnceKeyUp('D'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftSwim"), ImageManager::GetInstance()->FindImage("playerLeftSwim"));
				player.setCurrentState(player.getSwimState());
			}
			player.setX(player.getX() - 3);
		}
	}

	//아래쪽키 떼면
	if (KEYMANAGER->isOnceKeyUp('A'))
	{
		//아무키도 안누르면 Idle 상태로 전환
		if (KEYMANAGER->getKeyUp() == NULL)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftIdleSwim"), ImageManager::GetInstance()->FindImage("playerLeftIdleSwim"));
			//player.setCurrentState(player.getIdleSwimState());
		}
		//위쪽키를 누르면 다시 이동
		else if (GetAsyncKeyState('D') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightSwim"), ImageManager::GetInstance()->FindImage("playerRightSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirectionY(false);
		}
	}

	//오른쪽
	if (player.getDirectionX())
	{
		if (KEYMANAGER->isStayKeyDown('D'))
		{
			//만약 왼쪽키 누르면 오른쪽 idleSwim 모습으로 변함
			if (KEYMANAGER->isOnceKeyDown('A'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightIdleSwim"), ImageManager::GetInstance()->FindImage("playerRightIdleSwim"));
			}
			//오른쪽 idleSwim 모습으로 멈추기
			else if (KEYMANAGER->isStayKeyDown('A'))
			{
				player.setX(player.getX() + 0);
				return;
			}
			//키 떼면 다시 이동
			else if (KEYMANAGER->isOnceKeyUp('A'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightSwim"), ImageManager::GetInstance()->FindImage("playerRightSwim"));
				player.setCurrentState(player.getSwimState());
			}
			player.setX(player.getX() + 3);
		}
	}

	//오른쪽키 떼면
	if (KEYMANAGER->isOnceKeyUp('D'))
	{
		//아무키도 안누르면 Idle 상태로 전환
		if (KEYMANAGER->getKeyUp() == NULL)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightIdleSwim"), ImageManager::GetInstance()->FindImage("playerRightIdleSwim"));
			//player.setCurrentState(player.getIdleSwimState());
		}
		//위쪽키를 누르면 다시 이동
		else if (GetAsyncKeyState('A') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightSwim"), ImageManager::GetInstance()->FindImage("playerRightSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirectionY(false);
		}
	}
}

//bow 상태
void playerbowState::update(player & player)
{

}

//sword 상태
void playerSwordState::update(player & player)
{

}
