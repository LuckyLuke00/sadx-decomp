#include "decls.h"

// GLOBAL: SADX 0x009be6f0
static const signed char colliparam_tbl[3][7];

// FUNCTION: SADX 0x006c4030
void setBossColliRot(struct taskwk *twp, int mode)
{
	int var1;

	for (var1 = 0; var1 < 0x150; var1 += 0x30)
	{
		if (mode == 0)
		{
			*(int *)((char *)twp->cwp->info + var1 + 4) &= 0xfffffdff;
		}
		else
		{
			*(int *)((char *)twp->cwp->info + var1 + 4) |= 0x200;
		}
	}
}

// FUNCTION: SADX 0x006c4070
void setBossColliOnOff(struct taskwk *twp, int mode)
{
	int var1;
	int var2;

	for (var1 = 0, var2 = 0; var1 < 0x150; var1 += 0x30, var2++)
	{
		if (colliparam_tbl[mode][var2] != 0)
		{
			*(int *)((char *)twp->cwp->info + var1 + 4) &= 0xffffffef;
		}
		else
		{
			*(int *)((char *)twp->cwp->info + var1 + 4) |= 0x10;
		}
	}
}

// STUB: SADX 0x006c40c0
void InitEgm1Coli(struct task *tp)
{
}
