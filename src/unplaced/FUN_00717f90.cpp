#include "decls.h"
extern int DAT_060cb340;
struct task *FUN_00717eb0(int param_1, int param_2);
void FreeTask(struct task *tp);
void Free(void *mp);
extern int DAT_060cb338;
extern int DAT_060cb33c;

// STUB: SADX 0x00717f90
void FUN_00717f90(int param_1)
{
}

// FUNCTION: SADX 0x00717fc0
void FUN_00717fc0()
{
	if (DAT_060cb33c)
	{
		int var1;
		struct task *var2;
		for (var1 = 0; var1 < DAT_060cb338; var1++)
		{
			var2 = *(struct task **)((char *)DAT_060cb33c + var1 * 4);
			if (var2)
			{
				FreeTask(var2);
			}
		}
		Free((void *)DAT_060cb33c);
		DAT_060cb33c = 0;
	}
}

// FUNCTION: SADX 0x00718010
void FUN_00718010(int param_1, int param_2, int param_3)
{
	if (param_1 < DAT_060cb338 && *(int *)((char *)DAT_060cb33c + param_1 * 4) == 0)
	{
		*(int *)((char *)DAT_060cb33c + param_1 * 4) = (int)FUN_00717eb0(param_2, param_3);
	}
}

// FUNCTION: SADX 0x00718050
void FUN_00718050(int param_1)
{
	if (param_1 < DAT_060cb338)
	{
		struct task *var1 = (struct task *)*(int *)((char *)DAT_060cb33c + param_1 * 4);
		if (var1 != 0)
		{
			FreeTask(var1);
			*(int *)((char *)DAT_060cb33c + param_1 * 4) = 0;
		}
	}
}

// FUNCTION: SADX 0x00718120
void FUN_00718120(int param_1, int param_2, int param_3, int param_4)
{
	void *local_8 = TH_GetWork(0);
	local_8 = (char *)local_8 + DAT_060cb340;
	dsPlay_timer(param_1, (int)local_8, 1, 0, 0x78);
	dsVolume_id((int)local_8, param_2);
	dsPan_id((int)local_8, param_3);
	dsPitch_id((int)local_8, param_4);
	DAT_060cb340 = (DAT_060cb340 + 1) & 0x1f;
}
