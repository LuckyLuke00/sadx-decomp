#include "decls.h"
extern int DAT_05b9d838;
extern struct obj *DAT_04a08338;

// FUNCTION: SADX 0x00893000
void hane_draw(struct task *task_p)
{
	struct taskwk *var1 = task_p->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	if (CheckRangeOut(task_p))
	{
		return;
	}
	SetObjectTexture();
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.y)
	{
		njRotateY(0, (Uint16)var1->ang.y);
	}
	FUN_0067d2d0(0, var1->scl.x, var1->scl.y, var1->scl.z);
	ds_DrawObjectClip(DAT_04a08338, FUN_00500c70(var1->scl.x, var1->scl.y, var1->scl.z));
	njPopMatrix(1);
}

// FUNCTION: SADX 0x008930c0
void hane_exec(struct task *task_p)
{
	struct taskwk *var1 = task_p->twp;
	if (FUN_004c39c0(task_p) != 0)
	{
		njPrintC(0x110010, "<- FAN SPEED(ANGLE)");
		if (var1->ang.x != 0)
		{
			var1->value.l = var1->ang.x;
		}
	}
	*(int *)((char *)var1 + 0x18) += var1->value.l;
	hane_draw(task_p);
	dsPlay_timer_v(0x3ed, (int)task_p, 1, 0, 2, var1->pos.x, var1->pos.y, var1->pos.z);
}

// FUNCTION: SADX 0x00893130
void ObjectFinalEggHane(struct task *task_p)
{
	struct taskwk *var1 = task_p->twp;
	var1->value.l = var1->ang.x ? var1->ang.x : 0xb6;
	var1->ang.x = 0;
	var1->scl.x = var1->scl.x < 0.01f ? 1.0f : var1->scl.x;
	var1->scl.y = var1->scl.y < 0.01f ? 1.0f : var1->scl.y;
	var1->scl.z = var1->scl.z < 0.01f ? 1.0f : var1->scl.z;
	task_p->exec = hane_exec;
	task_p->disp = hane_draw;
	task_p->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
}
