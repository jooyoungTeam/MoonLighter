#include "stdafx.h"
#include "enemy.h"

HRESULT enemy::init(int index, float x, float y, float width, float height, ENEMYTYPE type, string map)
{
	_index = index;

	ani();

	//_motion = KEYANIMANAGER->findAnimation("slimeIlde");

	_x = x;
	_y = y;
	_width = width;
	_height = height;
	_type = type;
	_mapName = map;
	_maxHP = 100;

	_rc = RectMakePivot(Vector2(_x, _y), Vector2(_width, _height), Pivot::Center);

	switch (_type)
	{
	case ENEMY_RED_SLIME:
		_motion = KEYANIMANAGER->findAnimation(_index, "slimeIlde");
		_img = ImageManager::GetInstance()->FindImage("slimeIlde");
		_motion->start();
		break;
	case ENEMY_BLUE_SLIME:
		_motion = KEYANIMANAGER->findAnimation(_index, "blueSlime");
		_img = ImageManager::GetInstance()->FindImage("blueSlime");
		_motion->start();
		break;
	case ENEMY_YELLOW_SLIME:
		_motion = KEYANIMANAGER->findAnimation(_index, "yellowSlime");
		_img = ImageManager::GetInstance()->FindImage("yellowSlime");
		_motion->start();
		break;
	case ENEMY_GOLEM:
		_motion = KEYANIMANAGER->findAnimation(_index, "idleBoss");
		_img = ImageManager::GetInstance()->FindImage("idleBoss");
		_motion->start();
		break;
	case ENEMY_POT:
		_motion = KEYANIMANAGER->findAnimation(_index, "idleBoss");
		_img = ImageManager::GetInstance()->FindImage("idleBoss");
		_motion->start();
		break;
	case ENEMY_BOSS:
		_motion = KEYANIMANAGER->findAnimation(_index, "idleBoss");
		_img = ImageManager::GetInstance()->FindImage("idleBoss");
		_motion->start();
		break;
	}
	return S_OK;
}

void enemy::release()
{
}

void enemy::update()
{
	test();
	_rc = RectMakePivot(Vector2(_width, _height), Vector2(50, 50), Pivot::Center);
	KEYANIMANAGER->update();
}

void enemy::render()
{
	D2DRenderer::GetInstance()->DrawRectangle
	(
		_rc, D2DRenderer::DefaultBrush::Black, 1.f
	);
	//_img->SetScale(0.5f);
	_img->aniRender(Vector2(_x, _y), _motion,1.0f);
}

