#include "decls.h"
extern int DAT_05b33110;
struct task *FUN_00484ad0(int param_1);
extern int DAT_05b33294[3];
extern int DAT_05b332a8;
extern char DAT_05b33291;
void FUN_00484bd0();

// FUNCTION: SADX 0x00484ac0
void *ADV1_AL_GetRaceTimeRam()
{
	return &DAT_05b33110;
}

// FUNCTION: SADX 0x00484ad0
struct task *FUN_00484ad0(int param_1)
{
	if ((unsigned)param_1 <= 2)
	{
		return (struct task *)DAT_05b33294[param_1];
	}
	return 0;
}

#pragma optimize("", off)
// STUB: SADX 0x00484af0
void ADV1_AL_LimitChao()
{
}
#pragma optimize("", on)

#pragma optimize("", off)
// STUB: SADX 0x00484bd0
void FUN_00484bd0()
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x00484c20
void AL_DeleteChaoList(struct task *tp)
{
	for (int var1 = 0; var1 < 3; var1++)
	{
		struct task *var2 = FUN_00484ad0(var1);
		while (var2)
		{
			Free(var2);
			var2 = var2->ptp;
		}
	}
}

// FUNCTION: SADX 0x00484c50
void AL_ChaoListControl(struct task *tp)
{
	if (tp->twp->mode == 0)
	{
		tp->dest = AL_DeleteChaoList;
		tp->twp->mode++;
	}
}

// FUNCTION: SADX 0x00484c70
void ADV1_AL_InitChaoList()
{
	DAT_05b332a8 = 0;
	DAT_05b33294[0] = 0;
	DAT_05b33294[1] = 0;
	DAT_05b33294[2] = 0;
	if (DAT_05b33291 == 0)
	{
		FUN_00484bd0();
	}
	ADV1_AL_LimitChao();
	CreateElementalTask(2, 2, AL_ChaoListControl);
}
