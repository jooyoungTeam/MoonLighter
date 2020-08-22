#include "stdafx.h"
#include "shopNPC.h"
#include "display.h"

HRESULT shopNPC::init(npcType type, vector<POINT> vUnMove)
{

	_emotionImg = ImageManager::GetInstance()->FindImage("thinking");

	switch (type)
	{
	case NPC_NOMAL:
		_img = ImageManager::GetInstance()->FindImage("npc1");
		break;
	case NPC_HERO:
		_img = ImageManager::GetInstance()->FindImage("npc2");
		break;
	case NPC_RICH:
		_img = ImageManager::GetInstance()->FindImage("npc3");
		break;
	}
	// 테스트

	// 동적 할당
	{
		_aStar = new aStar;
	}

	// 변수 초기화
	{
		_centerX = 870;
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
		_oldRndChoiceItem = -1;
		_npcActionState = NPC_ENTER;
		_npcEmotionState = NPC_EMOTION_NULL;
		_npcType = type;
		_isBuy = false;
		_vUnMove = vUnMove;
	}

	// 초기화 함수
	{
		//unMoveSet();
		wayPointSet();
		//chooseItem();
	}

	_aStar->init(WINSIZEX / 50, 1400 / 50, _centerX / 50, _centerY / 50 - 3, _goToPoint.x, _goToPoint.y, _vUnMove, true);

	_rc = RectMakePivot(Vector2(_centerX, _centerY), Vector2(_img->GetFrameSize().x, _img->GetFrameSize().y), Pivot::Center);


	return S_OK;
}

void shopNPC::release()
{
}

void shopNPC::updadte()
{
	for (int i = 0; i < 4; ++i)
	{
		if (INVENTORY->getShowCase()[i*2].item != NULL)
		{
			_isExist = true;
			break;
		}

		if (i == 4)
			_isExist = false;
	}

	_aStar->update(_centerX / 50, _centerY / 50, _goToPoint.x, _goToPoint.y);

	_thinkBoxX = _centerX;
	_thinkBoxY = _centerY - 80;


	// NPC 행동에 따른 업데이트
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
			if (_isExist)
			{
				chooseItem();
			}
			else
			{
				choosePt();
			}
		}
		break;

	case NPC_IDLE:
		_delayTimer++;
		if (_delayTimer > 100)
		{
			if (_checkItemCount < 4 && _isExist)
			{
				if (_idleCount > 3)
				{
					_npcActionState = NPC_AWAY;
					_goToPoint = _eixtPoint;
					_aStar->changeWayPoint();
					break;
				}
				chooseItem();
			}
			else
			{
				_npcActionState = NPC_AWAY;
				_goToPoint = _eixtPoint;
				_aStar->changeWayPoint();
			}
			_delayTimer = 0;
		}
		break;

	case NPC_WALK:
		frameUpdate();
		move();
		break;

	case NPC_SHOPPING:
		frameUpdate();
		move();
		break;

	case NPC_CHECKITEM:
		emotionFrameUpdate();
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
			// 구매했으면 BUY 상태로 바꿔라
			if (_isBuy)
			{
				_goToPoint = _counterPoint;
				_aStar->changeWayPoint();
				_npcActionState = NPC_BUY;
				_delayTimer = 0;
			}
			// 아니면 다시 쇼핑
			else
			{
				if (_delayTimer > 290 && _delayTimer < 292)
				{
					INVENTORY->getShowCase()[_oldRndChoiceItem * 2].isPeople = false;
				}
				if (_delayTimer > 300)
				{
					if (_checkItemCount < 4 && _isExist)
					{
						chooseItem();
					}
					else if (_checkItemCount < 4 && !_isExist)
					{
						choosePt();
					}
					_delayTimer = 0;
				}
			}
		}		
		break;
	case NPC_BUY:
		_delayTimer++;
		emotionFrameUpdate();
		_isBuy = false;
		if (_delayTimer < 200)
		{
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
		}
		if (_delayTimer > 199 && _delayTimer <= 200)
		{
			_itemImg = INVENTORY->getShowCase()[_oldRndChoiceItem * 2].item->getImg();
			INVENTORY->resetShowCase(_oldRndChoiceItem * 2);
			
		}
		if (_delayTimer > 200)
		{
			_npcEmotionState = NPC_EMOTION_NULL;
			INVENTORY->getShowCase()[_oldRndChoiceItem * 2].isPeople = false;
			frameUpdate();
			move();
		}
		break;
	case NPC_AWAY:
		frameUpdate();
		move();
		_delayTimer = 0;
		break;
	}


	_rc = RectMakePivot(Vector2(_centerX, _centerY), Vector2(50, 50), Pivot::Center);

}

