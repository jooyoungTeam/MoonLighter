#include "stdafx.h"
#include "keyAniManager.h"
#include "image.h"
#include "animation.h"

keyAniManager::keyAniManager()
{
}


keyAniManager::~keyAniManager()
{
}

HRESULT keyAniManager::init()
{
	return S_OK;
}

void keyAniManager::release()
{
	//싸그리 해제해주자
	deleteAll();
}

void keyAniManager::update()
{
	for (int i = 0; i < _mTotalAnimation.size(); ++i)
	{
		iterAnimation iter = _mTotalAnimation[i].begin();

		for (iter; iter != _mTotalAnimation[i].end(); ++iter)
		{
			if (!iter->second->isPlay()) continue;
			
			iter->second->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f / _mTotalAnimation.size());
		}
	}

}

void keyAniManager::render()
{
}

void keyAniManager::addDefaultFrameAnimation(int index, string animationKeyName, const char * imageKeyName, int fps, bool reverse, bool loop)
{
	if (_mTotalAnimation.size() < index + 1)
	{
		arrAnimation* temp;
		temp = new arrAnimation;
		_mTotalAnimation.push_back(*temp);
	}

	Image* img = ImageManager::GetInstance()->FindImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->GetWidth(), img->GetHeight(), img->GetSize().x, img->GetSize().y);
	ani->setDefPlayFrame(reverse, loop);
	ani->setFPS(fps);

	_mTotalAnimation[index].insert(pair<string, animation*>(animationKeyName, ani));
}

void keyAniManager::addDefaultFrameAnimation(int index, string animationKeyName, const char * imageKeyName, int fps, bool reverse, bool loop, void * cbFunction)
{
	if (_mTotalAnimation.size() < index + 1)
	{
		arrAnimation* temp;
		temp = new arrAnimation;
		_mTotalAnimation.push_back(*temp);
	}

	Image* img = ImageManager::GetInstance()->FindImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->GetWidth(), img->GetHeight(), img->GetSize().x, img->GetSize().y);
	ani->setDefPlayFrame(reverse, loop, CALLBACK_FUNCTION(cbFunction));
	ani->setFPS(fps);

	_mTotalAnimation[index].insert(pair<string, animation*>(animationKeyName, ani));
}

void keyAniManager::addDefaultFrameAnimation(int index, string animationKeyName, const char * imageKeyName, int fps, bool reverse, bool loop, void * cbFunction, void * obj)
{
	if (_mTotalAnimation.size() < index + 1)
	{
		arrAnimation* temp;
		temp = new arrAnimation;
		_mTotalAnimation.push_back(*temp);
	}

	Image* img = ImageManager::GetInstance()->FindImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->GetWidth(), img->GetHeight(), img->GetSize().x, img->GetSize().y);
	ani->setDefPlayFrame(reverse, loop, CALLBACK_FUNCTION_PARAMETER(cbFunction), obj);
	ani->setFPS(fps);

	_mTotalAnimation[index].insert(pair<string, animation*>(animationKeyName, ani));
}

void keyAniManager::addArrayFrameAnimation(int index, string animationKeyName, const char * imageKeyName, int * arr, int arrLen, int fps, bool loop)
{
	if (_mTotalAnimation.size() < index + 1)
	{
		arrAnimation* temp;
		temp = new arrAnimation;
		_mTotalAnimation.push_back(*temp);
	}

	Image* img = ImageManager::GetInstance()->FindImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->GetWidth(), img->GetHeight(), img->GetSize().x, img->GetSize().y);
	ani->setPlayFrame(arr, arrLen, loop);
	ani->setFPS(fps);

	_mTotalAnimation[index].insert(pair<string, animation*>(animationKeyName, ani));
}

void keyAniManager::addArrayFrameAnimation(int index, string animationKeyName, const char * imageKeyName, int * arr, int arrLen, int fps, bool loop, void * cbFunction)
{
	if (_mTotalAnimation.size() < index + 1)
	{
		arrAnimation* temp;
		temp = new arrAnimation;
		_mTotalAnimation.push_back(*temp);
	}

	Image* img = ImageManager::GetInstance()->FindImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->GetWidth(), img->GetHeight(), img->GetSize().x, img->GetSize().y);
	ani->setPlayFrame(arr, arrLen, loop, CALLBACK_FUNCTION(cbFunction));
	ani->setFPS(fps);

	_mTotalAnimation[index].insert(pair<string, animation*>(animationKeyName, ani));
}

