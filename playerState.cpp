#include "stdafx.h"
#include "playerState.h"
#include "player.h"
#include "arrow.h"

HRESULT playerIdleState::init()
{
	return S_OK;
}

//Idle ����
void playerIdleState::update(player & player)
{
	player.setPlayerRc(player.getX(), player.getY(), player.getPlayerRcW(), player.getPlayerRcH());	//��ǻ� �ʿ���� �ϴ� ����~
	player.setBedCount(player.getBedCount() + 1);
	//���̵� ���� ���� ���ӵǸ� ���ڷ�����
	if (player.getBedCount() >= 300)
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerBroom"), ImageManager::GetInstance()->FindImage("playerBroom"));
		player.setCurrentState(player.getBroomState());
		player.setBedCount(player.getBedCount() == 0);
	}

	//���ʹ����� ������ ��Ʈ���·� �Ѿ
	if (player.getEnemyCol())
	{
		player.setCurrentState(player.getHitState());
	}

	if (!player.getTransform())
	{
		//�ȱ�
		//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
		//��
		if (KEYMANAGER->isOnceKeyDown('W'))
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpWalk"), ImageManager::GetInstance()->FindImage("playerUpWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::UP);
		}
		//�Ʒ� 
		if (KEYMANAGER->isOnceKeyDown('S'))
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::DOWN);
		}
		//���� 
		if (KEYMANAGER->isOnceKeyDown('A'))
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftWalk"), ImageManager::GetInstance()->FindImage("playerLeftWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::LEFT);
		}
		//������ 
		if (KEYMANAGER->isOnceKeyDown('D'))
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightWalk"), ImageManager::GetInstance()->FindImage("playerRightWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::RIGHT);
		}
		//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
	}

	//�÷��̾� ������
	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
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
	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�


	//�÷��̾� ��� <-- �ӽ�
	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
	if (KEYMANAGER->isOnceKeyDown('0'))
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDie"), ImageManager::GetInstance()->FindImage("playerDie"));
		player.setCurrentState(player.getDieState());
	}
	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�

	//�÷��̾� ����
	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
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
	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�

	//�÷��̾� ���� && ���� in <-- �ӽ�
	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�

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
		//Ȱ ���� ī��Ʈ
		if (player.getBowBool())
		{
			player.setBowChargeCount(player.getBowChargeCount() + 1);
		}
		if (!player.getBowBool())
		{
			player.setBowChargeCount(player.getBowChargeCount() == 0);
		}

		//Ȱ���� ���İ�
		if (player.getBowChargeAlpha())
		{
			player.setBowAlphaCount(player.getBowAlphaCount() + 1);
		}

		if (!player.getBowChargeAlpha())
		{
			player.setBowAlphaCount(player.getBowAlphaCount() == 0);
		}

		//Ȱ �ٷ� ������ְ� �ڴ����� ������
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
					//���İ�ȿ�� ��������
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
	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�

	//�÷��̾� �ڷ���Ʈ
	if (KEYMANAGER->isOnceKeyDown('L'))
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerTeleport"), ImageManager::GetInstance()->FindImage("playerTeleport"));
		player.setCurrentState(player.getTeleportState());
		player.setBedCount(player.getBedCount() == 0);
	}

}

