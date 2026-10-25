#include "decls.h"
static void execTgt(struct task *pTask);
extern struct obj object_e105_105_a_105_a;

// STUB: SADX 0x008ac5c0
void destTgt(struct task *pTask)
{
}

// STUB: SADX 0x008ac600
int FUN_008ac600(void)
{
	return (int)0;
}

// FUNCTION: SADX 0x008acd90
void dispFlyingHead(struct task *pTask)
{
	struct taskwk *var1 = pTask->twp;
	___njSetTexture(&texlist_e105);
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.z != 0)
	{
		njRotateZ(0, (unsigned short)var1->ang.z);
	}
	if (var1->ang.x != 0)
	{
		njRotateX(0, (unsigned short)var1->ang.x);
	}
	if (-0x4000 - var1->ang.y != 0)
	{
		njRotateY(0, (unsigned short)(-0x4000 - var1->ang.y));
	}
	FUN_0067d830(0, posRoundCenter.x, -45.0f, posRoundCenter.x);
	ds_DrawObjectClip(&object_e105_105_a_105_a, 1.0f);
	njPopMatrix(1);
}

#pragma optimize("", off)
// STUB: SADX 0x008adb00
static void execTgt(struct task *pTask)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x008adb80
void execTgt_waitPlayerTask(struct task *pTask)
{
	struct task *var1;
	var1 = GetPlayerTaskPointer(0);
	if (var1 != 0 && var1->twp != 0)
	{
		pTask->exec = execTgt;
	}
}
