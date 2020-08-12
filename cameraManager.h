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
	float _left, _top;         // ī�޶� left top ���� ��ǥ
	float _x, _y;              // ī�޶� ���� ��ǥ
	float _width, _height;     // ī�޶� �ʺ� ����
	float _minLeft, _maxLeft;  // ī�޶� �ּ�, �ִ� left
	float _minTop, _maxTop;    // ī�޶� �ּ�, �ִ� top
	float _minX, _maxX; 	   // ī�޶� �ּ�, �ִ� x
	float _minY, _maxY; 	   // ī�޶� �ּ�, �ִ� y

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
	// ��Ʈ���� ���� �߰� ( ���� Ÿ��, �̹���, ���� x, ���� y)
	void zOrderRender(Image* img, float x, float y, float z,float alpha, float scale);
	// ��Ʈ���� ���� �߰� ( ���� Ÿ��, �̹���, ���� x, ���� y, ������ x, ������ y)
	void zOrderFrameRender(Image* img, float x, float y, float z, float frmaeX, float frameY, float scale, float alpha);
	// ��Ʈ���� ���� �߰� ( ���� Ÿ��, �̹���, ���� x, ���� y, �ִϸ��̼�)
	void zOrderAniRender(Image* img, float x, float y, float z, animation* ani,float scale);

	// �� ���� ��� Z-Order �����Լ� (�������� �Ŵ��� or �� �������� ������Ʈ �κп� ���� ��)
	void zOrderSort(int i, int j);

	// ���� �Լ� (���� �κп� ���� ��)
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