void keyAniManager::addArrayFrameAnimation(int index, string animationKeyName, const char * imageKeyName, int * arr, int arrLen, int fps, bool loop, void * cbFunction, void * obj)
{
	if (_mTotalAnimation.size() < index + 1)
	{
		arrAnimation* temp;
		temp = new arrAnimation;
		_mTotalAnimation.push_back(*temp);
	}

	Image* img = ImageManager::GetInstance()->FindImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->GetWidth(), img->GetHeight(), img->GetSize().x, img->GetSize().y);
	ani->setPlayFrame(arr, arrLen, loop, CALLBACK_FUNCTION_PARAMETER(cbFunction), obj);
	ani->setFPS(fps);

	_mTotalAnimation[index].insert(pair<string, animation*>(animationKeyName, ani));
}

void keyAniManager::addCoordinateFrameAnimation(int index, string animationKeyName, const char * imageKeyName, int start, int end, int fps, bool reverse, bool loop)
{
	if (_mTotalAnimation.size() < index + 1)
	{
		arrAnimation* temp;
		temp = new arrAnimation;
		_mTotalAnimation.push_back(*temp);
	}

	Image* img = ImageManager::GetInstance()->FindImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->GetWidth(), img->GetHeight(), img->GetSize().x, img->GetSize().y);
	ani->setPlayFrame(start, end, reverse, loop);
	ani->setFPS(fps);

	_mTotalAnimation[index].insert(pair<string, animation*>(animationKeyName, ani));
}

void keyAniManager::addCoordinateFrameAnimation(int index, string animationKeyName, const char * imageKeyName, int start, int end, int fps, bool reverse, bool loop, void * cbFunction)
{
	if (_mTotalAnimation.size() < index + 1)
	{
		arrAnimation* temp;
		temp = new arrAnimation;
		_mTotalAnimation.push_back(*temp);
	}

	Image* img = ImageManager::GetInstance()->FindImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->GetWidth(), img->GetHeight(), img->GetSize().x, img->GetSize().y);
	ani->setPlayFrame(start, end, reverse, loop, CALLBACK_FUNCTION(cbFunction));
	ani->setFPS(fps);

	_mTotalAnimation[index].insert(pair<string, animation*>(animationKeyName, ani));
}

void keyAniManager::addCoordinateFrameAnimation(int index, string animationKeyName, const char * imageKeyName, int start, int end, int fps, bool reverse, bool loop, void * cbFunction, void * obj)
{
	if (_mTotalAnimation.size() < index + 1)
	{
		arrAnimation* temp;
		temp = new arrAnimation;
		_mTotalAnimation.push_back(*temp);
	}

	Image* img = ImageManager::GetInstance()->FindImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->GetWidth(), img->GetHeight(), img->GetSize().x, img->GetSize().y);
	ani->setPlayFrame(start, end, reverse, loop, CALLBACK_FUNCTION_PARAMETER(cbFunction), obj);
	ani->setFPS(fps);

	_mTotalAnimation[index].insert(pair<string, animation*>(animationKeyName, ani));
}

void keyAniManager::start(int index, string animationKeyName)
{
	iterAnimation iter = _mTotalAnimation[index].find(animationKeyName);

	iter->second->start();
}

void keyAniManager::stop(int index, string animationKeyName)
{
	iterAnimation iter = _mTotalAnimation[index].find(animationKeyName);

	iter->second->stop();
}

void keyAniManager::pause(int index, string animationKeyName)
{
	iterAnimation iter = _mTotalAnimation[index].find(animationKeyName);

	iter->second->pause();
}

void keyAniManager::resume(int index, string animationKeyName)
{
	iterAnimation iter = _mTotalAnimation[index].find(animationKeyName);

	iter->second->resume();
}

animation * keyAniManager::findAnimation(int index, string animationKeyName)
{
	iterAnimation iter = _mTotalAnimation[index].find(animationKeyName);

	//찾았다면
	if (iter != _mTotalAnimation[index].end()) return iter->second;

	return nullptr;
}

void keyAniManager::deleteAll()
{
	for (int i = 0; i < _mTotalAnimation.size(); ++i)
	{
		for (iterAnimation iter = _mTotalAnimation[i].begin(); iter != _mTotalAnimation[i].end();)
		{
			if (iter->second != NULL)
			{
				iter->second->release();
				SAFE_DELETE(iter->second);
				iter = _mTotalAnimation[i].erase(iter);
			}
			else ++iter;
		}
		_mTotalAnimation[i].clear();
	}

	_mTotalAnimation.clear();

}
