#include "stdafx.h"
#include "playerState.h"
#include "player.h"
#include "arrow.h"

HRESULT playerIdleState::init()
{
	_transForm = false;

	return S_OK;
}

//Idle ����
void playerIdleState::update(player & player)
{
	_idleCount++;
	//���̵� ���� ���� ���ӵǸ� ���ڷ�����
	if (_idleCount >= 300)
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerBroom"), ImageManager::GetInstance()->FindImage("playerBroom"));
		player.setCurrentState(player.getBroomState());
		_idleCount = 0;
	}

	if (!_transForm)
	{
		//�ȱ�
		//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
		//��
		if (KEYMANAGER->isOnceKeyDown('W'))
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpWalk"), ImageManager::GetInstance()->FindImage("playerUpWalk"));
			player.setCurrentState(player.getWalkState());
		}
		//�Ʒ� 
		if (KEYMANAGER->isOnceKeyDown('S'))
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
			player.setCurrentState(player.getWalkState());
		}
		//���� 
		if (KEYMANAGER->isOnceKeyDown('A'))
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftWalk"), ImageManager::GetInstance()->FindImage("playerLeftWalk"));
			player.setCurrentState(player.getWalkState());
		}
		//������ 
		if (KEYMANAGER->isOnceKeyDown('D'))
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightWalk"), ImageManager::GetInstance()->FindImage("playerRightWalk"));
			player.setCurrentState(player.getWalkState());
		}
		//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
	}
	
	//�÷��̾� ������
	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
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
	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�


	//�÷��̾� ��� <-- �ӽ�
	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
	if (KEYMANAGER->isOnceKeyDown('L'))
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerBed"), ImageManager::GetInstance()->FindImage("playerBed"));
		player.setCurrentState(player.getDieState());
	}
	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�

	//�÷��̾� ����
	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
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
	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�

	//�÷��̾� ���� <-- �ӽ�
	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
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
	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�

	//���� ����
	if (player.getWeaponChange())
	{
		if (KEYMANAGER->isOnceKeyDown('Z'))
		{
			//ȭ��� ����
			player.setWeaponChange(false);
			player.setCurrentState(player.getBowState());
		}
	}

	//���� ����
	if (!player.getWeaponChange())
	{
		if (KEYMANAGER->isOnceKeyDown('Z'))
		{
			//������ ����
			player.setWeaponChange(true);
			player.setCurrentState(player.getSwordState());
		}
	}

	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�

	//Ȱ
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

	//��
	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
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
	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
}

