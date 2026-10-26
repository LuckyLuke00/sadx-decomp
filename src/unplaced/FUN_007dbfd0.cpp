#include "decls.h"
extern struct task *DAT_060ccb48;
void FreeTask(struct task *tp);

// FUNCTION: SADX 0x007dbfd0
void FUN_007dbfd0(int param_1)
{
	int var1;
	int var2;
	int var3;

	var1 = param_1;
	if (var1 == 0)
	{
		return;
	}
	var1 = *(int *)(var1 + 0x20);
	if (var1 == 0)
	{
		return;
	}
	var2 = *(int *)(var1 + 0x38);
	if (var2 == 0)
	{
		return;
	}
	var3 = 0;
	while (var3 < (int)(unsigned short)(*(unsigned short *)(var2 + 6)))
	{
		*(unsigned char *)(*(int *)(var2 + 0xc) + var3 * 0x30 + 2) &= 0xef;
		var3++;
	}
}

// FUNCTION: SADX 0x007dc010
void FUN_007dc010(void)
{
	if (DAT_060ccb48 != NULL)
	{
		FreeTask(DAT_060ccb48);
	}
}

// FUNCTION: SADX 0x007dc030
void FUN_007dc030(void)
{
	struct taskwk *var1 = DAT_060ccb48->twp;
	var1->timer.l = 0;
	var1->mode = 1;
}
