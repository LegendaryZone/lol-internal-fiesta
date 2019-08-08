#pragma once
#include "Utils.h"
#include "CObject.h"

class CObjectManager
{
public:
	CObject** GetObjectArray()
	{
		return *(CObject***)((DWORD)this + 0x4);
	}

	int GetMaxObjects()
	{
		return *(int*)((DWORD)this + 0x8);
	}

	int GetObjectsUsed()
	{
		return *(int*)((DWORD)this + 0xC);
	}

	int GetHighestObjectID()
	{
		return *(int*)((DWORD)this + 0x10);
	}
};
extern CObjectManager* ObjManager;