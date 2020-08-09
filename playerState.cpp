#include "stdafx.h"
#include "playerState.h"
#include "player.h"

void playerIdleState::update(player & player)
{
	//��
	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpWalk"), ImageManager::GetInstance()->FindImage("playerUpWalk"));
		player.setCurrentState(player.getWalkState());
		player.setDirectionY(false);
	}

	//�Ʒ�
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
		player.setCurrentState(player.getWalkState());
		player.setDirectionY(true);
	}

	//����
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftWalk"), ImageManager::GetInstance()->FindImage("playerLeftWalk"));
		player.setCurrentState(player.getWalkState());
		player.setDirectionX(false);
	}

	//������
	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightWalk"), ImageManager::GetInstance()->FindImage("playerRightWalk"));
		player.setCurrentState(player.getWalkState());
		player.setDirectionX(true);
	}
}

void playerWalkState::update(player & player)
{
	//��
	if (!player.getDirectionY())
	{
		if (KEYMANAGER->isStayKeyDown('W'))
		{
			//���� �Ʒ�Ű ������ ����Idle ������� ����
			if (KEYMANAGER->isOnceKeyDown('S'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpIdle"), ImageManager::GetInstance()->FindImage("playerUpIdle"));
			}
			//����Idle ������� ���߱�
			else if (KEYMANAGER->isStayKeyDown('S'))
			{
				player.setY(player.getY() - 0);
				return;
			}
			//�Ʒ�Ű�� ���� ���� �ٽ� ������
			else if (KEYMANAGER->isOnceKeyUp('S'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpWalk"), ImageManager::GetInstance()->FindImage("playerUpWalk"));
				player.setCurrentState(player.getWalkState());
			}
			//���� �̵��� ����Ű ������
			if (KEYMANAGER->isOnceKeyDown('A'))
			{
				player.setDirectionX(false);
			}
			//���� �̵��� ������Ű ������
			if (KEYMANAGER->isOnceKeyDown('D'))
			{
				player.setDirectionX(true);
			}

			player.setY(player.getY() - 5);
		}
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
			player.setDirectionY(true);
		}
	}

	//�Ʒ�
	if (player.getDirectionY())
	{
		if (KEYMANAGER->isStayKeyDown('S'))
		{
			//���� ����Ű ������ �Ʒ� Idle ������� ����
			if (KEYMANAGER->isOnceKeyDown('W'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownIdle"), ImageManager::GetInstance()->FindImage("playerDownIdle"));
			}
			//�Ʒ�Idle ������� ���߱�
			else if (KEYMANAGER->isStayKeyDown('W'))
			{
				player.setY(player.getY() + 0);
				return;
			}
			//����Ű�� ���� �Ʒ��� �ٽ� ������
			else if (KEYMANAGER->isOnceKeyUp('W'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
				player.setCurrentState(player.getWalkState());
			}
			//���� �̵��� ����Ű ������
			if (KEYMANAGER->isOnceKeyDown('A'))
			{
				player.setDirectionX(false);
			}
			//���� �̵��� ������Ű ������
			if (KEYMANAGER->isOnceKeyDown('D'))
			{
				player.setDirectionX(true);
			}
			player.setY(player.getY() + 5);
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
			player.setDirectionY(true);
		}
	}

	//����
	if (!player.getDirectionX())
	{
		if (KEYMANAGER->isStayKeyDown('A'))
		{
			//���� ������Ű ������ ���� Idle ������� ����
			if (KEYMANAGER->isOnceKeyDown('D'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftIdle"), ImageManager::GetInstance()->FindImage("playerLeftIdle"));
			}
			//����Idle ������� ���߱�
			else if (KEYMANAGER->isStayKeyDown('D'))
			{
				player.setX(player.getX() - 0);
				return;
			}
			//������Ű�� ���� �������� �ٽ� ������
			else if (KEYMANAGER->isOnceKeyUp('D'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftWalk"), ImageManager::GetInstance()->FindImage("playerLeftWalk"));
				player.setCurrentState(player.getWalkState());
			}
			//���� �̵��� ����Ű ������
			if (KEYMANAGER->isOnceKeyDown('W'))
			{
				player.setDirectionY(false);
			}
			//���� �̵��� �Ʒ���Ű ������
			if (KEYMANAGER->isOnceKeyDown('S'))
			{
				player.setDirectionY(true);
			}
			player.setX(player.getX() - 5);
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
			player.setDirectionX(true);
		}
	}

	//������
	if (player.getDirectionX())
	{
		if (KEYMANAGER->isStayKeyDown('D'))
		{
			//���� ����Ű ������ ������ Idle ������� ����
			if (KEYMANAGER->isOnceKeyDown('A'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightIdle"), ImageManager::GetInstance()->FindImage("playerRightIdle"));
			}
			//������Idle ������� ���߱�
			else if (KEYMANAGER->isStayKeyDown('A'))
			{
				player.setX(player.getX() + 0);
				return;
			}
			//����Ű�� ���� ���������� �ٽ� ������
			else if (KEYMANAGER->isOnceKeyUp('A'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightWalk"), ImageManager::GetInstance()->FindImage("playerRightWalk"));
				player.setCurrentState(player.getWalkState());
			}
			//���� �̵��� ����Ű ������
			if (KEYMANAGER->isOnceKeyDown('W'))
			{
				player.setDirectionY(false);
			}
			//���� �̵��� �Ʒ���Ű ������
			if (KEYMANAGER->isOnceKeyDown('S'))
			{
				player.setDirectionY(true);
			}
			player.setX(player.getX() + 5);
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
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightWalk"), ImageManager::GetInstance()->FindImage("playerRightWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirectionX(false);
		}
	}
}

void playerRollState::update(player & player)
{

}

void playerDieState::update(player & player)
{

}

void playerShieldState::update(player & player)
{

}

void playerSwimState::update(player & player)
{

}

void playerbowState::update(player & player)
{

}

void playerSwordState::update(player & player)
{

}
