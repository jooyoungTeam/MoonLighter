#include "stdafx.h"
#include "potionCreate.h"

HRESULT potionCreate::init()
{
	_select = ImageManager::GetInstance()->FindImage("select_potion");
	_effectImg = ImageManager::GetInstance()->FindImage("potion_make_effect");

	_selectIndex = 0;
	_state = POTION_INIT;
	_effectState = POTION_E_NULL;

	_selectPt = _pt[0] = Vector2(585, 259);
	_pt[1] = Vector2(695, 259);
	_pt[2] = Vector2(806, 259);
	_pt[3] = Vector2(916, 259);

	_isSizeLeft = true;
	_isSizeRight = true;
	_isPotionCheck = true;
	_isActive = false;
	_makeCount = 1;
	_isBuy = false;
	_makeItemY = 580;
	_makeMaterialY = 510;
	potionSet();

	
	return S_OK;
}

void potionCreate::update()
{
	if (_effectState != POTION_E_NULL)
	{
		_effectTimer++;

		if (_effectState == POTION_E_START || _effectState == POTION_E_MID)
		{
			if (_effectTimer > 5)
			{
				if (_effectIndex >= _effectImg->GetMaxFrameX() - 1)
				{
					switch (_effectState)
					{
					case POTION_E_START:
						_effectIndex = 0;
						_effectState = POTION_E_MID;
						_effectImg = ImageManager::GetInstance()->FindImage("potion_complete_effect"); 
						SOUNDMANAGER->play("슬라임펑");
						break;
					case POTION_E_MID:
						_effectIndex = 0;
						_effectState = POTION_E_END;
						SOUNDMANAGER->play("gameStart");
						break;
					}
				}

				_effectIndex++;

				_effectTimer = 0;
			}
		}
		else if (_effectState == POTION_E_INIT)
		{
			_makeMaterialY++;
			if (_effectTimer > 50)
			{
				_effectIndex = 0;
				_effectState = POTION_E_START;

				_effectTimer = 0;
			}

		}
		else if (_effectState == POTION_E_END)
		{
			_makeItemY--;
			if (_effectTimer > 50)
			{
				reset();
				_effectTimer = 0;
			}

		}
	}



	_selectPt = _pt[_selectIndex];
	indexSet();
	isSizeUpdate();
	isBuyUpdate();

	switch (_state)
	{
	case POTION_INIT:
		if (_effectState == POTION_E_NULL)
		{
			if (KEYMANAGER->isOnceKeyDown('A'))
			{
				SOUNDMANAGER->play("errorItem");
				_selectIndex--;
				if (_selectIndex == -1)
					_selectIndex = 3;
			}

			if (KEYMANAGER->isOnceKeyDown('D'))
			{
				SOUNDMANAGER->play("errorItem");
				_selectIndex++;
				if (_selectIndex == 4)
					_selectIndex = 0;
			}
		}
		break;
	case POTION_SIZE:
		if (KEYMANAGER->isOnceKeyDown('A'))
		{
			if (_isSizeLeft)
			{
				SOUNDMANAGER->play("errorItem");
				_makeCount--;
			}
			// 포션 개수 마이너스
		}
		if (KEYMANAGER->isOnceKeyDown('D'))
		{
			if (_isSizeRight)
			{
				SOUNDMANAGER->play("errorItem");
				_makeCount++;
			}
			// 포션 개수 플러스	
		}
		break;
	case POTION_CHECK:
		if (KEYMANAGER->isOnceKeyDown('A'))
		{
			SOUNDMANAGER->play("errorItem");
			if (_isPotionCheck)
			{
				_isPotionCheck = false;
			}
			else
			{
				_isPotionCheck = true;
			}
		}
		if (KEYMANAGER->isOnceKeyDown('D'))
		{
			SOUNDMANAGER->play("errorItem");
			if (_isPotionCheck)
			{
				_isPotionCheck = false;
			}
			else
			{
				_isPotionCheck = true;
			}
		}
		break;

	}

	if (KEYMANAGER->isOnceKeyDown('J'))
	{
		SOUNDMANAGER->play("putItem");
		switch (_state)
		{
		case POTION_INIT:
			if (_isBuy && _effectState == POTION_E_NULL)
				_state = POTION_SIZE;
			break;
		case POTION_SIZE:
			_state = POTION_CHECK;
			break;
		case POTION_CHECK:
			if (_isPotionCheck)
			{
				INVENTORY->makePotion(_selectPotion.index, _makeCount, _selectPotion.needIndex, _selectPotion.needCount * _makeCount, _selectPotion.price * _makeCount);
				// 포션 만들기 함수
				_makeMaterial = _selectPotion.needItem;
				_makeItem = _selectPotion.img;
				_state = POTION_INIT;
				_effectImg = ImageManager::GetInstance()->FindImage("potion_make_effect");
				_effectState = POTION_E_INIT;
			}
			else
			{
				_state = POTION_SIZE;
			}
			break;
		}
	}

	if (KEYMANAGER->isOnceKeyDown('K'))
	{
		switch (_state)
		{
		case POTION_INIT:
			if(_effectState == POTION_E_NULL)
				_isActive = false;
			break;
		case POTION_SIZE:
			_makeCount = 1;
			_state = POTION_INIT;
			break;
		case POTION_CHECK:
			_state = POTION_SIZE;
			break;
		}
	}

}

