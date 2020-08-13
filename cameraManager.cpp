#include "stdafx.h"
#include "cameraManager.h"

HRESULT cameraManager::init()
{
	_fade.fadeRect = RectMake(0, 0, WINSIZEX, WINSIZEY);
	return S_OK;
}

void cameraManager::release()
{
}

void cameraManager::settingCamera(float left, float top, float width, float height, float minL, float minT, float maxL, float maxT)
{
	_left = left;
	_top = top;
	_width = width;
	_height = height;

	_minLeft = minL;
	_minTop = minT;
	_maxLeft = maxL;
	_maxTop = maxT;

	_x = _left + (_width * 0.5f);
	_y = _top + (_height * 0.5f);
	_minX = _minLeft + (_width * 0.5f);
	_minY = _minTop + (_height * 0.5f);
	_maxX = _maxLeft + (_width * 0.5f);
	_maxY = _maxTop + (_height * 0.5f);
}

void cameraManager::zOrderClear()
{
	_vZorder.clear();
}

void cameraManager::zOrderRender(Image * img, float x, float y, float z, float alpha, float scale)
{
	tagZoder tempZorder;

	tempZorder.rendertype = renderType::RENDER;
	tempZorder.img = img;
	tempZorder.pt.x = x;
	tempZorder.pt.y = y;
	tempZorder.z = z;
	tempZorder.frame.x = NULL;
	tempZorder.frame.y = NULL;
	tempZorder.ani = NULL;
	tempZorder.alpha = alpha;
	tempZorder.scale = scale;
	_vZorder.push_back(tempZorder);
}

void cameraManager::zOrderFrameRender(Image * img, float x, float y, float z, float frmaeX, float frameY, float scale, float alpha)
{
	tagZoder tempZorder;

	tempZorder.rendertype = renderType::FRAME_RENDER;
	tempZorder.img = img;
	tempZorder.pt.x = x;
	tempZorder.pt.y = y;
	tempZorder.z = z;
	tempZorder.frame.x = frmaeX;
	tempZorder.frame.y = frameY;
	tempZorder.ani = NULL;
	tempZorder.alpha = alpha;
	tempZorder.scale = scale;

	_vZorder.push_back(tempZorder);
}


void cameraManager::zOrderAniRender(Image * img, float x, float y, float z, animation * ani, float scale)
{
	tagZoder tempZorder;

	tempZorder.rendertype = renderType::ANI_RENDER;
	tempZorder.img = img;
	tempZorder.pt.x = x;
	tempZorder.pt.y = y;
	tempZorder.z = z;
	tempZorder.frame.x = NULL;
	tempZorder.frame.y = NULL;
	tempZorder.ani = ani;
	tempZorder.alpha = NULL;
	tempZorder.scale = scale;

	_vZorder.push_back(tempZorder);
}

void cameraManager::zOrderSort(int i, int j)
{
	if (i >= j) return;

	float pivot = _vZorder[(i + j) / 2].z;
	int left = i;
	int right = j;

	while (left <= right)
	{
		while (_vZorder[left].z < pivot) left++;
		while (_vZorder[right].z > pivot) right--;
		if (left <= right)
		{
			swap(_vZorder[left], _vZorder[right]);
			left++; right--;
		}
	}


	zOrderSort(i, right);
	zOrderSort(left, j);
}

void cameraManager::zOrderALLRender()
{
	zOrderSort(0, _vZorder.size() - 1);

	for (int i = 0; i < _vZorder.size(); i++)
	{
		switch (_vZorder[i].rendertype)
		{
		case renderType::RENDER:
			render(_vZorder[i].img, _vZorder[i].pt.x, _vZorder[i].pt.y, _vZorder[i].scale, _vZorder[i].alpha);
			break;
		case renderType::FRAME_RENDER:
			frameRender(_vZorder[i].img, _vZorder[i].pt.x, _vZorder[i].pt.y, _vZorder[i].frame.x, _vZorder[i].frame.y, _vZorder[i].scale, _vZorder[i].alpha);
			break;
		case renderType::ANI_RENDER:
			aniRender(_vZorder[i].img, _vZorder[i].pt.x, _vZorder[i].pt.y, _vZorder[i].ani, _vZorder[i].scale);
			break;
		}
	}
	//cout << _vZorder.capacity() << endl;
	zOrderClear();
}

