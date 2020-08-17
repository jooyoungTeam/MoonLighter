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
	iterTotalAni vIter;
	iterAnimation mIter;
	
	for (vIter = _mTotalAnimation.begin() ; vIter != _mTotalAnimation.end() ; ++vIter)
	{
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			iterAnimations vArrIter;
			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{
				if (!(*vArrIter)->isPlay()) continue;
				(*vArrIter)->frameUpdate((TIMEMANAGER->getElapsedTime() * 1.0f));
			}
		}
	}

	
}

void keyAniManager::render()
{
}

void keyAniManager::addDefaultFrameAnimation(string animationKeyName, const char * imageKeyName, int fps, bool reverse, bool loop)
{
	iterTotalAni vIter;
	iterAnimation mIter;
	arrAnimations mAniBuffer;
	arrAnimation mArrAni;

	Image* img = ImageManager::GetInstance()->FindImage(imageKeyName);
	animation* ani = new animation;
	ani->init(img->GetWidth(), img->GetHeight(), img->GetSize().x, img->GetSize().y);
	ani->setDefPlayFrame(reverse, loop);
	ani->setFPS(fps);

	for (vIter = _mTotalAnimation.begin(); vIter != _mTotalAnimation.end(); ++vIter)
	{
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			if (mIter->first == animationKeyName)
			{
				mIter->second.push_back(ani);
				return;
			}
		}
	}
	mAniBuffer.push_back(ani);
	mArrAni.insert(pair<string, arrAnimations>(animationKeyName, mAniBuffer));

	_mTotalAnimation.push_back(mArrAni);
}

void keyAniManager::addDefaultFrameAnimation(string animationKeyName, const char * imageKeyName, int fps, bool reverse, bool loop, void * cbFunction)
{
	iterTotalAni vIter;
	iterAnimation mIter;
	arrAnimations mAniBuffer;
	arrAnimation mArrAni;

	Image* img = ImageManager::GetInstance()->FindImage(imageKeyName);
	animation* ani = new animation;
	ani->init(img->GetWidth(), img->GetHeight(), img->GetSize().x, img->GetSize().y);
	ani->setDefPlayFrame(reverse, loop, CALLBACK_FUNCTION(cbFunction));
	ani->setFPS(fps);

	for (vIter = _mTotalAnimation.begin(); vIter != _mTotalAnimation.end(); ++vIter)
	{
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			if (mIter->first == animationKeyName)
			{
				mIter->second.push_back(ani);
				return;
			}
		}
	}
	mAniBuffer.push_back(ani);
	mArrAni.insert(pair<string, arrAnimations>(animationKeyName, mAniBuffer));

	_mTotalAnimation.push_back(mArrAni);
}

void keyAniManager::addDefaultFrameAnimation(string animationKeyName, const char * imageKeyName, int fps, bool reverse, bool loop, void * cbFunction, void * obj)
{
	iterTotalAni vIter;
	iterAnimation mIter;
	arrAnimations mAniBuffer;
	arrAnimation mArrAni;

	Image* img = ImageManager::GetInstance()->FindImage(imageKeyName);
	animation* ani = new animation;
	ani->init(img->GetWidth(), img->GetHeight(), img->GetSize().x, img->GetSize().y);
	ani->setDefPlayFrame(reverse, loop, CALLBACK_FUNCTION_PARAMETER(cbFunction), obj);
	ani->setFPS(fps);

	for (vIter = _mTotalAnimation.begin(); vIter != _mTotalAnimation.end(); ++vIter)
	{
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			if (mIter->first == animationKeyName)
			{
				mIter->second.push_back(ani);
				return;
			}
		}
	}
	mAniBuffer.push_back(ani);
	mArrAni.insert(pair<string, arrAnimations>(animationKeyName, mAniBuffer));

	_mTotalAnimation.push_back(mArrAni);
}

void keyAniManager::addArrayFrameAnimation(string animationKeyName, const char * imageKeyName, int * arr, int arrLen, int fps, bool loop)
{
	iterTotalAni vIter;
	iterAnimation mIter;
	arrAnimations mAniBuffer;
	arrAnimation mArrAni;

	Image* img = ImageManager::GetInstance()->FindImage(imageKeyName);
	animation* ani = new animation;
	ani->init(img->GetWidth(), img->GetHeight(), img->GetSize().x, img->GetSize().y);
	ani->setPlayFrame(arr, arrLen, loop);
	ani->setFPS(fps);

	for (vIter = _mTotalAnimation.begin(); vIter != _mTotalAnimation.end(); ++vIter)
	{
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			if (mIter->first == animationKeyName)
			{
				mIter->second.push_back(ani);			
				return;
			}
		}
	}
	mAniBuffer.push_back(ani);
	mArrAni.insert(pair<string, arrAnimations>(animationKeyName, mAniBuffer));

	_mTotalAnimation.push_back(mArrAni);
}

