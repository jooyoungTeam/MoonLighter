#include "stdafx.h"
#include "shopNPC.h"

HRESULT shopNPC::init()
{
	// �̹���
	{
		_img = ImageManager::GetInstance()->AddFrameImage("npc1", L"Image/Shop/Guy.png", 8, 4);
		ImageManager::GetInstance()->AddImage("thinkBox", L"Image/Shop/thinkBox.png");
		_emotionImg = ImageManager::GetInstance()->AddFrameImage("thinking", L"Image/Shop/think.png", 3, 1);
		ImageManager::GetInstance()->AddFrameImage("TooCheap", L"Image/Shop/tooCheap.png", 13, 1);
		ImageManager::GetInstance()->AddFrameImage("Cheap", L"Image/Shop/Cheap.png", 4, 1);
		ImageManager::GetInstance()->AddFrameImage("TooExpensive", L"Image/Shop/tooExpensive.png", 9, 1);
		ImageManager::GetInstance()->AddFrameImage("Expensive", L"Image/Shop/expensive.png", 5, 1);
	}

	// ���� �Ҵ�
	{
		_aStar = new aStar;
		_item = new item;
	}

	// ���� �ʱ�ȭ
	{
		_centerX = 795;
		_centerY = 1180;
		_indexX = 0;
		_indexY = 3;
		_thinkBoxX = _centerX;
		_thinkBoxY = _centerY - 80;
		_emotionIndexX = 0;
		_frameTimer = 0;
		_delayTimer = 0;
		_emotionFrameTimer = 0;
		_angle = 0;
		_checkItemCount = 0;
		_rightPrice = 0;
		_selectPrice = 0;
		_settingPrice = 0;
		_rndChoiceItem = RND->getInt(4);
		_npcActionState = NPC_ENTER;
		_npcEmotionState = NPC_CHOOSE;
		_isBuy = false;
	}

	// �ʱ�ȭ �Լ�
	{
		unMoveSet();
		wayPointSet();
		chooseItem();
	}

	_aStar->init(WINSIZEX / 50, 1400 / 50, _centerX / 50, _centerY / 50 - 3, _goToPoint.x, _goToPoint.y, _vUnMove, true);
	_item->init(ITEMTYPE::CRYSTAL_ENERGY, _centerX, _centerY - 50);

	_rc = RectMakePivot(Vector2(_centerX, _centerY), Vector2(_img->GetFrameSize().x, _img->GetFrameSize().y), Pivot::Center);

	return S_OK;
}

void shopNPC::release()
{
}

void shopNPC::updadte()
{
	directionCheck();

	_aStar->update(_centerX / 50, _centerY / 50, _goToPoint.x, _goToPoint.y);
	_item->setItemPos(_centerX, _centerY - 50);
	_item->update();

	_thinkBoxX = _centerX;
	_thinkBoxY = _centerY - 80;


	// NPC �ൿ�� ���� ������Ʈ
	switch (_npcActionState)
	{
	case NPC_ENTER:
		frameUpdate();
		_angle = PI / 180 * 90;
		if (_centerY > 1000)
		{
			_centerY--;
		}
		else
		{
			_npcActionState = NPC_SHOPPING;
			_aStar->changeWayPoint();
		}
		break;
	case NPC_IDLE:
		
		break;

	case NPC_SHOPPING:
		frameUpdate();
		move();

		break;

	case NPC_CHECKITEM:
		emotionFrameUpdate();
		cout << _rndChoiceItem << endl;
		if (_rndChoiceItem == 0 || _rndChoiceItem == 2)
		{
			_indexX = 0;
			_indexY = 0;
		}
		else if (_rndChoiceItem == 1 || _rndChoiceItem == 3)
		{
			_indexX = 0;
			_indexY = 3;
		}

		_delayTimer++;

		if (_delayTimer > 100)
		{
			comparePrice();
		}

		if (_delayTimer > 300)
		{
			// ���������� BUY ���·� �ٲ��
			if (_isBuy)
			{
				_goToPoint = _counterPoint;
				_aStar->changeWayPoint();
				_npcActionState = NPC_BUY;
				break;
			}

			// �ƴϸ� �ٽ� ����
			if (_checkItemCount < 4)
				chooseItem();

			_npcActionState = NPC_SHOPPING;
			_delayTimer = 0;
		}
		break;
	case NPC_BUY:
		frameUpdate();
		move();

		break;
	case NPC_AWAY:

		break;
	}


	_rc = RectMakePivot(Vector2(_centerX, _centerY), Vector2(_img->GetFrameSize().x, _img->GetFrameSize().y), Pivot::Center);
}

