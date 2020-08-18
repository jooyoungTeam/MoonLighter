#include "stdafx.h"
#include "bullet.h"

HRESULT bullet::init(const char* imageName)
{
	_imageName = imageName;
	return S_OK;
}

void bullet::release()
{
}

void bullet::update()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
		_viBullet->y += -sinf(_viBullet->angle) * _viBullet->speed;
		_viBullet->delay++;
		if (_viBullet->delay > 5)
		{
			_viBullet->index++;
			_viBullet->delay = 0;
		}
		if (_viBullet->index > 5)
		{
			_viBullet->index = 0;
		}

		_viBullet->rc = RectMakePivot(Vector2(_viBullet->x, _viBullet->y), Vector2(10, 20), Pivot::Center);

		if ((getDistance(_viBullet->x, _viBullet->y, _viBullet->sX, _viBullet->sY) > 1500))
		{
			_viBullet = _vBullet.erase(_viBullet);
		}
		else
		{
			++_viBullet;
		}
	}
}

void bullet::potRender()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		CAMERAMANAGER->frameRender(_viBullet->img, _viBullet->x, _viBullet->y, _viBullet->index, 0);
		_viBullet->img->SetScale(2.5f);
		//_viBullet->img->FrameRender(Vector2(_viBullet->x, _viBullet->y), _viBullet->index, 0);
		//D2DRenderer::GetInstance()->DrawRectangle(_viBullet->rc, D2DRenderer::DefaultBrush::Yellow, 1.0f);
	}
}
void bullet::bossRender()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		CAMERAMANAGER->render(_viBullet->img, _viBullet->x, _viBullet->y, 1.0f);
		//_viBullet->img->SetScale(2.5f);
		//_viBullet->img->FrameRender(Vector2(_viBullet->x, _viBullet->y), _viBullet->index, 0);
		//D2DRenderer::GetInstance()->DrawRectangle(_viBullet->rc, D2DRenderer::DefaultBrush::Yellow, 1.0f);
	}
}

void bullet::fire(float x, float y, float angle, float speed)
{

	if (80 < _vBullet.size()) return;
	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.img = ImageManager::GetInstance()->FindImage(_imageName);
	bullet.speed = speed;
	bullet.x = bullet.sX = x;
	bullet.y = bullet.sY = y;
	bullet.angle = angle;

	bullet.rc = RectMakePivot(Vector2(bullet.x, bullet.y), Vector2(10, 10), Pivot::Center);
	_vBullet.push_back(bullet);




}

void bullet::manyFire(float x, float y, float angle, float speed, float bulletNum)
{
	for (int i = 0; i < bulletNum; ++i)
	{
		if (300 < _vBullet.size()) return;
		tagBullet bullet;
		ZeroMemory(&bullet, sizeof(tagBullet));
		bullet.img = ImageManager::GetInstance()->FindImage(_imageName);
		bullet.speed = speed;
		bullet.x = bullet.sX = x;
		bullet.y = bullet.sY = y;
		bullet.angle = angle + 0.3f *i;

		bullet.rc = RectMakePivot(Vector2(bullet.x, bullet.y), Vector2(10, 10), Pivot::Center);
		_vBullet.push_back(bullet);


	}
}

void bullet::PFire(float x, float y, float angle, float speed)
{
	if (80 < _vBullet.size()) return;
	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.img = ImageManager::GetInstance()->FindImage(_imageName);
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
