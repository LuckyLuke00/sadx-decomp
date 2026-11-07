#include "decls.h"
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
