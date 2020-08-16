#include "stdafx.h"
#include "objectManager.h"

HRESULT objectManager::init()
{
	_leftRightButton[0] = RectMakeCenter(WINSIZEX - 321, 230, 70, 70);
	_leftRightButton[1] = RectMakeCenter(WINSIZEX - 220, 230, 70, 70);

	for (int i = 0; i < 4; i++)
	{
		_sampleObject[i].rc = RectMake(WINSIZEX - 505.0f + (i % 2) * 225, WINSIZEY * 0.5f - 70 + (i / 2) * 225, 225, 225);
	}

	return S_OK;
}

void objectManager::objectRender()
{
	for (int i = 0; i < _vObject.size(); i++) // 오브젝트들 렌더
	{
		if (CAMERAMANAGER->getLeft() > _vObject[i].rc.right || CAMERAMANAGER->getLeft() + WINSIZEX < _vObject[i].rc.left
			|| CAMERAMANAGER->getTop() > _vObject[i].rc.bottom || CAMERAMANAGER->getTop() + WINSIZEY < _vObject[i].rc.top) continue;

		if (_vObject[i].isFrameRender)
		{
			CAMERAMANAGER->zOrderFrameRender(findImg(_vObject[i].type, _vObject[i].imgNumber), (_vObject[i].rc.left + _vObject[i].rc.right) * 0.5f, (_vObject[i].rc.top + _vObject[i].rc.bottom) * 0.5f,
				_vObject[i].rc.bottom, _vObject[i].frameX, 0, _vObject[i].scale, 1);
			int frameCount = 0;
			_vObject[i].count++;
			_vObject[i].type == OBJ_NPC ? frameCount = 5 : frameCount = 10;
			if (_vObject[i].count % frameCount == 0)
			{
				_vObject[i].count = 0;
				_vObject[i].frameX++;

				if (findImg(_vObject[i].type, _vObject[i].imgNumber)->GetMaxFrameX() <= _vObject[i].frameX)
				{
					_vObject[i].frameX = 0;
				}
			}

		}
		else
		{
			CAMERAMANAGER->zOrderRender(findImg(_vObject[i].type, _vObject[i].imgNumber), _vObject[i].rc.left, _vObject[i].rc.top, _vObject[i].rc.bottom, 1, _vObject[i].scale);
		}
		//CAMERAMANAGER->render(_object[i]->img, _object[i]->rc.left, _object[i]->rc.top, 0.4f);
		//CAMERAMANAGER->rectangle(_object[i]->rc, D2D1::ColorF::LimeGreen, 1.0f, 5);
	}
	CAMERAMANAGER->zOrderALLRender();


}

void objectManager::currentObjectRender()
{
	if (_isSelectObject)
	{
		findImg(_currentObject.type, _currentObject.imgNumber)->SetAlpha(0.5f);
		if (_currentObject.isFrameRender)
		{
			_currentObject.rc = RectMakeCenter(_ptMouse.x, _ptMouse.y, findImg(_currentObject.type, _currentObject.imgNumber)->GetFrameSize().x *_currentObject.scale,
				findImg(_currentObject.type, _currentObject.imgNumber)->GetFrameSize().y * _currentObject.scale);
			findImg(_currentObject.type, _currentObject.imgNumber)->FrameRender(Vector2((_currentObject.rc.left + _currentObject.rc.right) * 0.5f, (_currentObject.rc.top + _currentObject.rc.bottom) * 0.5f), 1, 0, _currentObject.scale);
		}
		else
		{
			_currentObject.rc = RectMakeCenter(_ptMouse.x, _ptMouse.y, findImg(_currentObject.type, _currentObject.imgNumber)->GetWidth() * _currentObject.scale,
				findImg(_currentObject.type, _currentObject.imgNumber)->GetHeight() * _currentObject.scale);
			findImg(_currentObject.type, _currentObject.imgNumber)->Render(Vector2(_currentObject.rc.left, _currentObject.rc.top), _currentObject.scale);
		}

		D2DRenderer::GetInstance()->FillRectangle(_currentObject.rc, D2D1::ColorF::LimeGreen, 0.4f);
	}

}

