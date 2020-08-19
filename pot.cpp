#include "stdafx.h"
#include "pot.h"

void pot::render()
{
	CAMERAMANAGER->zOrderAniRender(_img, _x, _y, _z, _motion, 1.3f);
	CAMERAMANAGER->fillRectangle(_bar.back, D2D1::ColorF::DimGray, _barAlpha);
	CAMERAMANAGER->fillRectangle(_bar.middle, D2D1::ColorF::LightSalmon, _barAlpha);
	CAMERAMANAGER->fillRectangle(_bar.front, D2D1::ColorF::Tomato, _barAlpha);
}

void pot::dead()
{
	if (_onceAni)
	{
		_img = ImageManager::GetInstance()->FindImage("potDead");
		_motion->stop();
		_motion = KEYANIMANAGER->findAnimation( "potDead");
		_motion->start();
		_onceAni = false;
	}
	if (!_motion->isPlay() && !_onceAni)
	{
		_realDead = true;
	}
}
