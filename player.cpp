#include "stdafx.h"
#include "player.h"
#include "enemyManager.h"
#include "townStage.h"
#include "shopStage.h"

HRESULT player::init(float x, float y)
{
	animationLoad();

	_idle = new playerIdleState();
	_walk = new playerWalkState();
	_roll = new playerRollState();
	_die = new playerDieState();
	_shield = new playerShieldState();
	_idleSwim = new playerIdleSwimState();
	_swim = new playerSwimState();
	_bow = new playerbowState();
	_sword = new playerSwordState();
	_broom = new playerBroomState();
	_bed = new playerBedState();
	_trap = new playerTrapState();
	_teleport = new playerTeleportState();
	_teleportIn = new playerTeleportInState();
	_teleportOut = new playerTeleportOutState();
	_arrow = new arrow;
	_arrow->init();
	_townStage = new townStage;
	_townStage->init();
	_shopStage = new shopStage;
	_shopStage->init();

	_index = 0;
	_playerShadowX = x;
	_playerShadowY = y;
	_playerX = _playerShadowX;
	_playerY = _playerShadowY - 50;
	_playerRcW = _playerRcH = 50;
	_playerAttackX = _playerAttackY = _playerAttackW = _playerAttackH = 0;
	_playerCurrentHp = _playerMaxHp = 150;
	_SwordDamage = 30;
	_hitAlpha = 0;
	_playerMoveTrap = false;
	_colVoid = true;
	_enemyCol = false;
	_bowChargeState = false;
	_hitCondition = false;
	_deadState = false;
	_AttackProhibition = false;

	_playerShadowRc = RectMakePivot(Vector2(_playerShadowX, _playerShadowY), Vector2(50, 20), Pivot::Center);
	_playerRc = RectMakePivot(Vector2(_playerX, _playerY), Vector2(_playerRcW, _playerRcH), Pivot::Center);
	_playerAttackRc = RectMakePivot(Vector2(_playerAttackX, _playerAttackY), Vector2(_playerAttackW, _playerAttackH), Pivot::Center);

	_CurrentState = _idle;

	_playerShadowImg = ImageManager::GetInstance()->FindImage("playerShadow");
	_playerImg = ImageManager::GetInstance()->FindImage("playerBed");
	_playerMotion = KEYANIMANAGER->findAnimation("playerBed");
	_playerMotion->start();

	return S_OK;
}

void player::render()
{
	//CAMERAMANAGER->fillRectangle(_playerRc, D2D1::ColorF::Black, 1.f);
	//플레이어 히트 상태일 경우 알파값줌
	CAMERAMANAGER->zOrderRender(_playerShadowImg, _playerShadowX - 35, _playerShadowRc.bottom - 30, _playerShadowY - 100, 0.3f, 1.0f);
	if (_hitCondition)
	{
		CAMERAMANAGER->zOrderAniAlphaRender(_playerImg, _playerX, _playerY, _playerShadowY, _playerMotion, 1.3f, _hitAlpha);
	}
	else if (_playerMotion == KEYANIMANAGER->findAnimation("playerBroom")
		|| _playerMotion == KEYANIMANAGER->findAnimation("playerBed")
		|| _playerMotion == KEYANIMANAGER->findAnimation("playerTeleportIn")
		|| _playerMotion == KEYANIMANAGER->findAnimation("playerTeleportOut"))
	{
		//CAMERAMANAGER->render(_playerShadowImg, _playerShadowX - 35, _playerShadowY - 50, 0.3f);
		//CAMERAMANAGER->aniRender(_playerImg, _playerX, _playerY, _playerMotion, 2.63f);
		CAMERAMANAGER->zOrderAniRender(_playerImg, _playerX, _playerY, _playerShadowRc.bottom, _playerMotion, 2.63f);
	}
	else
	{
		//CAMERAMANAGER->render(_playerShadowImg, _playerShadowX - 35, _playerShadowY - 50, 0.3f);
		//CAMERAMANAGER->aniRender(_playerImg, _playerX, _playerY, _playerMotion, 1.3f);
		//D2DRenderer::GetInstance()->FillRectangle(_playerRc , D2D1::ColorF::Tomato, 1.0f);
		CAMERAMANAGER->zOrderAniRender(_playerImg, _playerX, _playerY, _playerShadowRc.bottom, _playerMotion, 1.3f);
	}
	_arrow->render();

	if (KEYMANAGER->isToggleKey('V'))
	{
		CAMERAMANAGER->rectangle(_playerRc, D2D1::ColorF::Red, 1.0f);
		CAMERAMANAGER->fillRectangle(_playerRc, D2D1::ColorF::Red, 0.5f);
		CAMERAMANAGER->rectangle(_playerAttackRc, D2D1::ColorF::Blue, 1.0f);
		CAMERAMANAGER->rectangle(_playerShadowRc, D2D1::ColorF::Blue, 1.0f);
	}


}

