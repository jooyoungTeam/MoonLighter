#include "stdafx.h"
#include "bullet.h"

HRESULT bullet::init()
{
	return S_OK;
}

void bullet::release()
{
}

void bullet::update()
{
	
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
		_viBullet->y += -sinf(_viBullet->angle) * _viBullet->speed;
		_viBullet->delay++;
		if (_viBullet->delay > 5)
		{
			_viBullet->index++;
			_viBullet->delay = 0;
		}
		if (_viBullet->index > 4)
		{
			_viBullet->index = 0;
		}

		_viBullet->rc = RectMakePivot(Vector2(_viBullet->x, _viBullet->y), Vector2(10, 10), Pivot::Center);

		if ((getDistance(_viBullet->x, _viBullet->y, _viBullet->sX, _viBullet->sY) > 1500))
		{
			_viBullet = _vBullet.erase(_viBullet);
		}
	}
}

void bullet::render()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->img->SetScale(1.5);
		_viBullet->img->FrameRender(Vector2(_viBullet->x, _viBullet->y), _viBullet->index, 0);
	}
}

void bullet::fire(float x, float y, float angle, float speed)
{
	if (80 < _vBullet.size()) return;
	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.img = ImageManager::GetInstance()->FindImage("bullet");
	bullet.speed = speed;
	bullet.x = bullet.sX = x;
	bullet.y = bullet.sY = y;
	bullet.angle = angle;

	bullet.rc = RectMakePivot(Vector2(bullet.x, bullet.y), Vector2(10, 10), Pivot::Center);
	_vBullet.push_back(bullet);


}

void bullet::remove(int arr)
{
	_vBullet.erase(_vBullet.begin() + arr);
}
