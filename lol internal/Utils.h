#pragma once
#include <Windows.h>
#include "Offsets.h"

#define baseAddr (DWORD)GetModuleHandle(NULL)

#define OBJ_MINION  1
#define OBJ_HERO    2
#define OBJ_MISSILE 3

inline char* GetStr(DWORD offset)
{
	if (*(int*)(offset + 0x10) > 15)
		return (char*)(*(DWORD*)offset);
	else
		return (char*)offset;
}

inline float GetEffectiveHP(float Armor, float HP)
{
	return HP * (100.0f + Armor) / 100.0f;
}

inline char* GetGameVersion()
{
	return (char*)(baseAddr + oGameVersion);
}