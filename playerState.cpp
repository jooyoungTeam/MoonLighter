#include "stdafx.h"
#include "playerState.h"
#include "player.h"
#include "arrow.h"

HRESULT playerIdleState::init()
{
	_transForm = false;

	return S_OK;
}

//Idle 상태
void playerIdleState::update(player & player)
{
	_idleCount++;
	//아이들 상태 오래 지속되면 빗자루질함
	if (_idleCount >= 300)
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerBroom"), ImageManager::GetInstance()->FindImage("playerBroom"));
		player.setCurrentState(player.getBroomState());
		_idleCount = 0;
	}

	if (!_transForm)
	{
		//걷기
		//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
		//위
		if (KEYMANAGER->isOnceKeyDown('W'))
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpWalk"), ImageManager::GetInstance()->FindImage("playerUpWalk"));
			player.setCurrentState(player.getWalkState());
		}
		//아래 
		if (KEYMANAGER->isOnceKeyDown('S'))
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
			player.setCurrentState(player.getWalkState());
		}
		//왼쪽 
		if (KEYMANAGER->isOnceKeyDown('A'))
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftWalk"), ImageManager::GetInstance()->FindImage("playerLeftWalk"));
			player.setCurrentState(player.getWalkState());
		}
		//오른쪽 
		if (KEYMANAGER->isOnceKeyDown('D'))
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightWalk"), ImageManager::GetInstance()->FindImage("playerRightWalk"));
			player.setCurrentState(player.getWalkState());
		}
		//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	}
	
	//플레이어 구르기
	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		if (player.getDirection() == DIRECTION::RIGHT)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightRoll"), ImageManager::GetInstance()->FindImage("playerRightRoll"));
			player.setCurrentState(player.getRollState());
		}
		if (player.getDirection() == DIRECTION::LEFT)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftRoll"), ImageManager::GetInstance()->FindImage("playerLeftRoll"));
			player.setCurrentState(player.getRollState());
		}
		if (player.getDirection() == DIRECTION::DOWN)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownRoll"), ImageManager::GetInstance()->FindImage("playerDownRoll"));
			player.setCurrentState(player.getRollState());
		}
		if (player.getDirection() == DIRECTION::UP)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpRoll"), ImageManager::GetInstance()->FindImage("playerUpRoll"));
			player.setCurrentState(player.getRollState());
		}
	}
	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ


	//플레이어 사망 <-- 임시
	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	if (KEYMANAGER->isOnceKeyDown('L'))
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerBed"), ImageManager::GetInstance()->FindImage("playerBed"));
		player.setCurrentState(player.getDieState());
	}
	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ

	//플레이어 쉴드
	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	if (KEYMANAGER->isOnceKeyDown('K'))
	{
		if (player.getDirection() == DIRECTION::RIGHT)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightShield"), ImageManager::GetInstance()->FindImage("playerRightShield"));
			player.setCurrentState(player.getShieldState());
		}
		if (player.getDirection() == DIRECTION::LEFT)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftShield"), ImageManager::GetInstance()->FindImage("playerLeftShield"));
			player.setCurrentState(player.getShieldState());
		}
		if (player.getDirection() == DIRECTION::DOWN)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownShield"), ImageManager::GetInstance()->FindImage("playerDownShield"));
			player.setCurrentState(player.getShieldState());
		}
		if (player.getDirection() == DIRECTION::UP)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpShield"), ImageManager::GetInstance()->FindImage("playerUpShield"));
			player.setCurrentState(player.getShieldState());
		}
	}
	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ

	//플레이어 수영 <-- 임시
	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	if (KEYMANAGER->isOnceKeyDown(VK_INSERT))
	{
		_transForm = true;
		player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownSwim"), ImageManager::GetInstance()->FindImage("playerDownSwim"));

		if (_transForm)
		{
			player.setCurrentState(player.getSwimState());
			player.setDirection(DIRECTION::DOWN);
		}
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
		if (KEYMANAGER->isOnceKeyDown('J'))
		{
			if (player.getDirection() == DIRECTION::UP)
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpBow"), ImageManager::GetInstance()->FindImage("playerUpBow"));
				player.setCurrentState(player.getBowState());
			}
			if (player.getDirection() == DIRECTION::DOWN)
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownBow"), ImageManager::GetInstance()->FindImage("playerDownBow"));
				player.setCurrentState(player.getBowState());
			}
			if (player.getDirection() == DIRECTION::LEFT)
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftBow"), ImageManager::GetInstance()->FindImage("playerLeftBow"));
				player.setCurrentState(player.getBowState());
			}
			if (player.getDirection() == DIRECTION::RIGHT)
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightBow"), ImageManager::GetInstance()->FindImage("playerRightBow"));
				player.setCurrentState(player.getBowState());
			}
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
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpSword1"), ImageManager::GetInstance()->FindImage("playerUpSword1"));
				player.setCurrentState(player.getSwordState());
				player.setAttackRc(player.getX(), player.getY() - 50, 50, 60);
			}

			if (player.getDirection() == DIRECTION::DOWN)
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownSword1"), ImageManager::GetInstance()->FindImage("playerDownSword1"));
				player.setCurrentState(player.getSwordState());
				player.setAttackRc(player.getX(), player.getY() + 50, 50, 60);
			}

			if (player.getDirection() == DIRECTION::LEFT)
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftSword1"), ImageManager::GetInstance()->FindImage("playerLeftSword1"));
				player.setCurrentState(player.getSwordState());
				player.setAttackRc(player.getX() - 50, player.getY(), 60, 50);
			}

			if (player.getDirection() == DIRECTION::RIGHT)
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightSword1"), ImageManager::GetInstance()->FindImage("playerRightSword1"));
				player.setCurrentState(player.getSwordState());
				player.setAttackRc(player.getX() + 50, player.getY(), 60, 50);
			}
		}
	}
	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
}

