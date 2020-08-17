#pragma once
#include "singletonBase.h"
#include <map>
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
class animation;
class Image;

class keyAniManager : public singletonBase<keyAniManager>
{
private:
	//»ý»ê
	typedef vector<animation*>				arrAnimations;
	typedef vector<animation*>::iterator	iterAnimations;

	typedef map<string, arrAnimations>				arrAnimation;
	typedef map<string, arrAnimations>::iterator	iterAnimation;

	typedef vector<map<string, arrAnimations>>				arrTotalAni;
	typedef vector<map<string, arrAnimations>>::iterator	    iterTotalAni;


private:
	arrTotalAni _mTotalAnimation;

public:
	keyAniManager();
	~keyAniManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void addDefaultFrameAnimation(string animationKeyName, const char* imageKeyName, int fps, bool reverse, bool loop);
	void addDefaultFrameAnimation(string animationKeyName, const char* imageKeyName, int fps, bool reverse, bool loop, void* cbFunction);
	void addDefaultFrameAnimation(string animationKeyName, const char* imageKeyName, int fps, bool reverse, bool loop, void* cbFunction, void* obj);

	void addArrayFrameAnimation(string animationKeyName, const char* imageKeyName, int* arr, int arrLen, int fps, bool loop);
	void addArrayFrameAnimation(string animationKeyName, const char* imageKeyName, int* arr, int arrLen, int fps, bool loop, void* cbFunction);
	void addArrayFrameAnimation(string animationKeyName, const char* imageKeyName, int* arr, int arrLen, int fps, bool loop, void* cbFunction, void* obj);

	void addCoordinateFrameAnimation(string animationKeyName, const char* imageKeyName, int start, int end, int fps, bool reverse, bool loop);
	void addCoordinateFrameAnimation(string animationKeyName, const char* imageKeyName, int start, int end, int fps, bool reverse, bool loop, void* cbFunction);
	void addCoordinateFrameAnimation(string animationKeyName, const char* imageKeyName, int start, int end, int fps, bool reverse, bool loop, void* cbFunction, void* obj);

	animation* findAnimation(string animationKeyName);

	void deleteAll();

};

