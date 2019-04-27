#pragma once
#include "Offsets.h"
#include "Utils.h"
#include "Vector.h"
#include "Hooks.h"
#include "CObjectManager.h"

#define me Engine::GetLocalObject()

class Engine
{
public:
	static Vector GetMouseWorldPosition()
	{
		DWORD MousePtr = (DWORD)GetModuleHandle(NULL) + oHudInstance;
		auto aux1 = *(DWORD*)MousePtr;
		aux1 += 0x14;
		auto aux2 = *(DWORD*)aux1;
		aux2 += 0x1C;

		float X = *(float*)(aux2 + 0x0);
		float Y = *(float*)(aux2 + 0x4);
		float Z = *(float*)(aux2 + 0x8);

		return Vector{ X, Y, Z };
	}

	static char* GetGameVersion()
	{
		return (char*)(baseAddr + oGameVersion);
	}

	static float GetGameTime()
	{
		return *(float*)(baseAddr + oGameTime);
	}

	static CObject* GetLocalObject()
	{
		auto retaddr = *(DWORD*)(baseAddr + oLocalPlayer);
		if (retaddr == NULL)
			return NULL;

		return (CObject*)retaddr;
	}

	static CObject* GetObjectByID(int ID)
	{
		if (ObjManager != NULL && ID >= 0 && ID <= ObjManager->GetMaxObjects())
		{
			return ObjManager->GetObjectArray()[ID];
		}

		return NULL;
	}

	static void MoveTo(Vector* pos)
	{
		Functions.IssueOrder(GetLocalObject(), 2, pos, NULL, false, false, false);
	}

	static void CastSpellSelf(int slotID)
	{
		if (me->IsAlive())
		{
			DWORD spellbook = (DWORD)me->GetSpellBook();
			CSpellSlot* spellslot = me->GetSpellBook()->GetSpellSlotByID(slotID);

			//if (spellslot->IsReady())
			Functions.CastSpell(spellbook, spellslot, slotID, &me->GetPos(), &me->GetPos(), 0x0);
		}
	}

	static void CastSpellPos(int slotID, Vector pos)
	{
		DWORD spellbook = (DWORD)me->GetSpellBook();
		CSpellSlot* spellslot = me->GetSpellBook()->GetSpellSlotByID(slotID);
		Vector* targetpos = &pos;

		//if (spellslot->IsReady())
		Functions.CastSpell(spellbook, spellslot, slotID, targetpos, &me->GetPos(), 0x0);
	}

	static void CastSpellTargetted(int slotID, CObject* obj)
	{
		DWORD spellbook = (DWORD)me->GetSpellBook();
		CSpellSlot* spellslot = me->GetSpellBook()->GetSpellSlotByID(slotID);
		static byte zero = 0;

		//if (Functions.GetSpellState(&spellbook, slotID, &zero) == 0)
			Functions.CastSpell(spellbook, spellslot, slotID, &obj->GetPos(), &me->GetPos(), obj->GetNetworkID());
	}
};