//walk 상태
void playerWalkState::update(player & player)
{
	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	//위
	bool isMove = false;
	bool isbool = true;

	int x = 0;
	int y = 0;
	if (KEYMANAGER->isStayKeyDown('W') && player.getDirection() != DIRECTION::DOWN && player.getDirection() != DIRECTION::LEFT && player.getDirection() != DIRECTION::RIGHT)
	{
		if (player.getDirection() != DIRECTION::UP)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpWalk"), ImageManager::GetInstance()->FindImage("playerUpWalk"));
			player.setDirection(DIRECTION::UP);
		}

		//만약 아래키 누르면 위쪽Idle 모습으로 변함
 
		if (KEYMANAGER->isOnceKeyDown('S'))
		{
			cout << "111" << endl;
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpIdle"), ImageManager::GetInstance()->FindImage("playerUpIdle"));
		}
		//위쪽Idle 모습으로 멈추기
		else if (KEYMANAGER->isStayKeyDown('S'))
		{
			cout << "222" << endl;
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpIdle"), ImageManager::GetInstance()->FindImage("playerUpIdle"));
			player.setShadowY(player.getShadowY() - 0);
			player.setY(player.getY() - 0);
			return;
		}
		//아래키를 떼면 위로 다시 움직임
		if (KEYMANAGER->isOnceKeyUp('S'))
		{
			cout << "333" << endl;
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpWalk"), ImageManager::GetInstance()->FindImage("playerUpWalk"));
			player.setCurrentState(player.getWalkState());
		}
		//만약 이동중 구르기 누르면
		if (!KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpRoll")->isPlay())
		{
			if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpRoll"), ImageManager::GetInstance()->FindImage("playerUpRoll"));

				player.setCurrentState(player.getRollState());
			}
		}
		
		isMove = true;
		y = -1;
		//player.setShadowY(player.getShadowY() - 5);
		//player.setY(player.getY() - 5);
	}
	if (KEYMANAGER->isStayKeyDown('S') && player.getDirection() != DIRECTION::UP && player.getDirection() != DIRECTION::LEFT && player.getDirection() != DIRECTION::RIGHT)
	{
		if (player.getDirection() != DIRECTION::DOWN)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
			player.setDirection(DIRECTION::DOWN);
		}

		//만약 위쪽키 누르면 아래 Idle 모습으로 변함
		if (KEYMANAGER->isOnceKeyDown('W'))
		{
			cout << "4444" << endl;
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownIdle"), ImageManager::GetInstance()->FindImage("playerDownIdle"));
		}
		//아래Idle 모습으로 멈추기
		else if (KEYMANAGER->isStayKeyDown('W'))
		{
			cout << "5555" << endl;
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownIdle"), ImageManager::GetInstance()->FindImage("playerDownIdle"));
			player.setShadowY(player.getShadowY() + 0);
			player.setY(player.getY() + 0);
			return;
		}
		//위쪽키를 떼면 아래로 다시 움직임
		if (KEYMANAGER->isOnceKeyUp('W'))
		{
			cout << "6666" << endl;
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
			player.setCurrentState(player.getWalkState());
		}


		//만약 이동중 구르기 누르면
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownRoll"), ImageManager::GetInstance()->FindImage("playerDownRoll"));
			player.setCurrentState(player.getRollState());
		}

		isMove = true;
		y = 1;
		//player.setShadowY(player.getShadowY() + 5);
		//player.setY(player.getY() + 5);
	}
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		if (player.getDirection() != DIRECTION::LEFT && !isMove)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftWalk"), ImageManager::GetInstance()->FindImage("playerLeftWalk"));
			player.setDirection(DIRECTION::LEFT);
		}

		//만약 오른쪽키 누르면 왼쪽 Idle 모습으로 변함
		if (KEYMANAGER->isOnceKeyDown('D'))
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftIdle"), ImageManager::GetInstance()->FindImage("playerLeftIdle"));
		}
		//왼쪽Idle 모습으로 멈추기
		else if (KEYMANAGER->isStayKeyDown('D'))
		{
			player.setShadowX(player.getShadowX() - 0);
			player.setX(player.getX() - 0);
			return;
		}
		//오른쪽키를 떼면 왼쪽으로 다시 움직임
		else if (KEYMANAGER->isOnceKeyUp('D'))
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftWalk"), ImageManager::GetInstance()->FindImage("playerLeftWalk"));
			player.setCurrentState(player.getWalkState());
		}
		//만약 이동중 구르기 누르면
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftRoll"), ImageManager::GetInstance()->FindImage("playerLeftRoll"));
			player.setCurrentState(player.getRollState());
		}
		isMove = true;
		//player.setShadowX(player.getShadowX() - 5);
		//player.setX(player.getX() - 5);
		x = - 1;
	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		if (player.getDirection() != DIRECTION::RIGHT && !isMove)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightWalk"), ImageManager::GetInstance()->FindImage("playerRightWalk"));
			player.setDirection(DIRECTION::RIGHT);
		}

		//만약 왼쪽키 누르면 오른쪽 Idle 모습으로 변함
		if (KEYMANAGER->isOnceKeyDown('A'))
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightIdle"), ImageManager::GetInstance()->FindImage("playerRightIdle"));
		}
		//오른쪽Idle 모습으로 멈추기
		else if (KEYMANAGER->isStayKeyDown('A'))
		{
			player.setShadowX(player.getShadowX() + 0);
			player.setX(player.getX() + 0);
			return;
		}
		//왼쪽키를 떼면 오른쪽으로 다시 움직임
		else if (KEYMANAGER->isOnceKeyUp('A'))
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightWalk"), ImageManager::GetInstance()->FindImage("playerRightWalk"));
			player.setCurrentState(player.getWalkState());
		}
		//만약 이동중 구르기 누르면
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightRoll"), ImageManager::GetInstance()->FindImage("playerRightRoll"));
			player.setCurrentState(player.getRollState());
		}
		isMove = true;
		//player.setShadowX(player.getShadowX() + 5);
		//player.setX(player.getX() + 5);
		x = 1;
		//Vector2(x, y).Normalize();
	}
	Vector2 vec(x, y);
	Vector2 diagonal = Vector2::Normalize(&vec);
	if (Vector2::Length(&vec) > 1) // 대각선일 때
	{
		player.setShadowX(player.getShadowX() + (diagonal.x * MOVESPPED));
		player.setX(player.getX() + (diagonal.x * MOVESPPED));
		player.setShadowY(player.getShadowY() + (diagonal.y * MOVESPPED));
		player.setY(player.getY() + (diagonal.y * MOVESPPED));
	}
	else
	{
		//대각선 아닐때
		player.setShadowX(player.getShadowX() + (vec.x * MOVESPPED));
		player.setX(player.getX() + (vec.x * MOVESPPED));
		player.setShadowY(player.getShadowY() + (vec.y * MOVESPPED));
		player.setY(player.getY() + (vec.y * MOVESPPED));
	}


	if (!isMove)
	{
		// idle로 돌아가게
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
			player.setDirection(DIRECTION::DOWN);
		}
		//오른쪽키를 누르면 다시 이동하게
		else if (GetAsyncKeyState('D') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightWalk"), ImageManager::GetInstance()->FindImage("playerRightWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::RIGHT);
		}
		//왼쪽키를 누르면 다시 이동하게
		else if (GetAsyncKeyState('A') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftWalk"), ImageManager::GetInstance()->FindImage("playerLeftWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::LEFT);
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
			player.setDirection(DIRECTION::UP);
		}
		//오른쪽키를 누르면 다시 이동하게
		else if (GetAsyncKeyState('D') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightWalk"), ImageManager::GetInstance()->FindImage("playerRightWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::RIGHT);
		}
		//왼쪽키를 누르면 다시 이동하게
		else if (GetAsyncKeyState('A') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftWalk"), ImageManager::GetInstance()->FindImage("playerLeftWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::LEFT);
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
			player.setDirection(DIRECTION::RIGHT);
		}
		//위쪽키를 누르면 다시 이동하게
		else if (GetAsyncKeyState('W') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpWalk"), ImageManager::GetInstance()->FindImage("playerUpWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::UP);
		}
		//아래를 누르면 다시 이동하게
		else if (GetAsyncKeyState('S') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::DOWN);
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
			player.setDirection(DIRECTION::LEFT);
		}
		//위쪽키를 누르면 다시 이동하게
		else if (GetAsyncKeyState('W') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpWalk"), ImageManager::GetInstance()->FindImage("playerUpWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::UP);
		}
		//아래를 누르면 다시 이동하게
		else if (GetAsyncKeyState('S') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::DOWN);
		}
	}
	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ

	//플레이어 구르기
	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		if (player.getDirection() == DIRECTION::RIGHT)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightRoll"), ImageManager::GetInstance()->FindImage("playerRightRoll"));
			player.setCurrentState(player.getRollState());
		}
		if (player.getDirection() == DIRECTION::LEFT)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftRoll"), ImageManager::GetInstance()->FindImage("playerLeftRoll"));
			player.setCurrentState(player.getRollState());
		}
		if (player.getDirection() == DIRECTION::DOWN)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownRoll"), ImageManager::GetInstance()->FindImage("playerDownRoll"));
			player.setCurrentState(player.getRollState());
		}
		if (player.getDirection() == DIRECTION::UP)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpRoll"), ImageManager::GetInstance()->FindImage("playerUpRoll"));
			player.setCurrentState(player.getRollState());
		}
	}
	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ

	//플레이어 쉴드
	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	if (KEYMANAGER->isOnceKeyDown('K'))
	{
		if (player.getDirection() == DIRECTION::RIGHT)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightShield"), ImageManager::GetInstance()->FindImage("playerRightShield"));
			player.setCurrentState(player.getShieldState());
		}
		if (player.getDirection() == DIRECTION::LEFT)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftShield"), ImageManager::GetInstance()->FindImage("playerLeftShield"));
			player.setCurrentState(player.getShieldState());
		}
		if (player.getDirection() == DIRECTION::DOWN)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownShield"), ImageManager::GetInstance()->FindImage("playerDownShield"));
			player.setCurrentState(player.getShieldState());
		}
		if (player.getDirection() == DIRECTION::UP)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpShield"), ImageManager::GetInstance()->FindImage("playerUpShield"));
			player.setCurrentState(player.getShieldState());
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
		if (KEYMANAGER->isOnceKeyDown('J'))
		{
			if (player.getDirection() == DIRECTION::UP)
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpBow"), ImageManager::GetInstance()->FindImage("playerUpBow"));
				player.setCurrentState(player.getBowState());
			}
			if (player.getDirection() == DIRECTION::DOWN)
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownBow"), ImageManager::GetInstance()->FindImage("playerDownBow"));
				player.setCurrentState(player.getBowState());
			}
			if (player.getDirection() == DIRECTION::LEFT)
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftBow"), ImageManager::GetInstance()->FindImage("playerLeftBow"));
				player.setCurrentState(player.getBowState());
			}
			if (player.getDirection() == DIRECTION::RIGHT)
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightBow"), ImageManager::GetInstance()->FindImage("playerRightBow"));
				player.setCurrentState(player.getBowState());
			}
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
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpSword1"), ImageManager::GetInstance()->FindImage("playerUpSword1"));
				player.setCurrentState(player.getSwordState());
				player.setAttackRc(player.getX(), player.getY() - 50, 50, 60);
			}

			if (player.getDirection() == DIRECTION::DOWN)
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownSword1"), ImageManager::GetInstance()->FindImage("playerDownSword1"));
				player.setCurrentState(player.getSwordState());
				player.setAttackRc(player.getX(), player.getY() + 50, 50, 60);
			}

			if (player.getDirection() == DIRECTION::LEFT)
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftSword1"), ImageManager::GetInstance()->FindImage("playerLeftSword1"));
				player.setCurrentState(player.getSwordState());
				player.setAttackRc(player.getX() - 50, player.getY(), 60, 50);
			}

			if (player.getDirection() == DIRECTION::RIGHT)
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightSword1"), ImageManager::GetInstance()->FindImage("playerRightSword1"));
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
	//위로 구르기 
	if (player.getPlayerMotion() == KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpRoll"))
	{
		player.setShadowY(player.getShadowY() - 5);
		player.setY(player.getY() - 5);
	}
	//아래로 구르기
	if (player.getPlayerMotion() == KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownRoll"))
	{
		player.setShadowY(player.getShadowY() + 5);
		player.setY(player.getY() + 5);
	}
	//왼쪽으로 구르기
	if (player.getPlayerMotion() == KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftRoll"))
	{
		player.setShadowX(player.getShadowX() - 5);
		player.setX(player.getX() - 5);
	}
	//오른쪽으로 구르기
	if (player.getPlayerMotion() == KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightRoll"))
	{
		player.setShadowX(player.getShadowX() + 5);
		player.setX(player.getX() + 5);
	}

	//애니메이션 재생이 끝나면 
	if(!KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpRoll")->isPlay() 
		&& !KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownRoll")->isPlay()
		&& !KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftRoll")->isPlay()
		&& !KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightRoll")->isPlay())
	{

		//위쪽키를 누르면 다시 이동하게
		if (GetAsyncKeyState('W') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpWalk"), ImageManager::GetInstance()->FindImage("playerUpWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::UP);
		}
		//아래키를 누르면 다시 이동하게
		else if (GetAsyncKeyState('S') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::DOWN);
		}
		//오른쪽키를 누르면 다시 이동하게
		else if (GetAsyncKeyState('D') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightWalk"), ImageManager::GetInstance()->FindImage("playerRightWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::RIGHT);
		}
		//왼쪽키를 누르면 다시 이동하게
		else if (GetAsyncKeyState('A') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftWalk"), ImageManager::GetInstance()->FindImage("playerLeftWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::LEFT);
		}
		//아무키도 누르지 않고있으면 Idle 상태로 전환
		else
		{
			if (player.getDirection() == DIRECTION::UP)
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpIdle"), ImageManager::GetInstance()->FindImage("playerUpIdle"));
				player.setCurrentState(player.getIdleState());
			}

			if (player.getDirection() == DIRECTION::DOWN)
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownIdle"), ImageManager::GetInstance()->FindImage("playerDownIdle"));
				player.setCurrentState(player.getIdleState());
			}

			if (player.getDirection() == DIRECTION::LEFT)
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftIdle"), ImageManager::GetInstance()->FindImage("playerLeftIdle"));
				player.setCurrentState(player.getIdleState());
			}

			if (player.getDirection() == DIRECTION::RIGHT)
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
	//아무키도 안누르면 Idle 상태로 전환
	if (KEYMANAGER->isOnceKeyUp('L'))
	{
		if (KEYMANAGER->getKeyUp() == NULL)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpIdle"), ImageManager::GetInstance()->FindImage("playerUpIdle"));
			player.setCurrentState(player.getIdleState());
		}
		//아래키를 누르면 다시 이동
		else if (GetAsyncKeyState('S') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::DOWN);
		}
	}
}