//walk ����
void playerWalkState::update(player & player)
{
	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
	//��
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

		//���� �Ʒ�Ű ������ ����Idle ������� ����
 
		if (KEYMANAGER->isOnceKeyDown('S'))
		{
			cout << "111" << endl;
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpIdle"), ImageManager::GetInstance()->FindImage("playerUpIdle"));
		}
		//����Idle ������� ���߱�
		else if (KEYMANAGER->isStayKeyDown('S'))
		{
			cout << "222" << endl;
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpIdle"), ImageManager::GetInstance()->FindImage("playerUpIdle"));
			player.setShadowY(player.getShadowY() - 0);
			player.setY(player.getY() - 0);
			return;
		}
		//�Ʒ�Ű�� ���� ���� �ٽ� ������
		if (KEYMANAGER->isOnceKeyUp('S'))
		{
			cout << "333" << endl;
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpWalk"), ImageManager::GetInstance()->FindImage("playerUpWalk"));
			player.setCurrentState(player.getWalkState());
		}
		//���� �̵��� ������ ������
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

		//���� ����Ű ������ �Ʒ� Idle ������� ����
		if (KEYMANAGER->isOnceKeyDown('W'))
		{
			cout << "4444" << endl;
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownIdle"), ImageManager::GetInstance()->FindImage("playerDownIdle"));
		}
		//�Ʒ�Idle ������� ���߱�
		else if (KEYMANAGER->isStayKeyDown('W'))
		{
			cout << "5555" << endl;
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownIdle"), ImageManager::GetInstance()->FindImage("playerDownIdle"));
			player.setShadowY(player.getShadowY() + 0);
			player.setY(player.getY() + 0);
			return;
		}
		//����Ű�� ���� �Ʒ��� �ٽ� ������
		if (KEYMANAGER->isOnceKeyUp('W'))
		{
			cout << "6666" << endl;
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
			player.setCurrentState(player.getWalkState());
		}


		//���� �̵��� ������ ������
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

		//���� ������Ű ������ ���� Idle ������� ����
		if (KEYMANAGER->isOnceKeyDown('D'))
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftIdle"), ImageManager::GetInstance()->FindImage("playerLeftIdle"));
		}
		//����Idle ������� ���߱�
		else if (KEYMANAGER->isStayKeyDown('D'))
		{
			player.setShadowX(player.getShadowX() - 0);
			player.setX(player.getX() - 0);
			return;
		}
		//������Ű�� ���� �������� �ٽ� ������
		else if (KEYMANAGER->isOnceKeyUp('D'))
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftWalk"), ImageManager::GetInstance()->FindImage("playerLeftWalk"));
			player.setCurrentState(player.getWalkState());
		}
		//���� �̵��� ������ ������
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

		//���� ����Ű ������ ������ Idle ������� ����
		if (KEYMANAGER->isOnceKeyDown('A'))
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightIdle"), ImageManager::GetInstance()->FindImage("playerRightIdle"));
		}
		//������Idle ������� ���߱�
		else if (KEYMANAGER->isStayKeyDown('A'))
		{
			player.setShadowX(player.getShadowX() + 0);
			player.setX(player.getX() + 0);
			return;
		}
		//����Ű�� ���� ���������� �ٽ� ������
		else if (KEYMANAGER->isOnceKeyUp('A'))
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightWalk"), ImageManager::GetInstance()->FindImage("playerRightWalk"));
			player.setCurrentState(player.getWalkState());
		}
		//���� �̵��� ������ ������
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
	if (Vector2::Length(&vec) > 1) // �밢���� ��
	{
		player.setShadowX(player.getShadowX() + (diagonal.x * MOVESPPED));
		player.setX(player.getX() + (diagonal.x * MOVESPPED));
		player.setShadowY(player.getShadowY() + (diagonal.y * MOVESPPED));
		player.setY(player.getY() + (diagonal.y * MOVESPPED));
	}
	else
	{
		//�밢�� �ƴҶ�
		player.setShadowX(player.getShadowX() + (vec.x * MOVESPPED));
		player.setX(player.getX() + (vec.x * MOVESPPED));
		player.setShadowY(player.getShadowY() + (vec.y * MOVESPPED));
		player.setY(player.getY() + (vec.y * MOVESPPED));
	}


	if (!isMove)
	{
		// idle�� ���ư���
	}

	//����Ű ����
	if (KEYMANAGER->isOnceKeyUp('W'))
	{
		//�ƹ�Ű�� �������°� �ƴϸ� Idle ���·� 
		if (KEYMANAGER->getKeyUp() == NULL)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpIdle"), ImageManager::GetInstance()->FindImage("playerUpIdle"));
			player.setCurrentState(player.getIdleState());
		}
		//�Ʒ�Ű�� ������ �ٽ� �̵��ϰ�
		else if (GetAsyncKeyState('S') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::DOWN);
		}
		//������Ű�� ������ �ٽ� �̵��ϰ�
		else if (GetAsyncKeyState('D') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightWalk"), ImageManager::GetInstance()->FindImage("playerRightWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::RIGHT);
		}
		//����Ű�� ������ �ٽ� �̵��ϰ�
		else if (GetAsyncKeyState('A') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftWalk"), ImageManager::GetInstance()->FindImage("playerLeftWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::LEFT);
		}
	}

	//�Ʒ�Ű ����
	if (KEYMANAGER->isOnceKeyUp('S'))
	{
		//�ƹ�Ű�� �������°� �ƴϸ� Idle ���·� 
		if (KEYMANAGER->getKeyUp() == NULL)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownIdle"), ImageManager::GetInstance()->FindImage("playerDownIdle"));
			player.setCurrentState(player.getIdleState());
		}
		//����Ű�� ������ �ٽ� �̵��ϰ�
		else if (GetAsyncKeyState('W') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpWalk"), ImageManager::GetInstance()->FindImage("playerUpWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::UP);
		}
		//������Ű�� ������ �ٽ� �̵��ϰ�
		else if (GetAsyncKeyState('D') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightWalk"), ImageManager::GetInstance()->FindImage("playerRightWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::RIGHT);
		}
		//����Ű�� ������ �ٽ� �̵��ϰ�
		else if (GetAsyncKeyState('A') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftWalk"), ImageManager::GetInstance()->FindImage("playerLeftWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::LEFT);
		}
	}

	//����Ű ����
	if (KEYMANAGER->isOnceKeyUp('A'))
	{
		//�ƹ�Ű�� �������°� �ƴϸ� Idle ���·� 
		if (KEYMANAGER->getKeyUp() == NULL)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftIdle"), ImageManager::GetInstance()->FindImage("playerLeftIdle"));
			player.setCurrentState(player.getIdleState());
		}
		//������Ű�� ������ �ٽ� �̵��ϰ�
		else if (GetAsyncKeyState('D') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightWalk"), ImageManager::GetInstance()->FindImage("playerRightWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::RIGHT);
		}
		//����Ű�� ������ �ٽ� �̵��ϰ�
		else if (GetAsyncKeyState('W') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpWalk"), ImageManager::GetInstance()->FindImage("playerUpWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::UP);
		}
		//�Ʒ��� ������ �ٽ� �̵��ϰ�
		else if (GetAsyncKeyState('S') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::DOWN);
		}
	}

	//������Ű ����
	if (KEYMANAGER->isOnceKeyUp('D'))
	{
		//�ƹ�Ű�� �������°� �ƴϸ� Idle ���·� 
		if (KEYMANAGER->getKeyUp() == NULL)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightIdle"), ImageManager::GetInstance()->FindImage("playerRightIdle"));
			player.setCurrentState(player.getIdleState());
		}
		//����Ű�� ������ �ٽ� �̵��ϰ�
		else if (GetAsyncKeyState('A') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftWalk"), ImageManager::GetInstance()->FindImage("playerLeftWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::LEFT);
		}
		//����Ű�� ������ �ٽ� �̵��ϰ�
		else if (GetAsyncKeyState('W') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpWalk"), ImageManager::GetInstance()->FindImage("playerUpWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::UP);
		}
		//�Ʒ��� ������ �ٽ� �̵��ϰ�
		else if (GetAsyncKeyState('S') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::DOWN);
		}
	}
	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�

	//�÷��̾� ������
	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
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
	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�

	//�÷��̾� ����
	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
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
	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�

	//���� ����
	if (player.getWeaponChange())
	{
		if (KEYMANAGER->isOnceKeyDown('Z'))
		{
			//ȭ��� ����
			player.setWeaponChange(false);
			player.setCurrentState(player.getBowState());
		}
	}

	//���� ����
	if (!player.getWeaponChange())
	{
		if (KEYMANAGER->isOnceKeyDown('Z'))
		{
			//������ ����
			player.setWeaponChange(true);
			player.setCurrentState(player.getSwordState());
		}
	}

	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
	//Ȱ
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

	//��
	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
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
	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
}

