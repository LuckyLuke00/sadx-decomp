#include "decls.h"

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

// STUB: SADX 0x006c4070
void setBossColliOnOff(struct taskwk *twp, int mode)
{
}

// STUB: SADX 0x006c40c0
void InitEgm1Coli(struct task *tp)
{
}