//shield 상태
void playerShieldState::update(player & player)
{
	//플레이어 쉴드
	if (KEYMANAGER->isStayKeyDown('K') || KEYMANAGER->isOnceKeyUp('W') || KEYMANAGER->isOnceKeyUp('S') || KEYMANAGER->isOnceKeyUp('A') || KEYMANAGER->isOnceKeyUp('D'));
	{
		if (player.getDirection() == DIRECTION::RIGHT)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightShield"), ImageManager::GetInstance()->FindImage("playerRightShield"));
			if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightRoll"), ImageManager::GetInstance()->FindImage("playerRightRoll"));
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
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftShield"), ImageManager::GetInstance()->FindImage("playerLeftShield"));
			if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftRoll"), ImageManager::GetInstance()->FindImage("playerLeftRoll"));
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
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownShield"), ImageManager::GetInstance()->FindImage("playerDownShield"));
			if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownRoll"), ImageManager::GetInstance()->FindImage("playerDownRoll"));
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
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpShield"), ImageManager::GetInstance()->FindImage("playerUpShield"));
			if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpRoll"), ImageManager::GetInstance()->FindImage("playerUpRoll"));
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
		if (KEYMANAGER->getKeyUp() == NULL)
		{
			if (player.getDirection() == DIRECTION::RIGHT)
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightIdle"), ImageManager::GetInstance()->FindImage("playerRightIdle"));
				player.setCurrentState(player.getIdleState());
			} 
			if (player.getDirection() == DIRECTION::LEFT)
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftIdle"), ImageManager::GetInstance()->FindImage("playerLeftIdle"));
				player.setCurrentState(player.getIdleState());
			}
			if (player.getDirection() == DIRECTION::DOWN)
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownIdle"), ImageManager::GetInstance()->FindImage("playerDownIdle"));
				player.setCurrentState(player.getIdleState());
			}
			if (player.getDirection() == DIRECTION::UP)
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
			player.setDirection(DIRECTION::RIGHT);
		}
		//왼쪽키를 누르면 다시 이동하게
		else if (GetAsyncKeyState('A') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftWalk"), ImageManager::GetInstance()->FindImage("playerLeftWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::LEFT);
		}
		//위쪽키를 누르면 다시 이동하게
		else if (GetAsyncKeyState('W') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpWalk"), ImageManager::GetInstance()->FindImage("playerUpWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::UP);
		}
		//아래키를 누르면 다시 이동하게
		else if (GetAsyncKeyState('S') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::DOWN);
		}
	}	
}