//roll(������) ����
void playerRollState::update(player & player)
{
	//���� ������ 
	if (player.getPlayerMotion() == KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpRoll"))
	{
		player.setShadowY(player.getShadowY() - 5);
		player.setY(player.getY() - 5);
	}
	//�Ʒ��� ������
	if (player.getPlayerMotion() == KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownRoll"))
	{
		player.setShadowY(player.getShadowY() + 5);
		player.setY(player.getY() + 5);
	}
	//�������� ������
	if (player.getPlayerMotion() == KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftRoll"))
	{
		player.setShadowX(player.getShadowX() - 5);
		player.setX(player.getX() - 5);
	}
	//���������� ������
	if (player.getPlayerMotion() == KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightRoll"))
	{
		player.setShadowX(player.getShadowX() + 5);
		player.setX(player.getX() + 5);
	}

	//�ִϸ��̼� ����� ������ 
	if(!KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpRoll")->isPlay() 
		&& !KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownRoll")->isPlay()
		&& !KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftRoll")->isPlay()
		&& !KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightRoll")->isPlay())
	{

		//����Ű�� ������ �ٽ� �̵��ϰ�
		if (GetAsyncKeyState('W') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpWalk"), ImageManager::GetInstance()->FindImage("playerUpWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::UP);
		}
		//�Ʒ�Ű�� ������ �ٽ� �̵��ϰ�
		else if (GetAsyncKeyState('S') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::DOWN);
		}
		//������Ű�� ������ �ٽ� �̵��ϰ�
		else if (GetAsyncKeyState('D') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightWalk"), ImageManager::GetInstance()->FindImage("playerRightWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::RIGHT);
		}
		//����Ű�� ������ �ٽ� �̵��ϰ�
		else if (GetAsyncKeyState('A') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftWalk"), ImageManager::GetInstance()->FindImage("playerLeftWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::LEFT);
		}
		//�ƹ�Ű�� ������ �ʰ������� Idle ���·� ��ȯ
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

//die ����
void playerDieState::update(player & player)
{
	//�ƹ�Ű�� �ȴ����� Idle ���·� ��ȯ
	if (KEYMANAGER->isOnceKeyUp('L'))
	{
		if (KEYMANAGER->getKeyUp() == NULL)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpIdle"), ImageManager::GetInstance()->FindImage("playerUpIdle"));
			player.setCurrentState(player.getIdleState());
		}
		//�Ʒ�Ű�� ������ �ٽ� �̵�
		else if (GetAsyncKeyState('S') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::DOWN);
		}
	}
}

//shield ����
void playerShieldState::update(player & player)
{
	//�÷��̾� ����
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

	//����Ű ����
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
		//������Ű�� ������ �ٽ� �̵��ϰ�
		else if (GetAsyncKeyState('D') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightWalk"), ImageManager::GetInstance()->FindImage("playerRightWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::RIGHT);
		}
		//����Ű�� ������ �ٽ� �̵��ϰ�
		else if (GetAsyncKeyState('A') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftWalk"), ImageManager::GetInstance()->FindImage("playerLeftWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::LEFT);
		}
		//����Ű�� ������ �ٽ� �̵��ϰ�
		else if (GetAsyncKeyState('W') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpWalk"), ImageManager::GetInstance()->FindImage("playerUpWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::UP);
		}
		//�Ʒ�Ű�� ������ �ٽ� �̵��ϰ�
		else if (GetAsyncKeyState('S') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::DOWN);
		}
	}	
}