//walk ����
void playerWalkState::update(player & player)
{
	player.setPlayerRc(player.getX(), player.getY(), player.getPlayerRcW(), player.getPlayerRcH());

	//���ʹ����� ������ ��Ʈ���·� �Ѿ
	if (player.getEnemyCol())
	{
		player.setCurrentState(player.getHitState());
	}

	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
	//��

	int x = 0;
	int y = 0;

	if (player.getDirection() == DIRECTION::UP)
	{
		if (KEYMANAGER->isStayKeyDown('W'))
		{
			//���� �Ʒ�Ű ������ ����Idle ������� ����
			if (KEYMANAGER->isOnceKeyDown('S'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpIdle"), ImageManager::GetInstance()->FindImage("playerUpIdle"));
			}
			//����Idle ������� ���߱�
			else if (KEYMANAGER->isStayKeyDown('S'))
			{
				return;
			}
			//�Ʒ�Ű�� ���� ���� �ٽ� ������
			else if (KEYMANAGER->isOnceKeyUp('S'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpWalk"), ImageManager::GetInstance()->FindImage("playerUpWalk"));
				player.setCurrentState(player.getWalkState());
			}
			//���� �̵��� ����Ű ������
			if (KEYMANAGER->isStayKeyDown('A'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpWalk"), ImageManager::GetInstance()->FindImage("playerUpWalk"));
				player.setCurrentState(player.getWalkState());
				player.setDirection(DIRECTION::LEFTTOP);
			}
			//���� �̵��� ������Ű ������
			if (KEYMANAGER->isStayKeyDown('D'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpWalk"), ImageManager::GetInstance()->FindImage("playerUpWalk"));
				player.setCurrentState(player.getWalkState());
				player.setDirection(DIRECTION::RIGHTTOP);
			}
			//���� �̵��� ������ ������
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

	//�Ʒ�
	if (player.getDirection() == DIRECTION::DOWN)
	{
		if (KEYMANAGER->isStayKeyDown('S'))
		{
			//���� ����Ű ������ �Ʒ� Idle ������� ����
			if (KEYMANAGER->isOnceKeyDown('W'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownIdle"), ImageManager::GetInstance()->FindImage("playerDownIdle"));
			}
			//�Ʒ�Idle ������� ���߱�
			else if (KEYMANAGER->isStayKeyDown('W'))
			{
				return;
			}
			//����Ű�� ���� �Ʒ��� �ٽ� ������
			else if (KEYMANAGER->isOnceKeyUp('W'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
				player.setCurrentState(player.getWalkState());
			}
			//���� �̵��� ����Ű ������
			if (KEYMANAGER->isStayKeyDown('A'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
				player.setCurrentState(player.getWalkState());
				player.setDirection(DIRECTION::LEFTBOTTOM);
			}
			//���� �̵��� ������Ű ������
			if (KEYMANAGER->isStayKeyDown('D'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
				player.setCurrentState(player.getWalkState());
				player.setDirection(DIRECTION::RIGHTBOTTOM);
			}

			//���� �̵��� ������ ������
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

	//����
	if (player.getDirection() == DIRECTION::LEFT)
	{
		if (KEYMANAGER->isStayKeyDown('A'))
		{
			//���� ������Ű ������ ���� Idle ������� ����
			if (KEYMANAGER->isOnceKeyDown('D'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftIdle"), ImageManager::GetInstance()->FindImage("playerLeftIdle"));
			}
			//����Idle ������� ���߱�
			else if (KEYMANAGER->isStayKeyDown('D'))
			{
				return;
			}
			//������Ű�� ���� �������� �ٽ� ������
			else if (KEYMANAGER->isOnceKeyUp('D'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftWalk"), ImageManager::GetInstance()->FindImage("playerLeftWalk"));
				player.setCurrentState(player.getWalkState());
			}
			//���� �̵��� ����Ű ������
			if (KEYMANAGER->isStayKeyDown('W'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpWalk"), ImageManager::GetInstance()->FindImage("playerUpWalk"));
				player.setCurrentState(player.getWalkState());
				player.setDirection(DIRECTION::LEFTTOP);
			}
			//���� �̵��� �Ʒ�Ű ������
			if (KEYMANAGER->isStayKeyDown('S'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
				player.setCurrentState(player.getWalkState());
				player.setDirection(DIRECTION::LEFTBOTTOM);
			}

			//���� �̵��� ������ ������
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

	//������
	if (player.getDirection() == DIRECTION::RIGHT)
	{
		if (KEYMANAGER->isStayKeyDown('D'))
		{
			//���� ����Ű ������ ������ Idle ������� ����
			if (KEYMANAGER->isOnceKeyDown('A'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightIdle"), ImageManager::GetInstance()->FindImage("playerRightIdle"));
			}
			//������Idle ������� ���߱�
			else if (KEYMANAGER->isStayKeyDown('A'))
			{
				return;
			}
			//����Ű�� ���� ���������� �ٽ� ������
			else if (KEYMANAGER->isOnceKeyUp('A'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightWalk"), ImageManager::GetInstance()->FindImage("playerRightWalk"));
				player.setCurrentState(player.getWalkState());
			}

			//���� �̵��� ����Ű ������
			if (KEYMANAGER->isStayKeyDown('W'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpWalk"), ImageManager::GetInstance()->FindImage("playerUpWalk"));
				player.setCurrentState(player.getWalkState());
				player.setDirection(DIRECTION::RIGHTTOP);
			}
			//���� �̵��� ������Ű ������
			if (KEYMANAGER->isStayKeyDown('S'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
				player.setCurrentState(player.getWalkState());
				player.setDirection(DIRECTION::RIGHTBOTTOM);
			}

			//���� �̵��� ������ ������
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

	//�������� �̵�
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
		//���� �̵��� ������ ������
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

	//������ �̵�
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
		//���� �̵��� ������ ������
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

	//���ʾƷ� �̵�
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
		//���� �̵��� ������ ������
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

	//�����ʾƷ� �̵�
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
		//���� �̵��� ������ ������
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
	if (Vector2::Length(&vec) > 1) // �밢���� ��
	{
		player.setShadowX(player.getShadowX() + (diagonal.x * MOVESPPED));
		//player.setX(player.getX() + (diagonal.x * MOVESPPED));
		player.setShadowY(player.getShadowY() + (diagonal.y * MOVESPPED));
		//player.setY(player.getY() + (diagonal.y * MOVESPPED));
	}
	else
	{
		//�밢�� �ƴҶ�
		player.setShadowX(player.getShadowX() + (vec.x * MOVESPPED));
		//player.setX(player.getX() + (vec.x * MOVESPPED));
		player.setShadowY(player.getShadowY() + (vec.y * MOVESPPED));
		//player.setY(player.getY() + (vec.y * MOVESPPED));
	}

	//����Ű ����
	if (KEYMANAGER->isOnceKeyUp('W'))
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpIdle"), ImageManager::GetInstance()->FindImage("playerUpIdle"));
		player.setCurrentState(player.getIdleState());

		//�Ʒ�Ű�� ������ �ٽ� �̵��ϰ�
		if (GetAsyncKeyState('S') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::DOWN);
		}
		//������Ű�� ������ �ٽ� �̵��ϰ�
		else if (GetAsyncKeyState('D') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightWalk"), ImageManager::GetInstance()->FindImage("playerRightWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::RIGHT);
		}
		//����Ű�� ������ �ٽ� �̵��ϰ�
		else if (GetAsyncKeyState('A') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftWalk"), ImageManager::GetInstance()->FindImage("playerLeftWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::LEFT);
		}
		player.setBedCount(player.getBedCount() == 0);
	}

	//�Ʒ�Ű ����
	if (KEYMANAGER->isOnceKeyUp('S'))
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownIdle"), ImageManager::GetInstance()->FindImage("playerDownIdle"));
		player.setCurrentState(player.getIdleState());

		//����Ű�� ������ �ٽ� �̵��ϰ�
		if (GetAsyncKeyState('W') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpWalk"), ImageManager::GetInstance()->FindImage("playerUpWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::UP);
		}
		//������Ű�� ������ �ٽ� �̵��ϰ�
		else if (GetAsyncKeyState('D') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightWalk"), ImageManager::GetInstance()->FindImage("playerRightWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::RIGHT);
		}
		//����Ű�� ������ �ٽ� �̵��ϰ�
		else if (GetAsyncKeyState('A') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftWalk"), ImageManager::GetInstance()->FindImage("playerLeftWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::LEFT);
		}
		player.setBedCount(player.getBedCount() == 0);
	}

	//����Ű ����
	if (KEYMANAGER->isOnceKeyUp('A'))
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftIdle"), ImageManager::GetInstance()->FindImage("playerLeftIdle"));
		player.setCurrentState(player.getIdleState());

		//������Ű�� ������ �ٽ� �̵��ϰ�
		if (GetAsyncKeyState('D') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightWalk"), ImageManager::GetInstance()->FindImage("playerRightWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::RIGHT);
		}
		//����Ű�� ������ �ٽ� �̵��ϰ�
		else if (GetAsyncKeyState('W') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpWalk"), ImageManager::GetInstance()->FindImage("playerUpWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::UP);
		}
		//�Ʒ��� ������ �ٽ� �̵��ϰ�
		else if (GetAsyncKeyState('S') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::DOWN);
		}
		player.setBedCount(player.getBedCount() == 0);
	}

	//������Ű ����
	if (KEYMANAGER->isOnceKeyUp('D'))
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightIdle"), ImageManager::GetInstance()->FindImage("playerRightIdle"));
		player.setCurrentState(player.getIdleState());

		//����Ű�� ������ �ٽ� �̵��ϰ�
		if (GetAsyncKeyState('A') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftWalk"), ImageManager::GetInstance()->FindImage("playerLeftWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::LEFT);
		}
		//����Ű�� ������ �ٽ� �̵��ϰ�
		else if (GetAsyncKeyState('W') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpWalk"), ImageManager::GetInstance()->FindImage("playerUpWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::UP);
		}
		//�Ʒ��� ������ �ٽ� �̵��ϰ�
		else if (GetAsyncKeyState('S') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::DOWN);
		}
		player.setBedCount(player.getBedCount() == 0);
	}
	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�

	//�÷��̾� ������
	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
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
	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�

	//�÷��̾� ����
	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
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
		//Ȱ ���� ī��Ʈ
		if (player.getBowBool())
		{
			player.setBowChargeCount(player.getBowChargeCount() + 1);
		}
		if (!player.getBowBool())
		{
			player.setBowChargeCount(player.getBowChargeCount() == 0);
		}

		//Ȱ���� ���İ�
		if (player.getBowChargeAlpha())
		{
			player.setBowAlphaCount(player.getBowAlphaCount() + 1);
		}

		if (!player.getBowChargeAlpha())
		{
			player.setBowAlphaCount(player.getBowAlphaCount() == 0);
		}

		//Ȱ �ٷ� ������ְ� �ڴ����� ������
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
					//���İ�ȿ�� ��������
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

	//��
	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
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
	//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
}

//roll(������) ����
void playerRollState::update(player & player)
{
	player.setPlayerRc(player.getX(), player.getY(), player.getPlayerRcW(), player.getPlayerRcH());
	//���� ������ 
	if (player.getDirection() == DIRECTION::UP)
	{
		if (!player.getTileColTop())
			player.setShadowY(player.getShadowY() - 7);
	}
	//�Ʒ��� ������
	if (player.getDirection() == DIRECTION::DOWN)
	{
		if (!player.getTileColBottom())
			player.setShadowY(player.getShadowY() + 7);
	}
	//�������� ������
	if (player.getDirection() == DIRECTION::LEFT)
	{
		if (!player.getTileColLeft())
			player.setShadowX(player.getShadowX() - 7);
	}
	//���������� ������
	if (player.getDirection() == DIRECTION::RIGHT)
	{
		if (!player.getTileColRight())
			player.setShadowX(player.getShadowX() + 7);
	}

	//�������� ������
	if (player.getDirection() == DIRECTION::RIGHTTOP)
	{
		if (!player.getTileColRightTop())
		{
			player.setShadowY(player.getShadowY() - 7);
			player.setShadowX(player.getShadowX() + 5);
		}
	}

	//������ ������
	if (player.getDirection() == DIRECTION::LEFTTOP)
	{
		if (!player.getTileColLeftTop())
		{
			player.setShadowY(player.getShadowY() - 7);
			player.setShadowX(player.getShadowX() - 5);
		}
	}

	//���ʾƷ� ������
	if (player.getDirection() == DIRECTION::LEFTBOTTOM)
	{
		if (!player.getTileColLeftBottom())
		{
			player.setShadowY(player.getShadowY() + 7);
			player.setShadowX(player.getShadowX() - 5);
		}
	}

	//�����ʾƷ� ������
	if (player.getDirection() == DIRECTION::RIGHTBOTTOM)
	{
		if (!player.getTileColRightBottom())
		{
			player.setShadowY(player.getShadowY() + 7);
			player.setShadowX(player.getShadowX() + 5);
		}
	}

	//�ִϸ��̼� ����� ������ 
	if (!KEYANIMANAGER->findAnimation("playerUpRoll")->isPlay()
		&& !KEYANIMANAGER->findAnimation("playerDownRoll")->isPlay()
		&& !KEYANIMANAGER->findAnimation("playerLeftRoll")->isPlay()
		&& !KEYANIMANAGER->findAnimation("playerRightRoll")->isPlay())
	{
		player.setPlayerRc(player.getX(), player.getY(), player.getPlayerRcW(), player.getPlayerRcH());
		//����Ű�� ������ �ٽ� �̵��ϰ�
		if (GetAsyncKeyState('W') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpWalk"), ImageManager::GetInstance()->FindImage("playerUpWalk"));
			player.setCurrentState(player.getWalkState());
		}
		//�Ʒ�Ű�� ������ �ٽ� �̵��ϰ�
		else if (GetAsyncKeyState('S') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
			player.setCurrentState(player.getWalkState());
		}
		//������Ű�� ������ �ٽ� �̵��ϰ�
		else if (GetAsyncKeyState('D') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightWalk"), ImageManager::GetInstance()->FindImage("playerRightWalk"));
			player.setCurrentState(player.getWalkState());
		}
		//����Ű�� ������ �ٽ� �̵��ϰ�
		else if (GetAsyncKeyState('A') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftWalk"), ImageManager::GetInstance()->FindImage("playerLeftWalk"));
			player.setCurrentState(player.getWalkState());
		}
		//�ƹ�Ű�� ������ �ʰ������� Idle ���·� ��ȯ
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

//die ����
void playerDieState::update(player & player)
{
	player.setPlayerRc(player.getX(), player.getY(), player.getPlayerRcW(), player.getPlayerRcH());
	//�ƹ�Ű�� �ȴ����� Idle ���·� ��ȯ
	if (KEYMANAGER->isOnceKeyUp('0'))
	{
		if (KEYMANAGER->getKeyUp() == NULL)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpIdle"), ImageManager::GetInstance()->FindImage("playerUpIdle"));
			player.setCurrentState(player.getIdleState());
		}
		//�Ʒ�Ű�� ������ �ٽ� �̵�
		else if (GetAsyncKeyState('S') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::DOWN);
		}
	}
}

//shield ����
void playerShieldState::update(player & player)
{
	player.setPlayerRc(player.getX(), player.getY(), player.getPlayerRcW(), player.getPlayerRcH());
	//�÷��̾� ����
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

	//����Ű ����
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
		//������Ű�� ������ �ٽ� �̵��ϰ�
		else if (GetAsyncKeyState('D') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightWalk"), ImageManager::GetInstance()->FindImage("playerRightWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::RIGHT);
		}
		//����Ű�� ������ �ٽ� �̵��ϰ�
		else if (GetAsyncKeyState('A') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftWalk"), ImageManager::GetInstance()->FindImage("playerLeftWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::LEFT);
		}
		//����Ű�� ������ �ٽ� �̵��ϰ�
		else if (GetAsyncKeyState('W') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpWalk"), ImageManager::GetInstance()->FindImage("playerUpWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::UP);
		}
		//�Ʒ�Ű�� ������ �ٽ� �̵��ϰ�
		else if (GetAsyncKeyState('S') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::DOWN);
		}
	}
}

//idleSwim ����
void playerIdleSwimState::update(player & player)
{
	player.setPlayerRc(player.getX(), player.getY(), player.getPlayerRcW(), player.getPlayerRcH());
	//��
	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpSwim"), ImageManager::GetInstance()->FindImage("playerUpSwim"));
		player.setCurrentState(player.getSwimState());
		player.setDirection(DIRECTION::UP);
	}

	//�Ʒ�
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownSwim"), ImageManager::GetInstance()->FindImage("playerDownSwim"));
		player.setCurrentState(player.getSwimState());
		player.setDirection(DIRECTION::DOWN);
	}

	//����
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftSwim"), ImageManager::GetInstance()->FindImage("playerLeftSwim"));
		player.setCurrentState(player.getSwimState());
		player.setDirection(DIRECTION::LEFT);
	}

	//������
	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightSwim"), ImageManager::GetInstance()->FindImage("playerRightSwim"));
		player.setCurrentState(player.getSwimState());
		player.setDirection(DIRECTION::RIGHT);
	}
}


