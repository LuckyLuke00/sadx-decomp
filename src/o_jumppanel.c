#include "decls.h"
void FUN_005b3ee0(struct task *param_1);
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

// STUB: SADX 0x005b3640
long CanIMakePanelJump(struct taskwk *ptwp)
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

// STUB: SADX 0x005b3730
void StartPlayerPanelJump(struct taskwk *ptwp)
{
}

// STUB: SADX 0x005b3c80
int FUN_005b3c80(void)
{
	return (int)0;
}

// STUB: SADX 0x005b3ce0
void ObjectJumpPanel(struct task *tp)
{
}

// FUNCTION: SADX 0x005b3e10
void ObjectJumpPanelRegular(struct task *tp)
{
	struct taskwk *local_8;

	local_8 = tp->twp;
	if (CheckRangeOut(tp) != 0)
	{
		return;
	}
	if (FUN_004c39c0(tp) == 0)
	{
		FUN_005b3ee0(tp);
		if (local_8->mode != 1)
		{
			EntryColliList(local_8);
		}
		ObjectSetupInput(local_8, 0);
	}
	else
	{
		ObjectJumpPanelSetNumber(tp);
		njPrintC(0x110010, "-> ROTATION X");
		njPrintC(0x110011, "-> ROTATION Y");
		njPrintC(0x110012, "-> ROTATION Z");
		njPrintC(0x110013, "-> PANEL NUMBER");
	}
	ObjectJumpPanelDisplay(tp);
}

// STUB: SADX 0x005b3ee0
void FUN_005b3ee0(struct task *param_1)
{
}

// FUNCTION: SADX 0x005b4170
void ObjectJumpPanelExit(struct task *tp)
{
	short local_8;

	local_8 = tp->twp->wtimer;
	if (DAT_05edbe48[local_8] == (int)tp)
	{
		DAT_05edbe48[local_8] = 0;
	}
}

// FUNCTION: SADX 0x005b41b0
void EffectJumpPannel(struct task *tp)
{
	tp->exec = EffJPExec;
	tp->disp = EffJPDisp;
	EffJPDisp(tp);
}

// STUB: SADX 0x005b41e0
void EffJPDisp(struct task *tp)
{
}

// STUB: SADX 0x005b42f0
void EffJPExec(struct task *tp)
{
}