void cameraManager::fadeInOut(FADETYPE fade)
{
	_fade.fadeType = fade;
	_fade.fadeStart = true;
	if (_fade.fadeType == FADETYPE::FADEIN)
		_fade.fadeAlpha = 0;
	else
		_fade.fadeAlpha = 1;
}

void cameraManager::shakeCamera(int shakePower, int shakeTime)
{
	_shake.shakePower = shakePower;
	_shake.shakeTime = shakeTime;
	_shake.isShakeCamera = true;
}


void cameraManager::cameraUpdate()
{
	if (_shake.isShakeCamera)
	{
		_shake.shakeCount++;
		if (_shake.shakeCount % _shake.shakeTime == 0)
		{
			_shake.shakeCount = 0;
			_shake.isShakeCamera = false;
		}
	}
	if (_fade.fadeStart)
	{
		_fade.fadeTime++;
		if (_fade.fadeTime % 5 == 0)
		{
			_fade.fadeTime = 0;
			if (_fade.fadeType == FADETYPE::FADEIN)
			{
				_fade.fadeAlpha += 0.07f;
				//if (_fade.fadeAlpha >= 1)
				//	_fade.fadeStart = false;
			}
			else
			{
				_fade.fadeAlpha -= 0.07f;
				if (_fade.fadeAlpha <= 0)
					_fade.fadeStart = false;
			}
		}
	}
}

void cameraManager::fadeRender()
{
	if (_fade.fadeStart)
		D2DRenderer::GetInstance()->FillRectangle(_fade.fadeRect, D2D1::ColorF::Black, _fade.fadeAlpha);

}


void cameraManager::rectangle(const RECT rect, const D2D1::ColorF::Enum& color, float alpha, float strokeWidth)
{
	RECT rc;
	rc.left = getRelativeLeft(rect.left);
	rc.top = getRelativeTop(rect.top);
	rc.right = getRelativeLeft(rect.right);
	rc.bottom = getRelativeTop(rect.bottom);

	D2DRenderer::GetInstance()->DrawRectangle(rc, color, alpha, strokeWidth);
}

void cameraManager::rectangle(const FloatRect rect, const D2D1::ColorF::Enum& color, float alpha, float strokeWidth)
{
	FloatRect rc;
	rc.left = getRelativeLeft(rect.left);
	rc.top = getRelativeTop(rect.top);
	rc.right = getRelativeLeft(rect.right);
	rc.bottom = getRelativeTop(rect.bottom);

	D2DRenderer::GetInstance()->DrawRectangle(rc, color, alpha, strokeWidth);
}

void cameraManager::fillRectangle(const RECT rect, const D2D1::ColorF::Enum & color, float alpha)
{
	RECT rc;
	rc.left = getRelativeLeft(rect.left);
	rc.top = getRelativeTop(rect.top);
	rc.right = getRelativeLeft(rect.right);
	rc.bottom = getRelativeTop(rect.bottom);

	D2DRenderer::GetInstance()->FillRectangle(rc, color, alpha);
}

void cameraManager::fillRectangle(const FloatRect rect, const D2D1::ColorF::Enum & color, float alpha)
{
	FloatRect rc;
	rc.left = getRelativeLeft(rect.left);
	rc.top = getRelativeTop(rect.top);
	rc.right = getRelativeLeft(rect.right);
	rc.bottom = getRelativeTop(rect.bottom);

	D2DRenderer::GetInstance()->FillRectangle(rc, color, alpha);
}

void cameraManager::ellipse(float x, float y, const float radius, const D2D1::ColorF::Enum& color, const float alpha, const float strokeWidth)
{
	float relativeX = getRelativeLeft(x);
	float relativeY = getRelativeTop(y);
	D2DRenderer::GetInstance()->DrawEllipse(Vector2(relativeX, relativeY), radius, color, strokeWidth);
}

