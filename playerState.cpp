#include "stdafx.h"
#include "playerState.h"
#include "player.h"
#include "arrow.h"

HRESULT playerIdleState::init()
{
	return S_OK;
}

//Idle 鼻鷓
void playerIdleState::update(player & player)
{
	player.setPlayerRc(player.getX(), player.getY(), player.getPlayerRcW(), player.getPlayerRcH());	//餌褒鼻 в蹂橈擠 橾欽 鹿菸~
	player.setBedCount(player.getBedCount() + 1);
	//嬴檜菟 鼻鷓 螃楚 雖樓腎賊 綿濠瑞韓л
	if (player.getBedCount() >= 300)
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerBroom"), ImageManager::GetInstance()->FindImage("playerBroom"));
		player.setCurrentState(player.getBroomState());
		player.setBedCount(player.getBedCount() == 0);
	}

	//避擎鼻鷓煎 剩橫陛晦~
	if (player.getDeadState() || player.getplayerCurrentHp() <= 0)
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDie"), ImageManager::GetInstance()->FindImage("playerDie"));
		player.setCurrentState(player.getDieState());
	}

	if (!player.getTransform())
	{
		//務晦
		//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天
		//嬪
		if (KEYMANAGER->isOnceKeyDown('W'))
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpWalk"), ImageManager::GetInstance()->FindImage("playerUpWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::UP);
		}
		//嬴楚 
		if (KEYMANAGER->isOnceKeyDown('S'))
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::DOWN);
		}
		//豭薹 
		if (KEYMANAGER->isOnceKeyDown('A'))
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftWalk"), ImageManager::GetInstance()->FindImage("playerLeftWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::LEFT);
		}
		//螃艇薹 
		if (KEYMANAGER->isOnceKeyDown('D'))
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightWalk"), ImageManager::GetInstance()->FindImage("playerRightWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::RIGHT);
		}
		//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天
	}

	//Ы溯檜橫 掘腦晦
	//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		SOUNDMANAGER->play("roll", 1.0f);
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
	//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天


	//Ы溯檜橫 餌蜂 <-- 歜衛
	//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天
	//if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	//{
	//	player.setPlayerCurrentHp(player.getplayerCurrentHp() - 30);
	//}
	//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天

	//Ы溯檜橫 蔓萄
	//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天
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
	//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天

	//Ы溯檜橫 熱艙 && 湍瞪 in <-- 歜衛
	//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天

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
	//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天

	//鼠晦 滲唳
	if (player.getWeaponChange())
	{
		if (KEYMANAGER->isOnceKeyDown('Z'))
		{
			SOUNDMANAGER->play("WeaponChange", 1.0f);
			//�香鼒� 滲唳
			player.setWeaponChange(false);
			player.setCurrentState(player.getBowState());
		}
	}

	//鼠晦 滲唳
	if (!player.getWeaponChange())
	{
		if (KEYMANAGER->isOnceKeyDown('Z'))
		{
			SOUNDMANAGER->play("WeaponChange", 1.0f);
			//匐戲煎 滲唳
			player.setWeaponChange(true);
			player.setCurrentState(player.getSwordState());
		}
	}

	//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天

	//��

	if (player.getWeaponChange())
	{
		if (!player.getAttackProhibition())
		{

			//�� 醱瞪 蘋遴お
			if (player.getBowBool())
			{
				player.setBowChargeCount(player.getBowChargeCount() + 1);
			}
			if (!player.getBowBool())
			{
				player.setBowChargeCount(player.getBowChargeCount() == 0);
			}

			//�冕磍� 憲だ高
			if (player.getBowChargeAlpha())
			{
				player.setBowAlphaCount(player.getBowAlphaCount() + 1);
			}

			if (!player.getBowChargeAlpha())
			{
				player.setBowAlphaCount(player.getBowAlphaCount() == 0);
			}

			//�� 夥煎 踩熱紫氈堅 缽援腦賊 醱瞪脾
			if (KEYMANAGER->isOnceKeyDown('J'))
			{
				player.setBowBool(true);
			}

			if (player.getBowChargeCount() >= 30)
			{
				if (!SOUNDMANAGER->isPlaySound("bow_Charge") && !player.getIsBowChargeSound())
					SOUNDMANAGER->play("bow_Charge", 1.0f);
				player.setBowChargeAlpha(true);
				player.setBowChargeState(true);
				player.setIsBowChargeSound(true);

				if (KEYMANAGER->isStayKeyDown('J'))
				{
					if (player.getDirection() == DIRECTION::UP)
					{
						player.setShadowY(player.getShadowY() - 0);
						//憲だ高�膩� 頂晦嬪п
						if (player.getBowAlphaCount() <= 10)
						{
							player.setPlayerMotion(KEYANIMANAGER->findAnimation("bowUpChargeWhite"), ImageManager::GetInstance()->FindImage("bowUpChargeWhite"));
						}
						if (player.getBowAlphaCount() >= 11)
						{
							player.setPlayerMotion(KEYANIMANAGER->findAnimation("bowUpCharge"), ImageManager::GetInstance()->FindImage("bowUpCharge"));
						}

						//HP陛 0檜ж陛 腎賊 Die 鼻鷓煎 剩橫陛晦
						if (player.getDeadState() || player.getplayerCurrentHp() <= 0)
						{
							player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDie"), ImageManager::GetInstance()->FindImage("playerDie"));
							player.setCurrentState(player.getDieState());
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

						//HP陛 0檜ж陛 腎賊 Die 鼻鷓煎 剩橫陛晦
						if (player.getDeadState() || player.getplayerCurrentHp() <= 0)
						{
							player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDie"), ImageManager::GetInstance()->FindImage("playerDie"));
							player.setCurrentState(player.getDieState());
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

						//HP陛 0檜ж陛 腎賊 Die 鼻鷓煎 剩橫陛晦
						if (player.getDeadState() || player.getplayerCurrentHp() <= 0)
						{
							player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDie"), ImageManager::GetInstance()->FindImage("playerDie"));
							player.setCurrentState(player.getDieState());
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

						//HP陛 0檜ж陛 腎賊 Die 鼻鷓煎 剩橫陛晦
						if (player.getDeadState() || player.getplayerCurrentHp() <= 0)
						{
							player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDie"), ImageManager::GetInstance()->FindImage("playerDie"));
							player.setCurrentState(player.getDieState());
						}

					}
					player.setBedCount(player.getBedCount() == 0);
				}
			}

			if (KEYMANAGER->isOnceKeyUp('J'))
			{
				SOUNDMANAGER->play("bow", 1.0f);
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
				player.setIsBowChargeSound(false);
			}
		}
	}

	//匐
	//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天
	if (!player.getWeaponChange())
	{
		if (!player.getAttackProhibition())
		{
			if (KEYMANAGER->isOnceKeyDown('J'))
			{
				SOUNDMANAGER->play("Sword", 1.0f);
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
	}
	//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天

	//Ы溯檜橫 蘿溯んお
	if (SCENEMANAGER->getCurrentScene() != "葆擊壁" && SCENEMANAGER->getCurrentScene() != "憧壁" && INVENTORY->getGold() >= 200)
	{
		if (KEYMANAGER->isOnceKeyDown('L'))
		{
			INVENTORY->setGold(-200);
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerTeleport"), ImageManager::GetInstance()->FindImage("playerTeleport"));
			player.setCurrentState(player.getTeleportState());
			player.setBedCount(player.getBedCount() == 0);
		}
	}
}

//walk 鼻鷓
void playerWalkState::update(player & player)
{
	player.setPlayerRc(player.getX(), player.getY(), player.getPlayerRcW(), player.getPlayerRcH());

	if (player.getplayerCurrentHp() <= 0)
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDie"), ImageManager::GetInstance()->FindImage("playerDie"));
		player.setCurrentState(player.getDieState());
	}

	//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天
	//嬪

	int x = 0;
	int y = 0;

	if (player.getDirection() == DIRECTION::UP)
	{
		if (KEYMANAGER->isStayKeyDown('W'))
		{
			if (!SOUNDMANAGER->isPlaySound("walk"))
				SOUNDMANAGER->play("walk", WALKSOUND);
			//虜擒 嬴楚酈 援腦賊 嬪薹Idle 賅蝗戲煎 滲л
			if (KEYMANAGER->isOnceKeyDown('S'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpIdle"), ImageManager::GetInstance()->FindImage("playerUpIdle"));
			}
			//嬪薹Idle 賅蝗戲煎 誇蹺晦
			else if (KEYMANAGER->isStayKeyDown('S'))
			{
				SOUNDMANAGER->stop("walk");
				return;
			}
			//嬴楚酈蒂 飲賊 嬪煎 棻衛 遺霜歜
			else if (KEYMANAGER->isOnceKeyUp('S'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpWalk"), ImageManager::GetInstance()->FindImage("playerUpWalk"));
				player.setCurrentState(player.getWalkState());
			}
			//虜擒 檜翕醞 豭薹酈 援腦賊
			if (KEYMANAGER->isStayKeyDown('A'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpWalk"), ImageManager::GetInstance()->FindImage("playerUpWalk"));
				player.setCurrentState(player.getWalkState());
				player.setDirection(DIRECTION::LEFTTOP);
			}
			//虜擒 檜翕醞 螃艇薹酈 援腦賊
			if (KEYMANAGER->isStayKeyDown('D'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpWalk"), ImageManager::GetInstance()->FindImage("playerUpWalk"));
				player.setCurrentState(player.getWalkState());
				player.setDirection(DIRECTION::RIGHTTOP);
			}
			//虜擒 檜翕醞 掘腦晦 援腦賊
			if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
			{
				SOUNDMANAGER->play("roll", 1.0f);
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpRoll"), ImageManager::GetInstance()->FindImage("playerUpRoll"));
				player.setCurrentState(player.getRollState());
			}

			y = -1;

		}
	}

	//嬴楚
	if (player.getDirection() == DIRECTION::DOWN)
	{
		if (KEYMANAGER->isStayKeyDown('S'))
		{
			if (!SOUNDMANAGER->isPlaySound("walk"))
				SOUNDMANAGER->play("walk", WALKSOUND);
			//虜擒 嬪薹酈 援腦賊 嬴楚 Idle 賅蝗戲煎 滲л
			if (KEYMANAGER->isOnceKeyDown('W'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownIdle"), ImageManager::GetInstance()->FindImage("playerDownIdle"));
			}
			//嬴楚Idle 賅蝗戲煎 誇蹺晦
			else if (KEYMANAGER->isStayKeyDown('W'))
			{
				SOUNDMANAGER->stop("walk");
				return;
			}
			//嬪薹酈蒂 飲賊 嬴楚煎 棻衛 遺霜歜
			else if (KEYMANAGER->isOnceKeyUp('W'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
				player.setCurrentState(player.getWalkState());
			}
			//虜擒 檜翕醞 豭薹酈 援腦賊
			if (KEYMANAGER->isStayKeyDown('A'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
				player.setCurrentState(player.getWalkState());
				player.setDirection(DIRECTION::LEFTBOTTOM);
			}
			//虜擒 檜翕醞 螃艇薹酈 援腦賊
			if (KEYMANAGER->isStayKeyDown('D'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
				player.setCurrentState(player.getWalkState());
				player.setDirection(DIRECTION::RIGHTBOTTOM);
			}

			//虜擒 檜翕醞 掘腦晦 援腦賊
			if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
			{
				SOUNDMANAGER->play("roll", 1.0f);
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownRoll"), ImageManager::GetInstance()->FindImage("playerDownRoll"));
				player.setCurrentState(player.getRollState());
			}

			y = 1;

		}
	}

	//豭薹
	if (player.getDirection() == DIRECTION::LEFT)
	{
		if (KEYMANAGER->isStayKeyDown('A'))
		{
			if (!SOUNDMANAGER->isPlaySound("walk"))
				SOUNDMANAGER->play("walk", WALKSOUND);
			//虜擒 螃艇薹酈 援腦賊 豭薹 Idle 賅蝗戲煎 滲л
			if (KEYMANAGER->isOnceKeyDown('D'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftIdle"), ImageManager::GetInstance()->FindImage("playerLeftIdle"));
			}
			//豭薹Idle 賅蝗戲煎 誇蹺晦
			else if (KEYMANAGER->isStayKeyDown('D'))
			{
				SOUNDMANAGER->stop("walk");
				return;
			}
			//螃艇薹酈蒂 飲賊 豭薹戲煎 棻衛 遺霜歜
			else if (KEYMANAGER->isOnceKeyUp('D'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftWalk"), ImageManager::GetInstance()->FindImage("playerLeftWalk"));
				player.setCurrentState(player.getWalkState());
			}
			//虜擒 檜翕醞 嬪薹酈 援腦賊
			if (KEYMANAGER->isStayKeyDown('W'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpWalk"), ImageManager::GetInstance()->FindImage("playerUpWalk"));
				player.setCurrentState(player.getWalkState());
				player.setDirection(DIRECTION::LEFTTOP);
			}
			//虜擒 檜翕醞 嬴楚酈 援腦賊
			if (KEYMANAGER->isStayKeyDown('S'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
				player.setCurrentState(player.getWalkState());
				player.setDirection(DIRECTION::LEFTBOTTOM);
			}

			//虜擒 檜翕醞 掘腦晦 援腦賊
			if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
			{
				SOUNDMANAGER->play("roll", 1.0f);
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftRoll"), ImageManager::GetInstance()->FindImage("playerLeftRoll"));
				player.setCurrentState(player.getRollState());
			}

			x = -1;

		}
	}

	//螃艇薹
	if (player.getDirection() == DIRECTION::RIGHT)
	{
		if (KEYMANAGER->isStayKeyDown('D'))
		{
			if (!SOUNDMANAGER->isPlaySound("walk"))
				SOUNDMANAGER->play("walk", WALKSOUND);
			//虜擒 豭薹酈 援腦賊 螃艇薹 Idle 賅蝗戲煎 滲л
			if (KEYMANAGER->isOnceKeyDown('A'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightIdle"), ImageManager::GetInstance()->FindImage("playerRightIdle"));
			}
			//螃艇薹Idle 賅蝗戲煎 誇蹺晦
			else if (KEYMANAGER->isStayKeyDown('A'))
			{
				SOUNDMANAGER->stop("walk");
				return;
			}
			//豭薹酈蒂 飲賊 螃艇薹戲煎 棻衛 遺霜歜
			else if (KEYMANAGER->isOnceKeyUp('A'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightWalk"), ImageManager::GetInstance()->FindImage("playerRightWalk"));
				player.setCurrentState(player.getWalkState());
			}

			//虜擒 檜翕醞 豭薹酈 援腦賊
			if (KEYMANAGER->isStayKeyDown('W'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpWalk"), ImageManager::GetInstance()->FindImage("playerUpWalk"));
				player.setCurrentState(player.getWalkState());
				player.setDirection(DIRECTION::RIGHTTOP);
			}
			//虜擒 檜翕醞 螃艇薹酈 援腦賊
			if (KEYMANAGER->isStayKeyDown('S'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
				player.setCurrentState(player.getWalkState());
				player.setDirection(DIRECTION::RIGHTBOTTOM);
			}

			//虜擒 檜翕醞 掘腦晦 援腦賊
			if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
			{
				SOUNDMANAGER->play("roll", 1.0f);
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightRoll"), ImageManager::GetInstance()->FindImage("playerRightRoll"));
				player.setCurrentState(player.getRollState());
			}

			x = 1;
		}
	}

	//螃艇薹嬪 檜翕
	if (player.getDirection() == DIRECTION::RIGHTTOP)
	{
		if (!SOUNDMANAGER->isPlaySound("walk"))
			SOUNDMANAGER->play("walk", WALKSOUND);
		x = 1;
		y = -1;

		//虜擒 檜翕醞 掘腦晦 援腦賊
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			SOUNDMANAGER->play("roll", 1.0f);
			if (KEYMANAGER->isStayKeyDown('D'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpRoll"), ImageManager::GetInstance()->FindImage("playerUpRoll"));
				player.setCurrentState(player.getRollState());
				player.setDirection(DIRECTION::RIGHTTOP);
			}
		}
	}

	//豭薹嬪 檜翕
	if (player.getDirection() == DIRECTION::LEFTTOP)
	{
		if (!SOUNDMANAGER->isPlaySound("walk"))
			SOUNDMANAGER->play("walk", WALKSOUND);
		x = -1;
		y = -1;

		//虜擒 檜翕醞 掘腦晦 援腦賊
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			SOUNDMANAGER->play("roll", 1.0f);
			if (KEYMANAGER->isStayKeyDown('A'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpRoll"), ImageManager::GetInstance()->FindImage("playerUpRoll"));
				player.setCurrentState(player.getRollState());
				player.setDirection(DIRECTION::LEFTTOP);
			}
		}
	}

	//豭薹嬴楚 檜翕
	if (player.getDirection() == DIRECTION::LEFTBOTTOM)
	{
		if (!SOUNDMANAGER->isPlaySound("walk"))
			SOUNDMANAGER->play("walk", WALKSOUND);
		x = -1;
		y = 1;


		//虜擒 檜翕醞 掘腦晦 援腦賊
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			SOUNDMANAGER->play("roll", 1.0f);
			if (KEYMANAGER->isStayKeyDown('A'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownRoll"), ImageManager::GetInstance()->FindImage("playerDownRoll"));
				player.setCurrentState(player.getRollState());
				player.setDirection(DIRECTION::LEFTBOTTOM);
			}
		}
	}

	//螃艇薹嬴楚 檜翕
	if (player.getDirection() == DIRECTION::RIGHTBOTTOM)
	{
		if (!SOUNDMANAGER->isPlaySound("walk"))
			SOUNDMANAGER->play("walk", WALKSOUND);
		x = 1;
		y = 1;

		//虜擒 檜翕醞 掘腦晦 援腦賊
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			SOUNDMANAGER->play("roll", 1.0f);
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
	if (Vector2::Length(&vec) > 1) // 渠陝摹橾 陽
	{
		player.setShadowX(player.getShadowX() + (diagonal.x * MOVESPPED));
		player.setShadowY(player.getShadowY() + (diagonal.y * MOVESPPED));
	}
	else
	{
		//渠陝摹 嬴棍陽
		player.setShadowX(player.getShadowX() + (vec.x * MOVESPPED));
		player.setShadowY(player.getShadowY() + (vec.y * MOVESPPED));
	}

	//嬪薹酈 飲賊
	if (KEYMANAGER->isOnceKeyUp('W'))
	{
		SOUNDMANAGER->stop("walk");
		player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpIdle"), ImageManager::GetInstance()->FindImage("playerUpIdle"));
		player.setCurrentState(player.getIdleState());

		//嬴楚酈蒂 援腦賊 棻衛 檜翕ж啪
		if (GetAsyncKeyState('S') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::DOWN);
		}
		//螃艇薹酈蒂 援腦賊 棻衛 檜翕ж啪
		else if (GetAsyncKeyState('D') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightWalk"), ImageManager::GetInstance()->FindImage("playerRightWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::RIGHT);
		}
		//豭薹酈蒂 援腦賊 棻衛 檜翕ж啪
		else if (GetAsyncKeyState('A') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftWalk"), ImageManager::GetInstance()->FindImage("playerLeftWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::LEFT);
		}
		player.setBedCount(player.getBedCount() == 0);
	}

	//嬴楚酈 飲賊
	if (KEYMANAGER->isOnceKeyUp('S'))
	{
		SOUNDMANAGER->stop("walk");
		player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownIdle"), ImageManager::GetInstance()->FindImage("playerDownIdle"));
		player.setCurrentState(player.getIdleState());

		//嬪薹酈蒂 援腦賊 棻衛 檜翕ж啪
		if (GetAsyncKeyState('W') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpWalk"), ImageManager::GetInstance()->FindImage("playerUpWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::UP);
		}
		//螃艇薹酈蒂 援腦賊 棻衛 檜翕ж啪
		else if (GetAsyncKeyState('D') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightWalk"), ImageManager::GetInstance()->FindImage("playerRightWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::RIGHT);
		}
		//豭薹酈蒂 援腦賊 棻衛 檜翕ж啪
		else if (GetAsyncKeyState('A') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftWalk"), ImageManager::GetInstance()->FindImage("playerLeftWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::LEFT);
		}
		player.setBedCount(player.getBedCount() == 0);
	}

	//豭薹酈 飲賊
	if (KEYMANAGER->isOnceKeyUp('A'))
	{
		SOUNDMANAGER->stop("walk");
		player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftIdle"), ImageManager::GetInstance()->FindImage("playerLeftIdle"));
		player.setCurrentState(player.getIdleState());

		//螃艇薹酈蒂 援腦賊 棻衛 檜翕ж啪
		if (GetAsyncKeyState('D') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightWalk"), ImageManager::GetInstance()->FindImage("playerRightWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::RIGHT);
		}
		//嬪薹酈蒂 援腦賊 棻衛 檜翕ж啪
		else if (GetAsyncKeyState('W') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpWalk"), ImageManager::GetInstance()->FindImage("playerUpWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::UP);
		}
		//嬴楚蒂 援腦賊 棻衛 檜翕ж啪
		else if (GetAsyncKeyState('S') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::DOWN);
		}
		player.setBedCount(player.getBedCount() == 0);
	}

	//螃艇薹酈 飲賊
	if (KEYMANAGER->isOnceKeyUp('D'))
	{
		SOUNDMANAGER->stop("walk");
		player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightIdle"), ImageManager::GetInstance()->FindImage("playerRightIdle"));
		player.setCurrentState(player.getIdleState());

		//豭薹酈蒂 援腦賊 棻衛 檜翕ж啪
		if (GetAsyncKeyState('A') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftWalk"), ImageManager::GetInstance()->FindImage("playerLeftWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::LEFT);
		}
		//嬪薹酈蒂 援腦賊 棻衛 檜翕ж啪
		else if (GetAsyncKeyState('W') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpWalk"), ImageManager::GetInstance()->FindImage("playerUpWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::UP);
		}
		//嬴楚蒂 援腦賊 棻衛 檜翕ж啪
		else if (GetAsyncKeyState('S') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::DOWN);
		}
		player.setBedCount(player.getBedCount() == 0);
	}
	//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天

	//熱艙鼻鷓
	//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天
	if (player.getTransform())
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownSwim"), ImageManager::GetInstance()->FindImage("playerDownSwim"));
		player.setCurrentState(player.getSwimState());
		player.setDirection(DIRECTION::DOWN);
	}
	//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天

	//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天
	//避擎鼻鷓煎 剩橫陛晦~
	if (player.getDeadState() || player.getplayerCurrentHp() <= 0)
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDie"), ImageManager::GetInstance()->FindImage("playerDie"));
		player.setCurrentState(player.getDieState());
	}
	//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天

	//Ы溯檜橫 掘腦晦
	//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		SOUNDMANAGER->play("roll", 1.0f);
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
	//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天

	//Ы溯檜橫 蔓萄
	//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天
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
	//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天

	//鼠晦 滲唳
	if (player.getWeaponChange())
	{
		if (KEYMANAGER->isOnceKeyDown('Z'))
		{
			SOUNDMANAGER->play("WeaponChange", 1.0f);
			//�香鼒� 滲唳
			player.setWeaponChange(false);
			player.setCurrentState(player.getBowState());
		}
	}

	//鼠晦 滲唳
	if (!player.getWeaponChange())
	{
		if (KEYMANAGER->isOnceKeyDown('Z'))
		{
			SOUNDMANAGER->play("WeaponChange", 1.0f);
			//匐戲煎 滲唳
			player.setWeaponChange(true);
			player.setCurrentState(player.getSwordState());
		}
	}

	//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天
	//��
	if (player.getWeaponChange())
	{	
		if (!player.getAttackProhibition())
		{
			//�� 醱瞪 蘋遴お
			if (player.getBowBool())
			{
				player.setBowChargeCount(player.getBowChargeCount() + 1);
			}
			if (!player.getBowBool())
			{
				player.setBowChargeCount(player.getBowChargeCount() == 0);
			}

			//�冕磍� 憲だ高
			if (player.getBowChargeAlpha())
			{
				player.setBowAlphaCount(player.getBowAlphaCount() + 1);
			}

			if (!player.getBowChargeAlpha())
			{
				player.setBowAlphaCount(player.getBowAlphaCount() == 0);
			}

			//�� 夥煎 踩熱紫氈堅 缽援腦賊 醱瞪脾
			if (KEYMANAGER->isOnceKeyDown('J'))
			{
				player.setBowBool(true);
			}

			if (player.getBowChargeCount() >= 30)
			{
				if (!SOUNDMANAGER->isPlaySound("bow_Charge") && !player.getIsBowChargeSound())
					SOUNDMANAGER->play("bow_Charge", 1.0f);
				player.setBowChargeAlpha(true);
				player.setIsBowChargeSound(true);

				if (KEYMANAGER->isStayKeyDown('J'))
				{
					if (player.getDirection() == DIRECTION::UP)
					{
						//憲だ高�膩� 頂晦嬪п
						if (player.getBowAlphaCount() <= 10)
						{
							player.setPlayerMotion(KEYANIMANAGER->findAnimation("bowUpChargeWhite"), ImageManager::GetInstance()->FindImage("bowUpChargeWhite"));
						}
						if (player.getBowAlphaCount() >= 11)
						{
							player.setPlayerMotion(KEYANIMANAGER->findAnimation("bowUpCharge"), ImageManager::GetInstance()->FindImage("bowUpCharge"));
						}

						//HP陛 0檜ж陛 腎賊 Die 鼻鷓煎 剩橫陛晦
						if (player.getDeadState() || player.getplayerCurrentHp() <= 0)
						{
							player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDie"), ImageManager::GetInstance()->FindImage("playerDie"));
							player.setCurrentState(player.getDieState());
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

						//HP陛 0檜ж陛 腎賊 Die 鼻鷓煎 剩橫陛晦
						if (player.getDeadState() || player.getplayerCurrentHp() <= 0)
						{
							player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDie"), ImageManager::GetInstance()->FindImage("playerDie"));
							player.setCurrentState(player.getDieState());
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

						//HP陛 0檜ж陛 腎賊 Die 鼻鷓煎 剩橫陛晦
						if (player.getDeadState() || player.getplayerCurrentHp() <= 0)
						{
							player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDie"), ImageManager::GetInstance()->FindImage("playerDie"));
							player.setCurrentState(player.getDieState());
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

						//HP陛 0檜ж陛 腎賊 Die 鼻鷓煎 剩橫陛晦
						if (player.getDeadState() || player.getplayerCurrentHp() <= 0)
						{
							player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDie"), ImageManager::GetInstance()->FindImage("playerDie"));
							player.setCurrentState(player.getDieState());
						}
					}
					player.setBedCount(player.getBedCount() == 0);
				}
			}

			if (KEYMANAGER->isOnceKeyUp('J'))
			{
				SOUNDMANAGER->play("bow", 1.0f);
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
				player.setIsBowChargeSound(false);
			}
		}
	}

	//匐
	//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天
	if (!player.getWeaponChange())
	{
		if (!player.getAttackProhibition())
		{
			if (KEYMANAGER->isOnceKeyDown('J'))
			{
				SOUNDMANAGER->play("Sword", 1.0f);
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
	}
	//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天
}

//roll(掘腦晦) 鼻鷓
void playerRollState::update(player & player)
{
	player.setPlayerRc(player.getX(), player.getY(), player.getPlayerRcW(), player.getPlayerRcH());
	//嬪煎 掘腦晦 
	if (player.getDirection() == DIRECTION::UP)
	{
		player.setShadowY(player.getShadowY() - 7);
	}
	//嬴楚煎 掘腦晦
	if (player.getDirection() == DIRECTION::DOWN)
	{
		player.setShadowY(player.getShadowY() + 7);
	}
	//豭薹戲煎 掘腦晦
	if (player.getDirection() == DIRECTION::LEFT)
	{
		player.setShadowX(player.getShadowX() - 7);
	}
	//螃艇薹戲煎 掘腦晦
	if (player.getDirection() == DIRECTION::RIGHT)
	{
		player.setShadowX(player.getShadowX() + 7);
	}

	//螃艇薹嬪 掘腦晦
	if (player.getDirection() == DIRECTION::RIGHTTOP)
	{
		player.setShadowY(player.getShadowY() - 7);
		player.setShadowX(player.getShadowX() + 5);
	}

	//豭薹嬪 掘腦晦
	if (player.getDirection() == DIRECTION::LEFTTOP)
	{
		player.setShadowY(player.getShadowY() - 7);
		player.setShadowX(player.getShadowX() - 5);
	}

	//豭薹嬴楚 掘腦晦
	if (player.getDirection() == DIRECTION::LEFTBOTTOM)
	{
		player.setShadowY(player.getShadowY() + 7);
		player.setShadowX(player.getShadowX() - 5);
	}

	//螃艇薹嬴楚 掘腦晦
	if (player.getDirection() == DIRECTION::RIGHTBOTTOM)
	{
		player.setShadowY(player.getShadowY() + 7);
		player.setShadowX(player.getShadowX() + 5);
	}

	//擁棲詭檜暮 營儅檜 部釭賊 
	if (!KEYANIMANAGER->findAnimation("playerUpRoll")->isPlay()
		&& !KEYANIMANAGER->findAnimation("playerDownRoll")->isPlay()
		&& !KEYANIMANAGER->findAnimation("playerLeftRoll")->isPlay()
		&& !KEYANIMANAGER->findAnimation("playerRightRoll")->isPlay())
	{
		player.setPlayerRc(player.getX(), player.getY(), player.getPlayerRcW(), player.getPlayerRcH());
		//嬪薹酈蒂 援腦賊 棻衛 檜翕ж啪
		if (GetAsyncKeyState('W') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpWalk"), ImageManager::GetInstance()->FindImage("playerUpWalk"));
			player.setCurrentState(player.getWalkState());
		}
		//嬴楚酈蒂 援腦賊 棻衛 檜翕ж啪
		else if (GetAsyncKeyState('S') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
			player.setCurrentState(player.getWalkState());
		}
		//螃艇薹酈蒂 援腦賊 棻衛 檜翕ж啪
		else if (GetAsyncKeyState('D') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightWalk"), ImageManager::GetInstance()->FindImage("playerRightWalk"));
			player.setCurrentState(player.getWalkState());
		}
		//豭薹酈蒂 援腦賊 棻衛 檜翕ж啪
		else if (GetAsyncKeyState('A') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftWalk"), ImageManager::GetInstance()->FindImage("playerLeftWalk"));
			player.setCurrentState(player.getWalkState());
		}
		//嬴鼠酈紫 援腦雖 彊堅氈戲賊 Idle 鼻鷓煎 瞪��
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

//die 鼻鷓
void playerDieState::update(player & player)
{
	player.setPlayerRc(player.getX(), player.getY(), player.getPlayerRcW(), player.getPlayerRcH());

	SOUNDMANAGER->stop("識憲踐晦");
	SOUNDMANAGER->stop("識憲濰瞪");
	SOUNDMANAGER->stop("識憲攪颶");
	SOUNDMANAGER->stop("識憲橫臢");
	SOUNDMANAGER->stop("溯萄蝸塭歜奢問");
	SOUNDMANAGER->stop("蝸塭歜み");
	SOUNDMANAGER->stop("埤源奢問");
	SOUNDMANAGER->stop("莊橫渡梯");
	SOUNDMANAGER->stop("給雲橫颶");
	SOUNDMANAGER->stop("給雲橫颶2");
	SOUNDMANAGER->stop("槳雲橫颶");
	SOUNDMANAGER->stop("槳�臍�");
	SOUNDMANAGER->stop("ァ嫦");
	SOUNDMANAGER->stop("給餌塭颶");

	if (!KEYANIMANAGER->findAnimation("playerDie")->isPlay())
	{
		dieCount++;

		if (!CAMERAMANAGER->getIsFadeStart())
		{
			CAMERAMANAGER->fadeInOut(FADETYPE::FADEIN);
		}

		if (dieCount >= 300)
		{
			player.setPlayerPos(WINSIZEX + 1000, WINSIZEY / 2 + 200);
			SCENEMANAGER->changeScene("葆擊壁");
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerTeleportOut"), ImageManager::GetInstance()->FindImage("playerTeleportOut"));
			player.setCurrentState(player.getTeleportOutState());
			dieCount = 0;
		}
	}

	//if (player.getplayerCurrentHp() > 0)
	//{
	//	player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownIdle"), ImageManager::GetInstance()->FindImage("playerDownIdle"));
	//	player.setCurrentState(player.getIdleState());
	//}
}

//shield 鼻鷓
void playerShieldState::update(player & player)
{
	//HP陛 0檜ж陛 腎賊 Die 鼻鷓煎 剩橫陛晦
	if (player.getplayerCurrentHp() <= 0)
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDie"), ImageManager::GetInstance()->FindImage("playerDie"));
		player.setCurrentState(player.getDieState());
	}

	player.setPlayerRc(player.getX(), player.getY(), player.getPlayerRcW(), player.getPlayerRcH());
	//Ы溯檜橫 蔓萄
	if (KEYMANAGER->isStayKeyDown('K'));
	{
		if (player.getDirection() == DIRECTION::RIGHT)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightShield"), ImageManager::GetInstance()->FindImage("playerRightShield"));
			if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
			{
				SOUNDMANAGER->play("roll", 1.0f);
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
				SOUNDMANAGER->play("roll", 1.0f);
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
				SOUNDMANAGER->play("roll", 1.0f);
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
				SOUNDMANAGER->play("roll", 1.0f);
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

	//蔓萄酈 飲賊
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
		//螃艇薹酈蒂 援腦賊 棻衛 檜翕ж啪
		else if (GetAsyncKeyState('D') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightWalk"), ImageManager::GetInstance()->FindImage("playerRightWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::RIGHT);
		}
		//豭薹酈蒂 援腦賊 棻衛 檜翕ж啪
		else if (GetAsyncKeyState('A') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftWalk"), ImageManager::GetInstance()->FindImage("playerLeftWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::LEFT);
		}
		//嬪薹酈蒂 援腦賊 棻衛 檜翕ж啪
		else if (GetAsyncKeyState('W') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpWalk"), ImageManager::GetInstance()->FindImage("playerUpWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::UP);
		}
		//嬴楚酈蒂 援腦賊 棻衛 檜翕ж啪
		else if (GetAsyncKeyState('S') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::DOWN);
		}
	}
}

//idleSwim 鼻鷓
void playerIdleSwimState::update(player & player)
{
	player.setPlayerRc(player.getX(), player.getY(), player.getPlayerRcW(), player.getPlayerRcH());
	if (!player.getTransform())
	{
		player.setCurrentState(player.getIdleState());
	}
	//嬪
	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpSwim"), ImageManager::GetInstance()->FindImage("playerUpSwim"));
		player.setCurrentState(player.getSwimState());
		player.setDirection(DIRECTION::UP);
	}

	//嬴楚
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownSwim"), ImageManager::GetInstance()->FindImage("playerDownSwim"));
		player.setCurrentState(player.getSwimState());
		player.setDirection(DIRECTION::DOWN);
	}

	//豭薹
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftSwim"), ImageManager::GetInstance()->FindImage("playerLeftSwim"));
		player.setCurrentState(player.getSwimState());
		player.setDirection(DIRECTION::LEFT);
	}

	//螃艇薹
	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightSwim"), ImageManager::GetInstance()->FindImage("playerRightSwim"));
		player.setCurrentState(player.getSwimState());
		player.setDirection(DIRECTION::RIGHT);
	}
}


//swim 鼻鷓
void playerSwimState::update(player & player)
{
	player.setPlayerRc(player.getX(), player.getY(), player.getPlayerRcW(), player.getPlayerRcH());

	if (!player.getTransform())
	{
		player.setCurrentState(player.getIdleState());
	}
	//嬪
	if (player.getDirection() == DIRECTION::UP)
	{
		if (KEYMANAGER->isStayKeyDown('W'))
		{
			//虜擒 嬴楚薹酈 援腦賊 嬪薹 idleSwim 賅蝗戲煎 滲л
			if (KEYMANAGER->isOnceKeyDown('S'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpIdleSwim"), ImageManager::GetInstance()->FindImage("playerUpIdleSwim"));
			}
			//嬪薹 idleSwim 賅蝗戲煎 誇蹺晦
			else if (KEYMANAGER->isStayKeyDown('S'))
			{
				player.setShadowY(player.getShadowY() - 0);
				player.setY(player.getY() - 0);
				return;
			}
			//酈 飲賊 棻衛 檜翕
			else if (KEYMANAGER->isOnceKeyUp('S'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpSwim"), ImageManager::GetInstance()->FindImage("playerUpSwim"));
				player.setCurrentState(player.getSwimState());
			}
			player.setShadowY(player.getShadowY() - 3);
			player.setY(player.getY() - 3);
		}
	}

	//嬪薹酈 飲賊
	if (KEYMANAGER->isOnceKeyUp('W'))
	{
		//嬴鼠酈紫 寰援腦賊 Idle 鼻鷓煎 瞪��
		if (KEYMANAGER->getKeyUp() == NULL)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpIdleSwim"), ImageManager::GetInstance()->FindImage("playerUpIdleSwim"));
			player.setCurrentState(player.getIdleSwimState());
		}
		//嬴楚酈蒂 援腦賊 棻衛 檜翕
		else if (GetAsyncKeyState('S') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownSwim"), ImageManager::GetInstance()->FindImage("playerDownSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirection(DIRECTION::DOWN);
		}
		//豭薹酈蒂 援腦賊 棻衛 檜翕
		else if (GetAsyncKeyState('A') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftSwim"), ImageManager::GetInstance()->FindImage("playerLeftSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirection(DIRECTION::LEFT);
		}
		//螃艇薹酈蒂 援腦賊 棻衛 檜翕
		else if (GetAsyncKeyState('D') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightSwim"), ImageManager::GetInstance()->FindImage("playerRightSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirection(DIRECTION::RIGHT);
		}
		player.setBedCount(player.getBedCount() == 0);
	}

	//嬴楚
	if (player.getDirection() == DIRECTION::DOWN)
	{
		if (KEYMANAGER->isStayKeyDown('S'))
		{
			//虜擒 嬪薹酈 援腦賊 嬴楚 idleSwim 賅蝗戲煎 滲л
			if (KEYMANAGER->isOnceKeyDown('W'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownIdleSwim"), ImageManager::GetInstance()->FindImage("playerDownIdleSwim"));
			}
			//嬴楚 idleSwim 賅蝗戲煎 誇蹺晦
			else if (KEYMANAGER->isStayKeyDown('W'))
			{
				player.setShadowY(player.getShadowY() + 0);
				player.setY(player.getY() + 0);
				return;
			}
			//酈 飲賊 棻衛 檜翕
			else if (KEYMANAGER->isOnceKeyUp('W'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownSwim"), ImageManager::GetInstance()->FindImage("playerDownSwim"));
				player.setCurrentState(player.getSwimState());
			}
			player.setShadowY(player.getShadowY() + 3);
			player.setY(player.getY() + 3);
		}
	}

	//嬴楚薹酈 飲賊
	if (KEYMANAGER->isOnceKeyUp('S'))
	{
		//嬴鼠酈紫 寰援腦賊 Idle 鼻鷓煎 瞪��
		if (KEYMANAGER->getKeyUp() == NULL)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownIdleSwim"), ImageManager::GetInstance()->FindImage("playerDownIdleSwim"));
			player.setCurrentState(player.getIdleSwimState());
		}
		//嬪薹酈蒂 援腦賊 棻衛 檜翕
		else if (GetAsyncKeyState('W') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpSwim"), ImageManager::GetInstance()->FindImage("playerUpSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirection(DIRECTION::UP);
		}
		//豭薹酈蒂 援腦賊 棻衛 檜翕
		else if (GetAsyncKeyState('A') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftSwim"), ImageManager::GetInstance()->FindImage("playerLeftSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirection(DIRECTION::LEFT);
		}
		//螃艇薹酈蒂 援腦賊 棻衛 檜翕
		else if (GetAsyncKeyState('D') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightSwim"), ImageManager::GetInstance()->FindImage("playerRightSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirection(DIRECTION::RIGHT);
		}
		player.setBedCount(player.getBedCount() == 0);
	}

	//豭薹
	if (player.getDirection() == DIRECTION::LEFT)
	{
		if (KEYMANAGER->isStayKeyDown('A'))
		{
			//虜擒 螃艇薹酈 援腦賊 豭薹 idleSwim 賅蝗戲煎 滲л
			if (KEYMANAGER->isOnceKeyDown('D'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftIdleSwim"), ImageManager::GetInstance()->FindImage("playerLeftIdleSwim"));
			}
			//豭薹 idleSwim 賅蝗戲煎 誇蹺晦
			else if (KEYMANAGER->isStayKeyDown('D'))
			{
				player.setShadowX(player.getShadowX() - 0);
				player.setX(player.getX() - 0);
				return;
			}
			//酈 飲賊 棻衛 檜翕
			else if (KEYMANAGER->isOnceKeyUp('D'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftSwim"), ImageManager::GetInstance()->FindImage("playerLeftSwim"));
				player.setCurrentState(player.getSwimState());
			}
			player.setShadowX(player.getShadowX() - 3);
			player.setX(player.getX() - 3);
		}
	}

	//豭薹酈 飲賊
	if (KEYMANAGER->isOnceKeyUp('A'))
	{
		//嬴鼠酈紫 寰援腦賊 Idle 鼻鷓煎 瞪��
		if (KEYMANAGER->getKeyUp() == NULL)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftIdleSwim"), ImageManager::GetInstance()->FindImage("playerLeftIdleSwim"));
			player.setCurrentState(player.getIdleSwimState());
		}
		//螃艇薹酈蒂 援腦賊 棻衛 檜翕
		else if (GetAsyncKeyState('D') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightSwim"), ImageManager::GetInstance()->FindImage("playerRightSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirection(DIRECTION::RIGHT);
		}
		//嬪薹酈蒂 援腦賊 棻衛 檜翕
		else if (GetAsyncKeyState('W') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpSwim"), ImageManager::GetInstance()->FindImage("playerUpSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirection(DIRECTION::UP);
		}
		//嬴楚酈蒂 援腦賊 棻衛 檜翕
		else if (GetAsyncKeyState('S') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownSwim"), ImageManager::GetInstance()->FindImage("playerDownSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirection(DIRECTION::DOWN);
		}
		player.setBedCount(player.getBedCount() == 0);
	}

	//螃艇薹
	if (player.getDirection() == DIRECTION::RIGHT)
	{
		if (KEYMANAGER->isStayKeyDown('D'))
		{
			//虜擒 豭薹酈 援腦賊 螃艇薹 idleSwim 賅蝗戲煎 滲л
			if (KEYMANAGER->isOnceKeyDown('A'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightIdleSwim"), ImageManager::GetInstance()->FindImage("playerRightIdleSwim"));
			}
			//螃艇薹 idleSwim 賅蝗戲煎 誇蹺晦
			else if (KEYMANAGER->isStayKeyDown('A'))
			{
				player.setShadowX(player.getShadowX() + 0);
				player.setX(player.getX() + 0);
				return;
			}
			//酈 飲賊 棻衛 檜翕
			else if (KEYMANAGER->isOnceKeyUp('A'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightSwim"), ImageManager::GetInstance()->FindImage("playerRightSwim"));
				player.setCurrentState(player.getSwimState());
			}
			player.setShadowX(player.getShadowX() + 3);
			player.setX(player.getX() + 3);
		}
	}

	//螃艇薹酈 飲賊
	if (KEYMANAGER->isOnceKeyUp('D'))
	{
		//嬴鼠酈紫 寰援腦賊 Idle 鼻鷓煎 瞪��
		if (KEYMANAGER->getKeyUp() == NULL)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightIdleSwim"), ImageManager::GetInstance()->FindImage("playerRightIdleSwim"));
			player.setCurrentState(player.getIdleSwimState());
		}
		//豭薹酈蒂 援腦賊 棻衛 檜翕
		else if (GetAsyncKeyState('A') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftSwim"), ImageManager::GetInstance()->FindImage("playerLeftSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirection(DIRECTION::LEFT);
		}
		//嬪薹酈蒂 援腦賊 棻衛 檜翕
		else if (GetAsyncKeyState('W') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpSwim"), ImageManager::GetInstance()->FindImage("playerUpSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirection(DIRECTION::UP);
		}
		//嬴楚酈蒂 援腦賊 棻衛 檜翕
		else if (GetAsyncKeyState('S') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownSwim"), ImageManager::GetInstance()->FindImage("playerDownSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirection(DIRECTION::DOWN);
		}
		player.setBedCount(player.getBedCount() == 0);
	}
}

//bow 鼻鷓
void playerbowState::update(player & player)
{
	//HP陛 0檜ж陛 腎賊 Die 鼻鷓煎 剩橫陛晦
	if (player.getplayerCurrentHp() <= 0)
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDie"), ImageManager::GetInstance()->FindImage("playerDie"));
		player.setCurrentState(player.getDieState());
	}

	player.setPlayerRc(player.getX(), player.getY(), player.getPlayerRcW(), player.getPlayerRcH());
	//虜擒 擁棲詭檜暮 營儅 部釭賊
	if (!KEYANIMANAGER->findAnimation("playerUpBow")->isPlay() && !KEYANIMANAGER->findAnimation("playerDownBow")->isPlay()
		&& !KEYANIMANAGER->findAnimation("playerLeftBow")->isPlay() && !KEYANIMANAGER->findAnimation("playerRightBow")->isPlay())
	{
		//嬴鼠酈紫 援腦雖彊戲賊 嬴檜菟 鼻鷓煎 瞪��
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

		//螃艇薹酈蒂 援腦賊 棻衛 檜翕ж啪
		else if (GetAsyncKeyState('D') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightWalk"), ImageManager::GetInstance()->FindImage("playerRightWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::RIGHT);
		}
		//豭薹酈蒂 援腦賊 棻衛 檜翕ж啪
		else if (GetAsyncKeyState('A') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftWalk"), ImageManager::GetInstance()->FindImage("playerLeftWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::LEFT);
		}
		//嬪薹酈蒂 援腦賊 棻衛 檜翕ж啪
		else if (GetAsyncKeyState('W') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpWalk"), ImageManager::GetInstance()->FindImage("playerUpWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::UP);
		}
		//嬴楚酈蒂 援腦賊 棻衛 檜翕ж啪
		else if (GetAsyncKeyState('S') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::DOWN);
		}
	}
}

//sword 鼻鷓
void playerSwordState::update(player & player)
{
	//HP陛 0檜ж陛 腎賊 Die 鼻鷓煎 剩橫陛晦
	if (player.getplayerCurrentHp() <= 0)
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDie"), ImageManager::GetInstance()->FindImage("playerDie"));
		player.setCurrentState(player.getDieState());
	}

	player.setPlayerRc(player.getX(), player.getY(), player.getPlayerRcW(), player.getPlayerRcH());
	//1顫 奢問
	if (!player.getSwordAttackCombo())
	{
		if (KEYMANAGER->isOnceKeyDown('J'))
		{
			SOUNDMANAGER->play("Sword", 1.0f);
			player.setSwrodAttackCombo(true);
		}
	}

	//奢問醞
	if (player.getSwordAttack())
	{
		if (player.getPlayerMotion() == KEYANIMANAGER->findAnimation("playerUpSword1")
			|| player.getPlayerMotion() == KEYANIMANAGER->findAnimation("playerDownSword1")
			|| player.getPlayerMotion() == KEYANIMANAGER->findAnimation("playerLeftSword1")
			|| player.getPlayerMotion() == KEYANIMANAGER->findAnimation("playerRightSword1"))
		{
			//擁棲詭檜暮 營儅 部釭賊
			if (!KEYANIMANAGER->findAnimation("playerUpSword1")->isPlay() && !KEYANIMANAGER->findAnimation("playerDownSword1")->isPlay()
				&& !KEYANIMANAGER->findAnimation("playerLeftSword1")->isPlay() && !KEYANIMANAGER->findAnimation("playerRightSword1")->isPlay())
			{
				player.setAttackRcbool(false);
				player.setAttackRc(player.getX(), player.getY(), 0, 0);
				//酈援腦賊 2顫煎 剩橫馬
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

	//虜擒 擁棲詭檜暮 營儅 部釭賊
	if (!KEYANIMANAGER->findAnimation("playerUpSword1")->isPlay() && !KEYANIMANAGER->findAnimation("playerDownSword1")->isPlay()
		&& !KEYANIMANAGER->findAnimation("playerLeftSword1")->isPlay() && !KEYANIMANAGER->findAnimation("playerRightSword1")->isPlay()
		&& !KEYANIMANAGER->findAnimation("playerUpSword2")->isPlay() && !KEYANIMANAGER->findAnimation("playerDownSword2")->isPlay()
		&& !KEYANIMANAGER->findAnimation("playerLeftSword2")->isPlay() && !KEYANIMANAGER->findAnimation("playerRightSword2")->isPlay())
	{
		player.setSwrodAttackCombo(false);
		player.setAttackRcbool(false);
		player.setAttackRc(player.getX(), player.getY(), 0, 0);

		//嬴鼠酈紫 援腦雖彊戲賊 嬴檜菟 鼻鷓煎 瞪��
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

		//螃艇薹酈蒂 援腦賊 棻衛 檜翕ж啪
		else if (GetAsyncKeyState('D') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightWalk"), ImageManager::GetInstance()->FindImage("playerRightWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::RIGHT);
		}
		//豭薹酈蒂 援腦賊 棻衛 檜翕ж啪
		else if (GetAsyncKeyState('A') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftWalk"), ImageManager::GetInstance()->FindImage("playerLeftWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::LEFT);
		}
		//嬪薹酈蒂 援腦賊 棻衛 檜翕ж啪
		else if (GetAsyncKeyState('W') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpWalk"), ImageManager::GetInstance()->FindImage("playerUpWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::UP);
		}
		//嬴楚酈蒂 援腦賊 棻衛 檜翕ж啪
		else if (GetAsyncKeyState('S') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirection(DIRECTION::DOWN);
		}
	}
}

//綿濠瑞韓 
void playerBroomState::update(player & player)
{
	player.setPlayerRc(player.getX(), player.getY(), player.getPlayerRcW(), player.getPlayerRcH());

	//HP陛 0檜ж陛 腎賊 Die 鼻鷓煎 剩橫陛晦
	if (player.getplayerCurrentHp() <= 0)
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDie"), ImageManager::GetInstance()->FindImage("playerDie"));
		player.setCurrentState(player.getDieState());
	}

	//嬪
	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerUpWalk"), ImageManager::GetInstance()->FindImage("playerUpWalk"));
		player.setCurrentState(player.getWalkState());
	}
	//嬴楚 
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
		player.setCurrentState(player.getWalkState());
	}
	//豭薹 
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftWalk"), ImageManager::GetInstance()->FindImage("playerLeftWalk"));
		player.setCurrentState(player.getWalkState());
	}
	//螃艇薹 
	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightWalk"), ImageManager::GetInstance()->FindImage("playerRightWalk"));
		player.setCurrentState(player.getWalkState());
	}
}

