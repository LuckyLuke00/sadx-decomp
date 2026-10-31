#include "decls.h"
extern struct NJS_POINT3 posRoundCenter;
static void execTgt(struct task *pTask);
extern struct obj object_e105_105_a_105_a;

// FUNCTION: SADX 0x008ac5c0
void destTgt(struct task *pTask)
{
	struct task **var1 = (struct task **)((char *)pTask->awp + 0xa0);
	int var2 = 8;
	do
	{
		if (var1[-1] != 0)
		{
			FreeTask(var1[-1]);
		}
		if (*var1 != 0)
		{
			FreeTask(*var1);
		}
		var1 = var1 + 0x12;
		var2 = var2 - 1;
	}
	while (var2 != 0);
}

// STUB: SADX 0x008ac600
int FUN_008ac600(void)
{
	return (int)0;
}

// STUB: SADX 0x008acb20
void callback_E105D(struct obj *obj)
{
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

// FUNCTION: SADX 0x008ace50
void execFlyingHead(struct task *pTask)
{
	struct anywk *var1 = pTask->awp;
	struct taskwk *var2 = pTask->twp;
	var1->work.ul[0]++;
	if ((long)var1->work.ul[0] >= 0xf0)
	{
		FreeTask(pTask);
	}
	var2->pos.x += var1->work.f[1];
	var2->pos.y += var1->work.f[2];
	var2->pos.z += var1->work.f[3];
	var1->work.f[2] -= 0.1f;
	var2->ang.x += var1->work.ul[4];
	var2->ang.z += var1->work.ul[6];
	dispFlyingHead(pTask);
}

// STUB: SADX 0x008adb00
static void execTgt(struct task *pTask)
{
}

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
