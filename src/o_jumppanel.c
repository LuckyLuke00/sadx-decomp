#include "decls.h"
extern int DAT_05edbe48[10];

// FUNCTION: SADX 0x005b35b0
void InitJumpPanel(void)
{
	int local_8;

	for (local_8 = 0; local_8 < 10; local_8++)
	{
		DAT_05edbe48[local_8] = 0;
	}
}

// STUB: SADX 0x005b35e0
long CheckCollisionedForJumpPanel(struct taskwk *ptwp)
{
	return (long)0;
}

// FUNCTION: SADX 0x005b36e0
void RefreshJumpPanel(void)
{
	int local_8;

	for (local_8 = 0; local_8 < 10; local_8++)
	{
		if (DAT_05edbe48[local_8] == 0)
		{
			continue;
		}
		*((char *)*(int *)(DAT_05edbe48[local_8] + 0x20)) = 0;
	}
}

// STUB: SADX 0x005b3c80
int FUN_005b3c80(void)
{
	return (int)0;
}

// FUNCTION: SADX 0x005b41b0
void EffectJumpPannel(struct task *tp)
{
	tp->exec = EffJPExec;
	tp->disp = EffJPDisp;
	EffJPDisp(tp);
}

// STUB: SADX 0x005b42f0
void EffJPExec(struct task *tp)
{
}
