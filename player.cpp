#include "stdafx.h"
#include "player.h"

HRESULT player::init()
{
	animationLoad();

	_idle = new playerIdleState();
	_walk = new playerWalkState();
	_roll = new playerRollState();
	_die = new playerDieState();
	_shield = new playerShieldState();
	_swim = new playerSwimState();
	_bow = new playerbowState();
	_sword = new playerSwordState();

	_index = 0;
	_playerX = 500;
	_playerY = 500;
	_directionX = true;

	_playerRc = RectMakePivot(Vector2(_playerX, _playerY), Vector2(50, 50), Pivot::LeftTop);

	_CurrentState = _idle;

	//???
	//_playerImg = ImageManager::GetInstance()->FindImage("playerRighrIdle");
	//???

	_playerMotion = KEYANIMANAGER->findAnimation(_index, "playerRightIdle");
	_playerMotion->start();

	return S_OK;
}

void player::render()
{
	CAMERAMANAGER->fillRectangle(_playerRc, D2D1::ColorF::Black, 1.f);
	CAMERAMANAGER->aniRender(_playerImg, _playerX, _playerY, _playerMotion, 1.5f);
	//_playerImg->aniRender(Vector2(_x, _y), _aniMotion, 1.0f);

	if (KEYMANAGER->isToggleKey('V'))
	{
		CAMERAMANAGER->rectangle(_playerRc, D2D1::ColorF::Red, 1.0f);
		CAMERAMANAGER->fillRectangle(_playerRc, D2D1::ColorF::Red, 1.0f);
	}
}

void player::update()
{
	KEYANIMANAGER->update();

	_CurrentState->update(*this);

	_playerRc = RectMakePivot(Vector2(_playerX, _playerY), Vector2(50, 50), Pivot::LeftTop);
}

void player::release()
{
}