//swim ����
void playerSwimState::update(player & player)
{
	player.setPlayerRc(player.getX(), player.getY(), player.getPlayerRcW(), player.getPlayerRcH());
	//�� 
	if (player.getDirection() == DIRECTION::UP)
	{
		if (KEYMANAGER->isStayKeyDown('W'))
		{
			//���� �Ʒ���Ű ������ ���� idleSwim ������� ����
			if (KEYMANAGER->isOnceKeyDown('S'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpIdleSwim"), ImageManager::GetInstance()->FindImage("playerUpIdleSwim"));
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
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpSwim"), ImageManager::GetInstance()->FindImage("playerUpSwim"));
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
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpIdleSwim"), ImageManager::GetInstance()->FindImage("playerUpIdleSwim"));
			player.setCurrentState(player.getIdleSwimState());
		}
		//�Ʒ�Ű�� ������ �ٽ� �̵�
		else if (GetAsyncKeyState('S') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownSwim"), ImageManager::GetInstance()->FindImage("playerDownSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirection(DIRECTION::DOWN);
		}
		//����Ű�� ������ �ٽ� �̵�
		else if (GetAsyncKeyState('A') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftSwim"), ImageManager::GetInstance()->FindImage("playerLeftSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirection(DIRECTION::LEFT);
		}
		//������Ű�� ������ �ٽ� �̵�
		else if (GetAsyncKeyState('D') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightSwim"), ImageManager::GetInstance()->FindImage("playerRightSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirection(DIRECTION::RIGHT);
		}
		player.setBedCount(player.getBedCount() == 0);
	}

	//�Ʒ�
	if (player.getDirection() == DIRECTION::DOWN)
	{
		if (KEYMANAGER->isStayKeyDown('S'))
		{
			//���� ����Ű ������ �Ʒ� idleSwim ������� ����
			if (KEYMANAGER->isOnceKeyDown('W'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownIdleSwim"), ImageManager::GetInstance()->FindImage("playerDownIdleSwim"));
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
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownSwim"), ImageManager::GetInstance()->FindImage("playerDownSwim"));
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
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownIdleSwim"), ImageManager::GetInstance()->FindImage("playerDownIdleSwim"));
			player.setCurrentState(player.getIdleSwimState());
		}
		//����Ű�� ������ �ٽ� �̵�
		else if (GetAsyncKeyState('W') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpSwim"), ImageManager::GetInstance()->FindImage("playerUpSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirection(DIRECTION::UP);
		}
		//����Ű�� ������ �ٽ� �̵�
		else if (GetAsyncKeyState('A') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftSwim"), ImageManager::GetInstance()->FindImage("playerLeftSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirection(DIRECTION::LEFT);
		}
		//������Ű�� ������ �ٽ� �̵�
		else if (GetAsyncKeyState('D') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightSwim"), ImageManager::GetInstance()->FindImage("playerRightSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirection(DIRECTION::RIGHT);
		}
		player.setBedCount(player.getBedCount() == 0);
	}

	//����
	if (player.getDirection() == DIRECTION::LEFT)
	{
		if (KEYMANAGER->isStayKeyDown('A'))
		{
			//���� ������Ű ������ ���� idleSwim ������� ����
			if (KEYMANAGER->isOnceKeyDown('D'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftIdleSwim"), ImageManager::GetInstance()->FindImage("playerLeftIdleSwim"));
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
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftSwim"), ImageManager::GetInstance()->FindImage("playerLeftSwim"));
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
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftIdleSwim"), ImageManager::GetInstance()->FindImage("playerLeftIdleSwim"));
			player.setCurrentState(player.getIdleSwimState());
		}
		//������Ű�� ������ �ٽ� �̵�
		else if (GetAsyncKeyState('D') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightSwim"), ImageManager::GetInstance()->FindImage("playerRightSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirection(DIRECTION::RIGHT);
		}
		//����Ű�� ������ �ٽ� �̵�
		else if (GetAsyncKeyState('W') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpSwim"), ImageManager::GetInstance()->FindImage("playerUpSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirection(DIRECTION::UP);
		}
		//�Ʒ�Ű�� ������ �ٽ� �̵�
		else if (GetAsyncKeyState('S') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownSwim"), ImageManager::GetInstance()->FindImage("playerDownSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirection(DIRECTION::DOWN);
		}
		player.setBedCount(player.getBedCount() == 0);
	}

	//������
	if (player.getDirection() == DIRECTION::RIGHT)
	{
		if (KEYMANAGER->isStayKeyDown('D'))
		{
			//���� ����Ű ������ ������ idleSwim ������� ����
			if (KEYMANAGER->isOnceKeyDown('A'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightIdleSwim"), ImageManager::GetInstance()->FindImage("playerRightIdleSwim"));
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
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightSwim"), ImageManager::GetInstance()->FindImage("playerRightSwim"));
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
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightIdleSwim"), ImageManager::GetInstance()->FindImage("playerRightIdleSwim"));
			player.setCurrentState(player.getIdleSwimState());
		}
		//����Ű�� ������ �ٽ� �̵�
		else if (GetAsyncKeyState('A') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftSwim"), ImageManager::GetInstance()->FindImage("playerLeftSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirection(DIRECTION::LEFT);
		}
		//����Ű�� ������ �ٽ� �̵�
		else if (GetAsyncKeyState('W') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpSwim"), ImageManager::GetInstance()->FindImage("playerUpSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirection(DIRECTION::UP);
		}
		//�Ʒ�Ű�� ������ �ٽ� �̵�
		else if (GetAsyncKeyState('S') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownSwim"), ImageManager::GetInstance()->FindImage("playerDownSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirection(DIRECTION::DOWN);
		}
		player.setBedCount(player.getBedCount() == 0);
	}
}

//bow ����
void playerbowState::update(player & player)
{
	//���ʹ����� ������ ��Ʈ���·� �Ѿ
	if (player.getEnemyCol())
	{
		player.setCurrentState(player.getHitState());
	}

	player.setPlayerRc(player.getX(), player.getY(), player.getPlayerRcW(), player.getPlayerRcH());
	//���� �ִϸ��̼� ��� ������
	if (!KEYANIMANAGER->findAnimation("playerUpBow")->isPlay() && !KEYANIMANAGER->findAnimation("playerDownBow")->isPlay()
		&& !KEYANIMANAGER->findAnimation("playerLeftBow")->isPlay() && !KEYANIMANAGER->findAnimation("playerRightBow")->isPlay())
	{
		//�ƹ�Ű�� ������������ ���̵� ���·� ��ȯ
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

		//������Ű�� ������ �ٽ� �̵��ϰ�
		else if (GetAsyncKeyState('D') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightWalk"), ImageManager::GetInstance()->FindImage("playerRightWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::RIGHT);
		}
		//����Ű�� ������ �ٽ� �̵��ϰ�
		else if (GetAsyncKeyState('A') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftWalk"), ImageManager::GetInstance()->FindImage("playerLeftWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::LEFT);
		}
		//����Ű�� ������ �ٽ� �̵��ϰ�
		else if (GetAsyncKeyState('W') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpWalk"), ImageManager::GetInstance()->FindImage("playerUpWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::UP);
		}
		//�Ʒ�Ű�� ������ �ٽ� �̵��ϰ�
		else if (GetAsyncKeyState('S') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::DOWN);
		}
	}
}

//sword ����
void playerSwordState::update(player & player)
{
	//���ʹ����� ������ ��Ʈ���·� �Ѿ
	if (player.getEnemyCol())
	{
		player.setCurrentState(player.getHitState());
	}

	player.setPlayerRc(player.getX(), player.getY(), player.getPlayerRcW(), player.getPlayerRcH());
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
		if (player.getPlayerMotion() == KEYANIMANAGER->findAnimation("playerUpSword1")
			|| player.getPlayerMotion() == KEYANIMANAGER->findAnimation("playerDownSword1")
			|| player.getPlayerMotion() == KEYANIMANAGER->findAnimation("playerLeftSword1")
			|| player.getPlayerMotion() == KEYANIMANAGER->findAnimation("playerRightSword1"))
		{
			//�ִϸ��̼� ��� ������
			if (!KEYANIMANAGER->findAnimation("playerUpSword1")->isPlay() && !KEYANIMANAGER->findAnimation("playerDownSword1")->isPlay()
				&& !KEYANIMANAGER->findAnimation("playerLeftSword1")->isPlay() && !KEYANIMANAGER->findAnimation("playerRightSword1")->isPlay())
			{
				player.setAttackRcbool(false);
				player.setAttackRc(player.getX(), player.getY(), 0, 0);
				//Ű������ 2Ÿ�� �Ѿ
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

	//���� �ִϸ��̼� ��� ������
	if (!KEYANIMANAGER->findAnimation("playerUpSword1")->isPlay() && !KEYANIMANAGER->findAnimation("playerDownSword1")->isPlay()
		&& !KEYANIMANAGER->findAnimation("playerLeftSword1")->isPlay() && !KEYANIMANAGER->findAnimation("playerRightSword1")->isPlay()
		&& !KEYANIMANAGER->findAnimation("playerUpSword2")->isPlay() && !KEYANIMANAGER->findAnimation("playerDownSword2")->isPlay()
		&& !KEYANIMANAGER->findAnimation("playerLeftSword2")->isPlay() && !KEYANIMANAGER->findAnimation("playerRightSword2")->isPlay())
	{
		player.setSwrodAttackCombo(false);
		player.setAttackRcbool(false);
		player.setAttackRc(player.getX(), player.getY(), 0, 0);

		//�ƹ�Ű�� ������������ ���̵� ���·� ��ȯ
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

		//������Ű�� ������ �ٽ� �̵��ϰ�
		else if (GetAsyncKeyState('D') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightWalk"), ImageManager::GetInstance()->FindImage("playerRightWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::RIGHT);
		}
		//����Ű�� ������ �ٽ� �̵��ϰ�
		else if (GetAsyncKeyState('A') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftWalk"), ImageManager::GetInstance()->FindImage("playerLeftWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::LEFT);
		}
		//����Ű�� ������ �ٽ� �̵��ϰ�
		else if (GetAsyncKeyState('W') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpWalk"), ImageManager::GetInstance()->FindImage("playerUpWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::UP);
		}
		//�Ʒ�Ű�� ������ �ٽ� �̵��ϰ�
		else if (GetAsyncKeyState('S') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::DOWN);
		}
	}
}

//���ڷ��� 
void playerBroomState::update(player & player)
{
	player.setPlayerRc(player.getX(), player.getY(), player.getPlayerRcW(), player.getPlayerRcH());
	//��
	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpWalk"), ImageManager::GetInstance()->FindImage("playerUpWalk"));
		player.setCurrentState(player.getWalkState());
	}
	//�Ʒ� 
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
		player.setCurrentState(player.getWalkState());
	}
	//���� 
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftWalk"), ImageManager::GetInstance()->FindImage("playerLeftWalk"));
		player.setCurrentState(player.getWalkState());
	}
	//������ 
	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightWalk"), ImageManager::GetInstance()->FindImage("playerRightWalk"));
		player.setCurrentState(player.getWalkState());
	}
}