void enemy::ani()
{
	_img = ImageManager::GetInstance()->AddFrameImage("slimeIlde", L"image/enemy/slimeIlde.png", 10, 1);
	int slimeIlde[] = { 0,1,2,3,4,5,6,7,8,9 };
	KEYANIMANAGER->addArrayFrameAnimation(_index, "slimeIlde", "slimeIlde", slimeIlde, 10, 13, true);


	ImageManager::GetInstance()->AddFrameImage("slimeJump", L"image/enemy/slimeJump.png", 12, 1);
	int jump[] = { 0,1,2,3,4,5,6,7,8,9,10,11 };
	KEYANIMANAGER->addArrayFrameAnimation(_index, "slimeJump", "slimeJump", jump, 12, 13, true);

	ImageManager::GetInstance()->AddFrameImage("blueSlime", L"image/enemy/blueSlime.png", 8, 1);
	int blueSlime[] = { 0,1,2,3,4,5,6,7,8 };
	KEYANIMANAGER->addArrayFrameAnimation(_index, "blueSlime", "blueSlime", blueSlime, 8, 13, true);

	ImageManager::GetInstance()->AddFrameImage("slimeDead", L"image/enemy/slimeDead.png", 11, 1);
	int slimeDead[] = { 0,1,2,3,4,5,6,7,8,9,10 };
	KEYANIMANAGER->addArrayFrameAnimation(_index, "slimeDead", "slimeDead", slimeDead, 11, 13, true);

	ImageManager::GetInstance()->AddFrameImage("blueSlimeDead", L"image/enemy/blueSlimeDead.png", 11, 1);
	KEYANIMANAGER->addArrayFrameAnimation(_index, "blueSlimeDead", "blueSlimeDead", slimeDead, 11, 13, true);

	ImageManager::GetInstance()->AddFrameImage("yellowSlimeDead", L"image/enemy/yellowSlimeDead.png", 11, 1);
	KEYANIMANAGER->addArrayFrameAnimation(_index, "yellowSlimeDead", "yellowSlimeDead", slimeDead, 11, 13, true);

	ImageManager::GetInstance()->AddFrameImage("yellowSlime", L"image/enemy/yellowSlime.png", 8, 1);
	int yellowSlime[] = { 0,1,2,3,4,5,6,7,8,9,10 };
	KEYANIMANAGER->addArrayFrameAnimation(_index, "yellowSlime", "yellowSlime", yellowSlime, 8, 13, true);


	ImageManager::GetInstance()->AddFrameImage("BossUp", L"image/enemy/BossUp.png", 32, 1);
	int BossUp[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31 };
	KEYANIMANAGER->addArrayFrameAnimation(_index, "BossUp", "BossUp", BossUp, 32, 13, true);

	ImageManager::GetInstance()->AddFrameImage("dead1", L"image/enemy/dead1.png", 41, 1);
	int dead1[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40 };
	KEYANIMANAGER->addArrayFrameAnimation(_index, "dead1", "dead1", dead1, 41, 13, true);

	ImageManager::GetInstance()->AddFrameImage("dead2", L"image/enemy/dead2.png", 41, 1);
	int dead2[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40 };
	KEYANIMANAGER->addArrayFrameAnimation(_index, "dead2", "dead2", dead2, 41, 13, true);


	ImageManager::GetInstance()->AddFrameImage("Hand_Shoot_Last", L"image/enemy/Hand_Shoot_Last.png", 11, 1);
	int Hand_Shoot_Last[] = { 0,1,2,3,4,5,6,7,8,9,10 };
	KEYANIMANAGER->addArrayFrameAnimation(_index, "Hand_Shoot_Last", "Hand_Shoot_Last", Hand_Shoot_Last, 11, 13, true);

	ImageManager::GetInstance()->AddFrameImage("attack", L"image/enemy/attack.png", 7, 1);
	int attack[] = { 6,5,4,3,2,1,0 };
	KEYANIMANAGER->addArrayFrameAnimation(_index, "attack", "attack", attack, 7, 13, true);

	ImageManager::GetInstance()->AddFrameImage("idleBoss", L"image/enemy/idleBoss.png", 2, 1);
	int idleBoss[] = { 0,1 };
	KEYANIMANAGER->addArrayFrameAnimation(_index, "idleBoss", "idleBoss", idleBoss, 2, 5, true);

	ImageManager::GetInstance()->AddFrameImage("attackIdle", L"image/enemy/attackIdle.png", 2, 1);
	int attackIdle[] = { 0,1 };
	KEYANIMANAGER->addArrayFrameAnimation(_index, "attackIdle", "attackIdle", attackIdle, 2, 5, true);

	ImageManager::GetInstance()->AddFrameImage("hand", L"image/enemy/hand.png", 19, 1);
	int hand[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18 };
	KEYANIMANAGER->addArrayFrameAnimation(_index, "hand", "hand", hand, 19, 13, true);

	ImageManager::GetInstance()->AddFrameImage("slimeAttack", L"image/enemy/slimeAttack.png", 8, 1);
	int slimeAttack[] = { 0,1,2,3,4,5,6,7 };
	KEYANIMANAGER->addArrayFrameAnimation(_index, "slimeAttack", "slimeAttack", slimeAttack, 8, 13, true);

	ImageManager::GetInstance()->AddFrameImage("FistShoot", L"image/enemy/FistShoot.png", 22, 3);
	int FistShoot[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,
		16, 15,14,13, 13, 44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59, 59, 58,57,56,55,
		54,53,52,51,50,49,48,47,46,45,44,
	22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43 };

	KEYANIMANAGER->addArrayFrameAnimation(_index, "FistShoot", "FistShoot", FistShoot, 76, 8, false);

}

void enemy::test()
{
	if (change)
	{
		switch (_type)
		{
		case ENEMY_RED_SLIME:
			_motion = KEYANIMANAGER->findAnimation(_index, "slimeIlde");
			_img = ImageManager::GetInstance()->FindImage("slimeIlde");
			_motion->start();
			break;
		case ENEMY_BLUE_SLIME:
			_img = ImageManager::GetInstance()->FindImage("slimeJump");
			_motion = KEYANIMANAGER->findAnimation(_index, "slimeJump");
			_motion->start();
			break;
		case ENEMY_YELLOW_SLIME:
			_img = ImageManager::GetInstance()->FindImage("blueSlime");
			_motion = KEYANIMANAGER->findAnimation(_index, "blueSlime");
			_motion->start();
			break;
		case ENEMY_GOLEM:
			_motion = KEYANIMANAGER->findAnimation(_index, "idleBoss");
			_img = ImageManager::GetInstance()->FindImage("idleBoss");
			_motion->start();
			break;
		case ENEMY_POT:
			_motion = KEYANIMANAGER->findAnimation(_index, "idleBoss");
			_img = ImageManager::GetInstance()->FindImage("idleBoss");
			_motion->start();
			break;
		case ENEMY_BOSS:
			_motion = KEYANIMANAGER->findAnimation(_index, "idleBoss");
			_img = ImageManager::GetInstance()->FindImage("idleBoss");
			_motion->start();
			break;
		}

		change = false;
	}
}