//idleSwim 상태
void playerIdleSwimState::update(player & player)
{
	//위
	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpSwim"), ImageManager::GetInstance()->FindImage("playerUpSwim"));
		player.setCurrentState(player.getSwimState());
		player.setDirection(DIRECTION::UP);
	}

	//아래
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownSwim"), ImageManager::GetInstance()->FindImage("playerDownSwim"));
		player.setCurrentState(player.getSwimState());
		player.setDirection(DIRECTION::DOWN);
	}

	//왼쪽
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftSwim"), ImageManager::GetInstance()->FindImage("playerLeftSwim"));
		player.setCurrentState(player.getSwimState());
		player.setDirection(DIRECTION::LEFT);
	}

	//오른쪽
	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightSwim"), ImageManager::GetInstance()->FindImage("playerRightSwim"));
		player.setCurrentState(player.getSwimState());
		player.setDirection(DIRECTION::RIGHT);
	}
}


//swim 상태
void playerSwimState::update(player & player)
{
	//위 
	if (player.getDirection() == DIRECTION::UP)
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
				player.setShadowY(player.getShadowY() - 0);
				player.setY(player.getY() - 0);
				return;
			}
			//키 떼면 다시 이동
			else if (KEYMANAGER->isOnceKeyUp('S'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpSwim"), ImageManager::GetInstance()->FindImage("playerUpSwim"));
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
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpIdleSwim"), ImageManager::GetInstance()->FindImage("playerUpIdleSwim"));
			player.setCurrentState(player.getIdleSwimState());
		}
		//아래키를 누르면 다시 이동
		else if (GetAsyncKeyState('S') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownSwim"), ImageManager::GetInstance()->FindImage("playerDownSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirection(DIRECTION::DOWN);
		}
		//왼쪽키를 누르면 다시 이동
		else if (GetAsyncKeyState('A') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftSwim"), ImageManager::GetInstance()->FindImage("playerLeftSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirection(DIRECTION::LEFT);
		}
		//오른쪽키를 누르면 다시 이동
		else if (GetAsyncKeyState('D') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightSwim"), ImageManager::GetInstance()->FindImage("playerRightSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirection(DIRECTION::RIGHT);
		}
	}

	//아래
	if (player.getDirection() == DIRECTION::DOWN)
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
				player.setShadowY(player.getShadowY() + 0);
				player.setY(player.getY() + 0);
				return;
			}
			//키 떼면 다시 이동
			else if (KEYMANAGER->isOnceKeyUp('W'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownSwim"), ImageManager::GetInstance()->FindImage("playerDownSwim"));
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
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownIdleSwim"), ImageManager::GetInstance()->FindImage("playerDownIdleSwim"));
			player.setCurrentState(player.getIdleSwimState());
		}
		//위쪽키를 누르면 다시 이동
		else if (GetAsyncKeyState('W') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpSwim"), ImageManager::GetInstance()->FindImage("playerUpSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirection(DIRECTION::UP);
		}
		//왼쪽키를 누르면 다시 이동
		else if (GetAsyncKeyState('A') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftSwim"), ImageManager::GetInstance()->FindImage("playerLeftSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirection(DIRECTION::LEFT);
		}
		//오른쪽키를 누르면 다시 이동
		else if (GetAsyncKeyState('D') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightSwim"), ImageManager::GetInstance()->FindImage("playerRightSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirection(DIRECTION::RIGHT);
		}
	}

	//왼쪽
	if (player.getDirection() == DIRECTION::LEFT)
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
				player.setShadowX(player.getShadowX() - 0);
				player.setX(player.getX() - 0);
				return;
			}
			//키 떼면 다시 이동
			else if (KEYMANAGER->isOnceKeyUp('D'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftSwim"), ImageManager::GetInstance()->FindImage("playerLeftSwim"));
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
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftIdleSwim"), ImageManager::GetInstance()->FindImage("playerLeftIdleSwim"));
			player.setCurrentState(player.getIdleSwimState());
		}
		//오른쪽키를 누르면 다시 이동
		else if (GetAsyncKeyState('D') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightSwim"), ImageManager::GetInstance()->FindImage("playerRightSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirection(DIRECTION::RIGHT);
		}
		//위쪽키를 누르면 다시 이동
		else if (GetAsyncKeyState('W') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpSwim"), ImageManager::GetInstance()->FindImage("playerUpSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirection(DIRECTION::UP);
		}
		//아래키를 누르면 다시 이동
		else if (GetAsyncKeyState('S') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownSwim"), ImageManager::GetInstance()->FindImage("playerDownSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirection(DIRECTION::DOWN);
		}
	}

	//오른쪽
	if (player.getDirection() == DIRECTION::RIGHT)
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
				player.setShadowX(player.getShadowX() + 0);
				player.setX(player.getX() + 0);
				return;
			}
			//키 떼면 다시 이동
			else if (KEYMANAGER->isOnceKeyUp('A'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightSwim"), ImageManager::GetInstance()->FindImage("playerRightSwim"));
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
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightIdleSwim"), ImageManager::GetInstance()->FindImage("playerRightIdleSwim"));
			player.setCurrentState(player.getIdleSwimState());
		}
		//왼쪽키를 누르면 다시 이동
		else if (GetAsyncKeyState('A') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftSwim"), ImageManager::GetInstance()->FindImage("playerLeftSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirection(DIRECTION::LEFT);
		}
				//위쪽키를 누르면 다시 이동
		else if (GetAsyncKeyState('W') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpSwim"), ImageManager::GetInstance()->FindImage("playerUpSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirection(DIRECTION::UP);
		}
		//아래키를 누르면 다시 이동
		else if (GetAsyncKeyState('S') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownSwim"), ImageManager::GetInstance()->FindImage("playerDownSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirection(DIRECTION::DOWN);
		}
	}
}