void objectManager::sampleObjectPageRender()
{
	if (_currentSampleObject == OBJ_HOUSE)
	{
		ImageManager::GetInstance()->FindImage("objectHouse")->Render(Vector2(WINSIZEX - 505.0f, WINSIZEY * 0.5f - 70));
	}
	else if (_currentSampleObject == OBJ_ARCHITECTURE)
	{
		ImageManager::GetInstance()->FindImage("objectArchitecture")->Render(Vector2(WINSIZEX - 505.0f, WINSIZEY * 0.5f - 70));
	}
	else if (_currentSampleObject == OBJ_DOOR)
	{
		ImageManager::GetInstance()->FindImage("objectDoor")->Render(Vector2(WINSIZEX - 505.0f, WINSIZEY * 0.5f - 70));
	}
	else if (_currentSampleObject == OBJ_PLANT)
	{
		ImageManager::GetInstance()->FindImage("objectPlant")->Render(Vector2(WINSIZEX - 505.0f, WINSIZEY * 0.5f - 70));
	}
	else if (_currentSampleObject == OBJ_NPC)
	{
		ImageManager::GetInstance()->FindImage("objectNPC")->Render(Vector2(WINSIZEX - 505.0f, WINSIZEY * 0.5f - 70));
	}
	else if (_currentSampleObject == OBJ_SPA)
	{
		ImageManager::GetInstance()->FindImage("objectSpa")->Render(Vector2(WINSIZEX - 505.0f, WINSIZEY * 0.5f - 70));
	}
	else if (_currentSampleObject == OBJ_DUN1)
	{
		ImageManager::GetInstance()->FindImage("objectDungeon1")->Render(Vector2(WINSIZEX - 505.0f, WINSIZEY * 0.5f - 70));
	}
	else if (_currentSampleObject == OBJ_DUN2)
	{
		ImageManager::GetInstance()->FindImage("objectDungeon2")->Render(Vector2(WINSIZEX - 505.0f, WINSIZEY * 0.5f - 70));
	}
}

void objectManager::update()
{
}

void objectManager::release()
{
	_vObject.clear();
}

void objectManager::sampleObjectPage()
{
	for (int i = 0; i < 2; i++) // 왼쪽 오른쪽 버튼 눌렀을 때
	{
		if (PtInRect(&_leftRightButton[i], _ptMouse))
		{
			if (i == 0)
			{
				int num = (int)_currentSampleObject;
				num--;
				if (num < 0) num = 0;
				_currentSampleObject = (OBJECT)num;
			}
			else
			{
				int num = (int)_currentSampleObject;
				num++;
				if (num > (int)OBJ_NONE - 1) num = (int)OBJ_NONE - 1;
				_currentSampleObject = (OBJECT)num;
			}
			break;
		}
	}
}

void objectManager::save(BUTTONTYPE type)
{
	HANDLE file;
	DWORD write;
	const char* fileName;
	fileName = "";
	if (type == BUTTON_SAVE_TOWN)
		fileName = "townMap.object";
	else if (type == BUTTON_SAVE_BOSS)
		fileName = "boss.object";
	else if (type == BUTTON_SAVE_SHOP)
		fileName = "shop.object";
	else if (type == BUTTON_SAVE_DUNGEON)
		fileName = "dungeon1.object";
	else if (type == BUTTON_SAVE_ENTERENCE)
		fileName = "dungeonEnterence.object";

	// ----------------- 오브젝트 ----------------- //
	int size[2] = { 1,_vObject.size() };
	tagObject* temp = new tagObject[_vObject.size()];
	for (int i = 0; i < _vObject.size(); i++)
	{
		temp[i] = _vObject[i];
	}
	// ----------------- 오브젝트 ----------------- //
	file = CreateFile(fileName, GENERIC_WRITE, NULL, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, size, sizeof(int) * 2, &write, NULL);
	WriteFile(file, temp, sizeof(tagObject) * _vObject.size(), &write, NULL);


	CloseHandle(file);
}