void potionCreate::render()
{
	ImageManager::GetInstance()->FindImage("alphaBlack")->Render(Vector2(0, 0));
	ImageManager::GetInstance()->FindImage("potion_shop_bg")->Render(Vector2(0,0));
	_select->Render(_selectPt);


	switch (_effectState)
	{
	case POTION_E_INIT:
		// 아이템 넣기
		_makeMaterial->Render(Vector2(WINSIZEX / 2 - 40, _makeMaterialY), 2.f);
		break;
	case POTION_E_START:
		// 항아리 젓기
		ImageManager::GetInstance()->FindImage("potion_make_effect")->FrameRender(Vector2(WINSIZEX / 2 - 10, 588), _effectIndex, 0, 2.f);
		break;
	case POTION_E_MID:
		// 항아리 터지기
		ImageManager::GetInstance()->FindImage("potion_complete_effect")->FrameRender(Vector2(WINSIZEX / 2 - 20, 530), _effectIndex, 0, 1.3f);
		break;
	case POTION_E_END:
		// 아이템 떠오르기
		_makeItem->Render(Vector2(WINSIZEX / 2 - 30, _makeItemY),2.f);
		break;

	}
	
	// 포션 설명
	D2DRenderer::GetInstance()->RenderTextField(1170, 100, _selectPotion.discription, 25, 300, 400, D2DRenderer::DefaultBrush::Black);
	// 포션 이름
	D2DRenderer::GetInstance()->RenderText(1250, 30, _selectPotion.name, 30, D2DRenderer::DefaultBrush::Gray);
	// 포션 가격
	D2DRenderer::GetInstance()->RenderText(1380, 455, to_wstring(_selectPotion.price), 25, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING);
	// 포션 개수
	D2DRenderer::GetInstance()->RenderText(1250, 175, to_wstring(INVENTORY->countOfItem(_selectPotion.index)), 30, D2DRenderer::DefaultBrush::White);
	// 필요한 아이템
	_selectPotion.needItem->Render(Vector2(WINSIZEX - 430, 550),1.7f);
	// 필요한 개수
	D2DRenderer::GetInstance()->RenderText(WINSIZEX - 280, 530, to_wstring(_selectPotion.needCount), 26, D2DRenderer::DefaultBrush::Gray);
	// 소지 개수
	D2DRenderer::GetInstance()->RenderText(WINSIZEX - 280, 573, to_wstring(INVENTORY->countOfItem(_selectPotion.needIndex)), 26, D2DRenderer::DefaultBrush::Gray);
	// 확인 & 취소
	if (_isBuy)
	{
		ImageManager::GetInstance()->FindImage("buy_true")->Render(Vector2(WINSIZEX - 200, 511));
	}
	else
	{
		ImageManager::GetInstance()->FindImage("buy_false")->Render(Vector2(WINSIZEX - 200, 511));
	}

	switch (_state)
	{
	case POTION_INIT:
		break;
	case POTION_SIZE:
		ImageManager::GetInstance()->FindImage("alphaBlack")->Render(Vector2(0, 0));
		ImageManager::GetInstance()->FindImage("potion_size")->Render(Vector2(550, 300));

		if (_isSizeLeft)
		{
			ImageManager::GetInstance()->FindImage("potion_size_left")->Render(Vector2(601, WINSIZEY / 2 + 24));
		}
		if (_isSizeRight)
		{
			ImageManager::GetInstance()->FindImage("potion_size_right")->Render(Vector2(733, WINSIZEY / 2 + 24));
		}
		_selectPotion.img->Render(Vector2(659, 465),1.5f);
		D2DRenderer::GetInstance()->RenderText(700, 500, to_wstring(_makeCount), 30);


		// 필요한 최종 아이템
		_selectPotion.needItem->Render(Vector2(WINSIZEX - 630, 482), 1.3f);
		// 필요한 최종 아이템 개수
		D2DRenderer::GetInstance()->RenderText(WINSIZEX - 590, 510, to_wstring(_selectPotion.needCount * _makeCount), 15, D2DRenderer::DefaultBrush::Black);
		// 필요한 최종 돈
		D2DRenderer::GetInstance()->RenderText(WINSIZEX - 660, 420, to_wstring(_selectPotion.price * _makeCount), 25, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_LEADING);

		break;
	case POTION_CHECK:
		ImageManager::GetInstance()->FindImage("alphaBlack")->Render(Vector2(0, 0));
		ImageManager::GetInstance()->FindImage("alphaBlack")->Render(Vector2(0, 0));
		if (_isPotionCheck)
		{
			ImageManager::GetInstance()->FindImage("potion_check_yes")->Render(Vector2(450, 50));
		}
		else
		{
			ImageManager::GetInstance()->FindImage("potion_check_no")->Render(Vector2(450, 50));
		}
		break;
	}
}