void player::update()
{
	_CurrentState->update(*this);

	_arrow->update();
	arrowShoot();
	playerAlphaState();
	playerMoveTrapState();
	shopCollision();
	_playerShadowRc = RectMakePivot(Vector2(_playerShadowX, _playerShadowY), Vector2(50, 50), Pivot::Center);
	_playerX = _playerShadowX;
	_playerY = _playerShadowY;
	//arrowShoot();
	//_playerShadowRc = RectMakePivot(Vector2(_playerShadowX, _playerShadowY), Vector2(70, 20), Pivot::Center);

	//플레이어 HP가 0이하가 되면 Die 상태로 넘어감
	//if (_playerCurrentHp <= 0 && SCENEMANAGER->getCurrentScene() != "마을씬")
	//{
	//	_deadState = true;
	//}

	_playerRc = RectMakePivot(Vector2(_playerX, _playerY), Vector2(_playerRcW, _playerRcH), Pivot::Center);
	_playerAttackRc = RectMakePivot(Vector2(_playerAttackX, _playerAttackY), Vector2(_playerAttackW, _playerAttackH), Pivot::Center);
}

void player::release()
{
	SAFE_DELETE(_arrow);
}

void player::animationLoad()
{
	//플레이어 아이들상태
	_playerImg = ImageManager::GetInstance()->AddFrameImage("playerRightIdle", L"image/player/moveState.png", 10, 13);
	int playerRightIdle[] = { 80, 81, 82, 83, 84, 85, 86, 87, 88, 89 };
	KEYANIMANAGER->addArrayFrameAnimation("playerRightIdle", "playerRightIdle", playerRightIdle, 10, 13, true);

	_playerImg = ImageManager::GetInstance()->AddFrameImage("playerLeftIdle", L"image/player/moveState.png", 10, 13);
	int playerLeftIdle[] = { 90, 91, 92, 93, 94, 95, 96, 97, 98, 99 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftIdle", "playerLeftIdle", playerLeftIdle, 10, 13, true);

	_playerImg = ImageManager::GetInstance()->AddFrameImage("playerUpIdle", L"image/player/moveState.png", 10, 13);
	int playerUpIdle[] = { 100, 101, 102, 103, 104, 105, 106, 107, 108, 109 };
	KEYANIMANAGER->addArrayFrameAnimation("playerUpIdle", "playerUpIdle", playerUpIdle, 10, 13, true);

	_playerImg = ImageManager::GetInstance()->AddFrameImage("playerDownIdle", L"image/player/moveState.png", 10, 13);
	int playerDownIdle[] = { 110, 111, 112, 113, 114, 115, 116, 117, 118, 119 };
	KEYANIMANAGER->addArrayFrameAnimation("playerDownIdle", "playerDownIdle", playerDownIdle, 10, 13, true);

	//플레이어 죽음
	_playerImg = ImageManager::GetInstance()->AddFrameImage("playerDie", L"image/player/moveState.png", 10, 13);
	int playerDie[] = { 120, 121, 122, 123, 124, 125, 126, 127, 128, 129 };
	KEYANIMANAGER->addArrayFrameAnimation("playerDie", "playerDie", playerDie, 10, 13, false);

	//플레이어 이동
	_playerImg = ImageManager::GetInstance()->AddFrameImage("playerUpWalk", L"image/player/moveState.png", 10, 13);
	int playerUpWalk[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
	KEYANIMANAGER->addArrayFrameAnimation("playerUpWalk", "playerUpWalk", playerUpWalk, 8, 13, true);

	_playerImg = ImageManager::GetInstance()->AddFrameImage("playerDownWalk", L"image/player/moveState.png", 10, 13);
	int playerDownWalk[] = { 10, 11, 12, 13, 14, 15, 16, 17 };
	KEYANIMANAGER->addArrayFrameAnimation("playerDownWalk", "playerDownWalk", playerDownWalk, 8, 13, true);

	_playerImg = ImageManager::GetInstance()->AddFrameImage("playerRightWalk", L"image/player/moveState.png", 10, 13);
	int playerRightWalk[] = { 20, 21, 22, 23, 24, 25, 26, 27 };
	KEYANIMANAGER->addArrayFrameAnimation("playerRightWalk", "playerRightWalk", playerRightWalk, 8, 13, true);

	_playerImg = ImageManager::GetInstance()->AddFrameImage("playerLeftWalk", L"image/player/moveState.png", 10, 13);
	int playerLeftWalk[] = { 30, 31, 32, 33, 34, 35, 36, 37 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftWalk", "playerLeftWalk", playerLeftWalk, 8, 13, true);

	//플레이어 구르기
	_playerImg = ImageManager::GetInstance()->AddFrameImage("playerRightRoll", L"image/player/moveState.png", 10, 13);
	int playerRightRoll[] = { 40, 41, 42, 43, 44, 45, 46, 47 };
	KEYANIMANAGER->addArrayFrameAnimation("playerRightRoll", "playerRightRoll", playerRightRoll, 8, 13, false);

	_playerImg = ImageManager::GetInstance()->AddFrameImage("playerLeftRoll", L"image/player/moveState.png", 10, 13);
	int playerLeftRoll[] = { 50, 51, 52, 53, 54, 55, 56, 57 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftRoll", "playerLeftRoll", playerLeftRoll, 8, 13, false);

	_playerImg = ImageManager::GetInstance()->AddFrameImage("playerUpRoll", L"image/player/moveState.png", 10, 13);
	int playerUpRoll[] = { 60, 61, 62, 63, 64, 65, 66, 67 };
	KEYANIMANAGER->addArrayFrameAnimation("playerUpRoll", "playerUpRoll", playerUpRoll, 8, 13, false);

	_playerImg = ImageManager::GetInstance()->AddFrameImage("playerDownRoll", L"image/player/moveState.png", 10, 13);
	int playerDownRoll[] = { 70, 71, 72, 73, 74, 75, 76, 77 };
	KEYANIMANAGER->addArrayFrameAnimation("playerDownRoll", "playerDownRoll", playerDownRoll, 8, 13, false);

	//플레이어 활
	_playerImg = ImageManager::GetInstance()->AddFrameImage("playerUpBow", L"image/player/bowState.png", 9, 4);
	int playerUpBow[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
	KEYANIMANAGER->addArrayFrameAnimation("playerUpBow", "playerUpBow", playerUpBow, 9, 13, false);

	_playerImg = ImageManager::GetInstance()->AddFrameImage("playerDownBow", L"image/player/bowState.png", 9, 4);
	int playerDownBow[] = { 9, 10, 11, 12, 13, 14, 15, 16, 17 };
	KEYANIMANAGER->addArrayFrameAnimation("playerDownBow", "playerDownBow", playerDownBow, 9, 13, false);

	_playerImg = ImageManager::GetInstance()->AddFrameImage("playerRightBow", L"image/player/bowState.png", 9, 4);
	int playerRightBow[] = { 18, 19, 20, 21, 22, 23, 24, 25, 26 };
	KEYANIMANAGER->addArrayFrameAnimation("playerRightBow", "playerRightBow", playerRightBow, 9, 13, false);

	_playerImg = ImageManager::GetInstance()->AddFrameImage("playerLeftBow", L"image/player/bowState.png", 9, 4);
	int playerLeftBow[] = { 27, 28, 29, 30, 31, 32, 33, 34, 35 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftBow", "playerLeftBow", playerLeftBow, 9, 13, false);

	_playerImg = ImageManager::GetInstance()->AddFrameImage("playerArrow", L"image/player/arrow.png", 1, 1);
	int playerArrow[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("playerArrow", "playerArrow", playerArrow, 1, 0, false);

	_playerImg = ImageManager::GetInstance()->AddFrameImage("bowUpCharge", L"image/player/bowChargeState.png", 1, 4);
	int bowUpCharge[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("bowUpCharge", "bowUpCharge", bowUpCharge, 1, 0, false);

	_playerImg = ImageManager::GetInstance()->AddFrameImage("bowDownCharge", L"image/player/bowChargeState.png", 1, 4);
	int bowDownCharge[] = { 1 };
	KEYANIMANAGER->addArrayFrameAnimation("bowDownCharge", "bowDownCharge", bowDownCharge, 1, 0, false);

	_playerImg = ImageManager::GetInstance()->AddFrameImage("bowRightCharge", L"image/player/bowChargeState.png", 1, 4);
	int bowRightCharge[] = { 2 };
	KEYANIMANAGER->addArrayFrameAnimation("bowRightCharge", "bowRightCharge", bowRightCharge, 1, 0, false);

	_playerImg = ImageManager::GetInstance()->AddFrameImage("bowLeftCharge", L"image/player/bowChargeState.png", 1, 4);
	int bowLeftCharge[] = { 3 };
	KEYANIMANAGER->addArrayFrameAnimation("bowLeftCharge", "bowLeftCharge", bowLeftCharge, 1, 0, false);

	_playerImg = ImageManager::GetInstance()->AddFrameImage("bowUpChargeWhite", L"image/player/bowChargeStateAlpha.png", 1, 4);
	int bowUpChargeWhite[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("bowUpChargeWhite", "bowUpChargeWhite", bowUpChargeWhite, 1, 0, false);

	_playerImg = ImageManager::GetInstance()->AddFrameImage("bowDownChargeWhite", L"image/player/bowChargeStateAlpha.png", 1, 4);
	int bowDownChargeWhite[] = { 1 };
	KEYANIMANAGER->addArrayFrameAnimation("bowDownChargeWhite", "bowDownChargeWhite", bowDownChargeWhite, 1, 0, false);

	_playerImg = ImageManager::GetInstance()->AddFrameImage("bowRightChargeWhite", L"image/player/bowChargeStateAlpha.png", 1, 4);
	int bowRightChargeWhite[] = { 2 };
	KEYANIMANAGER->addArrayFrameAnimation("bowRightChargeWhite", "bowRightChargeWhite", bowRightChargeWhite, 1, 0, false);

	_playerImg = ImageManager::GetInstance()->AddFrameImage("bowLeftChargeWhite", L"image/player/bowChargeStateAlpha.png", 1, 4);
	int bowLeftChargeWhite[] = { 3 };
	KEYANIMANAGER->addArrayFrameAnimation("bowLeftChargeWhite", "bowLeftChargeWhite", bowLeftChargeWhite, 1, 0, false);

	//플레이어 검 콤보
	_playerImg = ImageManager::GetInstance()->AddFrameImage("playerUpSword1", L"image/player/swordState.png", 11, 4);
	int playerUpSword1[] = { 0, 1, 2, 3, 4, 5 };
	KEYANIMANAGER->addArrayFrameAnimation("playerUpSword1", "playerUpSword1", playerUpSword1, 6, 13, false);

	_playerImg = ImageManager::GetInstance()->AddFrameImage("playerUpSword2", L"image/player/swordState.png", 11, 4);
	int playerUpSword2[] = { 6, 7, 8, 9, 10 };
	KEYANIMANAGER->addArrayFrameAnimation("playerUpSword2", "playerUpSword2", playerUpSword2, 5, 13, false);

	_playerImg = ImageManager::GetInstance()->AddFrameImage("playerDownSword1", L"image/player/swordState.png", 11, 4);
	int playerDownSword1[] = { 11, 12, 13, 14, 15, 16 };
	KEYANIMANAGER->addArrayFrameAnimation("playerDownSword1", "playerDownSword1", playerDownSword1, 6, 13, false);

	_playerImg = ImageManager::GetInstance()->AddFrameImage("playerDownSword2", L"image/player/swordState.png", 11, 4);
	int playerDownSword2[] = { 17, 18, 19, 20, 21 };
	KEYANIMANAGER->addArrayFrameAnimation("playerDownSword2", "playerDownSword2", playerDownSword2, 5, 13, false);

	_playerImg = ImageManager::GetInstance()->AddFrameImage("playerRightSword1", L"image/player/swordState.png", 11, 4);
	int playerRightSword1[] = { 22, 23, 24, 25, 26, 27 };
	KEYANIMANAGER->addArrayFrameAnimation(+"playerRightSword1", "playerRightSword1", playerRightSword1, 6, 13, false);

	_playerImg = ImageManager::GetInstance()->AddFrameImage("playerRightSword2", L"image/player/swordState.png", 11, 4);
	int playerRightSword2[] = { 28, 29, 30, 31, 32 };
	KEYANIMANAGER->addArrayFrameAnimation("playerRightSword2", "playerRightSword2", playerRightSword2, 5, 13, false);

	_playerImg = ImageManager::GetInstance()->AddFrameImage("playerLeftSword1", L"image/player/swordState.png", 11, 4);
	int playerLeftSword1[] = { 33, 34, 35, 36, 37, 38 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftSword1", "playerLeftSword1", playerLeftSword1, 6, 13, false);

	_playerImg = ImageManager::GetInstance()->AddFrameImage("playerLeftSword2", L"image/player/swordState.png", 11, 4);
	int playerLeftSword2[] = { 39, 40, 41, 42, 43 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftSword2", "playerLeftSword2", playerLeftSword2, 5, 13, false);

	//플레이어 막기
	_playerImg = ImageManager::GetInstance()->AddFrameImage("playerRightShield", L"image/player/shieldState.png", 4, 1);
	int playerRightShield[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("playerRightShield", "playerRightShield", playerRightShield, 1, 13, false);

	_playerImg = ImageManager::GetInstance()->AddFrameImage("playerLeftShield", L"image/player/shieldState.png", 4, 1);
	int playerLeftShield[] = { 1 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftShield", "playerLeftShield", playerLeftShield, 1, 13, false);

	_playerImg = ImageManager::GetInstance()->AddFrameImage("playerUpShield", L"image/player/shieldState.png", 4, 1);
	int playerUpShield[] = { 2 };
	KEYANIMANAGER->addArrayFrameAnimation("playerUpShield", "playerUpShield", playerUpShield, 1, 13, false);

	_playerImg = ImageManager::GetInstance()->AddFrameImage("playerDownShield", L"image/player/shieldState.png", 4, 1);
	int playerDownShield[] = { 3 };
	KEYANIMANAGER->addArrayFrameAnimation("playerDownShield", "playerDownShield", playerDownShield, 1, 13, false);

	//플레이어 수영
	_playerImg = ImageManager::GetInstance()->AddFrameImage("playerDownIdleSwim", L"image/player/swimState.png", 10, 4);
	int playerDownIdleSwim[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("playerDownIdleSwim", "playerDownIdleSwim", playerDownIdleSwim, 1, 13, true);

	_playerImg = ImageManager::GetInstance()->AddFrameImage("playerLeftIdleSwim", L"image/player/swimState.png", 10, 4);
	int playerLeftIdleSwim[] = { 10 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftIdleSwim", "playerLeftIdleSwim", playerLeftIdleSwim, 1, 13, true);

	_playerImg = ImageManager::GetInstance()->AddFrameImage("playerRightIdleSwim", L"image/player/swimState.png", 10, 4);
	int playerRightIdleSwim[] = { 20 };
	KEYANIMANAGER->addArrayFrameAnimation("playerRightIdleSwim", "playerRightIdleSwim", playerRightIdleSwim, 1, 13, true);

	_playerImg = ImageManager::GetInstance()->AddFrameImage("playerUpIdleSwim", L"image/player/swimState.png", 10, 4);
	int playerUpIdleSwim[] = { 30 };
	KEYANIMANAGER->addArrayFrameAnimation("playerUpIdleSwim", "playerUpIdleSwim", playerUpIdleSwim, 1, 13, true);

	_playerImg = ImageManager::GetInstance()->AddFrameImage("playerDownSwim", L"image/player/swimState.png", 10, 4);
	int playerDownSwim[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	KEYANIMANAGER->addArrayFrameAnimation("playerDownSwim", "playerDownSwim", playerDownSwim, 9, 13, true);

	_playerImg = ImageManager::GetInstance()->AddFrameImage("playerLeftSwim", L"image/player/swimState.png", 10, 4);
	int playerLeftSwim[] = { 11, 12, 13, 14, 15, 16, 17, 18, 19 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftSwim", "playerLeftSwim", playerLeftSwim, 9, 13, true);

	_playerImg = ImageManager::GetInstance()->AddFrameImage("playerRightSwim", L"image/player/swimState.png", 10, 4);
	int playerRightSwim[] = { 21, 22, 23, 24, 25, 26, 27, 28, 29 };
	KEYANIMANAGER->addArrayFrameAnimation("playerRightSwim", "playerRightSwim", playerRightSwim, 9, 13, true);

	_playerImg = ImageManager::GetInstance()->AddFrameImage("playerUpSwim", L"image/player/swimState.png", 10, 4);
	int playerUpSwim[] = { 31, 32, 33, 34, 35, 36, 37, 38, 39 };
	KEYANIMANAGER->addArrayFrameAnimation("playerUpSwim", "playerUpSwim", playerUpSwim, 9, 13, true);

	//빗자루 개싹수;
	_playerImg = ImageManager::GetInstance()->AddFrameImage("playerBroom", L"image/player/droomState.png", 119, 1);
	int playerBroom[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
	31, 32, 33, 34, 35, 36, 37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,
	74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,
	114,115,116,117,118 };
	KEYANIMANAGER->addArrayFrameAnimation("playerBroom", "playerBroom", playerBroom, 119, 13, true);

	//침대 싹수
	_playerImg = ImageManager::GetInstance()->AddFrameImage("playerBed", L"image/player/bedState.png", 58, 1);
	int playerBed[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
	31, 32, 33, 34, 35, 36, 37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57 };
	KEYANIMANAGER->addArrayFrameAnimation("playerBed", "playerBed", playerBed, 58, 13, false);

	//텔레포트
	_playerImg = ImageManager::GetInstance()->AddFrameImage("playerTeleport", L"image/player/teleport.png", 26, 1);
	int playerTeleport[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25 };
	KEYANIMANAGER->addArrayFrameAnimation("playerTeleport", "playerTeleport", playerTeleport, 26, 13, false);

	_playerImg = ImageManager::GetInstance()->AddFrameImage("playerTeleportIn", L"image/player/teleportIn.png", 20, 1);
	int playerTeleportIn[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 };
	KEYANIMANAGER->addArrayFrameAnimation("playerTeleportIn", "playerTeleportIn", playerTeleportIn, 20, 13, false);

	_playerImg = ImageManager::GetInstance()->AddFrameImage("playerTeleportOut", L"image/player/teleportOut.png", 58, 1);
	int playerTeleportOut[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
	31, 32, 33, 34, 35, 36, 37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57 };
	KEYANIMANAGER->addArrayFrameAnimation("playerTeleportOut", "playerTeleportOut", playerTeleportOut, 58, 13, false);

	//그림자
	ImageManager::GetInstance()->AddImage("playerShadow", L"image/player/playerShadow.png");

	//이펙트
	ImageManager::GetInstance()->AddFrameImage("bowEffect", L"image/player/bowEffect.png", 3, 1);
	ImageManager::GetInstance()->AddFrameImage("swordEffect1", L"image/player/swordEffect1.png", 3, 1);
	ImageManager::GetInstance()->AddFrameImage("swordEffect2", L"image/player/swordEffect2.png", 3, 1);
	EFFECTMANAGER->addEffect("swordEffect1", "swordEffect1", 384, 128, 128, 42, 1.0f, 0.2f, 10.0f, 1.0f);
}

//활나가는 방향
void player::arrowShoot()
{
	if (_playerDirection == DIRECTION::UP)
	{
		//애니메이션 시작하면서 Count가 0이여야 한발씩 나감
		if (KEYANIMANAGER->findAnimation("playerUpBow")->isPlay() && _arrowCount == 0)
		{
			_arrowCount++;

			if (_bowChargeState)
			{
				_arrow->IsArrowShot(_playerX, _playerY, ARROWDIRECTION::UP, 80, true);
				_bowChargeState = false;
			}
			else
			{
				_arrow->IsArrowShot(_playerX, _playerY, ARROWDIRECTION::UP, 40, false);
			}
		}
	}
	if (_playerDirection == DIRECTION::DOWN)
	{
		if (KEYANIMANAGER->findAnimation("playerDownBow")->isPlay() && _arrowCount == 0)
		{
			_arrowCount++;
			if (_bowChargeState)
			{
				_arrow->IsArrowShot(_playerX, _playerY, ARROWDIRECTION::DOWN, 80, true);
				_bowChargeState = false;
			}
			else
			{
				_arrow->IsArrowShot(_playerX, _playerY, ARROWDIRECTION::DOWN, 40, false);
			}
		}
	}
	if (_playerDirection == DIRECTION::LEFT)
	{
		if (KEYANIMANAGER->findAnimation("playerLeftBow")->isPlay() && _arrowCount == 0)
		{
			_arrowCount++;
			if (_bowChargeState)
			{
				_arrow->IsArrowShot(_playerX, _playerY, ARROWDIRECTION::LEFT, 80, true);
				_bowChargeState = false;
			}
			else
			{
				_arrow->IsArrowShot(_playerX, _playerY, ARROWDIRECTION::LEFT, 40, false);
			}
		}
	}
	if (_playerDirection == DIRECTION::RIGHT)
	{
		if (KEYANIMANAGER->findAnimation("playerRightBow")->isPlay() && _arrowCount == 0)
		{
			_arrowCount++;
			if (_bowChargeState)
			{
				_arrow->IsArrowShot(_playerX, _playerY, ARROWDIRECTION::RIGHT, 80, true);
				_bowChargeState = false;
			}
			else
			{
				_arrow->IsArrowShot(_playerX, _playerY, ARROWDIRECTION::RIGHT, 40, false);
			}
		}
	}
	//애니메이션 끝나면 다시 카운트 초기화
	if (!KEYANIMANAGER->findAnimation("playerUpBow")->isPlay()
		&& !KEYANIMANAGER->findAnimation("playerDownBow")->isPlay()
		&& !KEYANIMANAGER->findAnimation("playerLeftBow")->isPlay()
		&& !KEYANIMANAGER->findAnimation("playerRightBow")->isPlay())
	{
		_arrowCount = 0;
	}
}

//피격시 알파 상태변경
void player::playerAlphaState()
{
	if (_enemyCol)
	{
		//플레이어 알파값 true
		_hitCondition = true;
		_hitAlphaCount++;
		cout << _hitAlphaCount << endl;
		if (_hitAlphaCount >= 10)
		{
			_hitCondition = false;
			_enemyCol = false;
			_hitAlphaCount = 0;
		}

		if (_hitCondition)
		{
			_hitAlpha = 0;
			_hitAlpha += 0.2f;
		}
		else
		{
			_hitAlpha = 1.0f;
		}
	}
}

//플레이어가 레드슬라임한테 잡힌상태
void player::playerMoveTrapState()
{
	if (_playerMoveTrap)
	{
		_CurrentState = _trap;

		if (KEYMANAGER->isOnceKeyDown('A') || KEYMANAGER->isOnceKeyDown('D'))
		{
			_escapeCount++;

			if (_escapeCount > 7)
			{
				_playerMoveTrap = false;
				_escapeCount = 0;
			}
		}
	}
}

//상점하고 충돌했을때, 공격불가
void player::shopCollision()
{
	if (SCENEMANAGER->getCurrentScene() == "마을씬")
	{
		RECT temp;
		if (IntersectRect(&temp, &_playerRc.GetRect(), &_townStage->getPotionShopRc().GetRect()))
		{
			_AttackProhibition = true;
		}
		else
		{
			_AttackProhibition = false;
		}
	}

	if (SCENEMANAGER->getCurrentScene() == "샵씬")
	{
		RECT temp;

		if (IntersectRect(&temp, &_playerRc.GetRect(), &_shopStage->getInteractionRC().GetRect()))
		{
			_AttackProhibition = true;
		}
		else
		{
			_AttackProhibition = false;
		}
	}
}

//타일 충돌용
void player::tileCollision(DWORD* attribute, tagTile* tile, int tileSizeX)
{
	RECT rcCollision;   //임의의 충돌판정용 렉트
	tileIndex[3];   //이동방향에 따라 타일속성 검출계산용(타일 인덱스가 몇 번인지)
	int tileX, tileY;   //실제 플레이어가 어디 타일에 있는지 좌표 계산용 (left, top)

	//임의 충돌판정용 렉트에 대입 먼저
	rcCollision.left = _playerShadowRc.left;
	rcCollision.right = _playerShadowRc.right;
	rcCollision.top = _playerShadowRc.top;
	rcCollision.bottom = _playerShadowRc.bottom;

	tileX = rcCollision.left / TILESIZE;
	tileY = rcCollision.top / TILESIZE;

	switch (_playerDirection)
	{
	case DIRECTION::LEFT:
		tileIndex[0] = tileX + tileY * tileSizeX;
		tileIndex[1] = tileX + (tileY + 1) * tileSizeX;
		break;
	case DIRECTION::UP:
		tileIndex[0] = tileX + tileY * tileSizeX;
		tileIndex[1] = (tileX + 1) + tileY * tileSizeX;
		break;
	case DIRECTION::RIGHT:
		tileIndex[0] = (tileX + tileY * tileSizeX) + 1;
		tileIndex[1] = (tileX + (tileY + 1) * tileSizeX) + 1;
		break;
	case DIRECTION::DOWN:
		tileIndex[0] = (tileX + tileY * tileSizeX) + tileSizeX;
		tileIndex[1] = (tileX + 1 + tileY * tileSizeX) + tileSizeX;
		break;
	case DIRECTION::LEFTTOP:
		tileIndex[0] = tileX + tileY * tileSizeX;
		tileIndex[1] = tileX + (tileY + 1) * tileSizeX;
		tileIndex[2] = (tileX + 1) + tileY * tileSizeX;
		break;
	case DIRECTION::RIGHTTOP:
		tileIndex[0] = (tileX + tileY * tileSizeX) + 1;
		tileIndex[1] = (tileX + (tileY + 1) * tileSizeX) + 1;
		tileIndex[2] = tileX + tileY * tileSizeX;
		break;
	case DIRECTION::LEFTBOTTOM:
		tileIndex[0] = (tileX + tileY * tileSizeX) + tileSizeX;
		tileIndex[1] = (tileX + 1 + tileY * tileSizeX) + tileSizeX;
		tileIndex[2] = (tileX + (tileY - 1) * tileSizeX) + tileSizeX;
		break;
	case DIRECTION::RIGHTBOTTOM:
		tileIndex[0] = (tileX + tileY * tileSizeX) + tileSizeX;
		tileIndex[1] = (tileX + 1 + tileY * tileSizeX) + tileSizeX;
		tileIndex[2] = (tileX + 1 + (tileY - 1) * tileSizeX) + tileSizeX;
		break;
	}
	if (tileSceneChange(attribute, tile, rcCollision))
	{
		return;
	}

	bool first = false;


	RECT rc = _playerShadowRc.GetRect();
	for (int i = 0; i < 3; ++i)
	{
		if (((attribute[tileIndex[i]] & ATTR_UNMOVE) == ATTR_UNMOVE) && isCollisionReaction(tile[tileIndex[i]].rc, rc))
		{
			_playerShadowX = (rc.left + rc.right) / 2;
			_playerShadowY = (rc.top + rc.bottom) / 2;
		}
	}
}

bool player::tileSceneChange(DWORD * attribute, tagTile * tile, RECT rcCol)
{
	RECT rc;
	if ((attribute[tileIndex[0]] == TP_TOWN) &&
		IntersectRect(&rc, &tile[tileIndex[0]].rc, &rcCol))
	{
		if (SCENEMANAGER->getCurrentScene() == "샵씬")
		{
			setPlayerPos(WINSIZEX + 330, 500);
		}
		else if (SCENEMANAGER->getCurrentScene() == "던전입구씬")
		{
			setPlayerPos(800, 200);
		}
		SCENEMANAGER->changeScene("마을씬");

		return true;
	}
	if ((attribute[tileIndex[0]] == TP_SHOP) &&
		IntersectRect(&rc, &tile[tileIndex[0]].rc, &rcCol))
	{
		setPlayerPos(WINSIZEX / 2 + 80, 1000);
		SCENEMANAGER->changeScene("샵씬");
		return true;
	}
	if ((attribute[tileIndex[0]] == TP_BOSS) &&
		IntersectRect(&rc, &tile[tileIndex[0]].rc, &rcCol))
	{
		setPlayerPos(WINSIZEX, 1800);
		SCENEMANAGER->changeScene("보스씬");
		return true;
	}
	if ((attribute[tileIndex[0]] == TP_ENTERENCE) &&
		IntersectRect(&rc, &tile[tileIndex[0]].rc, &rcCol))
	{
		if (SCENEMANAGER->getCurrentScene() == "마을씬")
		{
			if (!KEYANIMANAGER->findAnimation("playerTeleportIn")->isPlay())
			{
				setPlayerMotion(KEYANIMANAGER->findAnimation("playerTeleportIn"), ImageManager::GetInstance()->FindImage("playerTeleportIn"));
				_CurrentState = _teleportIn;
			}
		}
		else if (SCENEMANAGER->getCurrentScene() == "던전씬")
		{
			setPlayerPos(80, WINSIZEY / 2);

			SCENEMANAGER->changeScene("던전입구씬");
		}
		else if (SCENEMANAGER->getCurrentScene() == "던전씬2")
		{
			setPlayerPos(WINSIZEX - 80, WINSIZEY / 2);

			SCENEMANAGER->changeScene("던전입구씬");
		}
		else if (SCENEMANAGER->getCurrentScene() == "스파씬")
		{
			setPlayerPos(WINSIZEX / 2, 80);

			SCENEMANAGER->changeScene("던전입구씬");
		}


		return true;
	}
	if ((attribute[tileIndex[0]] == TP_DUN1) &&
		IntersectRect(&rc, &tile[tileIndex[0]].rc, &rcCol))
	{
		setPlayerPos(WINSIZEX - 80, WINSIZEY / 2);
		SCENEMANAGER->changeScene("던전씬");
		return true;
	}

	if ((attribute[tileIndex[0]] == TP_DUN2) &&
		IntersectRect(&rc, &tile[tileIndex[0]].rc, &rcCol))
	{
		setPlayerPos(80, WINSIZEY / 2);
		SCENEMANAGER->changeScene("던전씬2");
		return true;
	}

	if ((attribute[tileIndex[0]] == TP_SPA) &&
		IntersectRect(&rc, &tile[tileIndex[0]].rc, &rcCol))
	{
		setPlayerPos(WINSIZEX / 2, 840);
		SCENEMANAGER->changeScene("스파씬");
		return true;
	}
	return false;
}