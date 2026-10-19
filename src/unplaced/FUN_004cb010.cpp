#include "decls.h"
#include <windows.h>

extern struct __MYMEM_DATA *DAT_025d7b20;

// FUNCTION: SADX 0x004cb010
void *FUN_004cb010(unsigned long param_1)
{
	void *local_8;

	if (*(int *)((char *)DAT_025d7b20 + 4) == 0)
	{
		*(HANDLE *)DAT_025d7b20 = HeapCreate(0, 0, 0);
	}
	local_8 = HeapAlloc(*(HANDLE *)DAT_025d7b20, 8, param_1);
	if (local_8 != 0)
	{
		*(int *)((char *)DAT_025d7b20 + 4) = *(int *)((char *)DAT_025d7b20 + 4) + 1;
	}
	return local_8;
}


// FUNCTION: SADX 0x004cb070
void FUN_004cb070(void *param_1)
{
	int local_8;

	if (*(int *)((char *)DAT_025d7b20 + 4) > 0 && param_1 != 0)
	{
		if (HeapFree(*(HANDLE *)DAT_025d7b20, 0, param_1))
		{
			local_8 = *(int *)((char *)DAT_025d7b20 + 4) - 1;
			*(int *)((char *)DAT_025d7b20 + 4) = local_8;
			if (local_8 == 0)
			{
				HeapDestroy(*(HANDLE *)DAT_025d7b20);
			}
		}
	}
}