void shopNPC::render()
{
	_aStar->render();

	if (_npcType == NPC_HERO)
	{
		CAMERAMANAGER->zOrderFrameRender(_img, _centerX, _centerY, _rc.bottom, _indexX, _indexY, 0.7f, 1.f);
	}
	else
	{
		CAMERAMANAGER->zOrderFrameRender(_img, _centerX, _centerY, _rc.bottom, _indexX, _indexY, 1.2f, 1.f);
	}
	//CAMERAMANAGER->rectangle(_rc, D2D1::ColorF::Green, 1.f, 2.f);

	if (_npcEmotionState != NPC_EMOTION_NULL)
	{
		CAMERAMANAGER->zOrderRender(ImageManager::GetInstance()->FindImage("thinkBox"), _thinkBoxX, _thinkBoxY, _rc.bottom + _thinkBoxY, 1.f, 1.4f);
		CAMERAMANAGER->zOrderFrameRender(_emotionImg, _thinkBoxX + 18, _thinkBoxY + 17, _rc.bottom + _thinkBoxY + 17, _emotionIndexX, 0 , 1.4f,1.f);
	}

	if (_npcActionState == NPC_BUY && _itemImg != NULL)
		CAMERAMANAGER->zOrderRender(_itemImg, _rc.left + _itemImg->GetWidth()/2, _rc.top - 15,_rc.bottom + 10, 1.f,1.f);
	
	if (KEYMANAGER->isToggleKey('V'))
	{
		CAMERAMANAGER->rectangle(_rc, D2D1::ColorF::Blue, 1.f, 2.f);
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
		if (_emotionFrameTimer > 5)
		{
			if (_emotionIndexX == 0)
			{
				SOUNDMANAGER->play("shop_too_expensive", 1.f);
			}

			if (_emotionIndexX < _emotionImg->GetMaxFrameX() - 1)
			{
				_emotionIndexX++;
			}

			_emotionFrameTimer = 0;
		}
		break;
	case NPC_EXPENSIVE:
		if (_emotionFrameTimer > 5)
		{
			if (_emotionIndexX == 0)
			{
				SOUNDMANAGER->play("shop_expensive", 1.f);
			}

			if (_emotionIndexX < _emotionImg->GetMaxFrameX() - 1)
			{
				_emotionIndexX++;
			}

			_emotionFrameTimer = 0;
		}
		break;
	case NPC_CHEAP:
		if (_emotionFrameTimer > 5)
		{
			if (_emotionIndexX == 0)
			{
				SOUNDMANAGER->play("shop_cheap", 1.f);
			}

			if (_emotionIndexX < _emotionImg->GetMaxFrameX() - 1)
			{
				_emotionIndexX++;
			}

			_emotionFrameTimer = 0;
		}
		break;
	case NPC_TOO_CHEAP:
		if (_emotionFrameTimer > 5)
		{
			if (_emotionIndexX == 0)
			{
				SOUNDMANAGER->play("shop_too_cheap", 1.f);
			}

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
	directionCheck();
	if (_aStar->getVShortest().size() > 0)
	{
		_angle = getAngle(_centerX, _centerY, _aStar->getVShortest()[_aStar->getMoveIndex()]->center.x, _aStar->getVShortest()[_aStar->getMoveIndex()]->center.y);

		// 이동 시켜줌
		_centerX += cosf(_angle);
		_centerY -= sinf(_angle);

		if (getDistance(_centerX, _centerY, _aStar->getVShortest()[_aStar->getMoveIndex()]->center.x, _aStar->getVShortest()[_aStar->getMoveIndex()]->center.y) < 1)
		{
			if (_aStar->getMoveIndex() > 0)
				_aStar->setMoveIndex(_aStar->getMoveIndex() - 1);
		}

		if (getDistance(_centerX, _centerY, _aStar->getVShortest()[0]->center.x, _aStar->getVShortest()[0]->center.y) < 1)
		{
			if (_npcActionState == NPC_WALK)
			{
				_npcActionState = NPC_IDLE;
			}
			if (_npcActionState == NPC_SHOPPING)
			{
				_npcActionState = NPC_CHECKITEM;
				_npcEmotionState = NPC_CHOOSE;
				_emotionImg = _emotionImg = ImageManager::GetInstance()->FindImage("thinking");
				_emotionIndexX = 0;
			}
			else if (_npcActionState == NPC_BUY)
			{
				INVENTORY->setGold(_settingPrice);
				_isCount = true;
				_npcActionState = NPC_AWAY;
				_goToPoint = _eixtPoint;
				_aStar->changeWayPoint();
			}
			else if (_npcActionState == NPC_AWAY)
			{
				_isAway = true;
			}
		}
	}
}

void shopNPC::comparePrice()
{
	// 아이템의 정보 중 적정가를 가져와서. 비교후 처리

	// 아이템 적정가와 플레이어 셋팅가격 차이 구하기
	int tempPrice;
	tempPrice = _settingPrice - _rightPrice;

	// tempPrice의 크기에 따른 처리

	// 엄청 저렴
	if (tempPrice < -100)
	{
		_npcEmotionState = NPC_TOO_CHEAP;
		_emotionImg = ImageManager::GetInstance()->FindImage("TooCheap");
		_selectPrice = _settingPrice;
		_isBuy = true;
	}
	// 저렴
	else if (tempPrice >= -100 && tempPrice < -50)
	{
		_npcEmotionState = NPC_CHEAP;
		_emotionImg = ImageManager::GetInstance()->FindImage("Cheap");
		_selectPrice = _settingPrice;
		_isBuy = true;
	}
	// 비쌈
	else if (tempPrice >= -50 && tempPrice < 100)
	{
		_npcEmotionState = NPC_EXPENSIVE;
		_emotionImg = ImageManager::GetInstance()->FindImage("Expensive");
		_selectPrice = 0;
	}
	// 너무 비쌈
	else if (tempPrice > 100)
	{
		_npcEmotionState = NPC_TOO_EXPENSIVE;
		_emotionImg = ImageManager::GetInstance()->FindImage("TooExpensive");
		_selectPrice = 0;
	}
}


void shopNPC::wayPointSet()
{
	// 왼쪽 첫번째 아이템
	_itemWayPoint[0].x = 12;
	_itemWayPoint[0].y = 16;

	// 왼쪽 두번째 아이템
	_itemWayPoint[1].x = 12;
	_itemWayPoint[1].y = 20;

	// 오른쪽 첫번째아이템
	_itemWayPoint[2].x = 14;
	_itemWayPoint[2].y = 16;

	// 오른쪽 두번째 아이템
	_itemWayPoint[3].x = 14;
	_itemWayPoint[3].y = 20;

	// 계산대
	_counterPoint.x = 19;
	_counterPoint.y = 18;

	// 출입문
	_eixtPoint.x = 17;
	_eixtPoint.y = 23;

	_aroundPoint[0].x = 20;
	_aroundPoint[0].y = 21;

	_aroundPoint[1].x = 18;
	_aroundPoint[1].y = 21;
	
	_aroundPoint[2].x = 19;
	_aroundPoint[2].y = 19;

	_goToPoint = _itemWayPoint[0];
}

void shopNPC::directionCheck()
{
	int DegAngle = _angle * 180 / PI; // 라디안 디그리(각도)로 변환

	// 오른쪽 방향
	if ((DegAngle <= 45 && DegAngle >= 0) || (DegAngle <= 360 && DegAngle > 315))
	{
		_indexY = 2;
	}

	// 위쪽 방향
	else if ((DegAngle <= 135 && DegAngle > 45))
	{
		_indexY = 3;
	}

	// 왼쪽 방향
	else if ((DegAngle <= 225 && DegAngle > 135))
	{
		_indexY = 1;
	}

	// 아래쪽 방향 
	else if ((DegAngle <= 315 && DegAngle > 225))
	{
		_indexY = 0;
	}
}

void shopNPC::chooseItem()
{	
	// 중복 방지 (안 본 아이템이 나올때 까지 루프)
	int count = 0;
	while (true)
	{
		count++;
		_rndChoiceItem = RND->getInt(4);

		if (!_checkItem[_rndChoiceItem] && INVENTORY->getShowCase()[_rndChoiceItem *2].item != NULL)
			break;

		if (count > 10)
		{
			choosePt();
			return;
		}

	}

	if (INVENTORY->getShowCase()[_rndChoiceItem * 2].isPeople)
	{
		choosePt();
		return;
	}

	INVENTORY->getShowCase()[_rndChoiceItem * 2].isPeople = true;

	_oldRndChoiceItem = _rndChoiceItem;
	// 확인한 아이템 숫자 늘려주기
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
	_settingPrice = INVENTORY->getShowCase()[_rndChoiceItem * 2].totalPrice;
	_rightPrice = INVENTORY->getShowCase()[_rndChoiceItem * 2].originalPrice;

	_aStar->changeWayPoint();

	_npcActionState = NPC_SHOPPING;
}

void shopNPC::choosePt()
{
	int oldPt = _rndChoicePt;
	_npcEmotionState = NPC_EMOTION_NULL;
	_idleCount++;

	while (true)
	{
		_rndChoicePt = RND->getInt(3);

		if (oldPt != _rndChoicePt)
			break;
	}

	cout << _rndChoicePt << endl;

	switch (_rndChoicePt)
	{
	case 0:
		_goToPoint = _aroundPoint[0];
		break;
		
	case 1:
		_goToPoint = _aroundPoint[1];
		break;

	case 2:
		_goToPoint = _aroundPoint[2];
		break;
	}

	_aStar->changeWayPoint();

	_npcActionState = NPC_WALK;
}