//idleSwim ����
void playerIdleSwimState::update(player & player)
{
	//��
	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpSwim"), ImageManager::GetInstance()->FindImage("playerUpSwim"));
		player.setCurrentState(player.getSwimState());
		player.setDirection(DIRECTION::UP);
	}

	//�Ʒ�
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownSwim"), ImageManager::GetInstance()->FindImage("playerDownSwim"));
		player.setCurrentState(player.getSwimState());
		player.setDirection(DIRECTION::DOWN);
	}

	//����
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftSwim"), ImageManager::GetInstance()->FindImage("playerLeftSwim"));
		player.setCurrentState(player.getSwimState());
		player.setDirection(DIRECTION::LEFT);
	}

	//������
	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightSwim"), ImageManager::GetInstance()->FindImage("playerRightSwim"));
		player.setCurrentState(player.getSwimState());
		player.setDirection(DIRECTION::RIGHT);
	}
}


//swim ����
void playerSwimState::update(player & player)
{
	//�� 
	if (player.getDirection() == DIRECTION::UP)
	{
		if (KEYMANAGER->isStayKeyDown('W'))
		{
			//���� �Ʒ���Ű ������ ���� idleSwim ������� ����
			if (KEYMANAGER->isOnceKeyDown('S'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpIdleSwim"), ImageManager::GetInstance()->FindImage("playerUpIdleSwim"));
			}
			//���� idleSwim ������� ���߱�
			else if (KEYMANAGER->isStayKeyDown('S'))
			{
				player.setShadowY(player.getShadowY() - 0);
				player.setY(player.getY() - 0);
				return;
			}
			//Ű ���� �ٽ� �̵�
			else if (KEYMANAGER->isOnceKeyUp('S'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpSwim"), ImageManager::GetInstance()->FindImage("playerUpSwim"));
				player.setCurrentState(player.getSwimState());
			}
			player.setShadowY(player.getShadowY() - 3);
			player.setY(player.getY() - 3);
		}
	}

	//����Ű ����
	if (KEYMANAGER->isOnceKeyUp('W'))
	{
		//�ƹ�Ű�� �ȴ����� Idle ���·� ��ȯ
		if (KEYMANAGER->getKeyUp() == NULL)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpIdleSwim"), ImageManager::GetInstance()->FindImage("playerUpIdleSwim"));
			player.setCurrentState(player.getIdleSwimState());
		}
		//�Ʒ�Ű�� ������ �ٽ� �̵�
		else if (GetAsyncKeyState('S') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownSwim"), ImageManager::GetInstance()->FindImage("playerDownSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirection(DIRECTION::DOWN);
		}
		//����Ű�� ������ �ٽ� �̵�
		else if (GetAsyncKeyState('A') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftSwim"), ImageManager::GetInstance()->FindImage("playerLeftSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirection(DIRECTION::LEFT);
		}
		//������Ű�� ������ �ٽ� �̵�
		else if (GetAsyncKeyState('D') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightSwim"), ImageManager::GetInstance()->FindImage("playerRightSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirection(DIRECTION::RIGHT);
		}
	}

	//�Ʒ�
	if (player.getDirection() == DIRECTION::DOWN)
	{
		if (KEYMANAGER->isStayKeyDown('S'))
		{
			//���� ����Ű ������ �Ʒ� idleSwim ������� ����
			if (KEYMANAGER->isOnceKeyDown('W'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownIdleSwim"), ImageManager::GetInstance()->FindImage("playerDownIdleSwim"));
			}
			//�Ʒ� idleSwim ������� ���߱�
			else if (KEYMANAGER->isStayKeyDown('W'))
			{
				player.setShadowY(player.getShadowY() + 0);
				player.setY(player.getY() + 0);
				return;
			}
			//Ű ���� �ٽ� �̵�
			else if (KEYMANAGER->isOnceKeyUp('W'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownSwim"), ImageManager::GetInstance()->FindImage("playerDownSwim"));
				player.setCurrentState(player.getSwimState());
			}
			player.setShadowY(player.getShadowY() + 3);
			player.setY(player.getY() + 3);
		}
	}

	//�Ʒ���Ű ����
	if (KEYMANAGER->isOnceKeyUp('S'))
	{
		//�ƹ�Ű�� �ȴ����� Idle ���·� ��ȯ
		if (KEYMANAGER->getKeyUp() == NULL)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownIdleSwim"), ImageManager::GetInstance()->FindImage("playerDownIdleSwim"));
			player.setCurrentState(player.getIdleSwimState());
		}
		//����Ű�� ������ �ٽ� �̵�
		else if (GetAsyncKeyState('W') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpSwim"), ImageManager::GetInstance()->FindImage("playerUpSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirection(DIRECTION::UP);
		}
		//����Ű�� ������ �ٽ� �̵�
		else if (GetAsyncKeyState('A') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftSwim"), ImageManager::GetInstance()->FindImage("playerLeftSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirection(DIRECTION::LEFT);
		}
		//������Ű�� ������ �ٽ� �̵�
		else if (GetAsyncKeyState('D') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightSwim"), ImageManager::GetInstance()->FindImage("playerRightSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirection(DIRECTION::RIGHT);
		}
	}

	//����
	if (player.getDirection() == DIRECTION::LEFT)
	{
		if (KEYMANAGER->isStayKeyDown('A'))
		{
			//���� ������Ű ������ ���� idleSwim ������� ����
			if (KEYMANAGER->isOnceKeyDown('D'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftIdleSwim"), ImageManager::GetInstance()->FindImage("playerLeftIdleSwim"));
			}
			//���� idleSwim ������� ���߱�
			else if (KEYMANAGER->isStayKeyDown('D'))
			{
				player.setShadowX(player.getShadowX() - 0);
				player.setX(player.getX() - 0);
				return;
			}
			//Ű ���� �ٽ� �̵�
			else if (KEYMANAGER->isOnceKeyUp('D'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftSwim"), ImageManager::GetInstance()->FindImage("playerLeftSwim"));
				player.setCurrentState(player.getSwimState());
			}
			player.setShadowX(player.getShadowX() - 3);
			player.setX(player.getX() - 3);
		}
	}

	//����Ű ����
	if (KEYMANAGER->isOnceKeyUp('A'))
	{
		//�ƹ�Ű�� �ȴ����� Idle ���·� ��ȯ
		if (KEYMANAGER->getKeyUp() == NULL)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftIdleSwim"), ImageManager::GetInstance()->FindImage("playerLeftIdleSwim"));
			player.setCurrentState(player.getIdleSwimState());
		}
		//������Ű�� ������ �ٽ� �̵�
		else if (GetAsyncKeyState('D') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightSwim"), ImageManager::GetInstance()->FindImage("playerRightSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirection(DIRECTION::RIGHT);
		}
		//����Ű�� ������ �ٽ� �̵�
		else if (GetAsyncKeyState('W') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpSwim"), ImageManager::GetInstance()->FindImage("playerUpSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirection(DIRECTION::UP);
		}
		//�Ʒ�Ű�� ������ �ٽ� �̵�
		else if (GetAsyncKeyState('S') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownSwim"), ImageManager::GetInstance()->FindImage("playerDownSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirection(DIRECTION::DOWN);
		}
	}

	//������
	if (player.getDirection() == DIRECTION::RIGHT)
	{
		if (KEYMANAGER->isStayKeyDown('D'))
		{
			//���� ����Ű ������ ������ idleSwim ������� ����
			if (KEYMANAGER->isOnceKeyDown('A'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightIdleSwim"), ImageManager::GetInstance()->FindImage("playerRightIdleSwim"));
			}
			//������ idleSwim ������� ���߱�
			else if (KEYMANAGER->isStayKeyDown('A'))
			{
				player.setShadowX(player.getShadowX() + 0);
				player.setX(player.getX() + 0);
				return;
			}
			//Ű ���� �ٽ� �̵�
			else if (KEYMANAGER->isOnceKeyUp('A'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightSwim"), ImageManager::GetInstance()->FindImage("playerRightSwim"));
				player.setCurrentState(player.getSwimState());
			}
			player.setShadowX(player.getShadowX() + 3);
			player.setX(player.getX() + 3);
		}
	}

	//������Ű ����
	if (KEYMANAGER->isOnceKeyUp('D'))
	{
		//�ƹ�Ű�� �ȴ����� Idle ���·� ��ȯ
		if (KEYMANAGER->getKeyUp() == NULL)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightIdleSwim"), ImageManager::GetInstance()->FindImage("playerRightIdleSwim"));
			player.setCurrentState(player.getIdleSwimState());
		}
		//����Ű�� ������ �ٽ� �̵�
		else if (GetAsyncKeyState('A') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftSwim"), ImageManager::GetInstance()->FindImage("playerLeftSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirection(DIRECTION::LEFT);
		}
				//����Ű�� ������ �ٽ� �̵�
		else if (GetAsyncKeyState('W') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpSwim"), ImageManager::GetInstance()->FindImage("playerUpSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirection(DIRECTION::UP);
		}
		//�Ʒ�Ű�� ������ �ٽ� �̵�
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

//bow ����
void playerbowState::update(player & player)
{
	//���� �ִϸ��̼� ��� ������
	if (!KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpBow")->isPlay() && !KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownBow")->isPlay()
		&& !KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftBow")->isPlay() && !KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightBow")->isPlay())
	{
		//�ƹ�Ű�� ������������ ���̵� ���·� ��ȯ
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

		//������Ű�� ������ �ٽ� �̵��ϰ�
		else if (GetAsyncKeyState('D') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightWalk"), ImageManager::GetInstance()->FindImage("playerRightWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::RIGHT);
		}
		//����Ű�� ������ �ٽ� �̵��ϰ�
		else if (GetAsyncKeyState('A') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftWalk"), ImageManager::GetInstance()->FindImage("playerLeftWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::LEFT);
		}
		//����Ű�� ������ �ٽ� �̵��ϰ�
		else if (GetAsyncKeyState('W') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpWalk"), ImageManager::GetInstance()->FindImage("playerUpWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::UP);
		}
		//�Ʒ�Ű�� ������ �ٽ� �̵��ϰ�
		else if (GetAsyncKeyState('S') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::DOWN);
		}
	}
}