//藹渠 鼻鷓
void playerBedState::update(player & player)
{
	if(!SOUNDMANAGER->isPlaySound("bed"))
	SOUNDMANAGER->play("bed", 1.0f);
	player.setPlayerRc(player.getX(), player.getY(), player.getPlayerRcW(), player.getPlayerRcH());
	//擁棲詭檜暮檜 部釭堅 霞ч
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

//蘿溯んお 鼻鷓
void playerTeleportState::update(player & player)
{
	player.setPlayerRc(player.getX(), player.getY(), player.getPlayerRcW(), player.getPlayerRcH());
	//擁棲詭檜暮 部釭堅 霞ч
	if (!KEYANIMANAGER->findAnimation("playerTeleport")->isPlay())
	{
		player.setPlayerPos(WINSIZEX + 1000, WINSIZEY / 2 + 200);
		SCENEMANAGER->changeScene("葆擊壁");
		player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerTeleportOut"), ImageManager::GetInstance()->FindImage("playerTeleportOut"));
		player.setCurrentState(player.getTeleportOutState());

	}
}

//蘿溯んお(湍瞪) 菟橫陛晦 鼻鷓
void playerTeleportInState::update(player & player)
{
	player.setPlayerRc(player.getX(), player.getY(), player.getPlayerRcW(), player.getPlayerRcH());
	//player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerTeleportIn"), ImageManager::GetInstance()->FindImage("playerTeleportIn"));


	//擁棲詭檜暮 部釭堅 霞ч
	if (!KEYANIMANAGER->findAnimation("playerTeleportIn")->isPlay())
	{
		player.setPlayerPos(800, 770);
		SCENEMANAGER->changeScene("湍瞪殮掘壁");
		player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownIdle"), ImageManager::GetInstance()->FindImage("playerDownIdle"));
		player.setCurrentState(player.getIdleState());
	}
}

//蘿溯んお(驍轎) 鼻鷓
void playerTeleportOutState::update(player & player)
{
	player.setPlayerRc(player.getX(), player.getY(), player.getPlayerRcW(), player.getPlayerRcH());
	//擁棲詭檜暮 部釭堅 霞ч

	if (!KEYANIMANAGER->findAnimation("playerTeleportOut")->isPlay())
	{
		player.setPlayerCurrentHp(150);
		player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownIdle"), ImageManager::GetInstance()->FindImage("playerDownIdle"));
		player.setCurrentState(player.getIdleState());
	}
}

//Ы溯檜橫 溯萄蝸塭歜и纔 濩�欞鬌�
void playerTrapState::update(player & player)
{
	player.setPlayerMotion(KEYANIMANAGER->findAnimation("playerDownIdle"), ImageManager::GetInstance()->FindImage("playerDownIdle"));

	if (!player.getPlayerMoveTrap())
	{
		player.setCurrentState(player.getWalkState());
	}
}