void keyAniManager::addArrayFrameAnimation(string animationKeyName, const char * imageKeyName, int * arr, int arrLen, int fps, bool loop, void * cbFunction)
{
	iterTotalAni vIter;
	iterAnimation mIter;
	arrAnimations mAniBuffer;
	arrAnimation mArrAni;

	Image* img = ImageManager::GetInstance()->FindImage(imageKeyName);
	animation* ani = new animation;
	ani->init(img->GetWidth(), img->GetHeight(), img->GetSize().x, img->GetSize().y);
	ani->setPlayFrame(arr, arrLen, loop, CALLBACK_FUNCTION(cbFunction));
	ani->setFPS(fps);

	for (vIter = _mTotalAnimation.begin(); vIter != _mTotalAnimation.end(); ++vIter)
	{
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			if (mIter->first == animationKeyName)
			{
				mIter->second.push_back(ani);
				return;
			}
		}
	}
	mAniBuffer.push_back(ani);
	mArrAni.insert(pair<string, arrAnimations>(animationKeyName, mAniBuffer));

	_mTotalAnimation.push_back(mArrAni);
}

void keyAniManager::addArrayFrameAnimation(string animationKeyName, const char * imageKeyName, int * arr, int arrLen, int fps, bool loop, void * cbFunction, void * obj)
{
	iterTotalAni vIter;
	iterAnimation mIter;
	arrAnimations mAniBuffer;
	arrAnimation mArrAni;

	Image* img = ImageManager::GetInstance()->FindImage(imageKeyName);
	animation* ani = new animation;
	ani->init(img->GetWidth(), img->GetHeight(), img->GetSize().x, img->GetSize().y);
	ani->setPlayFrame(arr, arrLen, loop, CALLBACK_FUNCTION_PARAMETER(cbFunction), obj);
	ani->setFPS(fps);

	for (vIter = _mTotalAnimation.begin(); vIter != _mTotalAnimation.end(); ++vIter)
	{
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			if (mIter->first == animationKeyName)
			{
				mIter->second.push_back(ani);
				return;
			}
		}
	}
	mAniBuffer.push_back(ani);
	mArrAni.insert(pair<string, arrAnimations>(animationKeyName, mAniBuffer));

	_mTotalAnimation.push_back(mArrAni);
}

void keyAniManager::addCoordinateFrameAnimation(string animationKeyName, const char * imageKeyName, int start, int end, int fps, bool reverse, bool loop)
{
	iterTotalAni vIter;
	iterAnimation mIter;
	arrAnimations mAniBuffer;
	arrAnimation mArrAni;

	Image* img = ImageManager::GetInstance()->FindImage(imageKeyName);
	animation* ani = new animation;
	ani->init(img->GetWidth(), img->GetHeight(), img->GetSize().x, img->GetSize().y);
	ani->setPlayFrame(start, end, reverse, loop);
	ani->setFPS(fps);

	for (vIter = _mTotalAnimation.begin(); vIter != _mTotalAnimation.end(); ++vIter)
	{
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			if (mIter->first == animationKeyName)
			{
				mIter->second.push_back(ani);
				return;
			}
		}
	}
	mAniBuffer.push_back(ani);
	mArrAni.insert(pair<string, arrAnimations>(animationKeyName, mAniBuffer));

	_mTotalAnimation.push_back(mArrAni);
}

void keyAniManager::addCoordinateFrameAnimation(string animationKeyName, const char * imageKeyName, int start, int end, int fps, bool reverse, bool loop, void * cbFunction)
{
	iterTotalAni vIter;
	iterAnimation mIter;
	arrAnimations mAniBuffer;
	arrAnimation mArrAni;

	Image* img = ImageManager::GetInstance()->FindImage(imageKeyName);
	animation* ani = new animation;
	ani->init(img->GetWidth(), img->GetHeight(), img->GetSize().x, img->GetSize().y);
	ani->setPlayFrame(start, end, reverse, loop, CALLBACK_FUNCTION(cbFunction));
	ani->setFPS(fps);

	for (vIter = _mTotalAnimation.begin(); vIter != _mTotalAnimation.end(); ++vIter)
	{
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			if (mIter->first == animationKeyName)
			{
				mIter->second.push_back(ani);
				return;
			}
		}
	}
	mAniBuffer.push_back(ani);
	mArrAni.insert(pair<string, arrAnimations>(animationKeyName, mAniBuffer));

	_mTotalAnimation.push_back(mArrAni);
}

