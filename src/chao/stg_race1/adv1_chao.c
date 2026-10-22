#include "decls.h"
extern int DAT_05b33294[3];
extern int DAT_05b332a8;
extern char DAT_05b33291;
void FUN_00484bd0();

// FUNCTION: SADX 0x00484ac0
void *ADV1_AL_GetRaceTimeRam()
{
	return (void *)0x5b33110;
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