void cameraManager::line(Vector2 start, Vector2 end, const D2D1::ColorF::Enum & color, const float strokeWidth)
{
	float relativeX = getRelativeLeft(start.x);
	float relativeY = getRelativeTop(start.y);
	float relativeeX = getRelativeLeft(end.x);
	float relativeeY = getRelativeTop(end.y);
	D2DRenderer::GetInstance()->DrawLine(Vector2(relativeX, relativeY), Vector2(relativeeX, relativeeY), color, strokeWidth);
}

void cameraManager::render(Image * img, float destX, float destY, float alpha)
{
	float relativeLeft = getRelativeLeft(destX);
	float relativeTop = getRelativeTop(destY);
	img->SetAlpha(alpha);

	if (img) img->Render(Vector2(relativeLeft, relativeTop));
}


void cameraManager::render(Image * img, float destX, float destY, float scale, float alpha)
{
	float relativeLeft = getRelativeLeft(destX);
	float relativeTop = getRelativeTop(destY);
	img->SetAlpha(alpha);
	img->SetScale(scale);

	if (img) img->Render(Vector2(relativeLeft, relativeTop));
}



void cameraManager::frameRender(Image * img, float destX, float destY, int frameX, int frameY)
{
	float relativeLeft = getRelativeLeft(destX);
	float relativeTop = getRelativeTop(destY);

	if (img) img->FrameRender(Vector2(relativeLeft, relativeTop), frameX, frameY);
}

void cameraManager::frameRender(Image * img, float destX, float destY, int frameX, int frameY, float scale, float alpha)
{
	float relativeLeft = getRelativeLeft(destX);
	float relativeTop = getRelativeTop(destY);
	img->SetAlpha(alpha);
	img->SetScale(scale);

	if (img) img->FrameRender(Vector2(relativeLeft, relativeTop), frameX, frameY);
}

void cameraManager::setX(float relativeX)
{
	if (_shake.isShakeCamera)
	{
		int rnd = RND->getInt(2) == 1 ? -1 : 1;
		float newX = relativeX + rnd * _shake.shakePower;
		newX = min(_maxX, newX);
		newX = max(_minX, newX);
		if (newX == _minX)
		{
			if (rnd * _shake.shakePower <= 0)
				newX -= rnd * _shake.shakePower;
			else
				newX += rnd * _shake.shakePower;
		}
		else if (newX == _maxX)
		{
			if (rnd * _shake.shakePower <= 0)
				newX -= rnd * _shake.shakePower;
			else
				newX += rnd * _shake.shakePower;
		}
		_x = floor(newX);
		_left = _x - (_width * 0.5f);
	}
	else
	{
		relativeX = min(_maxX, relativeX);
		relativeX = max(_minX, relativeX);
		_x = floor(relativeX);
		_left = _x - (_width * 0.5f);
	}
}

void cameraManager::setY(float relativeY)
{
	if (_shake.isShakeCamera)
	{
		int rnd = RND->getInt(2) == 1 ? -1 : 1;
		float newY = relativeY + rnd * _shake.shakePower;
		newY = min(_maxY, newY);
		newY = max(_minY, newY);
		if (newY == _minY)
		{
			if (rnd * _shake.shakePower <= 0)
				newY -= rnd * _shake.shakePower;
			else
				newY += rnd * _shake.shakePower;
		}
		else if (newY == _maxY)
		{
			if (rnd * _shake.shakePower <= 0)
				newY -= rnd * _shake.shakePower;
			else
				newY += rnd * _shake.shakePower;
		}
		_y = floor(newY);
		_top = _y - (_height * 0.5f);
	}
	else
	{

		relativeY = min(_maxY, relativeY);
		relativeY = max(_minY, relativeY);
		_y = floor(relativeY);
		_top = _y - (_height * 0.5f);
	}
}

void cameraManager::setXY(float x, float y)
{
	setX(x);
	setY(y);
}


void cameraManager::aniRender(Image * img, int destX, int destY, animation * ani, float scale)
{
	Vector2 pos;
	pos.x = getRelativeLeft(destX);
	pos.y = getRelativeTop(destY);
	if (img) img->aniRender(pos, ani, scale);
}