void objectManager::load(BUTTONTYPE type)
{
	HANDLE file;
	DWORD read;
	int size[2];
	const char* fileName;
	fileName = "";
	if (type == BUTTON_LOAD_TOWN)
		fileName = "townMap.object";
	else if (type == BUTTON_LOAD_BOSS)
		fileName = "boss.object";
	else if (type == BUTTON_LOAD_SHOP)
		fileName = "shop.object";
	else if (type == BUTTON_LOAD_DUNGEON)
		fileName = "dungeon1.object";
	else if (type == BUTTON_LOAD_ENTERENCE)
		fileName = "dungeonEnterence.object";

	if (_vObject.size() > 0)
		_vObject.clear();

	file = CreateFile(fileName, GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, size, sizeof(int) * 2, &read, NULL);

	// ------------ 오브젝트		
	tagObject* temp = new tagObject[size[1]];
	ReadFile(file, temp, sizeof(tagObject) * size[1], &read, NULL);
	for (int i = 0; i < size[1]; i++)
	{
		_vObject.push_back(temp[i]);
	}

	CloseHandle(file);
}

void objectManager::setObject(POINT pt)
{
	if (_isSelectObject)
	{
		int w = (_currentObject.rc.right - _currentObject.rc.left) / 2;
		int h = (_currentObject.rc.bottom - _currentObject.rc.top) / 2;
		tagObject tempObject = _currentObject;
		tempObject.rc.left = pt.x - w;
		tempObject.rc.top = pt.y - h;
		tempObject.frameX = 0;

		if (tempObject.isFrameRender)
		{
			tempObject.rc.right = tempObject.rc.left + findImg(tempObject.type, tempObject.imgNumber)->GetFrameSize().x * tempObject.scale;
			tempObject.rc.bottom = tempObject.rc.top + findImg(tempObject.type, tempObject.imgNumber)->GetFrameSize().y * tempObject.scale;
		}
		else
		{
			tempObject.rc.right = tempObject.rc.left + findImg(tempObject.type, tempObject.imgNumber)->GetWidth() * tempObject.scale;
			tempObject.rc.bottom = tempObject.rc.top + findImg(tempObject.type, tempObject.imgNumber)->GetHeight() * tempObject.scale;
		}
		_vObject.push_back(tempObject);
		_isSelectObject = false;
	}
}

void objectManager::selectObject()
{
	for (int i = 0; i < 4; i++)
	{
		if (PtInRect(&_sampleObject[i].rc, _ptMouse))
		{
			_currentObject.scale = 1;
			_currentObject.type = _currentSampleObject;
			_isSelectObject = true;
			_currentObject.imgNumber = i;
			if (_currentSampleObject == OBJ_HOUSE)
			{
				_currentObject.isFrameRender = false;
				if (i == 0)
				{
					_currentObject.scale = 1.7f;
					_currentObject.isFrameRender = true;
				}

				else if (i == 2)
				{
					_currentObject.scale = 1.2f;
				}
				break;
			}

			else if (_currentSampleObject == OBJ_ARCHITECTURE)
			{
				_currentObject.isFrameRender = false;
				if (i == 2)
				{
					_currentObject.scale = 5.0f;
				}

				break;
			}
			else if (_currentSampleObject == OBJ_DOOR)
			{
				_currentObject.isFrameRender = false;
				break;
			}
			else if (_currentSampleObject == OBJ_PLANT)
			{
				_currentObject.isFrameRender = true;
				if (i == 0)
				{
					_currentObject.scale = 1.5f;
				}
				if (i == 1)
				{
					_currentObject.scale = 2.5f;
				}
				if (i == 2)
				{
					_currentObject.scale = 1.5f;
				}
				if (i == 3)
				{
					_currentObject.scale = 2.3f;
					_currentObject.isFrameRender = false;
				}

				break;
			}
			else if (_currentSampleObject == OBJ_NPC)
			{
				_currentObject.isFrameRender = true;
				break;
			}
			else if (_currentSampleObject == OBJ_SPA)
			{
				_currentObject.isFrameRender = false;
				break;
			}
			else if (_currentSampleObject == OBJ_DUN1)
			{
				_currentObject.isFrameRender = false;
				break;
			}
			else if (_currentSampleObject == OBJ_DUN2)
			{
				_currentObject.isFrameRender = false;
				if (i == 1)
				{
					_currentObject.scale = 2.0f;
				}
				break;
			}
		}

	}
}

