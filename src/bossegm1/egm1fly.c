#include "decls.h"
extern struct taskwk *DAT_05baf368[8];

// STUB: SADX 0x006c2e40
long GetVsPlayerAng(struct taskwk *twp)
{
	return (long)0;
}

// STUB: SADX 0x006c2e80
long GetVsPlayerAbsAng(struct taskwk *twp)
{
	return (long)0;
}

// FUNCTION: SADX 0x006c2ec0
int GetBossAngMode(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct anywk *var2 = tp->awp;
	if (((var1->mode == 1) || (var1->mode == 2)) && (*(int *)((char *)var2 + 0x38) >= 0xc))
	{
		return 1;
	}
	return 0;
}

// STUB: SADX 0x006c2ef0
long InterpolateEgm1Ang(long src, long dst, float avg)
{
	return (long)0;
}

// STUB: SADX 0x006c2f60
int FUN_006c2f60(int param_1, short param_2, short param_3)
{
	return (int)0;
}

// FUNCTION: SADX 0x006c2ff0
int FUN_006c2ff0()
{
	if (*(float *)((char *)*DAT_05baf368 + 0x20) < 752.0)
	{
		return 2;
	}
	if (1008.0 < *(float *)((char *)*DAT_05baf368 + 0x20))
	{
		return 0;
	}
	return 1;
}

// FUNCTION: SADX 0x006c3030
int __fastcall FUN_006c3030(struct task *param_1)
{
	if (*(float *)((char *)param_1 + 0x20) < 752.0f)
	{
		return 2;
	}
	if (*(float *)((char *)param_1 + 0x20) > 1008.0)
	{
		return 0;
	}
	return 1;
}

// FUNCTION: SADX 0x006c34e0
void InitEgm1FlyPrm(struct task *tp, struct taskwk *twp)
{
	struct anywk *var1 = tp->awp;
	*(unsigned char *)((char *)var1 + 0xd2) = 0xff;
	*(int *)((char *)var1 + 0x38) = 0;
}
