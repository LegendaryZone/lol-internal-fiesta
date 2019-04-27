#include "Utils.h"
#include "CSpellSlot.h"

class CSpellBook
{
public:
	CSpellSlot* GetSpellSlotByID(int ID)
	{
		return *(CSpellSlot**)((DWORD)this + 0x508 + (0x4 * ID));
	}
};