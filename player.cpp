#include "stdafx.h"
#include "player.h"

HRESULT player::init()
{
	animationLoad();

	_idle = new playerState();

	_x = 500;
	_y = 500;
	
	_rc = RectMakePivot(Vector2(_x, _y), Vector2(50, 50), Pivot::Center);

	_CurrentState = _idle;
	
	_playerimg = ImageManager::GetInstance()->FindImage("playerRighrIdle");
	//_aniState = IMAGEMANAGER->findAnimation("playerRighrIdle");
	_aniState->start();

	return S_OK;
}

void player::render()
{
	CAMERAMANAGER->fillRectangle(_rc, D2D1::ColorF::Black, 1.f);
}

void player::update()
{
	_CurrentState->update(*this);

	if (KEYMANAGER->isStayKeyDown('W'))
	{
		_y -= 5;
	}

	if (KEYMANAGER->isStayKeyDown('S'))
	{
		_y += 5;
	}

	if (KEYMANAGER->isStayKeyDown('A'))
	{
		_x -= 5;
	}

	if (KEYMANAGER->isStayKeyDown('D'))
	{
		_x += 5;
	}
	_rc = RectMakePivot(Vector2(_x, _y), Vector2(50, 50), Pivot::Center);
}

void player::release()
{
}

void player::animationLoad()
{
	_playerimg = ImageManager::GetInstance()->AddFrameImage("playerRighrIdle", L"image/player/moveState.png", 10, 13);
	_aniState = new animation;


}
 