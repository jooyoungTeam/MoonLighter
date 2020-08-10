#include "stdafx.h"
#include "playerState.h"
#include "player.h"

HRESULT playerIdleState::init()
{
	_transForm = false;

	return S_OK;
}

//Idle ����
void playerIdleState::update(player & player)
{
	cout << _transForm << endl;
	if (!_transForm)
	{
		//�� �ȱ�
		if (KEYMANAGER->isOnceKeyDown('W'))
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpWalk"), ImageManager::GetInstance()->FindImage("playerUpWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirectionY(false);
		}

		//�Ʒ� �ȱ�
		if (KEYMANAGER->isOnceKeyDown('S'))
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirectionY(true);
		}

		//���� �ȱ�
		if (KEYMANAGER->isOnceKeyDown('A'))
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftWalk"), ImageManager::GetInstance()->FindImage("playerLeftWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirectionX(false);
		}

		//������ �ȱ�
		if (KEYMANAGER->isOnceKeyDown('D'))
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightWalk"), ImageManager::GetInstance()->FindImage("playerRightWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirectionX(true);
		}
	}
	
	//�÷��̾� ������
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

	//�÷��̾� ��� <-- �ӽ�
	if (KEYMANAGER->isOnceKeyDown('I'))
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDie"), ImageManager::GetInstance()->FindImage("playerDie"));
		player.setCurrentState(player.getDieState());
	}

	//�÷��̾� ����
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
	
	//�÷��̾� ���� <-- �ӽ�
	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
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
	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
}

//walk ����
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
			//���� �̵��� ������ ������
			if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpRoll"), ImageManager::GetInstance()->FindImage("playerUpRoll"));
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

			//���� �̵��� ������ ������
			if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownRoll"), ImageManager::GetInstance()->FindImage("playerDownRoll"));
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
			//���� �̵��� ������ ������
			if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftRoll"), ImageManager::GetInstance()->FindImage("playerLeftRoll"));
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
			//���� �̵��� ������ ������
			if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightRoll"), ImageManager::GetInstance()->FindImage("playerRightRoll"));
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
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftWalk"), ImageManager::GetInstance()->FindImage("playerLeftWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirectionX(false);
		}
	}

	//�÷��̾� ������
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

	//�÷��̾� ����
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

//roll(������) ����
void playerRollState::update(player & player)
{
	//���� ������ 
	if(player.getPlayerMotion() == KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpRoll"))
	{
		player.setY(player.getY() - 10);
	}
	//�Ʒ��� ������
	if (player.getPlayerMotion() == KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownRoll"))
	{
		player.setY(player.getY() + 10);
	}
	//�������� ������
	if (player.getPlayerMotion() == KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftRoll"))
	{
		player.setX(player.getX() - 10);
	}
	//���������� ������
	if (player.getPlayerMotion() == KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightRoll"))
	{
		player.setX(player.getX() + 10);
	}

	//Ű ����
	if (KEYMANAGER->isOnceKeyUp(VK_SPACE))
	{
		//�ƹ�Ű�� ������ �ʰ������� Idle ���·� ��ȯ
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

//die ����
void playerDieState::update(player & player)
{

}

//shield ����
void playerShieldState::update(player & player)
{
	//�÷��̾� ����
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

	//����Ű ����
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
		//������Ű�� ������ �ٽ� �̵��ϰ�
		else if (GetAsyncKeyState('D') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightWalk"), ImageManager::GetInstance()->FindImage("playerRightWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirectionX(true);
		}
		//����Ű�� ������ �ٽ� �̵��ϰ�
		else if (GetAsyncKeyState('A') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftWalk"), ImageManager::GetInstance()->FindImage("playerLeftWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirectionX(true);
		}
		//����Ű�� ������ �ٽ� �̵��ϰ�
		else if (GetAsyncKeyState('W') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpWalk"), ImageManager::GetInstance()->FindImage("playerUpWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirectionX(true);
		}
		//�Ʒ�Ű�� ������ �ٽ� �̵��ϰ�
		else if (GetAsyncKeyState('S') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirectionX(true);
		}
	}	
}

//idleSwim ����
void playerIdleSwimState::update(player & player)
{

}


//swim ����
void playerSwimState::update(player & player)
{
	//�� 
	if (!player.getDirectionY())
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
				player.setY(player.getY() - 0);
				return;
			}
			//Ű ���� �ٽ� �̵�
			else if (KEYMANAGER->isOnceKeyUp('S'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpSwim"), ImageManager::GetInstance()->FindImage("playerUpSwim"));
				player.setCurrentState(player.getSwimState());
			}
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
			//player.setCurrentState(player.getIdleSwimState());
		}
		//�Ʒ�Ű�� ������ �ٽ� �̵�
		else if (GetAsyncKeyState('S') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownSwim"), ImageManager::GetInstance()->FindImage("playerDownSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirectionY(true);
		}
	}

	//�Ʒ�
	if (player.getDirectionY())
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
				player.setY(player.getY() + 0);
				return;
			}
			//Ű ���� �ٽ� �̵�
			else if (KEYMANAGER->isOnceKeyUp('W'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownSwim"), ImageManager::GetInstance()->FindImage("playerDownSwim"));
				player.setCurrentState(player.getSwimState());
			}
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
			//player.setCurrentState(player.getIdleSwimState());
		}
		//����Ű�� ������ �ٽ� �̵�
		else if (GetAsyncKeyState('W') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpSwim"), ImageManager::GetInstance()->FindImage("playerUpSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirectionY(false);
		}
	}

	//����
	if (!player.getDirectionX())
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
				player.setX(player.getX() - 0);
				return;
			}
			//Ű ���� �ٽ� �̵�
			else if (KEYMANAGER->isOnceKeyUp('D'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftSwim"), ImageManager::GetInstance()->FindImage("playerLeftSwim"));
				player.setCurrentState(player.getSwimState());
			}
			player.setX(player.getX() - 3);
		}
	}

	//�Ʒ���Ű ����
	if (KEYMANAGER->isOnceKeyUp('A'))
	{
		//�ƹ�Ű�� �ȴ����� Idle ���·� ��ȯ
		if (KEYMANAGER->getKeyUp() == NULL)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftIdleSwim"), ImageManager::GetInstance()->FindImage("playerLeftIdleSwim"));
			//player.setCurrentState(player.getIdleSwimState());
		}
		//����Ű�� ������ �ٽ� �̵�
		else if (GetAsyncKeyState('D') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightSwim"), ImageManager::GetInstance()->FindImage("playerRightSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirectionY(false);
		}
	}

	//������
	if (player.getDirectionX())
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
				player.setX(player.getX() + 0);
				return;
			}
			//Ű ���� �ٽ� �̵�
			else if (KEYMANAGER->isOnceKeyUp('A'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightSwim"), ImageManager::GetInstance()->FindImage("playerRightSwim"));
				player.setCurrentState(player.getSwimState());
			}
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
			//player.setCurrentState(player.getIdleSwimState());
		}
		//����Ű�� ������ �ٽ� �̵�
		else if (GetAsyncKeyState('A') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightSwim"), ImageManager::GetInstance()->FindImage("playerRightSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirectionY(false);
		}
	}
}

//bow ����
void playerbowState::update(player & player)
{

}

//sword ����
void playerSwordState::update(player & player)
{

}
