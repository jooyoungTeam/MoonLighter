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
	// �������� ���� �� �������� �����ͼ�. ���� ó��

}