void shopNPC::render()
{
	_aStar->render();

	CAMERAMANAGER->frameRender(_img, _centerX, _centerY, _indexX, _indexY, 1.2f, 1.f);

	if (_npcActionState == NPC_CHECKITEM)
	{
		CAMERAMANAGER->render(ImageManager::GetInstance()->FindImage("thinkBox"), _thinkBoxX, _thinkBoxY, 1.4f, 1.f);
		CAMERAMANAGER->frameRender(_emotionImg, _thinkBoxX + 18, _thinkBoxY + 17, _emotionIndexX, 0 , 1.4f,1.f);
	}

	if (_npcActionState == NPC_BUY)
	{
		_item->cameraRender();
	}

}

void shopNPC::frameUpdate()
{
	_frameTimer++;
	if (_frameTimer > 10)
	{

		_indexX++;

		if (_indexX > _img->GetMaxFrameX() - 1)
		{
			_indexX = 0;
		}
		_frameTimer = 0;
	}
}

void shopNPC::emotionFrameUpdate()
{
	_emotionFrameTimer++;

	switch (_npcEmotionState)
	{
	case NPC_CHOOSE:
		if (_emotionFrameTimer > 15)
		{
			_emotionIndexX++;

			if (_emotionIndexX > _emotionImg->GetMaxFrameX() - 1)
			{
				_emotionIndexX = 0;
			}
			_emotionFrameTimer = 0;
		}
		break;
	case NPC_TOO_EXPENSIVE:
	case NPC_EXPENSIVE:
	case NPC_CHEAP:
	case NPC_TOO_CHEAP:
		if (_emotionFrameTimer > 5)
		{
			if (_emotionIndexX < _emotionImg->GetMaxFrameX() - 1)
			{
				_emotionIndexX++;
			}

			_emotionFrameTimer = 0;
		}
		break;
	}
}

void shopNPC::move()
{
	if (_aStar->getVShortest().size() > 0)
	{
		_angle = getAngle(_centerX, _centerY, _aStar->getVShortest()[_aStar->getMoveIndex()]->center.x, _aStar->getVShortest()[_aStar->getMoveIndex()]->center.y);

		// �̵� ������
		_centerX += cosf(_angle);
		_centerY -= sinf(_angle);

		if (getDistance(_centerX, _centerY, _aStar->getVShortest()[_aStar->getMoveIndex()]->center.x, _aStar->getVShortest()[_aStar->getMoveIndex()]->center.y) < 1)
		{
			if (_aStar->getMoveIndex() > 0)
				_aStar->setMoveIndex(_aStar->getMoveIndex() - 1);
		}

		if (getDistance(_centerX, _centerY, _aStar->getVShortest()[0]->center.x, _aStar->getVShortest()[0]->center.y) < 3)
		{
			if (_npcActionState == NPC_SHOPPING)
			{
				_npcActionState = NPC_CHECKITEM;
				_npcEmotionState = NPC_CHOOSE;
				_emotionImg = _emotionImg = ImageManager::GetInstance()->FindImage("thinking");
				_emotionIndexX = 0;
			}
			else if (_npcActionState == NPC_BUY)
			{
				_npcActionState = NPC_AWAY;
			}
			else if (_npcActionState == NPC_AWAY)
			{

			}
		}
	}
}