//sword ����
void playerSwordState::update(player & player)
{
	//1Ÿ ����
	if (!player.getSwordAttackCombo())
	{
		if (KEYMANAGER->isOnceKeyDown('J'))
		{
			player.setSwrodAttackCombo(true);
		}
	}

	//������
	if (player.getSwordAttack())
	{
		if (player.getPlayerMotion() == KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpSword1")
			|| player.getPlayerMotion() == KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownSword1")
			|| player.getPlayerMotion() == KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftSword1")
			|| player.getPlayerMotion() == KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightSword1"))
		{
			//�ִϸ��̼� ��� ������
			if (!KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpSword1")->isPlay() && !KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownSword1")->isPlay()
				&& !KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftSword1")->isPlay() && !KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightSword1")->isPlay())
			{
				player.setAttackRcbool(false);
				player.setAttackRc(player.getX(), player.getY(), 0, 0);
				//Ű������ 2Ÿ�� �Ѿ
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

	//���� �ִϸ��̼� ��� ������
	if (!KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpSword1")->isPlay() && !KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownSword1")->isPlay()
		&& !KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftSword1")->isPlay() && !KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightSword1")->isPlay()
		&& !KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpSword2")->isPlay() && !KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownSword2")->isPlay()
		&& !KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftSword2")->isPlay() && !KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightSword2")->isPlay())
	{
		player.setSwrodAttackCombo(false);
		player.setAttackRcbool(false);
		player.setAttackRc(player.getX(), player.getY(), 0, 0);

		//�ƹ�Ű�� ������������ ���̵� ���·� ��ȯ
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

		//������Ű�� ������ �ٽ� �̵��ϰ�
		else if (GetAsyncKeyState('D') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightWalk"), ImageManager::GetInstance()->FindImage("playerRightWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::RIGHT);
		}
		//����Ű�� ������ �ٽ� �̵��ϰ�
		else if (GetAsyncKeyState('A') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftWalk"), ImageManager::GetInstance()->FindImage("playerLeftWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::LEFT);
		}
		//����Ű�� ������ �ٽ� �̵��ϰ�
		else if (GetAsyncKeyState('W') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpWalk"), ImageManager::GetInstance()->FindImage("playerUpWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::UP);
		}
		//�Ʒ�Ű�� ������ �ٽ� �̵��ϰ�
		else if (GetAsyncKeyState('S') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::DOWN);
		}
	}
}

//���ڷ��� 
void playerBroomState::update(player & player)
{
	//��
	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpWalk"), ImageManager::GetInstance()->FindImage("playerUpWalk"));
		player.setCurrentState(player.getWalkState());
	}
	//�Ʒ� 
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
		player.setCurrentState(player.getWalkState());
	}
	//���� 
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftWalk"), ImageManager::GetInstance()->FindImage("playerLeftWalk"));
		player.setCurrentState(player.getWalkState());
	}
	//������ 
	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightWalk"), ImageManager::GetInstance()->FindImage("playerRightWalk"));
		player.setCurrentState(player.getWalkState());
	}
}

//ħ�� ����
void playerBedState::update(player & player)
{
	//�ִϸ��̼��� ������ ����
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