HRESULT playerbowState::init()
{
	//_arrow  = new arrow;
	//_arrow->init();
	return S_OK;
}

void playerbowState::render()
{
	//_arrow->render();
}

void playerbowState::release()
{
	//_arrow->release();
}

//bow 상태
void playerbowState::update(player & player)
{
	//만약 애니메이션 재생 끝나면
	if (!KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpBow")->isPlay() && !KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownBow")->isPlay()
		&& !KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftBow")->isPlay() && !KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightBow")->isPlay())
	{
		//아무키도 누르지않으면 아이들 상태로 전환
		if (KEYMANAGER->getKeyUp() == NULL || KEYMANAGER->isOnceKeyUp('W') || KEYMANAGER->isOnceKeyUp('S') || KEYMANAGER->isOnceKeyUp('A') || KEYMANAGER->isOnceKeyUp('D'))
		{
			if (player.getDirection() == DIRECTION::UP)
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpIdle"), ImageManager::GetInstance()->FindImage("playerUpIdle"));
				player.setCurrentState(player.getIdleState());
				player.setDirection(DIRECTION::UP);
			}

			if (player.getDirection() == DIRECTION::DOWN)
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownIdle"), ImageManager::GetInstance()->FindImage("playerDownIdle"));
				player.setCurrentState(player.getIdleState());
				player.setDirection(DIRECTION::DOWN);
			}

			if (player.getDirection() == DIRECTION::LEFT)
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftIdle"), ImageManager::GetInstance()->FindImage("playerLeftIdle"));
				player.setCurrentState(player.getIdleState());
				player.setDirection(DIRECTION::LEFT);
			}

			if (player.getDirection() == DIRECTION::RIGHT)
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightIdle"), ImageManager::GetInstance()->FindImage("playerRightIdle"));
				player.setCurrentState(player.getIdleState());
				player.setDirection(DIRECTION::RIGHT);
			}
		}

		//오른쪽키를 누르면 다시 이동하게
		else if (GetAsyncKeyState('D') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightWalk"), ImageManager::GetInstance()->FindImage("playerRightWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::RIGHT);
		}
		//왼쪽키를 누르면 다시 이동하게
		else if (GetAsyncKeyState('A') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftWalk"), ImageManager::GetInstance()->FindImage("playerLeftWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::LEFT);
		}
		//위쪽키를 누르면 다시 이동하게
		else if (GetAsyncKeyState('W') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpWalk"), ImageManager::GetInstance()->FindImage("playerUpWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::UP);
		}
		//아래키를 누르면 다시 이동하게
		else if (GetAsyncKeyState('S') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::DOWN);
		}
	}
}

