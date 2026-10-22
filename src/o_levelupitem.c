#include "decls.h"
extern short DAT_00997d78[4];

// STUB: SADX 0x005e5f80
void levelupitemDisplay(struct task *tp)
{
}

// STUB: SADX 0x005e6010
void *FUN_005e6010(void)
{
	return (void *)0;
}

// FUNCTION: SADX 0x005e6370
bool FUN_005e6370(short param_1, short param_2)
{
	return *(short *)((char *)DAT_00997d78 + param_1 * 8) == param_2;
}

// FUNCTION: SADX 0x005e6390
int FUN_005e6390(short param_1, int param_2)
{
	if (param_1 < 0xd)
	{
		return (*(int *)((char *)DAT_00997d78 + param_1 * 8 + 4) == param_2);
	}
	else
	{
		return 1;
	}
}

// STUB: SADX 0x005e63c0
void FUN_005e63c0(short param_1, int param_2, int *param_3)
{
}

// STUB: SADX 0x005e6ad0
void FUN_005e6ad0(struct task *param_1)
{
}

// STUB: SADX 0x005e70e0
void FUN_005e70e0(void)
{
}

// STUB: SADX 0x005e7310
void init_tubu()
{
}
