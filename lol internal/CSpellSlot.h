#include "Utils.h"
#include "CSpellInfo.h"

class CSpellSlot
{
public:
	int GetLevel()
	{
		return *(int*)((DWORD)this + 0x20);
	}

	float GetTime()
	{
		return *(float*)((DWORD)this + 0x28);
	}

	float GetCD()
	{
		return *(float*)((DWORD)this + 0x18);
	}

	/*bool IsReady()
	{
		if (GetSpellInfo()->GetSpellData()->GetCooldownTime() == 0) return true;
		return false;
	}*/

	// for smite
	float GetSpellTrueDamage()
	{
		return *(float*)((DWORD)this + 0x84);
	}

	CSpellInfo* GetSpellInfo()
	{
		return *(CSpellInfo**)((DWORD)this + 0x124);
	}
};