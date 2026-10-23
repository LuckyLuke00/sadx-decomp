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
		njRotateY(0, var1->ang.y);
	}
	FUN_0067d2d0(0, var1->scl.x, var1->scl.y, var1->scl.z);
	ds_DrawObjectClip(DAT_04a08338, FUN_00500c70(var1->scl.x, var1->scl.y, var1->scl.z));
	njPopMatrix(1);
}

// STUB: SADX 0x00893130
void ObjectFinalEggHane(struct task *task_p)
{
}