void potionCreate::release()
{
	
}

void potionCreate::indexSet()
{
	switch (_selectIndex)
	{
	case 0:
		_selectPotion = _potion[0];
		break;

	case 1:
		_selectPotion = _potion[1];
		break;

	case 2:
		_selectPotion = _potion[2];
		break;

	case 3:
		_selectPotion = _potion[3];
		break;
	}

}

void potionCreate::potionSet()
{
	_potion[0].index = 1001;
	_potion[0].price = 100;
	_potion[0].img = ImageManager::GetInstance()->FindImage("potion_S");
	_potion[0].name = L"포션(소)";
	_potion[0].discription = L"체력을 40 회복한다. 한두 개 정도는 항상 휴대하는 게 좋다.";
	_potion[0].needIndex = 101;
	_potion[0].needItem = ImageManager::GetInstance()->FindImage("slime_red");
	_potion[0].needCount = 1;

	_potion[1].index = 1002;
	_potion[1].price = 500;
	_potion[1].img = ImageManager::GetInstance()->FindImage("potion_M");
	_potion[1].name = L"포션(중)";
	_potion[1].discription = L"체력을 60 회복한다. 제값을 톡톡히 하는 제품이다. ";
	_potion[1].needIndex = 101;
	_potion[1].needItem = ImageManager::GetInstance()->FindImage("slime_red");
	_potion[1].needCount = 2;

	_potion[2].index = 1003;
	_potion[2].price = 1000;
	_potion[2].img = ImageManager::GetInstance()->FindImage("potion_B");
	_potion[2].name = L"포션(대)";
	_potion[2].discription = L"체력을 80 회복한다. 그 괴물과 맞닥뜨렸을 때 하나 가지고 있었다면 좋았겠지만...";
	_potion[2].needIndex = 102;
	_potion[2].needItem = ImageManager::GetInstance()->FindImage("slime_blue");
	_potion[2].needCount = 2;

	_potion[3].index = 1004;
	_potion[3].price = 2000;
	_potion[3].img = ImageManager::GetInstance()->FindImage("potion_L");
	_potion[3].name = L"포션(특대)";
	_potion[3].discription = L"체력을 100 회복한다. 마녀가 드디어 스스로의 능력을 뛰어넘는 물건을 만들어 냈다.";
	_potion[3].needIndex = 103;
	_potion[3].needItem = ImageManager::GetInstance()->FindImage("slime_yellow");
	_potion[3].needCount = 4;
}

void potionCreate::reset()
{
	_effectImg = ImageManager::GetInstance()->FindImage("potion_make_effect");
	_state = POTION_INIT;
	_effectState = POTION_E_NULL;
	_selectIndex = 0;
	_isSizeLeft = false;
	_isSizeRight = true;
	_isPotionCheck = false;
	//_isActive = false;
	_makeCount = 1;
	_makeItemY = 580;
	_makeMaterialY = 510;
}

void potionCreate::isSizeUpdate()
{
	if (_makeCount == 1)
	{
		_isSizeLeft = false;
	}
	else
	{
		_isSizeLeft = true;
	}

	if ((INVENTORY->getGold() >= _selectPotion.price * _makeCount) && (INVENTORY->countOfItem(_selectPotion.needIndex) >= _selectPotion.needCount * (_makeCount+1)))
	{
		_isSizeRight = true;
	}
	else
	{
		_isSizeRight = false;
	}
}

void potionCreate::isBuyUpdate()
{
	if ((_selectPotion.needCount <= INVENTORY->countOfItem(_selectPotion.needIndex)) && (INVENTORY->getGold() >= _selectPotion.price))
	{
		_isBuy = true;
	}
	else
	{
		_isBuy = false;
	}
}
