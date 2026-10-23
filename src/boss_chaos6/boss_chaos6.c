#include "decls.h"
extern unsigned char DAT_05edd131;
extern unsigned char DAT_05edd13c;

// STUB: SADX 0x006f4f40
void setChaos6ColliParam(struct taskwk *twp, int mode)
{
}

// FUNCTION: SADX 0x006f6510
int Chaos6AttackStatus()
{
	int local_8;
	local_8 = *(char *)DAT_05edd128;
	if (local_8 == 1)
	{
		return 0;
	}
	if (local_8 == 2)
	{
		return 0;
	}
	if (local_8 == 0x13)
	{
		return 0;
	}
	return local_8 != 3;
}

// FUNCTION: SADX 0x006f66c0
void Chaos6ChangeMode(int mode)
{
	long var1;
	if ((long)mode != *(char *)((char *)DAT_05edd128 + 0x0))
	{
		var1 = mode;
		DAT_05edd13c = (char)mode;
		DAT_05edd131 = *(char *)((char *)DAT_05edd128 + 0x0);
	}
}

// STUB: SADX 0x006f66e0
void SetLandDamagePow(struct task *tp)
{
}

// FUNCTION: SADX 0x006f7b20
void setChaos6()
{
	CreateElementalTask(3, 2, BossChaos6);
}
