#include <iostream>
#include <chrono>
#include "CConsole.h"
#include "Engine.h"
#include "Hooks.h"

using Clock = std::chrono::high_resolution_clock;

void DetachDll(HMODULE base);

CObjectManager* ObjManager;
CConsole Console;
CFunctions Functions;

void __stdcall Start(HMODULE base)
{
	Console.startConsole();

	if (strcmp(GetGameVersion(), TARGET_GAMEVERSION) != 0)
	{
		printf("Game version changed from %s to %s\n", TARGET_GAMEVERSION, GetGameVersion());
		Sleep(5 * 1000);
		DetachDll(base);
	}

	while (Engine::GetGameTime() < 1.0f || !me)
	{
		Sleep(10);
	}

	//////////////////////////////////////////////////////////////////////////////////////////

	ObjManager = (CObjectManager*)(baseAddr + oObjManager);

	Functions.PrintChat = (Typedefs::fnPrintChat)(baseAddr + oPrintChat);
	Functions.IsTargetable = (Typedefs::fnIsTargetable)(baseAddr + oIsTargetable);
	Functions.IsAlive = (Typedefs::fnIsAlive)(baseAddr + oIsAlive);

	Functions.IsMinion = (Typedefs::fnIsMinion)(baseAddr + oIsMinion);
	Functions.IsTurret = (Typedefs::fnIsTurret)(baseAddr + oIsTurret);
	Functions.IsHero = (Typedefs::fnIsHero)(baseAddr + oIsHero);
	Functions.IsMissile = (Typedefs::fnIsMissile)(baseAddr + oIsMissile);
	Functions.IsNexus = (Typedefs::fnIsNexus)(baseAddr + oIsNexus);
	Functions.IsInhibitor = (Typedefs::fnIsInhibitor)(baseAddr + oIsInhib);
	Functions.IsTroyEnt = (Typedefs::fnIsTroyEnt)(baseAddr + oIsTroy);
	Functions.IsDragon = (Typedefs::fnIsDragon)(baseAddr + oIsDragon);
	Functions.IsBaron = (Typedefs::fnIsBaron)(baseAddr + oIsBaron);

	Functions.CastSpell = (Typedefs::fnCastSpell)(baseAddr + oCastSpell);
	Functions.GetSpellState = (Typedefs::fnGetSpellState)(baseAddr + oGetSpellState);
	Functions.IssueOrder = (Typedefs::fnIssueOrder)(baseAddr + oIssueOrder);
	Functions.DrawCircle = (Typedefs::fnDrawCircle)(baseAddr + oDrawCircle);

	Functions.GetAttackCastDelay = (Typedefs::fnGetAttackCastDelay)(baseAddr + oGetAttackCastDelay);
	Functions.GetAttackDelay = (Typedefs::fnGetAttackDelay)(baseAddr + oGetAttackDelay);

	//////////////////////////////////////////////////////////////////////////////////////////

	if (ObjManager == NULL)
	{
		printf("ObjMgr is dead.\n");
		Sleep(5 * 1000);
		DetachDll(base);
	}

	if (me)
	{
		printf("Press 'del' to exit.\n");
		printf("Local player's name: %s | Champion: %s | Address: 0x%0x\n", me->GetName(), me->GetChampionName(), (DWORD)me);
		printf("Game version: %s\n", GetGameVersion());
	}

	///////////////////////////// Spells section ///////////////////////////////////////////////

	bool smiteToggle = true;
	const int smiteSlot = 4;

	auto Q = me->GetSpellBook()->GetSpellSlotByID(0);
	auto W = me->GetSpellBook()->GetSpellSlotByID(1);
	auto E = me->GetSpellBook()->GetSpellSlotByID(2);
	auto R = me->GetSpellBook()->GetSpellSlotByID(3);
	auto D = me->GetSpellBook()->GetSpellSlotByID(smiteSlot);
	auto F = me->GetSpellBook()->GetSpellSlotByID(5);

	auto lastCheck = Clock::now();
	// seconds
	const int interval = 2;
	int monsterIndex = -1;
	const float minDist = 2500.0f;

	while (!GetAsyncKeyState(VK_DELETE))
	{
		if (GetAsyncKeyState(VK_MBUTTON) & 0x1)
		{
			smiteToggle = !smiteToggle;
			printf("Smite is %s\n", smiteToggle ? "ON" : "OFF");
		}

		if (!smiteToggle) continue;

		auto nowCheck = Clock::now();
		for (int i = 0; i < ObjManager->GetMaxObjects(); i++)
		{
			if (std::chrono::duration_cast<std::chrono::seconds>(nowCheck - lastCheck).count() < interval)
				break;

			CObject* obj = Engine::GetObjectByID(i);

			if (obj && obj->IsMinion() && (obj->IsDragon() || obj->IsBaron()))
			{
				// if object is too far
				if (obj->GetPos().DistTo(me->GetPos()) > minDist)
					continue;

				printf("Object name:%s | Object HP:%.2f | Object index:%d | Object dist to me:%.2f\n", obj->GetName(), obj->GetHealth(), i, obj->GetPos().DistTo(me->GetPos()));
				monsterIndex = i;
				lastCheck = Clock::now();
				break;
			}
		}

		CObject* monster = Engine::GetObjectByID(monsterIndex);

		if (monster && (monster->GetHealth() <= D->GetSpellTrueDamage()))
		{
			Engine::CastSpellTargetted(smiteSlot, monster);
		}

		Sleep(1);
	}

	DetachDll(base);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hModule);
		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)Start, hModule, 0, nullptr);
		return TRUE;
	}

	if (ul_reason_for_call == DLL_PROCESS_DETACH)
	{
		return TRUE;
	}

	return FALSE;
}

void DetachDll(HMODULE base)
{
	Console.stopConsole();
	FreeLibraryAndExitThread(static_cast<HMODULE>(base), 1);
}