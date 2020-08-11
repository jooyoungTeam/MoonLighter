#include "stdafx.h"
#include "enemy.h"

HRESULT enemy::init(int index, float x, float y, float width, float height, ENEMYTYPE type)
{
	_idle = new enemyIdleState;
	_move = new enemyMoveState;
	_attack = new enemyAttackState;
	_hit = new enemyHitState;
	_dead = new enemyDeadState;

	_aStar = new aStar;

	_index = index;
	_scale = 1.0f;
	ani();

	_x = x;
	_y = y;
	_width = width;
	_height = height;
	_type = type;
	_maxHP = _curHP = _saveHP = 100;
	_speed = 0;
	_bar.width = 50;
	_bar.x = _x;
	_bar.y = _y - (_height / 2) - 15;

	_bar.rc = (RectMakePivot(Vector2(_bar.x, _bar.y), Vector2(50, 5), Pivot::Center));
	_rc = RectMakePivot(Vector2(_x, _y), Vector2(_width, _height), Pivot::Center);
	_attackRc = RectMakePivot(Vector2(_x, _y), Vector2(_width, _height), Pivot::Center);

	_backBar = ImageManager::GetInstance()->FindImage("backBar");
	_middleBar = ImageManager::GetInstance()->FindImage("middleBar");
	_frontBar = ImageManager::GetInstance()->FindImage("frontBar");


	switch (_type)
	{
	case ENEMY_RED_SLIME:
		//_state->enemyIdle()
		_motion = KEYANIMANAGER->findAnimation(_index, "redSlime");
		_img = ImageManager::GetInstance()->FindImage("redSlime");
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
		_motion = KEYANIMANAGER->findAnimation(_index, "golemDown");
		_img = ImageManager::GetInstance()->FindImage("golem");
		_motion->start();
		set();
		break;
	case ENEMY_POT:
		_motion = KEYANIMANAGER->findAnimation(_index, "potLeft");
		_img = ImageManager::GetInstance()->FindImage("pot");
		_motion->start();
		break;
	case ENEMY_BOSS:
		_motion = KEYANIMANAGER->findAnimation(_index, "boss");
		_img = ImageManager::GetInstance()->FindImage("boss");
		_motion->start();
		break;
	}
	_state = _idle;

	_isAttack = false;
	_isCol = false;
	_onceAni = false;
	_realDead = false;
	_isHit = false;

	_attackDelay = 0;
	_attackAngle = 0;
	_middleBarCut = 0;

	vector<POINT> tempV;
	_aStar->init(38, 18 , _x / 50 , _y / 50 , _pX / 50, _pY / 50, tempV, false);

	return S_OK;
}

void enemy::release()
{
}

void enemy::update()
{
	_aStar->update(_x / 50, _y / 50, _pX / 50, _pY / 50);
	_state->update(*this,  _type);
	enemyWay();
	KEYANIMANAGER->update();
	if (_curHP <= 0)
	{
		_curHP = 0;
		_state = _dead;
	}
	if (_isHit)
	{
		_saveHP--;
	}
	if (_saveHP <= 0)
	{
		_isHit = false;
	}
	setGauge(_curHP, _maxHP);
	//cout << "세이브" << _saveHP << "현재" << _curHP << endl;
	_bar.x = _x;
	_bar.y = _y - (_height / 2) - 15;
	_bar.rc = (RectMakePivot(Vector2(_bar.x, _bar.y), Vector2(_frontBar->GetWidth(), 5), Pivot::Center));
	_rc = RectMakePivot(Vector2(_x, _y), Vector2(_width, _height), Pivot::Center);
}

void enemy::render()
{
	_aStar->render();
	_img->aniRender(Vector2(_x, _y), _motion, _scale);

	_backBar->Render(Vector2(_bar.rc.left, _bar.rc.top));
	_middleBar->Render(Vector2(_bar.rc.left, _bar.rc.top));
	_middleBar->SetSize(Vector2(_saveHP, _backBar->GetHeight()));
	_frontBar->Render(Vector2(_bar.rc.left, _bar.rc.top));
	_frontBar->SetSize(Vector2(_bar.width, _backBar->GetHeight()));
	
	D2DRenderer::GetInstance()->DrawRectangle(_bar.rc, D2DRenderer::DefaultBrush::Yellow, 1.0f);
	
}

