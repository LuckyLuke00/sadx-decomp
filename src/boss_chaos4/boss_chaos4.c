#include "decls.h"

// GLOBAL: SADX 0x02910a58
static signed char colliparam_tbl[2][7];

// FUNCTION: SADX 0x006eef70
void setChaos4ColliParam(struct taskwk *twp, int mode)
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

// FUNCTION: SADX 0x006f0300
void setChaos4()
{
	CreateElementalTask(3, 1, BossChaos4);
}
