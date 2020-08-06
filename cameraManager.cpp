#include "stdafx.h"
#include "cameraManager.h"

HRESULT cameraManager::init()
{
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
	_minTop  = minT;
	_maxLeft = maxL;
	_maxTop  = maxT;

	_x = _left + (_width * 0.5f);
	_y = _top  + (_height * 0.5f);
	_minX = _minLeft + (_width * 0.5f);
	_minY = _minTop  + (_height * 0.5f);
	_maxX = _maxLeft + (_width * 0.5f);
	_maxY = _maxTop  + (_height * 0.5f);
}

void cameraManager::rectangle(const RECT rect,const D2D1::ColorF::Enum& color, float alpha, float strokeWidth)
{
	RECT rc;
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

void cameraManager::ellipse(float x, float y, const float radius, const D2D1::ColorF::Enum& color, const float alpha, const float strokeWidth)
{
	float relativeX = getRelativeLeft(x);
	float relativeY = getRelativeTop(y);
	D2DRenderer::GetInstance()->DrawEllipse(Vector2(relativeX, relativeY), radius, color,strokeWidth);
}


void cameraManager::render(Image * img, float destX, float destY)
{
	float relativeLeft = getRelativeLeft(destX);
	float relativeTop = getRelativeTop(destY);

	if (img) img->Render(Vector2(relativeLeft, relativeTop));
}


void cameraManager::frameRender(Image * img, float destX, float destY, int frameX, int frameY)
{
	float relativeLeft = getRelativeLeft(destX);
	float relativeTop = getRelativeTop(destY);

	if (img) img->FrameRender(Vector2(relativeLeft, relativeTop),frameX,frameY);
}

void cameraManager::setX(float relativeX)
{
	relativeX = min(_maxX, relativeX);
	relativeX = max(_minX, relativeX);
	_x = floor(relativeX);
	_left = _x - (_width * 0.5f);
}

void cameraManager::setY(float relativeY)
{
	relativeY = min(_maxY, relativeY);
	relativeY = max(_minY, relativeY);
	_y = floor(relativeY);
	_top = _y - (_height * 0.5f);
}