void enemy::playerCheck(float x, float y, FloatRect rc)
{
	_pX = x;
	_pY = y;
	_pRc = rc;
	//cout << _pX << endl;
}

void enemy::ani()
{

	//레드 슬라임
	ImageManager::GetInstance()->AddFrameImage("redSlime", L"image/enemy/slimeIlde.png", 10, 1);
	ImageManager::GetInstance()->AddFrameImage("redSlimeJump", L"image/enemy/slimeJump.png", 12, 1);
	ImageManager::GetInstance()->AddFrameImage("redSlimeDead", L"image/enemy/slimeDead.png", 11, 1);
	ImageManager::GetInstance()->AddFrameImage("slimeAttack", L"image/enemy/slimeAttack.png", 8, 1);

	//블루 슬라임
	ImageManager::GetInstance()->AddFrameImage("blueSlime", L"image/enemy/blueSlime.png", 8, 1);
	ImageManager::GetInstance()->AddFrameImage("blueSlimeDead", L"image/enemy/blueSlimeDead.png", 11, 1);

	//옐로 슬라임
	ImageManager::GetInstance()->AddFrameImage("yellowSlime", L"image/enemy/yellowSlime.png", 8, 1);
	ImageManager::GetInstance()->AddFrameImage("yellowSlimeDead", L"image/enemy/yellowSlimeDead.png", 11, 1);

	//팟
	ImageManager::GetInstance()->AddFrameImage("bulletCollision", L"image/enemy/bullet_collision.png", 5, 1);
	ImageManager::GetInstance()->AddFrameImage("bullet", L"image/enemy/enemy_bullet.png", 6, 1);
	ImageManager::GetInstance()->AddFrameImage("pot", L"image/enemy/pot.png", 11, 4);

	//골렘
	ImageManager::GetInstance()->AddFrameImage("golemAttack", L"image/enemy/GolemAttack.png", 13, 4);
	ImageManager::GetInstance()->AddFrameImage("golem", L"image/enemy/GolemMove.png", 8,4);


	//보스
	ImageManager::GetInstance()->AddFrameImage("BossUp", L"image/enemy/BossUp.png", 32, 1);
	ImageManager::GetInstance()->AddFrameImage("bossHit", L"image/enemy/dead1.png", 41, 1);
	ImageManager::GetInstance()->AddFrameImage("bossDead", L"image/enemy/dead2.png", 41, 1);
	ImageManager::GetInstance()->AddFrameImage("bossHandCome", L"image/enemy/Hand_Shoot_Last.png", 11, 1);
	ImageManager::GetInstance()->AddFrameImage("bossAttack", L"image/enemy/attack.png", 7, 1);
	ImageManager::GetInstance()->AddFrameImage("boss", L"image/enemy/idleBoss.png", 2, 1);
	ImageManager::GetInstance()->AddFrameImage("bossAttackIdle", L"image/enemy/attackIdle.png", 2, 1);
	ImageManager::GetInstance()->AddFrameImage("bossHand", L"image/enemy/hand.png", 19, 1);
	ImageManager::GetInstance()->AddFrameImage("bossHandFly", L"image/enemy/FistShoot.png", 22, 3);
	ImageManager::GetInstance()->AddImage("Boss_Rock0", L"image/enemy/Boss_Rock0.png");
	ImageManager::GetInstance()->AddImage("Boss_Rock1", L"image/enemy/Boss_Rock1.png");
	ImageManager::GetInstance()->AddImage("Boss_Rock2", L"image/enemy/Boss_Rock2.png");
	ImageManager::GetInstance()->AddImage("Boss_Rock3", L"image/enemy/Boss_Rock3.png");

	//체력바
	ImageManager::GetInstance()->AddImage("backBar", L"image/enemy/backBar.png");
	ImageManager::GetInstance()->AddImage("middleBar", L"image/enemy/middleBar.png");
	ImageManager::GetInstance()->AddImage("frontBar", L"image/enemy/frontBar.png");



	//레드 슬라임
	int slimeIlde[] = { 0,1,2,3,4,5,6,7,8,9 };
	KEYANIMANAGER->addArrayFrameAnimation(_index, "redSlime", "redSlime", slimeIlde, 10, 13, true);

	int jump[] = { 0,1,2,3,4,5,6,7,8,9,10,11 };
	KEYANIMANAGER->addArrayFrameAnimation(_index, "redSlimeJump", "redSlimeJump", jump, 12, 13, false);

	int slimeDead[] = { 0,1,2,3,4,5,6,7,8,9,10 };
	KEYANIMANAGER->addArrayFrameAnimation(_index, "redSlimeDead", "redSlimeDead", slimeDead, 11, 13, false);

	int slimeAttack[] = { 0,1,2,3,4,5,6,7 };
	KEYANIMANAGER->addArrayFrameAnimation(_index, "slimeAttack", "slimeAttack", slimeAttack, 8, 13, true);


	//블루 슬라임
	int blueSlime[] = { 0,1,2,3,4,5,6,7,8 };
	KEYANIMANAGER->addArrayFrameAnimation(_index, "blueSlime", "blueSlime", blueSlime, 8, 13, true);


	KEYANIMANAGER->addArrayFrameAnimation(_index, "blueSlimeDead", "blueSlimeDead", slimeDead, 11, 13, false);


	//옐로 슬라임
	int yellowSlime[] = { 0,1,2,3,4,5,6,7,8,9,10 };
	KEYANIMANAGER->addArrayFrameAnimation(_index, "yellowSlime", "yellowSlime", yellowSlime, 8, 13, true);

	KEYANIMANAGER->addArrayFrameAnimation(_index, "yellowSlimeDead", "yellowSlimeDead", slimeDead, 11, 13, false);


	//팟
	int bulletCol[] = { 0,1,2,3,4 };
	KEYANIMANAGER->addArrayFrameAnimation(_index, "bulletCollision", "bulletCollision", bulletCol, 5, 13, false);

	int bullet[] = { 0,1,2,3,4,5 };
	KEYANIMANAGER->addArrayFrameAnimation(_index, "bullet", "bullet", bullet, 6, 13, true);

	int leftPot[] = { 0,1,2,3,4,5,6,7,8,9,10 }; 
	KEYANIMANAGER->addArrayFrameAnimation(_index, "potLeft", "pot", leftPot, 11, 7, true);
	int rightPot[] = { 11,12,13,14,15,16,17,18,19,20,21 };
	KEYANIMANAGER->addArrayFrameAnimation(_index, "potRight", "pot", rightPot, 11, 7, true);
	int upPot[] = { 22,23,24,25,26,27,28,29,30,31,32 };
	KEYANIMANAGER->addArrayFrameAnimation(_index, "potUp", "pot", upPot, 11, 7, true);
	int downPot[] = { 33,34,35,36,37,38,39,40,41,42,43 };
	KEYANIMANAGER->addArrayFrameAnimation(_index, "potDown", "pot", downPot, 11, 7, true);




	//골렘
	int goLeftAttack[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12 };
	KEYANIMANAGER->addArrayFrameAnimation(_index, "golemLeftAttack", "golemAttack", goLeftAttack, 13, 13, false);

	int goRightAttack[] = { 13,14,15,16,17,18,19,20,21,22,23,24,25 };
	KEYANIMANAGER->addArrayFrameAnimation(_index, "golemRightAttack", "golemAttack", goRightAttack, 13, 13, false);

	int goUpAttack[] = { 26,27,28,29,30,31,32,33,34,35,36,37,38 };
	KEYANIMANAGER->addArrayFrameAnimation(_index, "golemUpAttack", "golemAttack", goUpAttack, 13, 13, false);

	int goDownAttack[] = {39,40,41,42,43,44,45,46,47,48,49,50,51 };
	KEYANIMANAGER->addArrayFrameAnimation(_index, "golemDownAttack", "golemAttack", goDownAttack, 13, 13, false);
	

	int goLeft[] = { 0,1,2,3,4,5,6,7 };
	KEYANIMANAGER->addArrayFrameAnimation(_index, "golemLeft", "golem", goLeft, 8, 13, true);

	int goRight[] = { 8,9,10,11,12,13,14,15 };
	KEYANIMANAGER->addArrayFrameAnimation(_index, "golemRight", "golem", goRight, 8, 13, true);

	int goUp[] = { 16,17,18,19,20,21,22,23 };
	KEYANIMANAGER->addArrayFrameAnimation(_index, "golemUp", "golem", goUp, 8, 13, true);

	int goDown[] = { 24,25,26,27,28,29,30,31 };
	KEYANIMANAGER->addArrayFrameAnimation(_index, "golemDown", "golem", goDown, 8, 13, true);



	//보스
	int BossUp[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31 };
	KEYANIMANAGER->addArrayFrameAnimation(_index, "BossUp", "BossUp", BossUp, 32, 13, false);

	int dead1[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40 };
	KEYANIMANAGER->addArrayFrameAnimation(_index, "bossHit", "bossHit", dead1, 41, 13, false);

	int dead2[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40 };
	KEYANIMANAGER->addArrayFrameAnimation(_index, "bossDead", "bossDead", dead2, 41, 13, false);


	int Hand_Shoot_Last[] = { 0,1,2,3,4,5,6,7,8,9,10 };
	KEYANIMANAGER->addArrayFrameAnimation(_index, "bossHandCome", "bossHandCome", Hand_Shoot_Last, 11, 13, false);

	int attack[] = { 6,5,4,3,2,1,0 };
	KEYANIMANAGER->addArrayFrameAnimation(_index, "bossAttack", "bossAttack", attack, 7, 13, false);

	int idleBoss[] = { 0,1 };
	KEYANIMANAGER->addArrayFrameAnimation(_index, "boss", "boss", idleBoss, 2, 5, true);

	int attackIdle[] = { 0,1 };
	KEYANIMANAGER->addArrayFrameAnimation(_index, "bossAttackIdle", "bossAttackIdle", attackIdle, 2, 5, true);

	int hand[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18 };
	KEYANIMANAGER->addArrayFrameAnimation(_index, "bossHand", "bossHand", hand, 19, 13, false);

	int FistShoot[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,
		16, 15,14,13, 13, 44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59, 59, 58,57,56,55,
		54,53,52,51,50,49,48,47,46,45,44,
	22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43 };
	KEYANIMANAGER->addArrayFrameAnimation(_index, "bossHandFly", "bossHandFly", FistShoot, 76, 8, false);


}