void shopNPC::comparePrice()
{
	// �������� ���� �� �������� �����ͼ�. ���� ó��

	// ������ �������� �÷��̾� ���ð��� ���� ���ϱ�
	int tempPrice;
	tempPrice = _settingPrice - _rightPrice;

	// tempPrice�� ũ�⿡ ���� ó��

	// ��û ����
	if (tempPrice < -100)
	{
		_npcEmotionState = NPC_TOO_CHEAP;
		_emotionImg = ImageManager::GetInstance()->FindImage("TooCheap");
		_selectPrice = _settingPrice;
		_isBuy = true;
	}
	// ����
	else if (tempPrice >= -100 && tempPrice < -50)
	{
		_npcEmotionState = NPC_CHEAP;
		_emotionImg = ImageManager::GetInstance()->FindImage("Cheap");
		_selectPrice = _settingPrice;
		_isBuy = true;
	}
	// ���
	else if (tempPrice >= -50 && tempPrice < 100)
	{
		_npcEmotionState = NPC_EXPENSIVE;
		_emotionImg = ImageManager::GetInstance()->FindImage("Expensive");
		_selectPrice = 0;
	}
	// �ʹ� ���
	else if (tempPrice > 100)
	{
		_npcEmotionState = NPC_TOO_EXPENSIVE;
		_emotionImg = ImageManager::GetInstance()->FindImage("TooExpensive");
		_selectPrice = 0;
	}
}

void shopNPC::unMoveSet()
{
	POINT temp;

	temp.x = 10;
	temp.y = 19;
	_vUnMove.push_back(temp);

	temp.x = 10;
	temp.y = 18;
	_vUnMove.push_back(temp);

	temp.x = 10;
	temp.y = 17;
	_vUnMove.push_back(temp);

	temp.x = 11;
	temp.y = 19;
	_vUnMove.push_back(temp);

	temp.x = 11;
	temp.y = 18;
	_vUnMove.push_back(temp);

	temp.x = 11;
	temp.y = 17;
	_vUnMove.push_back(temp);

	temp.x = 12;
	temp.y = 19;
	_vUnMove.push_back(temp);

	temp.x = 12;
	temp.y = 18;
	_vUnMove.push_back(temp);

	temp.x = 12;
	temp.y = 17;
	_vUnMove.push_back(temp);

	temp.x = 13;
	temp.y = 19;
	_vUnMove.push_back(temp);

	temp.x = 13;
	temp.y = 18;
	_vUnMove.push_back(temp);

	temp.x = 13;
	temp.y = 17;
	_vUnMove.push_back(temp);
}

void shopNPC::wayPointSet()
{
	// ���� ù��° ������
	_itemWayPoint[0].x = 11;
	_itemWayPoint[0].y = 16;

	// ���� �ι�° ������
	_itemWayPoint[1].x = 11;
	_itemWayPoint[1].y = 20;

	// ������ ù��°������
	_itemWayPoint[2].x = 12;
	_itemWayPoint[2].y = 16;

	// ������ �ι�° ������
	_itemWayPoint[3].x = 12;
	_itemWayPoint[3].y = 20;

	// ����
	_counterPoint.x = 17;
	_counterPoint.y = 18;
}

void shopNPC::directionCheck()
{
	int DegAngle = _angle * 180 / PI; // ���� ��׸�(����)�� ��ȯ

	// ������ ����
	if ((DegAngle <= 45 && DegAngle >= 0) || (DegAngle <= 360 && DegAngle > 315))
	{
		_indexY = 2;
	}

	// ���� ����
	else if ((DegAngle <= 135 && DegAngle > 45))
	{
		_indexY = 3;
	}

	// ���� ����
	else if ((DegAngle <= 225 && DegAngle > 135))
	{
		_indexY = 1;
	}

	// �Ʒ��� ���� 
	else if ((DegAngle <= 315 && DegAngle > 225))
	{
		_indexY = 0;
	}

}

void shopNPC::chooseItem()
{
	// �ߺ� ���� (�� �� �������� ���ö� ���� ����)
	while (_checkItem[_rndChoiceItem])
	{
		_rndChoiceItem = RND->getInt(4);
	}

	// Ȯ���� ������ ���� �÷��ֱ�
	_checkItemCount++;

	switch (_rndChoiceItem)
	{
	case 0:
		_goToPoint = _itemWayPoint[0];
		_checkItem[0] = true;
		break;

	case 1:
		_goToPoint = _itemWayPoint[1];
		_checkItem[1] = true;
		break;

	case 2:
		_goToPoint = _itemWayPoint[2];
		_checkItem[2] = true;
		break;

	case 3:
		_goToPoint = _itemWayPoint[3];
		_checkItem[3] = true;
		break;
	}

	_aStar->changeWayPoint();
}