void objectManager::eraseObject(POINT pt)
{
	for (int i = 0; i < _vObject.size(); i++)
	{
		if (PtInRect(&_vObject[i].rc, pt))
		{
			_vObject.erase(_vObject.begin() + i);
			break;
		}
	}
}

Image * objectManager::findImg(OBJECT type, int imgNum)
{
	Image* img = ImageManager::GetInstance()->FindImage("plant_tree1");
	if (type == OBJ_HOUSE)
	{
		if (imgNum == 0)			         img = ImageManager::GetInstance()->FindImage("Object_build_Bottom1");
		else if (imgNum == 1)		         img = ImageManager::GetInstance()->FindImage("build_Bottom2");
		else if (imgNum == 2)		         img = ImageManager::GetInstance()->FindImage("build_Shop");
		else if (imgNum == 3)		         img = ImageManager::GetInstance()->FindImage("build_Enchant");

	}
	else if (type == OBJ_ARCHITECTURE)
	{
		if (imgNum == 0)			         img = ImageManager::GetInstance()->FindImage("build_Well");
		else if (imgNum == 1)		         img = ImageManager::GetInstance()->FindImage("buildBoard");
		else if (imgNum == 2)		         img = ImageManager::GetInstance()->FindImage("build_fountain");
		else if (imgNum == 3)		         img = ImageManager::GetInstance()->FindImage("bench");
	}
	else if (type == OBJ_DOOR)
	{
		if (imgNum == 0)					 img = ImageManager::GetInstance()->FindImage("object_door1");
		else if (imgNum == 1)				 img = ImageManager::GetInstance()->FindImage("object_door2");
		else if (imgNum == 2)				 img = ImageManager::GetInstance()->FindImage("object_door3");
		else if (imgNum == 3)				 img = ImageManager::GetInstance()->FindImage("object_door4");
	}
	else if (type == OBJ_PLANT)
	{

		if (imgNum == 0)			          img = ImageManager::GetInstance()->FindImage("plant_tree1");
		else if (imgNum == 1)		          img = ImageManager::GetInstance()->FindImage("plant_fountain1");
		else if (imgNum == 2)		          img = ImageManager::GetInstance()->FindImage("plant_tree2");
		else if (imgNum == 3)		          img = ImageManager::GetInstance()->FindImage("plant_flower");
	}
	else if (type == OBJ_NPC)
	{
		if (imgNum == 0)		              img = ImageManager::GetInstance()->FindImage("npc_1");
		else if (imgNum == 1)	              img = ImageManager::GetInstance()->FindImage("npc_2");
		else if (imgNum == 2)	              img = ImageManager::GetInstance()->FindImage("npc_3");
		else if (imgNum == 3)	              img = ImageManager::GetInstance()->FindImage("npc_4");
	}
	else if (type == OBJ_SPA)
	{
		if (imgNum == 0 || imgNum == 1 || imgNum == 2 || imgNum == 3)			img = ImageManager::GetInstance()->FindImage("spa");

	}
	else if (type == OBJ_DUN1)
	{
		if (imgNum == 0)		              img = ImageManager::GetInstance()->FindImage("object_skull1");
		else if (imgNum == 1)	              img = ImageManager::GetInstance()->FindImage("object_skull2");
		else if (imgNum == 2)	              img = ImageManager::GetInstance()->FindImage("object_skull3");
		else if (imgNum == 3)	              img = ImageManager::GetInstance()->FindImage("object_pot");
	}
	else if (type == OBJ_DUN2)
	{
		if (imgNum == 0)		              img = ImageManager::GetInstance()->FindImage("object_pot_slime");
		else if (imgNum == 1)	              img = ImageManager::GetInstance()->FindImage("object_pillar");
		else if (imgNum == 2)	              img = ImageManager::GetInstance()->FindImage("object_smallRock");
		else if (imgNum == 3)	              img = ImageManager::GetInstance()->FindImage("object_smallRock_slime");
	}

	return img;
}
