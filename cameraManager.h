#pragma once
#include "singletonBase.h"
#include "image.h"

enum class renderType
{
	RENDER,
	FRAME_RENDER,
	ANI_RENDER,
};

struct tagZoder
{
	Image*     img;
	renderType rendertype;
	POINTFLOAT pt;
	float	   z;
	POINTFLOAT frame;
	animation* ani;
	float	   alpha;
	float      scale;
};

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

	vector<tagZoder> _vZorder;
	bool			 _isRect;


public:
	cameraManager() {}
	~cameraManager() {}
public:
	HRESULT init();
	void release();
public:
	void settingCamera(float left, float top, float width, float height, float minL, float minT, float maxL, float maxT);
public:
	void zOrderClear();
	// 제트오더 랜더 추가 ( 렌더 타입, 이미지, 중점 x, 중점 y)
	void zOrderRender(Image* img, float x, float y, float z,float alpha, float scale);
	// 제트오더 랜더 추가 ( 렌더 타입, 이미지, 중점 x, 중점 y, 프레임 x, 프레임 y)
	void zOrderFrameRender(Image* img, float x, float y, float z, float frmaeX, float frameY, float scale, float alpha);
	// 제트오더 랜더 추가 ( 렌더 타입, 이미지, 중점 x, 중점 y, 애니메이션)
	void zOrderAniRender(Image* img, float x, float y, float z, animation* ani,float scale);

	// 퀵 정렬 기반 Z-Order 정렬함수 (스테이지 매니저 or 각 스테이지 업데이트 부분에 넣을 것)
	void zOrderSort(int i, int j);

	// 랜더 함수 (랜더 부분에 넣을 것)
	void zOrderALLRender();

	int zOrderSize() { return _vZorder.size(); }

public:
	void rectangle(const RECT rect, const D2D1::ColorF::Enum& color, float alpha, float strokeWidth = 1.f);
	void rectangle(const FloatRect rect, const D2D1::ColorF::Enum& color, float alpha, float strokeWidth = 1.f);
	void fillRectangle(const RECT rect, const D2D1::ColorF::Enum& color, float alpha);
	void fillRectangle(const FloatRect rect, const D2D1::ColorF::Enum& color, float alpha);
	void ellipse(float x, float y, const float radius, const D2D1::ColorF::Enum& color, const float alpha, const float strokeWidth = 1.f);
	void render(Image* img, float destX, float destY, float alpha);
	void render(Image* img, float destX, float destY, float scale, float alpha);
	void frameRender(Image* img, float destX, float destY, int frameX, int frameY);
	void frameRender(Image* img, float destX, float destY, int frameX, int frameY, float scale, float alpha);
	void aniRender(Image * img, int destX, int destY, animation * ani, float scale);
public:
	float getLeft() { return _left; }
	float getTop() { return _top; }
	float getX() { return _x; }
	float getY() { return _y; }
	void  setX(float relativeX);
	void  setY(float relativeY);
	void  setXY(float x, float y);
public:
	float getRelativeLeft(float left) { float relativeLeft; return relativeLeft = left - _left; }
	float getRelativeTop(float top) { float relativeTop;  return relativeTop = top - _top; }

};

