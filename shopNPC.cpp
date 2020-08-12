#include "stdafx.h"
#include "shopNPC.h"

HRESULT shopNPC::init()
{
	_img = ImageManager::GetInstance()->AddFrameImage("npc1", L"Image/Shop/Guy.png", 8, 4);

	_centerX = 795;
	_centerY = 1180;

	unMoveSet();
	wayPointSet();

	_aStar = new aStar;

	//_centerY = 1000;

	_angle = 0;
	_checkItemCount = 0;

	_npcActionState = NPC_ENTER;

	_indexX = 0;
	_indexY = 3;

	_rndChoiceItem = RND->getInt(4);
	chooseItem();

	_aStar->init(WINSIZEX / 50, 1400 / 50, _centerX / 50, _centerY / 50 - 3, _goToPoint.x, _goToPoint.y, _vUnMove, true);


	return S_OK;
}

void shopNPC::release()
{
}

void shopNPC::updadte()
{
	_aStar->update(_centerX / 50, _centerY / 50, _goToPoint.x, _goToPoint.y);

	directionCheck();


	switch (_npcActionState)
	{
	case NPC_ENTER:
		if (_centerY > 1000)
		{
			_centerY--;
		}
		else
		{
			_npcActionState = NPC_SHOPPING;
		}
		break;
	case NPC_IDLE:
		
		break;

	case NPC_SHOPPING:

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

				_npcActionState = NPC_CHECKITEM;
				if(_checkItemCount < 4)
					chooseItem();
			}
		}
		break;

	case NPC_CHECKITEM:
		_delayTimer++;
	

		if (_delayTimer > 200)
		{
			_npcActionState = NPC_SHOPPING;
			_delayTimer = 0;
		}
		break;
	case NPC_BUY:

		break;
	case NPC_AWAY:

		break;
	}

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

void shopNPC::render()
{
	_aStar->render();

	CAMERAMANAGER->frameRender(_img, _centerX, _centerY, _indexX, _indexY, 1.2f, 1.f);
}

void shopNPC::comparePrice()
{
	// �������� ���� �� �������� �����ͼ�. ���� ó��

}

void shopNPC::unMoveSet()
{
	POINT temp;

	temp.x = 8;
	temp.y = 21;
	_vUnMove.push_back(temp);

	temp.x = 8;
	temp.y = 20;
	_vUnMove.push_back(temp);

	temp.x = 8;
	temp.y = 19;
	_vUnMove.push_back(temp);

	temp.x = 8;
	temp.y = 18;
	_vUnMove.push_back(temp);

	temp.x = 8;
	temp.y = 17;
	_vUnMove.push_back(temp);

	temp.x = 8;
	temp.y = 16;
	_vUnMove.push_back(temp);

	temp.x = 8;
	temp.y = 15;
	_vUnMove.push_back(temp);

	temp.x = 8;
	temp.y = 14;
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
	_counterPoint.x = 20;
	_counterPoint.y = 16;
}

void shopNPC::directionCheck()
{
	float DegAngle = _angle * 180 / PI; // ���� ��׸�(����)�� ��ȯ

	// ������ ����
	if ((DegAngle <= 45 && DegAngle > 0) || (DegAngle <= 360 && DegAngle > 315))
	{
		_indexY = 2;
	}

	// ���� ����
	if ((DegAngle <= 135 && DegAngle > 45))
	{
		_indexY = 3;
	}

	// ���� ����
	if ((DegAngle <= 225 && DegAngle > 135))
	{
		_indexY = 1;
	}

	// �Ʒ��� ���� 
	if ((DegAngle <= 315 && DegAngle > 225))
	{
		_indexY = 0;
	}

}

void shopNPC::chooseItem()
{
	// 4���� �������� ���� ���� �� ����
	if (_checkItemCount > 4) return;

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