//ħ�� ����
void playerBedState::update(player & player)
{
	player.setPlayerRc(player.getX(), player.getY(), player.getPlayerRcW(), player.getPlayerRcH());
	//�ִϸ��̼��� ������ ����
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

//�ڷ���Ʈ ����
void playerTeleportState::update(player & player)
{
	player.setPlayerRc(player.getX(), player.getY(), player.getPlayerRcW(), player.getPlayerRcH());
	//�ִϸ��̼� ������ ����
	if (!KEYANIMANAGER->findAnimation("playerTeleport")->isPlay())
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerTeleportOut"), ImageManager::GetInstance()->FindImage("playerTeleportOut"));
		player.setCurrentState(player.getTeleportOutState());
	}
}

//�ڷ���Ʈ(����) ���� ����
void playerTeleportInState::update(player & player)
{
	player.setPlayerRc(player.getX(), player.getY(), player.getPlayerRcW(), player.getPlayerRcH());
	//�ִϸ��̼� ������ ����
	if (!KEYANIMANAGER->findAnimation("playerTeleportIn")->isPlay())
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownIdle"), ImageManager::GetInstance()->FindImage("playerDownIdle"));
		player.setCurrentState(player.getIdleState());
	}
}

//�ڷ���Ʈ(Ż��) ����
void playerTeleportOutState::update(player & player)
{
	player.setPlayerRc(player.getX(), player.getY(), player.getPlayerRcW(), player.getPlayerRcH());
	//�ִϸ��̼� ������ ����
	if (!KEYANIMANAGER->findAnimation("playerTeleportOut")->isPlay())
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownIdle"), ImageManager::GetInstance()->FindImage("playerDownIdle"));
		player.setCurrentState(player.getIdleState());
	}
}

//�÷��̾� Hit ����
void playerHitState::update(player & player)
{
	//�÷��̾� ���İ� true
	player.setHitCondition(true);
	player.setHitAlphaCount(player.getHitAlphaCount() + 1);
	//Count�� 20�� �Ѿ�� �ٽ� ���İ� false �༭ �������
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