void keyAniManager::addCoordinateFrameAnimation(string animationKeyName, const char * imageKeyName, int start, int end, int fps, bool reverse, bool loop, void * cbFunction, void * obj)
{
	iterTotalAni vIter;
	iterAnimation mIter;
	arrAnimations mAniBuffer;
	arrAnimation mArrAni;

	Image* img = ImageManager::GetInstance()->FindImage(imageKeyName);
	animation* ani = new animation;
	ani->init(img->GetWidth(), img->GetHeight(), img->GetSize().x, img->GetSize().y);
	ani->setPlayFrame(start, end, reverse, loop, CALLBACK_FUNCTION_PARAMETER(cbFunction), obj);
	ani->setFPS(fps);

	for (vIter = _mTotalAnimation.begin(); vIter != _mTotalAnimation.end(); ++vIter)
	{
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			if (mIter->first == animationKeyName)
			{
				mIter->second.push_back(ani);
				return;
			}
		}
	}
	mAniBuffer.push_back(ani);
	mArrAni.insert(pair<string, arrAnimations>(animationKeyName, mAniBuffer));

	_mTotalAnimation.push_back(mArrAni);
}

//void keyAniManager::start(string animationKeyName)
//{
//	iterTotalAni vIter;
//	iterAnimation mIter;
//
//	for (vIter = _mTotalAnimation.begin(); vIter != _mTotalAnimation.end(); ++vIter)
//	{
//		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
//		{
//			if (mIter->first == animationKeyName)
//			{
//				if(!mIter->second->isPlay())
//					mIter->second->start();
//			}
//		}
//	}
//}
//
//void keyAniManager::stop(string animationKeyName)
//{
//	iterTotalAni vIter;
//	iterAnimation mIter;
//
//	for (vIter = _mTotalAnimation.begin(); vIter != _mTotalAnimation.end(); ++vIter)
//	{
//		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
//		{
//			if (mIter->first == animationKeyName)
//			{
//				if (!mIter->second->isPlay())
//					mIter->second->stop();
//			}
//		}
//	}
//}
//
//void keyAniManager::pause(string animationKeyName)
//{
//	iterTotalAni vIter;
//	iterAnimation mIter;
//
//	for (vIter = _mTotalAnimation.begin(); vIter != _mTotalAnimation.end(); ++vIter)
//	{
//		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
//		{
//			if (mIter->first == animationKeyName)
//			{
//				if (!mIter->second->isPlay())
//					mIter->second->pause();
//			}
//		}
//	}
//}
//
//void keyAniManager::resume(string animationKeyName)
//{
//	iterTotalAni vIter;
//	iterAnimation mIter;
//
//	for (vIter = _mTotalAnimation.begin(); vIter != _mTotalAnimation.end(); ++vIter)
//	{
//		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
//		{
//			if (mIter->first == animationKeyName)
//			{
//				if (!mIter->second->isPlay())
//					mIter->second->resume();
//			}
//		}
//	}
//}

animation * keyAniManager::findAnimation(string animationKeyName)
{
	iterTotalAni vIter;
	iterAnimation mIter;
	
	for (vIter = _mTotalAnimation.begin(); vIter != _mTotalAnimation.end(); ++vIter)
	{
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			if (mIter->first != animationKeyName) break;

			if (mIter->second.size() == 1)
			{
				return (*mIter->second.begin());
			}

			iterAnimations vArrIter;

			for(vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{
				if (!(*vArrIter)->isPlay())
				{
					return (*vArrIter);
				}
			}
		}
	}

	return nullptr;
}

void keyAniManager::deleteAll()
{
	iterTotalAni vIter;
	iterAnimation mIter;

	for (vIter = _mTotalAnimation.begin(); vIter != _mTotalAnimation.end(); ++vIter)
	{
		for (mIter = vIter->begin(); mIter != vIter->end();)
		{
			if (mIter->second.size() != NULL)
			{
				iterAnimations vArrIter = mIter->second.begin();

				for (; vArrIter != mIter->second.end();)
				{
					(*vArrIter)->release();
					delete *vArrIter;
					vArrIter = mIter->second.erase(vArrIter);
				}
			}
			else
				++mIter;
		}
	}
}