void enemy::enemyWay()
{
	_angle = getAngle(_pX, _pY, _x, _y)  * (180 / PI);
	if ((_angle >= 315 && _angle < 360) || (_angle >= 0 && _angle < 45))
	{
		_golemDir = GOLEM_LEFT;

	}
	else if (_angle >= 135 && _angle < 225)
	{
		_golemDir = GOLEM_RIGHT;

	}

	if (_angle >= 45 && _angle < 135)
	{
		_golemDir = GOLEM_BOTTOM;
	}
	else if (_angle >= 225 && _angle < 315)
	{
		_golemDir = GOLEM_TOP;
	}
}

void enemy::move()
{
	switch (_type)
	{
	case ENEMY_RED_SLIME:
		_speed = 1.5f;
		break;
	case ENEMY_BLUE_SLIME:
		_speed = 0.7f;
		break;
	case ENEMY_YELLOW_SLIME:
		_speed = 0.7f;
		break;
	case ENEMY_GOLEM:
		_speed = 2.f;
		break;

	}
	if (_aStar->getVOldClose().size() > 0 && _aStar->getMoveIndex() < _aStar->getVOldClose().size())
	{
		_moveAngle = getAngle(_x, _y, _aStar->getVOldClose()[_aStar->getMoveIndex()]->center.x + _aStar->getRndX(), _aStar->getVOldClose()[_aStar->getMoveIndex()]->center.y + _aStar->getRndY());

		_x += cosf(_moveAngle) * _speed;
		_y -= sinf(_moveAngle) * _speed;

		if (getDistance(_x, _y, _aStar->getVOldClose()[_aStar->getMoveIndex()]->center.x + _aStar->getRndX(), _aStar->getVOldClose()[_aStar->getMoveIndex()]->center.y + _aStar->getRndY()) < 1)
		{
			if(_aStar->getMoveIndex() < _aStar->getVOldClose().size())
				_aStar->setMoveIndex(_aStar->getMoveIndex() + 1);
		}

	}
}

void enemy::setGauge(float curHP, float maxHP)
{
	_bar.width = (curHP / maxHP) * _backBar->GetWidth();
}

