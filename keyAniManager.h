#pragma once
#include "singletonBase.h"
#include <map>
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
class animation;
class Image;

class keyAniManager : public singletonBase<keyAniManager>
{
private:
	typedef map<string, animation*>				arrAnimation;
	typedef map<string, animation*>::iterator	iterAnimation;

	typedef vector<arrAnimation>				arrTotalAni;
	typedef vector<arrAnimation>::iterator	    iterTotalAni;


private:
	arrTotalAni _mTotalAnimation;

public:
	keyAniManager();
	~keyAniManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void addDefaultFrameAnimation(int index, string animationKeyName, const char* imageKeyName, int fps, bool reverse, bool loop);
	void addDefaultFrameAnimation(int index, string animationKeyName, const char* imageKeyName, int fps, bool reverse, bool loop, void* cbFunction);
	void addDefaultFrameAnimation(int index, string animationKeyName, const char* imageKeyName, int fps, bool reverse, bool loop, void* cbFunction, void* obj);

	void addArrayFrameAnimation(int index, string animationKeyName, const char* imageKeyName, int* arr, int arrLen, int fps, bool loop);
	void addArrayFrameAnimation(int index, string animationKeyName, const char* imageKeyName, int* arr, int arrLen, int fps, bool loop, void* cbFunction);
	void addArrayFrameAnimation(int index, string animationKeyName, const char* imageKeyName, int* arr, int arrLen, int fps, bool loop, void* cbFunction, void* obj);

	void addCoordinateFrameAnimation(int index, string animationKeyName, const char* imageKeyName, int start, int end, int fps, bool reverse, bool loop);
	void addCoordinateFrameAnimation(int index, string animationKeyName, const char* imageKeyName, int start, int end, int fps, bool reverse, bool loop, void* cbFunction);
	void addCoordinateFrameAnimation(int index, string animationKeyName, const char* imageKeyName, int start, int end, int fps, bool reverse, bool loop, void* cbFunction, void* obj);

	void start(int index, string animationKeyName);
	void stop(int index, string animationKeyName);
	void pause(int index, string animationKeyName);
	void resume(int index, string animationKeyName);

	animation* findAnimation(int index, string animationKeyName);

	void deleteAll();

};

