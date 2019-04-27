#include "Utils.h"
#include "CSpellData.h"

class CSpellInfo
{
public:
	CSpellData* GetSpellData()
	{
		return *(CSpellData**)((DWORD)this + 0x38);
	}
};