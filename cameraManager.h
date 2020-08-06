#pragma once
#include "singletonBase.h"
#include "image.h"
class cameraManager : public singletonBase<cameraManager>
{
private:
	float _left, _top;         // 카메라 left top 절대 좌표
	float _x, _y;              // 카메라 중점 좌표
	float _width, _height;     // 카메라 너비 높이
	float _minLeft, _maxLeft;  // 카메라 최소, 최대 left
	float _minTop, _maxTop;    // 카메라 최소, 최대 top
	float _minX, _maxX; 	   // 카메라 최소, 최대 x
	float _minY, _maxY; 	   // 카메라 최소, 최대 y

public:
	cameraManager() {}
	~cameraManager() {}
public:
	HRESULT init();
	void release();
public:
	void settingCamera(float left, float top, float width, float height, float minL, float minT, float maxL, float maxT);
public:

	void rectangle(const RECT rect, const D2D1::ColorF::Enum& color, float alpha, float strokeWidth = 1.f);
	void ellipse(float x, float y, const float radius, const D2D1::ColorF::Enum& color, const float alpha, const float strokeWidth = 1.f);
	void render(Image* img, float destX, float destY);
	void frameRender(Image* img, float destX, float destY, int frameX, int frameY);
public:
	float getLeft() { return _left; }
	float getTop() { return _top; }
	float getX() { return _x; }
	float getY() { return _y; }
	void  setX(float relativeX);
	void  setY(float relativeY);
public:
	float getRelativeLeft(float left) { float relativeLeft; return relativeLeft = left - _left; }
	float getRelativeTop(float top) { float relativeTop;  return relativeTop = top - _top; }

};

