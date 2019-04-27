#pragma once
#include "CObject.h"

class Typedefs
{
public:
	//typedef void(__thiscall* fnUpdateChargeableSpell)(SpellBook* pSpellBook, Spell* pSpellslot, int slot, Vector* pPosition, bool ReleaseCast);
	typedef void(__thiscall* fnPrintChat)(DWORD ChatClient, const char* Message, int Color);
	typedef int*(__thiscall* fnIssueOrder)(void *thisPtr, int Order, Vector *Loc, CObject *Target, bool IsAttackMove, bool IsMinion, DWORD Unknown);
	typedef float(__cdecl* fnGetAttackCastDelay)(CObject* pObj);
	typedef float(__cdecl* fnGetAttackDelay)(CObject* pObj);
	typedef void(__cdecl* fnDrawCircle)(Vector* position, float range, int* color, int a4, float a5, int a6, float alpha);
	typedef int*(__thiscall* fnCastSpell)(DWORD spellbook_addr, CSpellSlot* spellslot, int SlotID, Vector* targetpos, Vector* startpos, DWORD NetworkID);
	typedef int(__thiscall* fnGetSpellState)(void* spellbook, unsigned int slot, byte*);

	typedef bool(__cdecl* fnIsHero)(CObject* pObj);
	typedef bool(__cdecl* fnIsMissile)(CObject* pObj);
	typedef bool(__cdecl* fnIsMinion)(CObject* pObj);
	typedef bool(__cdecl* fnIsTurret)(CObject* pObj);
	typedef bool(__cdecl* fnIsInhibitor)(CObject* pObj);
	typedef bool(__cdecl* fnIsTroyEnt)(CObject* pObj);
	typedef bool(__cdecl* fnIsNexus)(CObject* pObj);

	typedef bool(__thiscall* fnIsDragon)(CObject* pObj);
	typedef bool(__thiscall* fnIsBaron)(CObject* pObj);
	typedef bool(__thiscall* fnIsAlive)(CObject* pObj);
	typedef bool(__thiscall* fnIsTargetable)(CObject* pObj);
};

class CFunctions
{
public:
	Typedefs::fnIsTurret IsTurret;
	Typedefs::fnIsMinion IsMinion;
	Typedefs::fnIsHero IsHero;
	Typedefs::fnIsMissile IsMissile;
	Typedefs::fnIsTroyEnt IsTroyEnt;
	Typedefs::fnIsNexus IsNexus;
	Typedefs::fnIsInhibitor IsInhibitor;
	Typedefs::fnIsDragon IsDragon;
	Typedefs::fnIsBaron IsBaron;

	Typedefs::fnIsTargetable IsTargetable;
	Typedefs::fnIsAlive IsAlive;

	Typedefs::fnIssueOrder IssueOrder;
	Typedefs::fnGetAttackCastDelay GetAttackCastDelay;
	Typedefs::fnGetAttackDelay GetAttackDelay;
	Typedefs::fnDrawCircle DrawCircle;
	Typedefs::fnCastSpell CastSpell;
	Typedefs::fnGetSpellState GetSpellState;
	Typedefs::fnPrintChat PrintChat;
};

extern CFunctions Functions;