void player::animationLoad()
{
	//플레이어 아이들상태
	_playerImg = ImageManager::GetInstance()->AddFrameImage("playerRightIdle", L"image/player/moveState.png", 10, 13);
	int playerRightIdle[] = { 80, 81, 82, 83, 84, 85, 86, 87, 88, 89 };
	KEYANIMANAGER->addArrayFrameAnimation(_index, "playerRightIdle", "playerRightIdle", playerRightIdle, 10, 13, true);

	_playerImg = ImageManager::GetInstance()->AddFrameImage("playerLeftIdle", L"image/player/moveState.png", 10, 13);
	int playerLeftIdle[] = { 90, 91, 92, 93, 94, 95, 96, 97, 98, 99 };
	KEYANIMANAGER->addArrayFrameAnimation(_index, "playerLeftIdle", "playerLeftIdle", playerLeftIdle, 10, 13, true);

	_playerImg = ImageManager::GetInstance()->AddFrameImage("playerUpIdle", L"image/player/moveState.png", 10, 13);
	int playerUpIdle[] = { 100, 101, 102, 103, 104, 105, 106, 107, 108, 109 };
	KEYANIMANAGER->addArrayFrameAnimation(_index, "playerUpIdle", "playerUpIdle", playerUpIdle, 10, 13, true);

	_playerImg = ImageManager::GetInstance()->AddFrameImage("playerDownIdle", L"image/player/moveState.png", 10, 13);
	int playerDownIdle[] = { 110, 111, 112, 113, 114, 115, 116, 117, 118, 119 };
	KEYANIMANAGER->addArrayFrameAnimation(_index, "playerDownIdle", "playerDownIdle", playerDownIdle, 10, 13, true);

	//플레이어 죽음
	_playerImg = ImageManager::GetInstance()->AddFrameImage("playerDie", L"image/player/moveState.png", 10, 13);
	int playerDie[] = { 120, 121, 122, 123, 124, 125, 126, 127, 128, 129 };
	KEYANIMANAGER->addArrayFrameAnimation(_index, "playerDie", "playerDie", playerDie, 10, 13, true);

	//플레이어 이동
	_playerImg = ImageManager::GetInstance()->AddFrameImage("playerUpWalk", L"image/player/moveState.png", 10, 13);
	int playerUpWalk[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
	KEYANIMANAGER->addArrayFrameAnimation(_index, "playerUpWalk", "playerUpWalk", playerUpWalk, 8, 13, true);

	_playerImg = ImageManager::GetInstance()->AddFrameImage("playerDownWalk", L"image/player/moveState.png", 10, 13);
	int playerDownWalk[] = { 10, 11, 12, 13, 14, 15, 16, 17 };
	KEYANIMANAGER->addArrayFrameAnimation(_index, "playerDownWalk", "playerDownWalk", playerDownWalk, 8, 13, true);

	_playerImg = ImageManager::GetInstance()->AddFrameImage("playerRightWalk", L"image/player/moveState.png", 10, 13);
	int playerRightWalk[] = { 20, 21, 22, 23, 24, 25, 26, 27 };
	KEYANIMANAGER->addArrayFrameAnimation(_index, "playerRightWalk", "playerRightWalk", playerRightWalk, 8, 13, true);

	_playerImg = ImageManager::GetInstance()->AddFrameImage("playerLeftWalk", L"image/player/moveState.png", 10, 13);
	int playerLeftWalk[] = { 30, 31, 32, 33, 34, 35, 36, 37 };
	KEYANIMANAGER->addArrayFrameAnimation(_index, "playerLeftWalk", "playerLeftWalk", playerLeftWalk, 8, 13, true);

	//플레이어 구르기
	_playerImg = ImageManager::GetInstance()->AddFrameImage("playerRightRoll", L"image/player/moveState.png", 10, 13);
	int playerRightRoll[] = { 40, 41, 42, 43, 44, 45, 46, 47 };
	KEYANIMANAGER->addArrayFrameAnimation(_index, "playerRightRoll", "playerRightRoll", playerRightRoll, 8, 13, true);

	_playerImg = ImageManager::GetInstance()->AddFrameImage("playerLeftRoll", L"image/player/moveState.png", 10, 13);
	int playerLeftRoll[] = { 50, 51, 52, 53, 54, 55, 56, 57 };
	KEYANIMANAGER->addArrayFrameAnimation(_index, "playerLeftRoll", "playerLeftRoll", playerLeftRoll, 8, 13, true);

	_playerImg = ImageManager::GetInstance()->AddFrameImage("playerUpRoll", L"image/player/moveState.png", 10, 13);
	int playerUpRoll[] = { 60, 61, 62, 63, 64, 65, 66, 67 };
	KEYANIMANAGER->addArrayFrameAnimation(_index, "playerUpRoll", "playerUpRoll", playerUpRoll, 8, 13, true);

	_playerImg = ImageManager::GetInstance()->AddFrameImage("playerDownRoll", L"image/player/moveState.png", 10, 13);
	int playerDownRoll[] = { 70, 71, 72, 73, 74, 75, 76, 77 };
	KEYANIMANAGER->addArrayFrameAnimation(_index, "playerDownRoll", "playerDownRoll", playerDownRoll, 8, 13, true);

	//플레이어 활
	//_playerImg = ImageManager::GetInstance()->AddFrameImage("playerUpBow", L"image/player/bowState.png", 9, 4);
	//int playerUpBow[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
	//KEYANIMANAGER->addArrayFrameAnimation(_index, "playerUpBow", "playerUpBow", playerUpBow, 9, 13, true);

	//_playerImg = ImageManager::GetInstance()->AddFrameImage("playerDownBow", L"image/player/bowState.png", 9, 4);
	//int playerDownBow[] = { 9, 10, 11, 12, 13, 14, 15, 16, 17 };
	//KEYANIMANAGER->addArrayFrameAnimation(_index, "playerDownBow", "playerDownBow", playerDownBow, 9, 13, true);

	//_playerImg = ImageManager::GetInstance()->AddFrameImage("playerRightBow", L"image/player/bowState.png", 9, 4);
	//int playerRightBow[] = { 18, 19, 20, 21, 22, 23, 24, 25, 26 };
	//KEYANIMANAGER->addArrayFrameAnimation(_index, "playerRightBow", "playerRightBow", playerRightBow, 9, 13, true);

	//_playerImg = ImageManager::GetInstance()->AddFrameImage("playerLeftBow", L"image/player/bowState.png", 9, 4);
	//int playerLeftBow[] = { 27, 28, 29, 30, 31, 32, 33, 34, 35 };
	//KEYANIMANAGER->addArrayFrameAnimation(_index, "playerLeftBow", "playerLeftBow", playerLeftBow, 9, 13, true);

	//플레이어 검 콤보
	//_playerImg = ImageManager::GetInstance()->AddFrameImage("playerUpSword1", L"image/player/swordState.png", 11, 4);
	//int playerUpSword1[] = { 0, 1, 2, 3, 4, 5 };
	//KEYANIMANAGER->addArrayFrameAnimation(_index, "playerUpSword1", "playerUpSword1", playerUpSword1, 6, 13, true);

	//_playerImg = ImageManager::GetInstance()->AddFrameImage("playerUpSword2", L"image/player/swordState.png", 11, 4);
	//int playerUpSword2[] = { 6, 7, 8, 9, 10 };
	//KEYANIMANAGER->addArrayFrameAnimation(_index, "playerUpSword2", "playerUpSword2", playerUpSword2, 5, 13, true);

	//_playerImg = ImageManager::GetInstance()->AddFrameImage("playerDownSword1", L"image/player/swordState.png", 11, 4);
	//int playerDownSword1[] = { 11, 12, 13, 14, 15, 16 };
	//KEYANIMANAGER->addArrayFrameAnimation(_index, "playerDownSword1", "playerDownSword1", playerDownSword1, 6, 13, true);

	//_playerImg = ImageManager::GetInstance()->AddFrameImage("playerDownSword2", L"image/player/swordState.png", 11, 4);
	//int playerDownSword2[] = { 17, 18, 19, 20, 21 };
	//KEYANIMANAGER->addArrayFrameAnimation(_index, "playerDownSword2", "playerDownSword2", playerDownSword2, 5, 13, true);

	//_playerImg = ImageManager::GetInstance()->AddFrameImage("playerRightSword1", L"image/player/swordState.png", 11, 4);
	//int playerRightSword1[] = { 22, 23, 24, 25, 26, 27 };
	//KEYANIMANAGER->addArrayFrameAnimation(_index, "playerRightSword1", "playerRightSword1", playerRightSword1, 6, 13, true);

	//_playerImg = ImageManager::GetInstance()->AddFrameImage("playerRightSword2", L"image/player/swordState.png", 11, 4);
	//int playerRightSword2[] = { 28, 29, 30, 31, 32 };
	//KEYANIMANAGER->addArrayFrameAnimation(_index, "playerRightSword2", "playerRightSword2", playerRightSword2, 5, 13, true);

	//_playerImg = ImageManager::GetInstance()->AddFrameImage("playerLeftSword1", L"image/player/swordState.png", 11, 4);
	//int playerLeftSword1[] = { 33, 34, 35, 36, 37, 38 };
	//KEYANIMANAGER->addArrayFrameAnimation(_index, "playerLeftSword1", "playerLeftSword1", playerLeftSword1, 6, 13, true);

	//_playerImg = ImageManager::GetInstance()->AddFrameImage("playerLeftSword2", L"image/player/swordState.png", 11, 4);
	//int playerLeftSword2[] = { 39, 40, 41, 42, 43 };
	//KEYANIMANAGER->addArrayFrameAnimation(_index, "playerLeftSword2", "playerLeftSword2", playerLeftSword2, 5, 13, true);

	////================================================================================== 일단 여기까지 컷

	//플레이어 막기
	//_playerImg = ImageManager::GetInstance()->AddFrameImage("playerRightShield", L"image/player/shieldState.png", 4, 1);
	//int playerRightShield[] = { 0 };
	//KEYANIMANAGER->addArrayFrameAnimation(_index, "playerRightShield", "playerRightShield", playerRightShield, 1, 13, true);

	//_playerImg = ImageManager::GetInstance()->AddFrameImage("playerLeftShield", L"image/player/shieldState.png", 4, 1);
	//int playerLeftShield[] = { 1 };
	//KEYANIMANAGER->addArrayFrameAnimation(_index, "playerLeftShield", "playerLeftShield", playerLeftShield, 1, 13, true);

	//_playerImg = ImageManager::GetInstance()->AddFrameImage("playerUpShield", L"image/player/shieldState.png", 4, 1);
	//int playerUpShield[] = { 2 };
	//KEYANIMANAGER->addArrayFrameAnimation(_index, "playerUpShield", "playerUpShield", playerUpShield, 1, 13, true);

	//_playerImg = ImageManager::GetInstance()->AddFrameImage("playerDownShield", L"image/player/shieldState.png", 4, 1);
	//int playerDownShield[] = { 3 };
	//KEYANIMANAGER->addArrayFrameAnimation(_index, "playerDownShield", "playerDownShield", playerDownShield, 1, 13, true);

	//플레이어 수영
	//_playerImg = ImageManager::GetInstance()->AddFrameImage("playerDownSwim", L"image/player/swimState.png", 10, 4);
	//int playerDownSwim[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	//KEYANIMANAGER->addArrayFrameAnimation(_index, "playerDownSwim", "playerDownSwim", playerDownSwim, 10, 13, true);

	//_playerImg = ImageManager::GetInstance()->AddFrameImage("playerLeftSwim", L"image/player/swimState.png", 10, 4);
	//int playerLeftSwim[] = { 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 };
	//KEYANIMANAGER->addArrayFrameAnimation(_index, "playerLeftSwim", "playerLeftSwim", playerLeftSwim, 10, 13, true);

	//_playerImg = ImageManager::GetInstance()->AddFrameImage("playerRightSwim", L"image/player/swimState.png", 10, 4);
	//int playerRightSwim[] = { 20, 21, 22, 23, 24, 25, 26, 27, 28, 29 };
	//KEYANIMANAGER->addArrayFrameAnimation(_index, "playerRightSwim", "playerRightSwim", playerRightSwim, 10, 13, true);

	//_playerImg = ImageManager::GetInstance()->AddFrameImage("playerUpSwim", L"image/player/swimState.png", 10, 4);
	//int playerUpSwim[] = { 30, 31, 32, 33, 34, 35, 36, 37, 38, 39 };
	//KEYANIMANAGER->addArrayFrameAnimation(_index, "playerUpSwim", "playerUpSwim", playerUpSwim, 10, 13, true);
}
