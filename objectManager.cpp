#include "stdafx.h"
#include "objectManager.h"

HRESULT objectManager::init()
{


	return S_OK;
}

void objectManager::render()
{
	for (int i = 0; i < _vObject.size(); i++) // 오브젝트들 렌더
	{
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

void objectManager::update()
{
}

void objectManager::release()
{
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
		fileName = "dungeon3.object";
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
		fileName = "dungeon3.object";
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

void objectManager::setObject(POINT pt, tagObject object)
{
	int w = (object.rc.right - object.rc.left) / 2;
	int h = (object.rc.bottom - object.rc.top) / 2;
	tagObject tempObject = object;
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
}

void objectManager::selectObject(tagObject& object, OBJECT type, int imgNumber)
{
	object.scale = 1;
	object.type = type;
	object.imgNumber = imgNumber;
	if (type == OBJ_HOUSE)
	{
		object.isFrameRender = false;
		if (imgNumber == 0)
		{
			object.scale = 1.7f;
			object.isFrameRender = true;
		}

		else if (imgNumber == 2)
		{
			object.scale = 1.2f;
		}
		return;
	}

	else if (type == OBJ_ARCHITECTURE)
	{
		object.isFrameRender = false;
		if (imgNumber == 2)
		{
			object.scale = 5.0f;
		}
		return;

	}
	else if (type == OBJ_DOOR)
	{
		object.isFrameRender = false;

		return;
	}
	else if (type == OBJ_PLANT)
	{
		object.isFrameRender = true;
		if (imgNumber == 0)
		{
			object.scale = 1.5f;
		}
		if (imgNumber == 1)
		{
			object.scale = 2.5f;
		}
		if (imgNumber == 2)
		{
			object.scale = 1.5f;
		}
		if (imgNumber == 3)
		{
			object.scale = 2.3f;
			object.isFrameRender = false;
		}

		return;
	}
	else if (type == OBJ_NPC)
	{
		object.isFrameRender = true;
		return;

	}
	else if (type == OBJ_SPA)
	{
		object.isFrameRender = false;
		return;

	}
	else if (type == OBJ_DUN1)
	{
		object.isFrameRender = false;
		return;
		
	}
	else if (type == OBJ_DUN2)
	{
		object.isFrameRender = false;
		if (imgNumber == 1)
		{
			object.scale = 2.0f;
		}
		return;
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