//sword 상태
void playerSwordState::update(player & player)
{
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
		if (player.getPlayerMotion() == KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpSword1")
			|| player.getPlayerMotion() == KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownSword1")
			|| player.getPlayerMotion() == KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftSword1")
			|| player.getPlayerMotion() == KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightSword1"))
		{
			//애니메이션 재생 끝나면
			if (!KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpSword1")->isPlay() && !KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownSword1")->isPlay()
				&& !KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftSword1")->isPlay() && !KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightSword1")->isPlay())
			{
				player.setAttackRcbool(false);
				player.setAttackRc(player.getX(), player.getY(), 0, 0);
				//키누르면 2타로 넘어감
				if (player.getSwordAttackCombo())
				{
					player.setSwordAttack(true);
					if (player.getDirection() == DIRECTION::UP)
					{
						player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpSword2"), ImageManager::GetInstance()->FindImage("playerUpSword2"));
						player.setAttackRc(player.getX(), player.getY() - 50, 50, 60);
					}
					if (player.getDirection() == DIRECTION::DOWN)
					{
						player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownSword2"), ImageManager::GetInstance()->FindImage("playerDownSword2"));
						player.setAttackRc(player.getX(), player.getY() + 50, 50, 60);
					}
					if (player.getDirection() == DIRECTION::LEFT)
					{
						player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftSword2"), ImageManager::GetInstance()->FindImage("playerLeftSword2"));
						player.setAttackRc(player.getX() - 50, player.getY(), 60, 50);
					}
					if (player.getDirection() == DIRECTION::RIGHT)
					{
						player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightSword2"), ImageManager::GetInstance()->FindImage("playerRightSword2"));
						player.setAttackRc(player.getX() + 50, player.getY(), 60, 50);
					}
					player.setSwrodAttackCombo(false);
				}
			}
		}
	}

	//만약 애니메이션 재생 끝나면
	if (!KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpSword1")->isPlay() && !KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownSword1")->isPlay()
		&& !KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftSword1")->isPlay() && !KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightSword1")->isPlay()
		&& !KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpSword2")->isPlay() && !KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownSword2")->isPlay()
		&& !KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftSword2")->isPlay() && !KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightSword2")->isPlay())
	{
		player.setSwrodAttackCombo(false);
		player.setAttackRcbool(false);
		player.setAttackRc(player.getX(), player.getY(), 0, 0);

		//아무키도 누르지않으면 아이들 상태로 전환
		if (KEYMANAGER->getKeyUp() == NULL || KEYMANAGER->isOnceKeyUp('W') || KEYMANAGER->isOnceKeyUp('S') || KEYMANAGER->isOnceKeyUp('A') || KEYMANAGER->isOnceKeyUp('D'))
		{
			if (player.getDirection() == DIRECTION::UP)
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpIdle"), ImageManager::GetInstance()->FindImage("playerUpIdle"));
				player.setCurrentState(player.getIdleState());
				player.setDirection(DIRECTION::UP);
			}

			if (player.getDirection() == DIRECTION::DOWN)
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownIdle"), ImageManager::GetInstance()->FindImage("playerDownIdle"));
				player.setCurrentState(player.getIdleState());
				player.setDirection(DIRECTION::DOWN);
			}

			if (player.getDirection() == DIRECTION::LEFT)
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftIdle"), ImageManager::GetInstance()->FindImage("playerLeftIdle"));
				player.setCurrentState(player.getIdleState());
				player.setDirection(DIRECTION::LEFT);
			}

			if (player.getDirection() == DIRECTION::RIGHT)
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightIdle"), ImageManager::GetInstance()->FindImage("playerRightIdle"));
				player.setCurrentState(player.getIdleState());
				player.setDirection(DIRECTION::RIGHT);
			}
		}

		//오른쪽키를 누르면 다시 이동하게
		else if (GetAsyncKeyState('D') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightWalk"), ImageManager::GetInstance()->FindImage("playerRightWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::RIGHT);
		}
		//왼쪽키를 누르면 다시 이동하게
		else if (GetAsyncKeyState('A') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftWalk"), ImageManager::GetInstance()->FindImage("playerLeftWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::LEFT);
		}
		//위쪽키를 누르면 다시 이동하게
		else if (GetAsyncKeyState('W') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpWalk"), ImageManager::GetInstance()->FindImage("playerUpWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::UP);
		}
		//아래키를 누르면 다시 이동하게
		else if (GetAsyncKeyState('S') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::DOWN);
		}
	}
}

//빗자루질 
void playerBroomState::update(player & player)
{
	//위
	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpWalk"), ImageManager::GetInstance()->FindImage("playerUpWalk"));
		player.setCurrentState(player.getWalkState());
	}
	//아래 
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
		player.setCurrentState(player.getWalkState());
	}
	//왼쪽 
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftWalk"), ImageManager::GetInstance()->FindImage("playerLeftWalk"));
		player.setCurrentState(player.getWalkState());
	}
	//오른쪽 
	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightWalk"), ImageManager::GetInstance()->FindImage("playerRightWalk"));
		player.setCurrentState(player.getWalkState());
	}
}

//침대 상태
void playerBedState::update(player & player)
{
	//애니메이션이 끝나고 진행
	if (!KEYANIMANAGER->findAnimation(player.getIndex(), "playerBed")->isPlay())
	{
		player.setShadowX(player.getShadowX() + 11);
		player.setShadowY(player.getShadowY() + 50);
		player.setX(player.getShadowX());
		player.setY(player.getShadowY()- 50);

		player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownIdle"), ImageManager::GetInstance()->FindImage("playerDownIdle"));
		player.setCurrentState(player.getIdleState());
	}
}
