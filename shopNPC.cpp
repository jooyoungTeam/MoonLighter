#include "stdafx.h"
#include "shopNPC.h"

HRESULT shopNPC::init()
{
	
	return S_OK;
}

void shopNPC::release()
{
}

void shopNPC::updadte()
{
	switch (_npcActionState)
	{
	case NPC_IDLE:

		break;
	case NPC_SHOPPING:

		break;
	case NPC_BUY:

		break;
	case NPC_AWAY:

		break;
	}
}

void shopNPC::render()
{
}

void shopNPC::comparePrice()
{
	// 아이템의 정보 중 적정가를 가져와서. 비교후 처리

}